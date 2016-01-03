using GLib;
using Gst;
using DBus;

class Service: Epris.Service {

	public DBus.Connection connection { construct set; get; }
	public MainLoop loop;
	public AudioPlayer player;
	public HashTable<string, TrackList> tracklists;
	public TrackList current_tracklist;
	public KeyFile config;
	public string config_file;
	public string data_dir;
	static int timeout_quit = 5;
	uint timeout_quit_id = 0;
	int rv;

	public Service (DBus.Connection connection) {
		this.connection = connection;

		rv = 0;
		loop = new MainLoop (null, false);
		player = new AudioPlayer ();
		player.about_to_finish.connect (audio_player_about_to_finish);
		tracklists = new HashTable<string, TrackList> (str_hash, str_equal);

		player.notify += (s, p) => {

			// STATE
			if (p.name == "state") {
#if FIXME
                try {
					Process.spawn_command_line_async ("notify-send -t 1000 State" + ((int)player.state).to_string () + " " + player.duration.to_string ());
					State = player.state == State.PLAYING ? State.PLAYING : State.STOPPED;
					idle = State.STOPPED;
				} catch (SpawnError error) {
				}
#endif

			}

			// TAGLIST
			else if (p.name == "taglist") {
				if (player.taglist == null)
					return;

				player.taglist.@foreach ( (tl, tag) => {
						var value = ((GLib.Value?)((Gst.Structure)tl).get_value (tag));
						debug ("%s %s", tag, value.strdup_contents ());

						if (Epris.type_is_glib_dbus (value.type ())) {
							var copy = GLib.Value (value.type ());
							value.copy (ref copy);
							current_tracklist._current.replace (tag, copy);
						} else {
							// current_tracklist.current.insert (tag, value.strdup_contents ()); <- mising g_value_dup
							var copy = GLib.Value (typeof (string));
							copy = value.strdup_contents ();
							current_tracklist._current.replace (tag, copy);
						}
					});
			}
		};

		config = new KeyFile ();

		data_dir = Path.build_filename (Environment.get_user_data_dir (), "epris");

		string[] s = { Environment.get_user_config_dir () };
		try {
			config.load_from_dirs ("epris", s,
								   out config_file,
								   KeyFileFlags.KEEP_COMMENTS | KeyFileFlags.KEEP_TRANSLATIONS);
		} catch (KeyFileError error) {
			warning ("%s (while loading config)", error.message);
		}

		if (config_file == null)
			config_file = Path.build_filename (Environment.get_user_config_dir (), "epris");
	}

	bool idle { set {
			message ("idle %s", value.to_string ());

			if (timeout_quit_id != 0 && value == false) {
				Source.remove (timeout_quit_id);
				timeout_quit_id = 0;
			}

			if (timeout_quit == -1)
				return;

			if (timeout_quit_id == 0 && value == true)
				timeout_quit_id = Timeout.add_seconds (timeout_quit, _quit_cb);
		}
	}

	public bool set_current_tracklist_by_name (string name) throws GLib.Error {

		current_tracklist = tracklists.lookup (name);

		if (current_tracklist == null) {
			current_tracklist = new TrackList (Path.build_filename (data_dir, "lists", name));
			current_tracklist.load ();
		}

		current_tracklist.notify += (s, p) => {
			// CURRENT TRACK
			if (p.name == "current-track") {
				if (current_tracklist.current_track == null)
					return;
				debug ("Current track changed %s", current_tracklist.current_track.uri);
				player.request_location (current_tracklist.current_track.uri, true);
			}
		};

		current_tracklist.update_current += () => {
			message ("update current position..");

			var d = GLib.Value (typeof (int64));

			d.set_int64 (player.duration);
			current_tracklist._current.replace ("x-duration", d);
			d.set_int64 (player.position);
			current_tracklist._current.replace ("x-position", d);
		};

		connection.register_object ("/org/mpris/epris/lists/current", current_tracklist);

		return true;
	}

	void audio_player_about_to_finish () {
		debug ("about-to-finish");
		try {
			var t = current_tracklist.seek (+1, Epris.Whence.CURRENT);
			if (t == null)
				return;
			player.request_location (t.uri, false);
		} catch (Epris.Error err) {
			message ("End of list, or list empty: %s", err.message);
		}
	}

	public override void Play () throws Epris.Error {
 		message ("let's pump up the speakers!");

		current_tracklist.seek (0, Epris.Whence.CURRENT);
		if (current_tracklist.current_track == null)
			return;

		player.request_state (Epris.State.PLAYING);
		State = Epris.State.PLAYING;
		idle = false;
	}

	public override void Seek (Epris.Format format, int64 position) throws Epris.Error {
 		message ("I like to move it, move it! " + ((int)format).to_string () + " " + position.to_string ());

		player.request_seek ((Gst.Format)format, position);
	}

	private bool _quit_cb () {
		message ("That was a pleasant time, take care");

		loop.quit ();

		return false;
	}

	public override void Stop () throws Epris.Error {
 		message ("Nothing strengthens authority so much as silence.");

		player.request_state (Epris.State.STOPPED);
		State = Epris.State.STOPPED;

		idle = true;
	}

	private bool register () {

		if (Epris.request_name (connection, "org.mpris.epris") == true) {
			connection.register_object ("/org/mpris/epris", this); // TODO: namespace object path

			return true;
		}

		return false;
	}

	public int run () {
		if (register () == false) {
			message ("Cannot request name, exiting");
			return 0;
		}

		try {
			var tl = config.get_string ("General", "tracklist");
			set_current_tracklist_by_name (tl);
		} catch (GLib.Error error) {
			var time = TimeVal ();
			var date = GLib.Date ();

			warning (error.message);

			time.get_current_time ();
			date.set_time_val (time);
			char[] s = new char[20];
			date.strftime (s, "%Y-%m-%d");
			try {
				set_current_tracklist_by_name ((string)s);
			} catch (GLib.Error e) {
				critical (e.message);
				rv = 1;
			}
		}

		loop.run ();

		player.request_state (Epris.State.STOPPED);

		return rv;
	}

	static bool opversion;
	const OptionEntry[] main_options = {
		{ "version", 0, 0, OptionArg.NONE, ref opversion, "Display version number", null },
		{ "debug-level", 0, 0, OptionArg.INT, ref Epris.debug_level, "Debug level (1-5)", "INT" },
		{ "idle", 'i', 0, OptionArg.INT, ref timeout_quit, "Exit when idle (-1 = no timeout)", "SECS" },
		{ null }
	};

	static int main (string[] args) {
		Service epris;

		Log.set_default_handler (Epris.log_handler);

		var opt_context = new OptionContext ("- Epris audio player service");
		opt_context.set_help_enabled (true);
		opt_context.add_main_entries (main_options, null);
		opt_context.add_group (Gst.init_get_option_group ());

		try {
			opt_context.parse (ref args);
		} catch (OptionError e) {
			stdout.printf ("%s\n", e.message);
			stdout.printf ("Run '%s --help' to see a full list of available command line options.\n", Environment.get_prgname ());
			return 1;
		}

		if (opversion) {
			stdout.printf ("Epris %s\n", Config.PACKAGE_VERSION);
			return 0;
		}

		epris = new Service (DBus.Bus.get (DBus.BusType.SESSION));

		message ("Using %s config file", epris.config_file);
		message ("And %s data dir", epris.data_dir);

		return epris.run ();
	}

}
