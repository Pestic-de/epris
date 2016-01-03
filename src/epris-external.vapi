using GLib;

[CCode (cprefix = "", lower_case_cprefix = "", cheader_filename = "config.h")]
namespace Config {
	public const string PACKAGE_VERSION;
	public const string LIBEXECDIR;
}

[CCode (cheader_filename = "epris-external.h")]
namespace Epris {
    [CCode (cname = "epris_debug_level")]
	public int debug_level; // Vala FIXME: not namespaced...
	[CCode (cname = "epris_log_handler")]
	public void log_handler (string? domain, LogLevelFlags flags, string message);
    [CCode (cname = "epris_uri_is_valid")]
	public bool uri_is_valid (string uri);
    [CCode (cname = "epris_value_to_pointer")]
    public void* value_to_pointer (owned Value? v);
    [CCode (cname = "epris_time_to_string")]
    public string time_to_string (int64 t);
}
