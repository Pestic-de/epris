using GLib;
using DBus;

class Epr: GLib.Object {

	static bool version;
	[CCode (array_length = false, array_null_terminated = true)]
	[NoArrayLength ()]
	static int rv;

	DBus.Connection conn;
	public MainLoop loop;
	Epris.Client client;
	dynamic DBus.Object current;

	construct {
		loop = new MainLoop (null, false);
	}

	public void initialize () throws GLib.Error, DBus.Error {
		client = new Epris.Client (conn);

		client.initialize ("epris");
	}

	private void play_reply (GLib.Error? e) {
		rv = 0;

		if (e != null) {
			stderr.printf ("%s\n", e.message);
			rv = 1;
		}

		loop.quit ();
	}

	public void play () throws GLib.Error {
		client.player.Play (play_reply);
	}

	private void stop_reply (GLib.Error e) {
		rv = 0;

		if (e != null) {
			stderr.printf ("%s\n", e.message);
			rv = 1;
		}

		loop.quit ();
	}

	public void stop () throws GLib.Error {
		client.player.Stop (stop_reply);
	}

	private void add_reply (GLib.Error e) {
		current.unref ();

		rv = 0;

		if (e != null) {
			stderr.printf ("%s\n", e.message);
			rv = 1;
		}

		loop.quit ();
	}

	public void add (string[] args, bool immediately = false) throws GLib.Error {
		current = client.get_tracklist ("current");
		current.ref (); // see vala todo list
		current.AddTracks (args, immediately, add_reply);
	}

	private void rm_reply (GLib.Error e) {
		current.unref ();

		rv = 0;

		if (e != null) {
			stderr.printf ("%s\n", e.message);
			rv = 1;
		}

		loop.quit ();
	}

	public void rm (string[] args, bool immediately = false) throws GLib.Error {
		current = client.get_tracklist ("current");
		current.ref ();
		current.DelTracks (args, immediately, rm_reply);
	}

	static Epr get_epr () throws GLib.Error, Epris.Error, DBus.Error {
		var epr = new Epr ();

		try {
			epr.conn = DBus.Bus.get (DBus.BusType. SESSION);
		} catch (GLib.Error foo) {
			error (foo.message);
			throw new Epris.Error.NONE (null);
		}

		epr.initialize ();

		return epr;
	}

	public void show () {
		var format = "%-15s %s\n";

		HashTable<string, Value?> current = client.get_tracklist ("current").current;
		stdout.printf ("%s", Epris.hsv_to_string (current, format, "x-"));

		Value state = client.get ("State");
		if ((int)state == Epris.State.PLAYING) {
			stdout.printf ("%s", format.printf ("state:", "Playing"));
		} else {
			stdout.printf ("%s", format.printf ("state:", "Stopped"));
		}

		stdout.printf ("%s", format.printf ("position:", "%s / %s".printf (
												Epris.time_to_string (current.lookup ("x-position").get_int64 ()),
												Epris.time_to_string (current.lookup ("x-duration").get_int64 ()))));
		loop.quit ();
	}

	static int parse_args (OptionContext opt_context, ref weak string[] args, bool help = true) {
		try {
			opt_context.parse (ref args);
		} catch (OptionError e) {
			if (help)
				stderr.printf ("%s\n", e.message);
			return 1;
		}

		return 0;
	}

	const OptionEntry[] play_options = {
		{ null }
	};
	int cmd_play (ref weak string[] args) throws GLib.Error {
		var opt_context = new OptionContext ("- Play current track");
		opt_context.add_main_entries (play_options, null);

		if ((rv = parse_args (opt_context, ref args)) != 0)
			return rv;

		play ();

		return 0;
	}

	int cmd_stop (ref weak string[] args) throws GLib.Error {
		stop ();

		return 0;
	}

	[CCode (array_length = false, array_null_terminated = true)]
	[NoArrayLength]
	static string[] locations;
	const OptionEntry[] add_options = {
		{ "", 0, 0, OptionArg.FILENAME_ARRAY, ref locations, null, "locations..." },
		{ null }
	};
	int cmd_add (ref weak string[] args) throws GLib.Error {
		var opt_context = new OptionContext ("- Add a list of locations to a track list");
		opt_context.add_main_entries (add_options, null);

		if ((rv = parse_args (opt_context, ref args)) != 0)
			return rv;

		int i = 0;
		foreach (var s in locations) {
			if (i >= 1) {
				var uri = locations[i];

				if (!Epris.uri_is_valid (uri)) {
					if (!Path.is_absolute (uri)) {
						uri = Path.build_filename (Environment.get_current_dir (), uri);
					}
					try {
						uri = Filename.to_uri (uri);
					} catch (ConvertError error) {
						warning (error.message);
						i += 2;
						continue;
					}
				}

				locations[i-1] = uri;
			}
			i++;
		}

		if (i <= 1)
			return 1;

		locations[i-1] = null;
		add (locations);

		return 0;
	}

	const OptionEntry[] rm_options = {
		{ "", 0, 0, OptionArg.FILENAME_ARRAY, ref locations, null, "locations..." },
		{ null }
	};
	int cmd_rm (ref weak string[] args) throws GLib.Error {
		var opt_context = new OptionContext ("- Remove matching locations from a track list");
		opt_context.add_main_entries (rm_options, null);

		if ((rv = parse_args (opt_context, ref args)) != 0)
			return rv;

		HashTable<string, Value?>[] tracks = client.get_tracklist ("current").ListTracks ();
		List<string> list = new List<string>();

		uint i = 0;
		foreach (var pat in locations) {
			i += 1;
			if (i <= 1)
				continue;
			foreach (var t in tracks) {
				if (PatternSpec.match_simple (pat, t.lookup ("uri").get_string ()) ||
					PatternSpec.match_simple (pat, Filename.from_uri (t.lookup ("uri").get_string ()))) {
					debug ("removing %s", t.lookup ("uri").get_string ());
					list.append (t.lookup ("uri").get_string ());
				}
			}
		}

		rm (Epris.strv_from_list (list));

		return 0;
	}

	HashTable<string, string> list_other_cmd () {
		var r = new HashTable<string, string> (str_hash, str_equal);
		try {
			var d = Dir.open (Config.LIBEXECDIR);
			for (;;) {
				var c = d.read_name ();
				if (c == null)
					break;
				if (!c.has_prefix("epr-"))
					continue;
				var n = Path.build_filename (Config.LIBEXECDIR, c);
				if (!FileUtils.test (n, FileTest.IS_EXECUTABLE))
					continue;
				c = c.substring (4);
				for (var i = c.length - 1; i > 0; i--)
					if (c[i] == '.') {
						((char *)c)[i] = '\0';
						break;
					}
				r.insert (c, n);
			}
		} catch (FileError fe) {
			warning (fe.message);
		}
		return r;
	}

	static bool help_all = false;
	const OptionEntry[] help_options = {
		{ "all", 'a', 0, 0, ref help_all, "Show extra commands", "BOOL" },
		{ null }
	};
	int cmd_help (ref weak string[] args, OptionContext opt_context) throws GLib.Error {
		opt_context.add_main_entries (help_options, null);

		parse_args (opt_context, ref args);

		stdout.printf (opt_context.get_help (false, null));
		if (help_all) {
			var cmds = list_other_cmd ();
			if (cmds.size () > 0) {
				stdout.printf ("Other commands:\n");
				foreach (var c in cmds.get_keys ())
					stdout.printf ("  " + c + "\n");
			}
		}

		return 0;
	}

	int cmd_show (ref weak string[] args) throws GLib.Error {
		if (client.updated == true)
			show ();
		else
			client.notify += (s, p) => {
				if (p.name == "updated") {
					show ();
				}
			};
		return 0;
	}

	static bool numbered = false;
	const OptionEntry[] list_options = {
		{ "number", 'n', 0, 0, ref numbered, "Number output", "BOOL" },
		{ null }
	};
	int cmd_list (ref weak string[] args) throws GLib.Error {
		var opt_context = new OptionContext ("- List tracks in current tracklist");
		opt_context.add_main_entries (list_options, null);

		if ((rv = parse_args (opt_context, ref args)) != 0)
			return rv;

		int i = 1;
		HashTable<string, Value?>[] tracks = client.get_tracklist ("current").ListTracks ();

		foreach (var t in tracks) {
			if (t.lookup ("current") != null && t.lookup ("current").get_boolean()) {
				stdout.printf ("* ");
			} else {
				stdout.printf ("  ");
			}

			if (numbered)
				stdout.printf ("%4d ", i);
			stdout.printf ("%s\n", Filename.from_uri (t.lookup ("uri").get_string ()));
			++i;
		}

		loop.quit ();

		return 0;
	}

	private void skip_reply (GLib.Error e) {
		rv = 0;

		debug ("skip_reply");
		if (e != null) {
			stderr.printf ("%s\n", e.message);
			rv = 1;
		}

		loop.quit ();
	}

	static int nskip = 1;
	const OptionEntry[] skip_options = {
		{ "nskip", 'n', 0, OptionArg.INT, ref nskip, "Skip N", "INT" },
		{ null }
	};
	int cmd_skip (ref weak string[] args) throws GLib.Error {
		var opt_context = new OptionContext ("- Skip to a different track");
		opt_context.add_main_entries (skip_options, null);

		if ((rv = parse_args (opt_context, ref args)) != 0)
			return rv;

		if (args.length == 3)
			nskip = args[2].to_int ();

		debug ("Skip %d track(s)", nskip);

		// FIXME, current is unref: client.get_tracklist ("current").Seek (nskip, Epris.Whence.CURRENT, skip_reply);
		var c = client.get_tracklist ("current");
		c.Seek (nskip, Epris.Whence.CURRENT, skip_reply);
		c.ref ();
		return 0;
	}

	static string[] seek_position = null;
	const OptionEntry[] seek_options = {
		{ "", 0, 0, OptionArg.STRING_ARRAY, ref seek_position, null, "POSITION" },
		{ null }
	};
	int cmd_seek (ref weak string[] args) throws GLib.Error {
		var opt_context = new OptionContext ("- Seek to a given position");
		opt_context.add_main_entries (seek_options, null);

		if ((rv = parse_args (opt_context, ref args)) != 0)
			return rv;

		if (seek_position == null || seek_position[0] != "seek" || seek_position[1] == null) {
			stderr.printf ("Command 'seek' need a position argument. Ex: seek 40%%\n");
			return 1;
		}

		debug ("Seek to %s.", seek_position[1]);

		if (seek_position[1].has_suffix("%")) {
			int64 percent;
			seek_position[1].canon("0123456789", ' ');
			percent = seek_position[1].to_int64();
			client.player.Seek (Epris.Format.PERCENT, percent);
		}

		return 0;
	}

	const OptionEntry[] main_options = {
		{ "version", 0, 0, OptionArg.NONE, ref version, "Display version number", null },
		{ "debug-level", 0, 0, OptionArg.INT, ref Epris.debug_level, "Debug level (1-5)", "INT" },
		{ null }
	};
	static int main (string[] args) {
		Log.set_default_handler (Epris.log_handler);

		Epris.debug_level = 2;
		var opt_context = new OptionContext ("""- Manage Epris audio player

Available commands:

  play     Play
  stop     Stop
  add      Add tracks to tracklist
  rm       Remove tracks from tracklist
  seek     Seek to a given position within track
  skip     Move within the tracklist (alias skip)
  list     List tracks
  help     Display this help""");
		opt_context.add_main_entries (main_options, null);

		try {
			opt_context.set_help_enabled (false);
			parse_args (opt_context, ref args, false);
			opt_context.set_help_enabled (true);

			if (version) {
				stdout.printf ("Epr %s\n", Config.PACKAGE_VERSION);
				return 0;
			}

			Epr epr;
			try {
				epr = get_epr ();
			} catch (GLib.Error e) {
				warning (e.message);
				return 1;
			}

			switch (args[1]) {
			case "play":
				epr.cmd_play (ref args);
				break;
			case "stop":
				epr.cmd_stop (ref args);
				break;
			case "add":
				int status;
				status = epr.cmd_add (ref args);
				if (status != 0)
					return status;
				break;
			case "rm":
				epr.cmd_rm (ref args);
				break;
			case "show":
				epr.cmd_show (ref args);
				break;
			case "list":
				return epr.cmd_list (ref args);
			case "skip":
				epr.cmd_skip (ref args);
				break;
			case "seek":
				return epr.cmd_seek (ref args);
			case null:
			case "--help":
			case "help":
				return epr.cmd_help (ref args, opt_context);
			default:
				var cmds = epr.list_other_cmd ();
				var c = cmds.lookup (args[1]);
				if (c != null) {
					string output = null, error = null;
					int status = 0;
					Process.spawn_command_line_sync (c + " " + string.joinv (" ", args), out output, out error, out status);
					stdout.printf (output);
					stderr.printf (error);
					return status;
				} else
					stderr.printf ("Unknown command: %s\n", args[1]);

				stdout.printf ("Run '%s --help' to see a full list of available command line options.\n", Environment.get_prgname ());
				return 1;
			}

			epr.loop.run ();

			return rv;
		} catch (Epris.Error err) {
			//if (err == Epris.Error.NONE) FIXME
			return 0;
		}
	}

}
