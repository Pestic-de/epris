using GLib;
using Posix;

namespace Epris {
	public class Storage: Object {

		public string dirname { get; set; }

		public Storage (string dirname) {
			this.dirname = dirname;
		}

		private string get_path_for_string (string key) {
			var sha1 = Checksum.compute_for_string (ChecksumType.SHA1, key, -1);
			return Path.build_filename (dirname, sha1.substring (0, 2), sha1.substring (2));
		}

		public bool write (string key, void* buf, out size_t count) {
			var path = get_path_for_string (key);
			DirUtils.create_with_parents (Path.get_dirname (path), 0700);

			var file = FileStream.open (path, "w");
			var c = Posix.write (file.fileno (), buf, count);
			var result = (c == count);
			count = c;

			return result;
		}

		public bool read (string key, void* buf, out size_t count) {
			var path = get_path_for_string (key);

			var file = FileStream.open (path, "r");
			var c = Posix.read (file.fileno (), buf, count);
			var result = (c == count);
			count = c;

			return result;
		}
	}

#if TEST
	public static void main () {
		var tmp = Path.build_filename (Environment.get_tmp_dir (), "test-storage");
		try {
			var s = new Storage (tmp);
			var b = new uchar[1000];

			var count = 1000;
			s.write ("This is a test key", (void*)b, out count);

			var c = new uchar[1000];
			count = 1000;
			s.read ("This is a test key", (void*)c, out count);

		} finally {
			debug ("should clean up " + tmp);
		}
	}
#endif
}
