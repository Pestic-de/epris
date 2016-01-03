using GLib;

public class TrackList: Epris.TrackList {

	public class Track { // Let's try to keep this struct light.
		public string uri;

		public Track (string uri) {
			this.uri = uri;
		}

		public HashTable<string, Value?> get_hsv () {
			Value? v = Value (typeof (string));
			v.set_string (uri);
			var res = new HashTable<string, Value?> (str_hash, str_equal);
			res.insert ("uri", (owned) v);
			return res;
		}
	}

	public Track? current_track { get; private set; }
	public string? name { get; set; }
	public string path { get; set; }

	public List<Track> tracklist;

	uint _position;
	public uint position { get { return _position; } set {
			_position = value;
			if (tracklist.nth_data (value) != null)
				current = ((Track)tracklist.nth_data (value)).get_hsv ();
			save (false, true);
		}
	}

	public TrackList (string path) {
		this.path = path;

		if (DirUtils.create_with_parents (Path.get_dirname (path), 0700) != 0) {
			warning ("Failed to create %s", Path.get_dirname (path));
		}

		current_track = null;
	}

	private bool add (string uri) throws GLib.Error {
		uri.strip ();
		if (uri == "")
			return false;

		if (Gst.uri_is_valid (uri) == false)
			warning ("Uri is not valid: %s", uri);

		var track = new Track (uri);

		if (tracklist.find_custom (track, (CompareFunc)_track_cmp_uri) == null)
			tracklist.insert (track, -1);

		return true;
	}

	static int _track_cmp_uri (Track a, Track b) {
		return strcmp (a.uri, b.uri);
	}

	public override void AddTracks (string[] uris, bool immediately) throws Epris.Error {
		foreach (var uri in uris) {
			try {
				add (uri);
			} catch (GLib.Error error) {
				warning (error.message);
			}
		}

		save (true, false);
	}

	private bool rm (string uri) throws GLib.Error {
		var track = new Track (uri);

		weak List<Track> link = tracklist.find_custom (track, (CompareFunc)_track_cmp_uri);
		if (link != null) {
			tracklist.remove_link (link);
			return true;
		}

		debug ("track %s not found", uri);

		return false;
	}

	public override void DelTracks (string[] uris, bool immediately) throws Epris.Error {
		foreach (var uri in uris) {
			try {
				rm (uri);
			} catch (GLib.Error error) {
				warning (error.message);
			}
		}

		save (true, true);
	}

	public override HashTable<string, Value?>[] ListTracks () throws Epris.Error {
		var len = (int)tracklist.length ();
		debug ("listtracks len: %d", len);
		HashTable<string, Value?>[] list = new HashTable<string, Value?>[len];

		uint i = 0;
		foreach (var t in tracklist) {
			list[i] = t.get_hsv ();
			if (position == i) {
				var vb = Value (typeof (bool));
				vb.set_boolean(true);
				list[i].insert ("current", vb);
			}
			i += 1;
		}

		return list;
	}

	public bool save (bool save_list = true, bool save_keyfile = true) {
		bool success = true;

		if (save_list) {
			message ("Saving tracklist at %s", path);
			var f = FileStream.open (path, "w+");
			if (f == null) {
				//throw new FileError.INVAL (strerror (errno));
			}
			foreach (var track in tracklist) {
				f.puts (track.uri);
				f.putc ('\n');
			}
			f.flush ();
		}

		if (save_keyfile) {
			KeyFile keyfile = new KeyFile ();
			keyfile.set_integer ("List", "position", (int)position);

			success = Epris.keyfile_save (keyfile, path + ".ini");
		}

		return success;
	}

	public bool load () {
		message ("Opening tracklist at %s", path);

		try {
			var f = FileStream.open (path, "r");
			if (f == null) {
				throw new FileError.INVAL (strerror (errno));
			}

			char[] c = new char[4096];
			var s = f.gets (c);
			while (s != null) {
				add (s);
				s = f.gets (c);
			}
		} catch (GLib.Error error) {
			warning (error.message);
		}

		KeyFile keyfile = new KeyFile ();

		try {
			keyfile.load_from_file (path + ".ini", KeyFileFlags.KEEP_COMMENTS | KeyFileFlags.KEEP_TRANSLATIONS);
		} catch (KeyFileError error) {
// 			if (error.code != KeyFileError.NOT_FOUND)
			warning ("%s (while loading playlist)", error.message);
		} catch (GLib.Error error) {
			warning ("%s (while loading playlist)", error.message);
		}

		try {
			position = 0;
			position = keyfile.get_integer ("List", "position");
		} catch (GLib.Error error) {
			warning (error.message);
		}

		return true;
	}

 	public Track? seek (int offset, Epris.Whence whence) throws Epris.Error {
		if (tracklist.length () <= 0) {
			position = 0;
			current_track = null;
			throw new Epris.Error.STATE ("Cannot seek: empty playlist");
		}

		switch (whence) {
		case Epris.Whence.CURRENT:
			position = (position + offset) % tracklist.length ();
			break;
		case Epris.Whence.START:
			position = offset % tracklist.length ();
			break;
		case Epris.Whence.END:
			position = (tracklist.length () + offset) % tracklist.length ();
			break;
		default:
			throw new Epris.Error.ARGUMENT ("Invalid whence type");
		}

		var t = tracklist.nth_data (position);

		current_track = t;

		return t;
 	}

	public override void Seek (int offset, Epris.Whence whence) throws Epris.Error {
		this.seek (offset, whence);
	}

}
