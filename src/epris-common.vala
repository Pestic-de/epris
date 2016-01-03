using GLib;
using DBus;

namespace Epris {
    public errordomain Error {
        NONE,
        NOT_SUPPORTED,
        STATE,
        ARGUMENT
    }

    public class Pair<T1,T2> {
        public T1 first;
        public T2 second;

        public Pair (owned T1 first, owned T2 second) {
            this.first = (owned) first;
            this.second = (owned) second;
        }
    }

    public string[] strv_from_list (GLib.List<string>? list)
    {
        string[] rv = new string[list.length () + 1];
        uint i = 0;

        foreach (var s in list) {
            rv[i] = s;
            ++i;
        }

        return rv;
    }

    public bool bool_from_string (string? str) {
        if (str == null)
            return false;

        if (str == "true" || str == "yes" || str == "1")
            return true;

        return false;
    }

    public bool keyfile_save (KeyFile key_file, string file_path) {
        var file = FileStream.open (file_path, "w");

        try {
            var data = key_file.to_data (null);
            file.puts (data);
            // file = null;
        } catch (KeyFileError error) {
            warning (error.message);
            return false;
        }

        return true;
    }

	public bool type_is_glib_dbus (Type t) {
		return (t == typeof (string) || t == typeof (int) || t == typeof (uint) || t == typeof (bool));
	}

	static string hsv_to_string_rv = null; // get closure...
	static string hsv_to_string_format = null; // get closure...
	static string hsv_to_string_exclude = null; // get closure...
	public string hsv_to_string (HashTable<string, Value?> hsv, string format = "%-15s %s\n", string exclude_prefix = "x-") {
		hsv_to_string_rv = "";
		hsv_to_string_format = format;
		hsv_to_string_exclude = exclude_prefix;
		hsv.for_each ( (s, v) => {
				if (s == null || v == null)
					return;
				if (((string)s).has_prefix (hsv_to_string_exclude))
					return;
				hsv_to_string_rv += hsv_to_string_format.printf ((string)s + ":", ((Value?)v).strdup_contents ());
			});

		return hsv_to_string_rv;
	}
}
