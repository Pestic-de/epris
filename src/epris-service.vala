using GLib;
using DBus;

namespace Epris {

	public bool request_name (DBus.Connection conn, string name) {
		try {
			dynamic DBus.Object bus = conn.get_object (
				"org.freedesktop.DBus", "/org/freedesktop/DBus", "org.freedesktop.DBus");

			uint request_name_result = bus.request_name (name, (uint) 0);
			if (request_name_result != RequestNameReply.PRIMARY_OWNER)
				return false;

			return true;
		} catch (GLib.Error foo) {
			error (foo.message);
			return false;
		}
	}

	public enum State {
		STOPPED,
		PAUSED,
		PLAYING
	}

	public enum Whence {
		START,
		CURRENT,
		END
	}

	public enum Format {
		UNDEFINED,
		DEFAULT,
		BYTES,
		TIME,
		BUFFERS,
		PERCENT
	}

	[DBus (name = "org.freedesktop.DBus.Properties")]
	public class PropertiesNotify : GLib.Object {
		// Grr. s/Changed/Notify
		public signal void Changed (string interface_name, string property_name, Value value);
	}

	[DBus (name = "org.mpris.EprisPlayer")]
	public abstract class Service : PropertiesNotify {

		public string Identity { get; set; }

		// FIXME: This is a lazy attempt at doing notification...
		private State _state;
		public State State { get { return _state; }
			set {
				var v = Value (typeof (State));
				_state = value;
				v.set_enum (_state);
				Changed ("org.mpris.EprisPlayer", "state", v);
			}
		}

		construct {
			Identity = "epris service " + Config.PACKAGE_VERSION;
		}

		public virtual void Play () throws Epris.Error {
			throw new Epris.Error.NOT_SUPPORTED ("Play(): this function is not yet implemented");
		}

		public virtual void Stop () throws Epris.Error {
			throw new Epris.Error.NOT_SUPPORTED ("Stop(): this function is not yet implemented");
		}

		public virtual void Seek (Format format, int64 position) throws Epris.Error {
			throw new Epris.Error.NOT_SUPPORTED ("Seek(): this function is not yet implemented");
		}
	}

	public abstract class TrackListTrick : PropertiesNotify {
		private signal void update_current ();

		public HashTable<string, Value?> _current;
	}

	[DBus (name = "org.mpris.EprisTrackList")]
	public abstract class TrackList : TrackListTrick {

		public HashTable<string, Value?> current { get { update_current (); return _current; }
			set {
				_current = value;
				Changed ("org.mpris.EprisTrackList", "current", _current);
			}
		}

		public virtual void AddTracks (string[] uris, bool immediately) throws Epris.Error {
			throw new Epris.Error.NOT_SUPPORTED ("AddTracks(): this function is not yet implemented");
		}

		public virtual void DelTracks (string[] uris, bool immediately) throws Epris.Error {
			throw new Epris.Error.NOT_SUPPORTED ("DelTracks(): this function is not yet implemented");
		}

		public virtual HashTable<string, Value?>[] ListTracks () throws Epris.Error {
			throw new Epris.Error.NOT_SUPPORTED ("ListTracks(): this function is not yet implemented");
		}

		public virtual void Seek (int offset, Whence whence) throws Epris.Error {
			throw new Epris.Error.NOT_SUPPORTED ("Seek(): this function is not yet implemented");
		}
	}

}
