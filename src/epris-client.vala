using GLib;
using DBus;

namespace Epris {

	public class DBusProxy : Epris.Structure {
		public DBus.Connection conn { get; construct set; }
		public dynamic DBus.Object iself;
		public dynamic DBus.Object iprop;
		public bool updated { get; set; }

		public DBusProxy (DBus.Connection connection) {
			this.conn = connection;
			this.updated = false;
		}

		public void initialize (string name, string path, string @interface) throws DBus.Error, GLib.Error {
			this.name = path;
			this.iself = conn.get_object (name, path, @interface);
			this.iprop = conn.get_object (name, path, "org.freedesktop.DBus.Properties");
			this.iprop.GetAll (@interface, _get_all_reply);
		}

		private void _get_all_reply (HashTable<string, Value?> props, GLib.Error? err) {
			if (err != null) {
				warning (err.message);
				return;
			}

			foreach (var key in props.get_keys ()) {
				Value? v = props.lookup (key);
				message ("key " + key + " " + v.strdup_contents ());
				set (key, v);
			}

			props.steal_all ();
			message (this.to_string ());

			updated = true;
		}
	}

	public class Client : DBusProxy {

		public dynamic DBus.Object player { get { return iself; } }

		public Client (DBus.Connection connection) {
			this.conn = connection;
		}

		public dynamic DBus.Object get_tracklist (string listname) {
			var list = conn.get_object (iself.get_bus_name (),
										iself.get_path () + "/lists/" + listname,
										"org.mpris.EprisTrackList");
			return list;
		}

		public new void initialize (string name) throws DBus.Error, GLib.Error {
			base.initialize ("org.mpris." + name, "/org/mpris/" + name, "org.mpris.EprisPlayer");
		}
	}
}
