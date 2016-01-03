
extern gint	epris_debug_level;
gboolean        epris_uri_is_valid    (const gchar   *uri);
void            epris_log_handler     (const char    *log_domain, GLogLevelFlags log_level,
                                       const char    *message/* , void             *user_data */);
