
#include <glib.h>
#include <glib-object.h>
#include <dbus/dbus-glib-lowlevel.h>
#include <dbus/dbus-glib.h>
#include <epris-external.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <config.h>
#include <glib/gstdio.h>


#define TYPE_EPR (epr_get_type ())
#define EPR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_EPR, Epr))
#define EPR_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_EPR, EprClass))
#define IS_EPR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_EPR))
#define IS_EPR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_EPR))
#define EPR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_EPR, EprClass))

typedef struct _Epr Epr;
typedef struct _EprClass EprClass;
typedef struct _EprPrivate EprPrivate;

#define EPRIS_TYPE_STRUCTURE (epris_structure_get_type ())
#define EPRIS_STRUCTURE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), EPRIS_TYPE_STRUCTURE, EprisStructure))
#define EPRIS_STRUCTURE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), EPRIS_TYPE_STRUCTURE, EprisStructureClass))
#define EPRIS_IS_STRUCTURE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), EPRIS_TYPE_STRUCTURE))
#define EPRIS_IS_STRUCTURE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), EPRIS_TYPE_STRUCTURE))
#define EPRIS_STRUCTURE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), EPRIS_TYPE_STRUCTURE, EprisStructureClass))

typedef struct _EprisStructure EprisStructure;
typedef struct _EprisStructureClass EprisStructureClass;

#define EPRIS_TYPE_DBUS_PROXY (epris_dbus_proxy_get_type ())
#define EPRIS_DBUS_PROXY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), EPRIS_TYPE_DBUS_PROXY, EprisDBusProxy))
#define EPRIS_DBUS_PROXY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), EPRIS_TYPE_DBUS_PROXY, EprisDBusProxyClass))
#define EPRIS_IS_DBUS_PROXY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), EPRIS_TYPE_DBUS_PROXY))
#define EPRIS_IS_DBUS_PROXY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), EPRIS_TYPE_DBUS_PROXY))
#define EPRIS_DBUS_PROXY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), EPRIS_TYPE_DBUS_PROXY, EprisDBusProxyClass))

typedef struct _EprisDBusProxy EprisDBusProxy;
typedef struct _EprisDBusProxyClass EprisDBusProxyClass;

#define EPRIS_TYPE_CLIENT (epris_client_get_type ())
#define EPRIS_CLIENT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), EPRIS_TYPE_CLIENT, EprisClient))
#define EPRIS_CLIENT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), EPRIS_TYPE_CLIENT, EprisClientClass))
#define EPRIS_IS_CLIENT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), EPRIS_TYPE_CLIENT))
#define EPRIS_IS_CLIENT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), EPRIS_TYPE_CLIENT))
#define EPRIS_CLIENT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), EPRIS_TYPE_CLIENT, EprisClientClass))

typedef struct _EprisClient EprisClient;
typedef struct _EprisClientClass EprisClientClass;

#define EPRIS_TYPE_STATE (epris_state_get_type ())

#define EPRIS_TYPE_WHENCE (epris_whence_get_type ())

#define EPRIS_TYPE_FORMAT (epris_format_get_type ())

struct _Epr {
	GObject parent_instance;
	EprPrivate * priv;
	GMainLoop* loop;
};

struct _EprClass {
	GObjectClass parent_class;
};

struct _EprPrivate {
	DBusGConnection* conn;
	EprisClient* client;
	DBusGProxy* current;
};

typedef enum  {
	EPRIS_ERROR_NONE,
	EPRIS_ERROR_NOT_SUPPORTED,
	EPRIS_ERROR_STATE,
	EPRIS_ERROR_ARGUMENT
} EprisError;
#define EPRIS_ERROR epris_error_quark ()
typedef enum  {
	EPRIS_STATE_STOPPED,
	EPRIS_STATE_PAUSED,
	EPRIS_STATE_PLAYING
} EprisState;

typedef enum  {
	EPRIS_WHENCE_START,
	EPRIS_WHENCE_CURRENT,
	EPRIS_WHENCE_END
} EprisWhence;

typedef enum  {
	EPRIS_FORMAT_UNDEFINED,
	EPRIS_FORMAT_DEFAULT,
	EPRIS_FORMAT_BYTES,
	EPRIS_FORMAT_TIME,
	EPRIS_FORMAT_BUFFERS,
	EPRIS_FORMAT_PERCENT
} EprisFormat;



GType epr_get_type (void);
GType epris_structure_get_type (void);
GType epris_dbus_proxy_get_type (void);
GType epris_client_get_type (void);
#define EPR_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_EPR, EprPrivate))
enum  {
	EPR_DUMMY_PROPERTY
};
static gboolean epr_version;
static gboolean epr_version = FALSE;
static gint epr_rv;
static gint epr_rv = 0;
static char** epr_locations;
static char** epr_locations = NULL;
static gboolean epr_help_all;
static gboolean epr_help_all = FALSE;
static gboolean epr_numbered;
static gboolean epr_numbered = FALSE;
static gint epr_nskip;
static gint epr_nskip = 1;
static char** epr_seek_position;
static gint epr_seek_position_length1;
static char** epr_seek_position = NULL;
static gint epr_seek_position_length1 = 0;
static gint epr_seek_position_size = 0;
EprisClient* epris_client_new (DBusGConnection* connection);
EprisClient* epris_client_construct (GType object_type, DBusGConnection* connection);
void epris_client_initialize (EprisClient* self, const char* name, GError** error);
void epr_initialize (Epr* self, GError** error);
static void epr_play_reply (Epr* self, GError* e);
DBusGProxy* epris_client_get_player (EprisClient* self);
void _dynamic_Play0 (DBusGProxy* self, gpointer param1, void* param1_target, GError** error);
void epr_play (Epr* self, GError** error);
static void epr_stop_reply (Epr* self, GError* e);
void _dynamic_Stop1 (DBusGProxy* self, gpointer param1, void* param1_target, GError** error);
void epr_stop (Epr* self, GError** error);
static void epr_add_reply (Epr* self, GError* e);
DBusGProxy* epris_client_get_tracklist (EprisClient* self, const char* listname);
void _dynamic_AddTracks2 (DBusGProxy* self, char** param1, int param1_length1, gboolean param2, gpointer param3, void* param3_target, GError** error);
void epr_add (Epr* self, char** args, int args_length1, gboolean immediately, GError** error);
static void epr_rm_reply (Epr* self, GError* e);
void _dynamic_DelTracks3 (DBusGProxy* self, char** param1, int param1_length1, gboolean param2, gpointer param3, void* param3_target, GError** error);
void epr_rm (Epr* self, char** args, int args_length1, gboolean immediately, GError** error);
Epr* epr_new (void);
Epr* epr_construct (GType object_type);
GQuark epris_error_quark (void);
static Epr* epr_get_epr (GError** error);
static inline GHashTable* _dynamic_get_current0 (DBusGProxy* obj);
char* epris_hsv_to_string (GHashTable* hsv, const char* format, const char* exclude_prefix);
GValue* epris_structure_get (EprisStructure* self, const char* field_name);
GType epris_state_get_type (void);
void epr_show (Epr* self);
static gint epr_parse_args (GOptionContext* opt_context, char*** args, int* args_length1, gboolean help);
static gint epr_cmd_play (Epr* self, char*** args, int* args_length1, GError** error);
static gint epr_cmd_stop (Epr* self, char*** args, int* args_length1, GError** error);
static gint epr_cmd_add (Epr* self, char*** args, int* args_length1, GError** error);
GHashTable** _dynamic_ListTracks4 (DBusGProxy* self, int* result_length1, GError** error);
static void _g_list_free_g_free (GList* self);
char** epris_strv_from_list (GList* list, int* result_length1);
static gint epr_cmd_rm (Epr* self, char*** args, int* args_length1, GError** error);
static GHashTable* epr_list_other_cmd (Epr* self);
static gint epr_cmd_help (Epr* self, char*** args, int* args_length1, GOptionContext* opt_context, GError** error);
gboolean epris_dbus_proxy_get_updated (EprisDBusProxy* self);
static void _lambda2_ (EprisClient* s, GParamSpec* p, Epr* self);
static void __lambda2__g_object_notify (EprisClient* _sender, GParamSpec* pspec, gpointer self);
static gint epr_cmd_show (Epr* self, char*** args, int* args_length1, GError** error);
GHashTable** _dynamic_ListTracks5 (DBusGProxy* self, int* result_length1, GError** error);
static gint epr_cmd_list (Epr* self, char*** args, int* args_length1, GError** error);
static void epr_skip_reply (Epr* self, GError* e);
GType epris_whence_get_type (void);
void _dynamic_Seek6 (DBusGProxy* self, gint param1, EprisWhence param2, gpointer param3, void* param3_target, GError** error);
static gint epr_cmd_skip (Epr* self, char*** args, int* args_length1, GError** error);
GType epris_format_get_type (void);
void _dynamic_Seek7 (DBusGProxy* self, EprisFormat param1, gint64 param2, GError** error);
static gint epr_cmd_seek (Epr* self, char*** args, int* args_length1, GError** error);
static void _epris_log_handler_glog_func (const char* log_domain, GLogLevelFlags log_levels, const char* message, gpointer self);
static gint epr_main (char** args, int args_length1);
Epr* epr_new (void);
static GObject * epr_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static gpointer epr_parent_class = NULL;
static void epr_finalize (GObject* obj);
static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);
static gint _vala_array_length (gpointer array);
static int _vala_strcmp0 (const char * str1, const char * str2);

static const GOptionEntry EPR_play_options[] = {{NULL}};
static const GOptionEntry EPR_add_options[] = {{"", (gchar) 0, 0, G_OPTION_ARG_FILENAME_ARRAY, &epr_locations, NULL, "locations..."}, {NULL}};
static const GOptionEntry EPR_rm_options[] = {{"", (gchar) 0, 0, G_OPTION_ARG_FILENAME_ARRAY, &epr_locations, NULL, "locations..."}, {NULL}};
static const GOptionEntry EPR_help_options[] = {{"all", 'a', 0, 0, &epr_help_all, "Show extra commands", "BOOL"}, {NULL}};
static const GOptionEntry EPR_list_options[] = {{"number", 'n', 0, 0, &epr_numbered, "Number output", "BOOL"}, {NULL}};
static const GOptionEntry EPR_skip_options[] = {{"nskip", 'n', 0, G_OPTION_ARG_INT, &epr_nskip, "Skip N", "INT"}, {NULL}};
static const GOptionEntry EPR_seek_options[] = {{"", (gchar) 0, 0, G_OPTION_ARG_STRING_ARRAY, &epr_seek_position, NULL, "POSITION"}, {NULL}};
static const GOptionEntry EPR_main_options[] = {{"version", (gchar) 0, 0, G_OPTION_ARG_NONE, &epr_version, "Display version number", NULL}, {"debug-level", (gchar) 0, 0, G_OPTION_ARG_INT, &epris_debug_level, "Debug level (1-5)", "INT"}, {NULL}};


void epr_initialize (Epr* self, GError** error) {
	GError * _inner_error_;
	EprisClient* _tmp0_;
	g_return_if_fail (self != NULL);
	_inner_error_ = NULL;
	_tmp0_ = NULL;
	self->priv->client = (_tmp0_ = epris_client_new (self->priv->conn), (self->priv->client == NULL) ? NULL : (self->priv->client = (g_object_unref (self->priv->client), NULL)), _tmp0_);
	epris_client_initialize (self->priv->client, "epris", &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
}


static void epr_play_reply (Epr* self, GError* e) {
	g_return_if_fail (self != NULL);
	epr_rv = 0;
	if (e != NULL) {
		fprintf (stderr, "%s\n", e->message);
		epr_rv = 1;
	}
	g_main_loop_quit (self->loop);
}


static void _epr_play_reply_cb (DBusGProxy* proxy, DBusGProxyCall* call, void* user_data) {
	GError* error;
	error = NULL;
	dbus_g_proxy_end_call (proxy, call, &error, G_TYPE_INVALID);
	epr_play_reply (user_data, error);
}


void _dynamic_Play0 (DBusGProxy* self, gpointer param1, void* param1_target, GError** error) {
	dbus_g_proxy_begin_call (self, "Play", _epr_play_reply_cb, param1_target, NULL, G_TYPE_INVALID, G_TYPE_INVALID);
	if (*error) {
		return;
	}
}


void epr_play (Epr* self, GError** error) {
	GError * _inner_error_;
	g_return_if_fail (self != NULL);
	_inner_error_ = NULL;
	_dynamic_Play0 (epris_client_get_player (self->priv->client), epr_play_reply, self, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
}


static void epr_stop_reply (Epr* self, GError* e) {
	g_return_if_fail (self != NULL);
	epr_rv = 0;
	if (e != NULL) {
		fprintf (stderr, "%s\n", e->message);
		epr_rv = 1;
	}
	g_main_loop_quit (self->loop);
}


static void _epr_stop_reply_cb (DBusGProxy* proxy, DBusGProxyCall* call, void* user_data) {
	GError* error;
	error = NULL;
	dbus_g_proxy_end_call (proxy, call, &error, G_TYPE_INVALID);
	epr_stop_reply (user_data, error);
}


void _dynamic_Stop1 (DBusGProxy* self, gpointer param1, void* param1_target, GError** error) {
	dbus_g_proxy_begin_call (self, "Stop", _epr_stop_reply_cb, param1_target, NULL, G_TYPE_INVALID, G_TYPE_INVALID);
	if (*error) {
		return;
	}
}


void epr_stop (Epr* self, GError** error) {
	GError * _inner_error_;
	g_return_if_fail (self != NULL);
	_inner_error_ = NULL;
	_dynamic_Stop1 (epris_client_get_player (self->priv->client), epr_stop_reply, self, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
}


static void epr_add_reply (Epr* self, GError* e) {
	g_return_if_fail (self != NULL);
	g_object_unref ((GObject*) self->priv->current);
	epr_rv = 0;
	if (e != NULL) {
		fprintf (stderr, "%s\n", e->message);
		epr_rv = 1;
	}
	g_main_loop_quit (self->loop);
}


static void _epr_add_reply_cb (DBusGProxy* proxy, DBusGProxyCall* call, void* user_data) {
	GError* error;
	error = NULL;
	dbus_g_proxy_end_call (proxy, call, &error, G_TYPE_INVALID);
	epr_add_reply (user_data, error);
}


void _dynamic_AddTracks2 (DBusGProxy* self, char** param1, int param1_length1, gboolean param2, gpointer param3, void* param3_target, GError** error) {
	dbus_g_proxy_begin_call (self, "AddTracks", _epr_add_reply_cb, param3_target, NULL, G_TYPE_STRV, param1, G_TYPE_BOOLEAN, param2, G_TYPE_INVALID, G_TYPE_INVALID);
	if (*error) {
		return;
	}
}


void epr_add (Epr* self, char** args, int args_length1, gboolean immediately, GError** error) {
	GError * _inner_error_;
	DBusGProxy* _tmp0_;
	g_return_if_fail (self != NULL);
	_inner_error_ = NULL;
	_tmp0_ = NULL;
	self->priv->current = (_tmp0_ = epris_client_get_tracklist (self->priv->client, "current"), (self->priv->current == NULL) ? NULL : (self->priv->current = (g_object_unref (self->priv->current), NULL)), _tmp0_);
	g_object_ref ((GObject*) self->priv->current);
	/* see vala todo list*/
	_dynamic_AddTracks2 (self->priv->current, args, args_length1, immediately, epr_add_reply, self, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
}


static void epr_rm_reply (Epr* self, GError* e) {
	g_return_if_fail (self != NULL);
	g_object_unref ((GObject*) self->priv->current);
	epr_rv = 0;
	if (e != NULL) {
		fprintf (stderr, "%s\n", e->message);
		epr_rv = 1;
	}
	g_main_loop_quit (self->loop);
}


static void _epr_rm_reply_cb (DBusGProxy* proxy, DBusGProxyCall* call, void* user_data) {
	GError* error;
	error = NULL;
	dbus_g_proxy_end_call (proxy, call, &error, G_TYPE_INVALID);
	epr_rm_reply (user_data, error);
}


void _dynamic_DelTracks3 (DBusGProxy* self, char** param1, int param1_length1, gboolean param2, gpointer param3, void* param3_target, GError** error) {
	dbus_g_proxy_begin_call (self, "DelTracks", _epr_rm_reply_cb, param3_target, NULL, G_TYPE_STRV, param1, G_TYPE_BOOLEAN, param2, G_TYPE_INVALID, G_TYPE_INVALID);
	if (*error) {
		return;
	}
}


void epr_rm (Epr* self, char** args, int args_length1, gboolean immediately, GError** error) {
	GError * _inner_error_;
	DBusGProxy* _tmp0_;
	g_return_if_fail (self != NULL);
	_inner_error_ = NULL;
	_tmp0_ = NULL;
	self->priv->current = (_tmp0_ = epris_client_get_tracklist (self->priv->client, "current"), (self->priv->current == NULL) ? NULL : (self->priv->current = (g_object_unref (self->priv->current), NULL)), _tmp0_);
	g_object_ref ((GObject*) self->priv->current);
	_dynamic_DelTracks3 (self->priv->current, args, args_length1, immediately, epr_rm_reply, self, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
}


static Epr* epr_get_epr (GError** error) {
	Epr* result;
	GError * _inner_error_;
	Epr* epr;
	_inner_error_ = NULL;
	epr = epr_new ();
	{
		DBusGConnection* _tmp0_;
		DBusGConnection* _tmp1_;
		_tmp0_ = dbus_g_bus_get (DBUS_BUS_SESSION, &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch0_g_error;
			goto __finally0;
		}
		_tmp1_ = NULL;
		epr->priv->conn = (_tmp1_ = _tmp0_, (epr->priv->conn == NULL) ? NULL : (epr->priv->conn = (dbus_g_connection_unref (epr->priv->conn), NULL)), _tmp1_);
	}
	goto __finally0;
	__catch0_g_error:
	{
		GError * foo;
		foo = _inner_error_;
		_inner_error_ = NULL;
		{
			g_error (foo->message);
			_inner_error_ = g_error_new_literal (EPRIS_ERROR, EPRIS_ERROR_NONE, NULL);
			if (_inner_error_ != NULL) {
				g_propagate_error (error, _inner_error_);
				(foo == NULL) ? NULL : (foo = (g_error_free (foo), NULL));
				(epr == NULL) ? NULL : (epr = (g_object_unref (epr), NULL));
				return NULL;
			}
			(foo == NULL) ? NULL : (foo = (g_error_free (foo), NULL));
		}
	}
	__finally0:
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		(epr == NULL) ? NULL : (epr = (g_object_unref (epr), NULL));
		return NULL;
	}
	epr_initialize (epr, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		(epr == NULL) ? NULL : (epr = (g_object_unref (epr), NULL));
		return NULL;
	}
	result = epr;
	return result;
}


static inline GHashTable* _dynamic_get_current0 (DBusGProxy* obj) {
	DBusGProxy* property_proxy;
	GValue gvalue = {0};
	GHashTable* result;
	property_proxy = dbus_g_proxy_new_from_proxy (obj, DBUS_INTERFACE_PROPERTIES, NULL);
	dbus_g_proxy_call (property_proxy, "Get", NULL, G_TYPE_STRING, dbus_g_proxy_get_interface (obj), G_TYPE_STRING, "Current", G_TYPE_INVALID, G_TYPE_VALUE, &gvalue, G_TYPE_INVALID);
	g_object_unref (property_proxy);
	result = g_value_get_boxed (&gvalue);
	return result;
}


void epr_show (Epr* self) {
	char* format;
	DBusGProxy* _tmp0_;
	GHashTable* _tmp1_;
	GHashTable* current;
	char* _tmp2_;
	GValue _tmp4_ = {0};
	GValue* _tmp3_;
	GValue _tmp5_ = {0};
	GValue state;
	char* _tmp11_;
	char* _tmp10_;
	char* _tmp9_;
	char* _tmp8_;
	g_return_if_fail (self != NULL);
	format = g_strdup ("%-15s %s\n");
	_tmp0_ = NULL;
	_tmp1_ = NULL;
	current = (_tmp1_ = _dynamic_get_current0 (_tmp0_ = epris_client_get_tracklist (self->priv->client, "current")), (_tmp0_ == NULL) ? NULL : (_tmp0_ = (g_object_unref (_tmp0_), NULL)), _tmp1_);
	_tmp2_ = NULL;
	fprintf (stdout, "%s", _tmp2_ = epris_hsv_to_string (current, format, "x-"));
	_tmp2_ = (g_free (_tmp2_), NULL);
	_tmp3_ = NULL;
	state = (_tmp5_ = G_IS_VALUE (&(*(_tmp3_ = epris_structure_get ((EprisStructure*) self->priv->client, "State")))) ? (g_value_init (&_tmp4_, G_VALUE_TYPE (&(*(_tmp3_ = epris_structure_get ((EprisStructure*) self->priv->client, "State"))))), g_value_copy (&(*(_tmp3_ = epris_structure_get ((EprisStructure*) self->priv->client, "State"))), &_tmp4_), _tmp4_) : (*(_tmp3_ = epris_structure_get ((EprisStructure*) self->priv->client, "State"))), (_tmp3_ == NULL) ? NULL : (_tmp3_ = (g_free (_tmp3_), NULL)), _tmp5_);
	if (g_value_get_int (&state) == EPRIS_STATE_PLAYING) {
		char* _tmp6_;
		_tmp6_ = NULL;
		fprintf (stdout, "%s", _tmp6_ = g_strdup_printf (format, "state:", "Playing"));
		_tmp6_ = (g_free (_tmp6_), NULL);
	} else {
		char* _tmp7_;
		_tmp7_ = NULL;
		fprintf (stdout, "%s", _tmp7_ = g_strdup_printf (format, "state:", "Stopped"));
		_tmp7_ = (g_free (_tmp7_), NULL);
	}
	_tmp11_ = NULL;
	_tmp10_ = NULL;
	_tmp9_ = NULL;
	_tmp8_ = NULL;
	fprintf (stdout, "%s", _tmp11_ = g_strdup_printf (format, "position:", _tmp10_ = g_strdup_printf ("%s / %s", _tmp8_ = epris_time_to_string (g_value_get_int64 ((GValue*) g_hash_table_lookup (current, "x-position"))), _tmp9_ = epris_time_to_string (g_value_get_int64 ((GValue*) g_hash_table_lookup (current, "x-duration"))))));
	_tmp11_ = (g_free (_tmp11_), NULL);
	_tmp10_ = (g_free (_tmp10_), NULL);
	_tmp9_ = (g_free (_tmp9_), NULL);
	_tmp8_ = (g_free (_tmp8_), NULL);
	g_main_loop_quit (self->loop);
	format = (g_free (format), NULL);
	(current == NULL) ? NULL : (current = (g_hash_table_unref (current), NULL));
	G_IS_VALUE (&state) ? (g_value_unset (&state), NULL) : NULL;
}


static gint epr_parse_args (GOptionContext* opt_context, char*** args, int* args_length1, gboolean help) {
	gint result;
	GError * _inner_error_;
	g_return_val_if_fail (opt_context != NULL, 0);
	_inner_error_ = NULL;
	{
		g_option_context_parse (opt_context, &(*args_length1), &(*args), &_inner_error_);
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == G_OPTION_ERROR) {
				goto __catch1_g_option_error;
			}
			goto __finally1;
		}
	}
	goto __finally1;
	__catch1_g_option_error:
	{
		GError * e;
		e = _inner_error_;
		_inner_error_ = NULL;
		{
			if (help) {
				fprintf (stderr, "%s\n", e->message);
			}
			result = 1;
			(e == NULL) ? NULL : (e = (g_error_free (e), NULL));
			return result;
		}
	}
	__finally1:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return 0;
	}
	result = 0;
	return result;
}


static gint epr_cmd_play (Epr* self, char*** args, int* args_length1, GError** error) {
	gint result;
	GError * _inner_error_;
	GOptionContext* opt_context;
	g_return_val_if_fail (self != NULL, 0);
	_inner_error_ = NULL;
	opt_context = g_option_context_new ("- Play current track");
	g_option_context_add_main_entries (opt_context, EPR_play_options, NULL);
	if ((epr_rv = epr_parse_args (opt_context, &(*args), &(*args_length1), TRUE)) != 0) {
		result = epr_rv;
		(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
		return result;
	}
	epr_play (self, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
		return 0;
	}
	result = 0;
	(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
	return result;
}


static gint epr_cmd_stop (Epr* self, char*** args, int* args_length1, GError** error) {
	gint result;
	GError * _inner_error_;
	g_return_val_if_fail (self != NULL, 0);
	_inner_error_ = NULL;
	epr_stop (self, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return 0;
	}
	result = 0;
	return result;
}


static gint epr_cmd_add (Epr* self, char*** args, int* args_length1, GError** error) {
	gint result;
	GError * _inner_error_;
	GOptionContext* opt_context;
	gint i;
	char* _tmp8_;
	g_return_val_if_fail (self != NULL, 0);
	_inner_error_ = NULL;
	opt_context = g_option_context_new ("- Add a list of locations to a track list");
	g_option_context_add_main_entries (opt_context, EPR_add_options, NULL);
	if ((epr_rv = epr_parse_args (opt_context, &(*args), &(*args_length1), TRUE)) != 0) {
		result = epr_rv;
		(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
		return result;
	}
	i = 0;
	{
		char** s_collection;
		int s_collection_length1;
		int s_it;
		s_collection = epr_locations;
		s_collection_length1 = _vala_array_length (epr_locations);
		for (s_it = 0; s_it < _vala_array_length (epr_locations); s_it = s_it + 1) {
			const char* _tmp7_;
			char* s;
			_tmp7_ = NULL;
			s = (_tmp7_ = s_collection[s_it], (_tmp7_ == NULL) ? NULL : g_strdup (_tmp7_));
			{
				if (i >= 1) {
					const char* _tmp0_;
					char* uri;
					char* _tmp6_;
					const char* _tmp5_;
					_tmp0_ = NULL;
					uri = (_tmp0_ = epr_locations[i], (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_));
					if (!epris_uri_is_valid (uri)) {
						if (!g_path_is_absolute (uri)) {
							char* _tmp2_;
							char* _tmp1_;
							_tmp2_ = NULL;
							_tmp1_ = NULL;
							uri = (_tmp2_ = g_build_filename (_tmp1_ = g_get_current_dir (), uri, NULL), uri = (g_free (uri), NULL), _tmp2_);
							_tmp1_ = (g_free (_tmp1_), NULL);
						}
						{
							char* _tmp3_;
							char* _tmp4_;
							_tmp3_ = g_filename_to_uri (uri, NULL, &_inner_error_);
							if (_inner_error_ != NULL) {
								if (_inner_error_->domain == G_CONVERT_ERROR) {
									goto __catch2_g_convert_error;
								}
								goto __finally2;
							}
							_tmp4_ = NULL;
							uri = (_tmp4_ = _tmp3_, uri = (g_free (uri), NULL), _tmp4_);
						}
						goto __finally2;
						__catch2_g_convert_error:
						{
							GError * _error_;
							_error_ = _inner_error_;
							_inner_error_ = NULL;
							{
								g_warning (_error_->message);
								i = i + 2;
								(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
								uri = (g_free (uri), NULL);
								s = (g_free (s), NULL);
								continue;
							}
						}
						__finally2:
						if (_inner_error_ != NULL) {
							g_propagate_error (error, _inner_error_);
							uri = (g_free (uri), NULL);
							s = (g_free (s), NULL);
							(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
							return 0;
						}
					}
					_tmp6_ = NULL;
					_tmp5_ = NULL;
					epr_locations[i - 1] = (_tmp6_ = (_tmp5_ = uri, (_tmp5_ == NULL) ? NULL : g_strdup (_tmp5_)), epr_locations[i - 1] = (g_free (epr_locations[i - 1]), NULL), _tmp6_);
					uri = (g_free (uri), NULL);
				}
				i++;
				s = (g_free (s), NULL);
			}
		}
	}
	if (i <= 1) {
		result = 1;
		(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
		return result;
	}
	_tmp8_ = NULL;
	epr_locations[i - 1] = (_tmp8_ = NULL, epr_locations[i - 1] = (g_free (epr_locations[i - 1]), NULL), _tmp8_);
	epr_add (self, epr_locations, _vala_array_length (epr_locations), FALSE, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
		return 0;
	}
	result = 0;
	(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
	return result;
}


GHashTable** _dynamic_ListTracks4 (DBusGProxy* self, int* result_length1, GError** error) {
	GPtrArray* result;
	dbus_g_proxy_call (self, "ListTracks", error, G_TYPE_INVALID, dbus_g_type_get_collection ("GPtrArray", dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), &result, G_TYPE_INVALID);
	if (*error) {
		return NULL;
	}
	*result_length1 = result->len;
	return (GHashTable**) result->pdata;
}


static void _g_list_free_g_free (GList* self) {
	g_list_foreach (self, (GFunc) g_free, NULL);
	g_list_free (self);
}


static gint epr_cmd_rm (Epr* self, char*** args, int* args_length1, GError** error) {
	gint result;
	GError * _inner_error_;
	GOptionContext* opt_context;
	GHashTable** _tmp3_;
	gint tracks_size;
	gint tracks_length1;
	gint _tmp1_;
	DBusGProxy* _tmp0_;
	GHashTable** _tmp2_;
	GHashTable** tracks;
	GList* list;
	guint i;
	char** _tmp12_;
	gint _tmp11__length1;
	char** _tmp11_;
	gint _tmp10_;
	g_return_val_if_fail (self != NULL, 0);
	_inner_error_ = NULL;
	opt_context = g_option_context_new ("- Remove matching locations from a track list");
	g_option_context_add_main_entries (opt_context, EPR_rm_options, NULL);
	if ((epr_rv = epr_parse_args (opt_context, &(*args), &(*args_length1), TRUE)) != 0) {
		result = epr_rv;
		(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
		return result;
	}
	_tmp3_ = NULL;
	_tmp0_ = NULL;
	_tmp2_ = NULL;
	tracks = (_tmp3_ = (_tmp2_ = _dynamic_ListTracks4 (_tmp0_ = epris_client_get_tracklist (self->priv->client, "current"), &_tmp1_, &_inner_error_), (_tmp0_ == NULL) ? NULL : (_tmp0_ = (g_object_unref (_tmp0_), NULL)), _tmp2_), tracks_length1 = _tmp1_, tracks_size = tracks_length1, _tmp3_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
		return 0;
	}
	list = NULL;
	i = (guint) 0;
	{
		char** pat_collection;
		int pat_collection_length1;
		int pat_it;
		pat_collection = epr_locations;
		pat_collection_length1 = _vala_array_length (epr_locations);
		for (pat_it = 0; pat_it < _vala_array_length (epr_locations); pat_it = pat_it + 1) {
			const char* _tmp9_;
			char* pat;
			_tmp9_ = NULL;
			pat = (_tmp9_ = pat_collection[pat_it], (_tmp9_ == NULL) ? NULL : g_strdup (_tmp9_));
			{
				i = i + ((guint) 1);
				if (i <= 1) {
					pat = (g_free (pat), NULL);
					continue;
				}
				{
					GHashTable** t_collection;
					int t_collection_length1;
					int t_it;
					t_collection = tracks;
					t_collection_length1 = tracks_length1;
					for (t_it = 0; t_it < tracks_length1; t_it = t_it + 1) {
						GHashTable* _tmp8_;
						GHashTable* t;
						_tmp8_ = NULL;
						t = (_tmp8_ = t_collection[t_it], (_tmp8_ == NULL) ? NULL : g_hash_table_ref (_tmp8_));
						{
							gboolean _tmp4_;
							_tmp4_ = FALSE;
							if (g_pattern_match_simple (pat, g_value_get_string ((GValue*) g_hash_table_lookup (t, "uri")))) {
								_tmp4_ = TRUE;
							} else {
								char* _tmp5_;
								char* _tmp6_;
								_tmp5_ = g_filename_from_uri (g_value_get_string ((GValue*) g_hash_table_lookup (t, "uri")), NULL, &_inner_error_);
								if (_inner_error_ != NULL) {
									g_propagate_error (error, _inner_error_);
									(t == NULL) ? NULL : (t = (g_hash_table_unref (t), NULL));
									pat = (g_free (pat), NULL);
									(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
									tracks = (_vala_array_free (tracks, tracks_length1, (GDestroyNotify) g_hash_table_unref), NULL);
									(list == NULL) ? NULL : (list = (_g_list_free_g_free (list), NULL));
									return 0;
								}
								_tmp6_ = NULL;
								_tmp4_ = g_pattern_match_simple (pat, _tmp6_ = _tmp5_);
								_tmp6_ = (g_free (_tmp6_), NULL);
							}
							if (_tmp4_) {
								const char* _tmp7_;
								g_debug ("epr.vala:229: removing %s", g_value_get_string ((GValue*) g_hash_table_lookup (t, "uri")));
								_tmp7_ = NULL;
								list = g_list_append (list, (_tmp7_ = g_value_get_string ((GValue*) g_hash_table_lookup (t, "uri")), (_tmp7_ == NULL) ? NULL : g_strdup (_tmp7_)));
							}
							(t == NULL) ? NULL : (t = (g_hash_table_unref (t), NULL));
						}
					}
				}
				pat = (g_free (pat), NULL);
			}
		}
	}
	_tmp12_ = NULL;
	_tmp11_ = NULL;
	_tmp12_ = (_tmp11_ = epris_strv_from_list (list, &_tmp10_), _tmp11__length1 = _tmp10_, _tmp11_);
	epr_rm (self, _tmp12_, _tmp10_, FALSE, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
		tracks = (_vala_array_free (tracks, tracks_length1, (GDestroyNotify) g_hash_table_unref), NULL);
		(list == NULL) ? NULL : (list = (_g_list_free_g_free (list), NULL));
		return 0;
	}
	_tmp11_ = (_vala_array_free (_tmp11_, _tmp11__length1, (GDestroyNotify) g_free), NULL);
	result = 0;
	(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
	tracks = (_vala_array_free (tracks, tracks_length1, (GDestroyNotify) g_hash_table_unref), NULL);
	(list == NULL) ? NULL : (list = (_g_list_free_g_free (list), NULL));
	return result;
}


static char* string_substring (const char* self, glong offset, glong len) {
	char* result;
	glong string_length;
	const char* start;
	g_return_val_if_fail (self != NULL, NULL);
	string_length = g_utf8_strlen (self, -1);
	if (offset < 0) {
		offset = string_length + offset;
		g_return_val_if_fail (offset >= 0, NULL);
	} else {
		g_return_val_if_fail (offset <= string_length, NULL);
	}
	if (len < 0) {
		len = string_length - offset;
	}
	g_return_val_if_fail ((offset + len) <= string_length, NULL);
	start = g_utf8_offset_to_pointer (self, offset);
	result = g_strndup (start, ((gchar*) g_utf8_offset_to_pointer (start, len)) - ((gchar*) start));
	return result;
}


static glong string_get_length (const char* self) {
	glong result;
	g_return_val_if_fail (self != NULL, 0L);
	result = g_utf8_strlen (self, -1);
	return result;
}


static GHashTable* epr_list_other_cmd (Epr* self) {
	GHashTable* result;
	GError * _inner_error_;
	GHashTable* r;
	g_return_val_if_fail (self != NULL, NULL);
	_inner_error_ = NULL;
	r = g_hash_table_new (g_str_hash, g_str_equal);
	{
		GDir* d;
		d = g_dir_open (LIBEXECDIR, 0, &_inner_error_);
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == G_FILE_ERROR) {
				goto __catch3_g_file_error;
			}
			goto __finally3;
		}
		{
			gboolean _tmp0_;
			_tmp0_ = TRUE;
			while (TRUE) {
				const char* _tmp1_;
				char* c;
				char* n;
				char* _tmp2_;
				const char* _tmp5_;
				const char* _tmp4_;
				if (!_tmp0_) {
				}
				_tmp0_ = FALSE;
				_tmp1_ = NULL;
				c = (_tmp1_ = g_dir_read_name (d), (_tmp1_ == NULL) ? NULL : g_strdup (_tmp1_));
				if (c == NULL) {
					c = (g_free (c), NULL);
					break;
				}
				if (!g_str_has_prefix (c, "epr-")) {
					c = (g_free (c), NULL);
					continue;
				}
				n = g_build_filename (LIBEXECDIR, c, NULL);
				if (!g_file_test (n, G_FILE_TEST_IS_EXECUTABLE)) {
					c = (g_free (c), NULL);
					n = (g_free (n), NULL);
					continue;
				}
				_tmp2_ = NULL;
				c = (_tmp2_ = string_substring (c, (glong) 4, -1), c = (g_free (c), NULL), _tmp2_);
				{
					glong i;
					i = string_get_length (c) - 1;
					{
						gboolean _tmp3_;
						_tmp3_ = TRUE;
						while (TRUE) {
							if (!_tmp3_) {
								i--;
							}
							_tmp3_ = FALSE;
							if (!(i > 0)) {
								break;
							}
							if (g_utf8_get_char (g_utf8_offset_to_pointer (c, i)) == '.') {
								((gchar*) c)[i] = '\0';
								break;
							}
						}
					}
				}
				_tmp5_ = NULL;
				_tmp4_ = NULL;
				g_hash_table_insert (r, (_tmp4_ = c, (_tmp4_ == NULL) ? NULL : g_strdup (_tmp4_)), (_tmp5_ = n, (_tmp5_ == NULL) ? NULL : g_strdup (_tmp5_)));
				c = (g_free (c), NULL);
				n = (g_free (n), NULL);
			}
		}
		(d == NULL) ? NULL : (d = (g_dir_close (d), NULL));
	}
	goto __finally3;
	__catch3_g_file_error:
	{
		GError * fe;
		fe = _inner_error_;
		_inner_error_ = NULL;
		{
			g_warning (fe->message);
			(fe == NULL) ? NULL : (fe = (g_error_free (fe), NULL));
		}
	}
	__finally3:
	if (_inner_error_ != NULL) {
		(r == NULL) ? NULL : (r = (g_hash_table_unref (r), NULL));
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return NULL;
	}
	result = r;
	return result;
}


static gint epr_cmd_help (Epr* self, char*** args, int* args_length1, GOptionContext* opt_context, GError** error) {
	gint result;
	char* _tmp0_;
	g_return_val_if_fail (self != NULL, 0);
	g_return_val_if_fail (opt_context != NULL, 0);
	g_option_context_add_main_entries (opt_context, EPR_help_options, NULL);
	epr_parse_args (opt_context, &(*args), &(*args_length1), TRUE);
	_tmp0_ = NULL;
	fprintf (stdout, _tmp0_ = g_option_context_get_help (opt_context, FALSE, NULL));
	_tmp0_ = (g_free (_tmp0_), NULL);
	if (epr_help_all) {
		GHashTable* cmds;
		cmds = epr_list_other_cmd (self);
		if (g_hash_table_size (cmds) > 0) {
			fprintf (stdout, "Other commands:\n");
			{
				GList* c_collection;
				GList* c_it;
				c_collection = g_hash_table_get_keys (cmds);
				for (c_it = c_collection; c_it != NULL; c_it = c_it->next) {
					const char* c;
					c = (const char*) c_it->data;
					{
						char* _tmp2_;
						char* _tmp1_;
						_tmp2_ = NULL;
						_tmp1_ = NULL;
						fprintf (stdout, _tmp2_ = g_strconcat (_tmp1_ = g_strconcat ("  ", c, NULL), "\n", NULL));
						_tmp2_ = (g_free (_tmp2_), NULL);
						_tmp1_ = (g_free (_tmp1_), NULL);
					}
				}
				(c_collection == NULL) ? NULL : (c_collection = (g_list_free (c_collection), NULL));
			}
		}
		(cmds == NULL) ? NULL : (cmds = (g_hash_table_unref (cmds), NULL));
	}
	result = 0;
	return result;
}


static void _lambda2_ (EprisClient* s, GParamSpec* p, Epr* self) {
	g_return_if_fail (s != NULL);
	g_return_if_fail (p != NULL);
	if (_vala_strcmp0 (p->name, "updated") == 0) {
		epr_show (self);
	}
}


static void __lambda2__g_object_notify (EprisClient* _sender, GParamSpec* pspec, gpointer self) {
	_lambda2_ (_sender, pspec, self);
}


static gint epr_cmd_show (Epr* self, char*** args, int* args_length1, GError** error) {
	gint result;
	g_return_val_if_fail (self != NULL, 0);
	if (epris_dbus_proxy_get_updated ((EprisDBusProxy*) self->priv->client) == TRUE) {
		epr_show (self);
	} else {
		g_signal_connect ((GObject*) self->priv->client, "notify", (GCallback) __lambda2__g_object_notify, self);
	}
	result = 0;
	return result;
}


GHashTable** _dynamic_ListTracks5 (DBusGProxy* self, int* result_length1, GError** error) {
	GPtrArray* result;
	dbus_g_proxy_call (self, "ListTracks", error, G_TYPE_INVALID, dbus_g_type_get_collection ("GPtrArray", dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), &result, G_TYPE_INVALID);
	if (*error) {
		return NULL;
	}
	*result_length1 = result->len;
	return (GHashTable**) result->pdata;
}


static gint epr_cmd_list (Epr* self, char*** args, int* args_length1, GError** error) {
	gint result;
	GError * _inner_error_;
	GOptionContext* opt_context;
	gint i;
	GHashTable** _tmp3_;
	gint tracks_size;
	gint tracks_length1;
	gint _tmp1_;
	DBusGProxy* _tmp0_;
	GHashTable** _tmp2_;
	GHashTable** tracks;
	g_return_val_if_fail (self != NULL, 0);
	_inner_error_ = NULL;
	opt_context = g_option_context_new ("- List tracks in current tracklist");
	g_option_context_add_main_entries (opt_context, EPR_list_options, NULL);
	if ((epr_rv = epr_parse_args (opt_context, &(*args), &(*args_length1), TRUE)) != 0) {
		result = epr_rv;
		(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
		return result;
	}
	i = 1;
	_tmp3_ = NULL;
	_tmp0_ = NULL;
	_tmp2_ = NULL;
	tracks = (_tmp3_ = (_tmp2_ = _dynamic_ListTracks5 (_tmp0_ = epris_client_get_tracklist (self->priv->client, "current"), &_tmp1_, &_inner_error_), (_tmp0_ == NULL) ? NULL : (_tmp0_ = (g_object_unref (_tmp0_), NULL)), _tmp2_), tracks_length1 = _tmp1_, tracks_size = tracks_length1, _tmp3_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
		return 0;
	}
	{
		GHashTable** t_collection;
		int t_collection_length1;
		int t_it;
		t_collection = tracks;
		t_collection_length1 = tracks_length1;
		for (t_it = 0; t_it < tracks_length1; t_it = t_it + 1) {
			GHashTable* _tmp7_;
			GHashTable* t;
			_tmp7_ = NULL;
			t = (_tmp7_ = t_collection[t_it], (_tmp7_ == NULL) ? NULL : g_hash_table_ref (_tmp7_));
			{
				gboolean _tmp4_;
				char* _tmp5_;
				char* _tmp6_;
				_tmp4_ = FALSE;
				if (((GValue*) g_hash_table_lookup (t, "current")) != NULL) {
					_tmp4_ = g_value_get_boolean ((GValue*) g_hash_table_lookup (t, "current"));
				} else {
					_tmp4_ = FALSE;
				}
				if (_tmp4_) {
					fprintf (stdout, "* ");
				} else {
					fprintf (stdout, "  ");
				}
				if (epr_numbered) {
					fprintf (stdout, "%4d ", i);
				}
				_tmp5_ = g_filename_from_uri (g_value_get_string ((GValue*) g_hash_table_lookup (t, "uri")), NULL, &_inner_error_);
				if (_inner_error_ != NULL) {
					g_propagate_error (error, _inner_error_);
					(t == NULL) ? NULL : (t = (g_hash_table_unref (t), NULL));
					(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
					tracks = (_vala_array_free (tracks, tracks_length1, (GDestroyNotify) g_hash_table_unref), NULL);
					return 0;
				}
				_tmp6_ = NULL;
				fprintf (stdout, "%s\n", _tmp6_ = _tmp5_);
				_tmp6_ = (g_free (_tmp6_), NULL);
				i = i + 1;
				(t == NULL) ? NULL : (t = (g_hash_table_unref (t), NULL));
			}
		}
	}
	g_main_loop_quit (self->loop);
	result = 0;
	(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
	tracks = (_vala_array_free (tracks, tracks_length1, (GDestroyNotify) g_hash_table_unref), NULL);
	return result;
}


static void epr_skip_reply (Epr* self, GError* e) {
	g_return_if_fail (self != NULL);
	epr_rv = 0;
	g_debug ("epr.vala:338: skip_reply");
	if (e != NULL) {
		fprintf (stderr, "%s\n", e->message);
		epr_rv = 1;
	}
	g_main_loop_quit (self->loop);
}


static void _epr_skip_reply_cb (DBusGProxy* proxy, DBusGProxyCall* call, void* user_data) {
	GError* error;
	error = NULL;
	dbus_g_proxy_end_call (proxy, call, &error, G_TYPE_INVALID);
	epr_skip_reply (user_data, error);
}


void _dynamic_Seek6 (DBusGProxy* self, gint param1, EprisWhence param2, gpointer param3, void* param3_target, GError** error) {
	dbus_g_proxy_begin_call (self, "Seek", _epr_skip_reply_cb, param3_target, NULL, G_TYPE_INT, param1, G_TYPE_INT, param2, G_TYPE_INVALID, G_TYPE_INVALID);
	if (*error) {
		return;
	}
}


static gint epr_cmd_skip (Epr* self, char*** args, int* args_length1, GError** error) {
	gint result;
	GError * _inner_error_;
	GOptionContext* opt_context;
	DBusGProxy* c;
	g_return_val_if_fail (self != NULL, 0);
	_inner_error_ = NULL;
	opt_context = g_option_context_new ("- Skip to a different track");
	g_option_context_add_main_entries (opt_context, EPR_skip_options, NULL);
	if ((epr_rv = epr_parse_args (opt_context, &(*args), &(*args_length1), TRUE)) != 0) {
		result = epr_rv;
		(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
		return result;
	}
	if ((*args_length1) == 3) {
		epr_nskip = atoi ((*args)[2]);
	}
	g_debug ("epr.vala:362: Skip %d track(s)", epr_nskip);
	/* FIXME, current is unref: client.get_tracklist ("current").Seek (nskip, Epris.Whence.CURRENT, skip_reply);*/
	c = epris_client_get_tracklist (self->priv->client, "current");
	_dynamic_Seek6 (c, epr_nskip, EPRIS_WHENCE_CURRENT, epr_skip_reply, self, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
		(c == NULL) ? NULL : (c = (g_object_unref (c), NULL));
		return 0;
	}
	g_object_ref ((GObject*) c);
	result = 0;
	(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
	(c == NULL) ? NULL : (c = (g_object_unref (c), NULL));
	return result;
}


void _dynamic_Seek7 (DBusGProxy* self, EprisFormat param1, gint64 param2, GError** error) {
	dbus_g_proxy_call (self, "Seek", error, G_TYPE_INT, param1, G_TYPE_INT64, param2, G_TYPE_INVALID, G_TYPE_INVALID);
	if (*error) {
		return;
	}
}


static gint epr_cmd_seek (Epr* self, char*** args, int* args_length1, GError** error) {
	gint result;
	GError * _inner_error_;
	GOptionContext* opt_context;
	gboolean _tmp0_;
	gboolean _tmp1_;
	g_return_val_if_fail (self != NULL, 0);
	_inner_error_ = NULL;
	opt_context = g_option_context_new ("- Seek to a given position");
	g_option_context_add_main_entries (opt_context, EPR_seek_options, NULL);
	if ((epr_rv = epr_parse_args (opt_context, &(*args), &(*args_length1), TRUE)) != 0) {
		result = epr_rv;
		(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
		return result;
	}
	_tmp0_ = FALSE;
	_tmp1_ = FALSE;
	if (epr_seek_position == NULL) {
		_tmp1_ = TRUE;
	} else {
		_tmp1_ = _vala_strcmp0 (epr_seek_position[0], "seek") != 0;
	}
	if (_tmp1_) {
		_tmp0_ = TRUE;
	} else {
		_tmp0_ = epr_seek_position[1] == NULL;
	}
	if (_tmp0_) {
		fprintf (stderr, "Command 'seek' need a position argument. Ex: seek 40%%\n");
		result = 1;
		(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
		return result;
	}
	g_debug ("epr.vala:388: Seek to %s.", epr_seek_position[1]);
	if (g_str_has_suffix (epr_seek_position[1], "%")) {
		gint64 percent;
		percent = 0LL;
		g_strcanon (epr_seek_position[1], "0123456789", ' ');
		percent = g_ascii_strtoll (epr_seek_position[1], NULL, 0);
		_dynamic_Seek7 (epris_client_get_player (self->priv->client), EPRIS_FORMAT_PERCENT, percent, &_inner_error_);
		if (_inner_error_ != NULL) {
			g_propagate_error (error, _inner_error_);
			(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
			return 0;
		}
	}
	result = 0;
	(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
	return result;
}


static void _epris_log_handler_glog_func (const char* log_domain, GLogLevelFlags log_levels, const char* message, gpointer self) {
	epris_log_handler (log_domain, log_levels, message);
}


static gint epr_main (char** args, int args_length1) {
	gint result;
	GError * _inner_error_;
	GOptionContext* opt_context;
	_inner_error_ = NULL;
	g_log_set_default_handler (_epris_log_handler_glog_func, NULL);
	epris_debug_level = 2;
	opt_context = g_option_context_new ("- Manage Epris audio player\n\nAvailable commands:\n\n  play     Play\n  stop     Stop\n  add      Add tracks to tracklist\n  rm       Remove tracks from tracklist\n  seek     Seek to a given position within track\n  skip     Move within the tracklist (alias skip)\n  list     List tracks\n  help     Display this help");
	g_option_context_add_main_entries (opt_context, EPR_main_options, NULL);
	{
		Epr* epr;
		GQuark _tmp17_;
		const char* _tmp16_;
		g_option_context_set_help_enabled (opt_context, FALSE);
		epr_parse_args (opt_context, &args, &args_length1, FALSE);
		g_option_context_set_help_enabled (opt_context, TRUE);
		if (epr_version) {
			fprintf (stdout, "Epr %s\n", PACKAGE_VERSION);
			result = 0;
			(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
			return result;
		}
		epr = NULL;
		{
			Epr* _tmp0_;
			Epr* _tmp1_;
			_tmp0_ = epr_get_epr (&_inner_error_);
			if (_inner_error_ != NULL) {
				goto __catch5_g_error;
				goto __finally5;
			}
			_tmp1_ = NULL;
			epr = (_tmp1_ = _tmp0_, (epr == NULL) ? NULL : (epr = (g_object_unref (epr), NULL)), _tmp1_);
		}
		goto __finally5;
		__catch5_g_error:
		{
			GError * e;
			e = _inner_error_;
			_inner_error_ = NULL;
			{
				g_warning (e->message);
				result = 1;
				(e == NULL) ? NULL : (e = (g_error_free (e), NULL));
				(epr == NULL) ? NULL : (epr = (g_object_unref (epr), NULL));
				(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
				return result;
			}
		}
		__finally5:
		if (_inner_error_ != NULL) {
			(epr == NULL) ? NULL : (epr = (g_object_unref (epr), NULL));
			if (_inner_error_->domain == EPRIS_ERROR) {
				goto __catch4_epris_error;
			}
			goto __finally4;
		}
		_tmp16_ = NULL;
		static GQuark _tmp17__label0 = 0;
		static GQuark _tmp17__label1 = 0;
		static GQuark _tmp17__label2 = 0;
		static GQuark _tmp17__label3 = 0;
		static GQuark _tmp17__label4 = 0;
		static GQuark _tmp17__label5 = 0;
		static GQuark _tmp17__label6 = 0;
		static GQuark _tmp17__label7 = 0;
		static GQuark _tmp17__label8 = 0;
		static GQuark _tmp17__label9 = 0;
		static GQuark _tmp17__label10 = 0;
		_tmp16_ = args[1];
		_tmp17_ = (NULL == _tmp16_) ? 0 : g_quark_from_string (_tmp16_);
		if (_tmp17_ == ((0 != _tmp17__label0) ? _tmp17__label0 : (_tmp17__label0 = g_quark_from_static_string ("play"))))
		do {
			epr_cmd_play (epr, &args, &args_length1, &_inner_error_);
			if (_inner_error_ != NULL) {
				(epr == NULL) ? NULL : (epr = (g_object_unref (epr), NULL));
				if (_inner_error_->domain == EPRIS_ERROR) {
					goto __catch4_epris_error;
				}
				goto __finally4;
			}
			break;
		} while (0); else if (_tmp17_ == ((0 != _tmp17__label1) ? _tmp17__label1 : (_tmp17__label1 = g_quark_from_static_string ("stop"))))
		do {
			epr_cmd_stop (epr, &args, &args_length1, &_inner_error_);
			if (_inner_error_ != NULL) {
				(epr == NULL) ? NULL : (epr = (g_object_unref (epr), NULL));
				if (_inner_error_->domain == EPRIS_ERROR) {
					goto __catch4_epris_error;
				}
				goto __finally4;
			}
			break;
		} while (0); else if (_tmp17_ == ((0 != _tmp17__label2) ? _tmp17__label2 : (_tmp17__label2 = g_quark_from_static_string ("add"))))
		do {
			gint status;
			gint _tmp2_;
			status = 0;
			_tmp2_ = epr_cmd_add (epr, &args, &args_length1, &_inner_error_);
			if (_inner_error_ != NULL) {
				(epr == NULL) ? NULL : (epr = (g_object_unref (epr), NULL));
				if (_inner_error_->domain == EPRIS_ERROR) {
					goto __catch4_epris_error;
				}
				goto __finally4;
			}
			status = _tmp2_;
			if (status != 0) {
				result = status;
				(epr == NULL) ? NULL : (epr = (g_object_unref (epr), NULL));
				(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
				return result;
			}
			break;
		} while (0); else if (_tmp17_ == ((0 != _tmp17__label3) ? _tmp17__label3 : (_tmp17__label3 = g_quark_from_static_string ("rm"))))
		do {
			epr_cmd_rm (epr, &args, &args_length1, &_inner_error_);
			if (_inner_error_ != NULL) {
				(epr == NULL) ? NULL : (epr = (g_object_unref (epr), NULL));
				if (_inner_error_->domain == EPRIS_ERROR) {
					goto __catch4_epris_error;
				}
				goto __finally4;
			}
			break;
		} while (0); else if (_tmp17_ == ((0 != _tmp17__label4) ? _tmp17__label4 : (_tmp17__label4 = g_quark_from_static_string ("show"))))
		do {
			epr_cmd_show (epr, &args, &args_length1, &_inner_error_);
			if (_inner_error_ != NULL) {
				(epr == NULL) ? NULL : (epr = (g_object_unref (epr), NULL));
				if (_inner_error_->domain == EPRIS_ERROR) {
					goto __catch4_epris_error;
				}
				goto __finally4;
			}
			break;
		} while (0); else if (_tmp17_ == ((0 != _tmp17__label5) ? _tmp17__label5 : (_tmp17__label5 = g_quark_from_static_string ("list"))))
		do {
			gint _tmp3_;
			_tmp3_ = epr_cmd_list (epr, &args, &args_length1, &_inner_error_);
			if (_inner_error_ != NULL) {
				(epr == NULL) ? NULL : (epr = (g_object_unref (epr), NULL));
				if (_inner_error_->domain == EPRIS_ERROR) {
					goto __catch4_epris_error;
				}
				goto __finally4;
			}
			result = _tmp3_;
			(epr == NULL) ? NULL : (epr = (g_object_unref (epr), NULL));
			(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
			return result;
		} while (0); else if (_tmp17_ == ((0 != _tmp17__label6) ? _tmp17__label6 : (_tmp17__label6 = g_quark_from_static_string ("skip"))))
		do {
			epr_cmd_skip (epr, &args, &args_length1, &_inner_error_);
			if (_inner_error_ != NULL) {
				(epr == NULL) ? NULL : (epr = (g_object_unref (epr), NULL));
				if (_inner_error_->domain == EPRIS_ERROR) {
					goto __catch4_epris_error;
				}
				goto __finally4;
			}
			break;
		} while (0); else if (_tmp17_ == ((0 != _tmp17__label7) ? _tmp17__label7 : (_tmp17__label7 = g_quark_from_static_string ("seek"))))
		do {
			gint _tmp4_;
			_tmp4_ = epr_cmd_seek (epr, &args, &args_length1, &_inner_error_);
			if (_inner_error_ != NULL) {
				(epr == NULL) ? NULL : (epr = (g_object_unref (epr), NULL));
				if (_inner_error_->domain == EPRIS_ERROR) {
					goto __catch4_epris_error;
				}
				goto __finally4;
			}
			result = _tmp4_;
			(epr == NULL) ? NULL : (epr = (g_object_unref (epr), NULL));
			(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
			return result;
		} while (0); else if (((_tmp17_ == ((0 != _tmp17__label8) ? _tmp17__label8 : (_tmp17__label8 = g_quark_from_static_string (NULL)))) || (_tmp17_ == ((0 != _tmp17__label9) ? _tmp17__label9 : (_tmp17__label9 = g_quark_from_static_string ("--help"))))) || (_tmp17_ == ((0 != _tmp17__label10) ? _tmp17__label10 : (_tmp17__label10 = g_quark_from_static_string ("help")))))
		do {
			gint _tmp5_;
			_tmp5_ = epr_cmd_help (epr, &args, &args_length1, opt_context, &_inner_error_);
			if (_inner_error_ != NULL) {
				(epr == NULL) ? NULL : (epr = (g_object_unref (epr), NULL));
				if (_inner_error_->domain == EPRIS_ERROR) {
					goto __catch4_epris_error;
				}
				goto __finally4;
			}
			result = _tmp5_;
			(epr == NULL) ? NULL : (epr = (g_object_unref (epr), NULL));
			(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
			return result;
		} while (0); else
		do {
			GHashTable* cmds;
			const char* _tmp6_;
			char* c;
			cmds = epr_list_other_cmd (epr);
			_tmp6_ = NULL;
			c = (_tmp6_ = (const char*) g_hash_table_lookup (cmds, args[1]), (_tmp6_ == NULL) ? NULL : g_strdup (_tmp6_));
			if (c != NULL) {
				char* output;
				char* _error_;
				gint status;
				char* _tmp15_;
				gboolean _tmp14_;
				char* _tmp13_;
				char* _tmp12_;
				gboolean _tmp11_;
				char* _tmp10_;
				char* _tmp9_;
				char* _tmp8_;
				char* _tmp7_;
				output = NULL;
				_error_ = NULL;
				status = 0;
				_tmp15_ = NULL;
				_tmp13_ = NULL;
				_tmp12_ = NULL;
				_tmp10_ = NULL;
				_tmp9_ = NULL;
				_tmp8_ = NULL;
				_tmp7_ = NULL;
				_tmp14_ = (_tmp11_ = g_spawn_command_line_sync (_tmp9_ = g_strconcat (_tmp7_ = g_strconcat (c, " ", NULL), _tmp8_ = g_strjoinv (" ", args), NULL), &_tmp10_, &_tmp13_, &status, &_inner_error_), output = (_tmp12_ = _tmp10_, output = (g_free (output), NULL), _tmp12_), _tmp11_);
				_error_ = (_tmp15_ = _tmp13_, _error_ = (g_free (_error_), NULL), _tmp15_);
				_tmp14_;
				if (_inner_error_ != NULL) {
					output = (g_free (output), NULL);
					_error_ = (g_free (_error_), NULL);
					(cmds == NULL) ? NULL : (cmds = (g_hash_table_unref (cmds), NULL));
					c = (g_free (c), NULL);
					(epr == NULL) ? NULL : (epr = (g_object_unref (epr), NULL));
					if (_inner_error_->domain == EPRIS_ERROR) {
						goto __catch4_epris_error;
					}
					goto __finally4;
				}
				_tmp9_ = (g_free (_tmp9_), NULL);
				_tmp8_ = (g_free (_tmp8_), NULL);
				_tmp7_ = (g_free (_tmp7_), NULL);
				fprintf (stdout, output);
				fprintf (stderr, _error_);
				result = status;
				output = (g_free (output), NULL);
				_error_ = (g_free (_error_), NULL);
				(cmds == NULL) ? NULL : (cmds = (g_hash_table_unref (cmds), NULL));
				c = (g_free (c), NULL);
				(epr == NULL) ? NULL : (epr = (g_object_unref (epr), NULL));
				(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
				return result;
			} else {
				fprintf (stderr, "Unknown command: %s\n", args[1]);
			}
			fprintf (stdout, "Run '%s --help' to see a full list of available command line options.\n", g_get_prgname ());
			result = 1;
			(cmds == NULL) ? NULL : (cmds = (g_hash_table_unref (cmds), NULL));
			c = (g_free (c), NULL);
			(epr == NULL) ? NULL : (epr = (g_object_unref (epr), NULL));
			(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
			return result;
		} while (0);
		g_main_loop_run (epr->loop);
		result = epr_rv;
		(epr == NULL) ? NULL : (epr = (g_object_unref (epr), NULL));
		(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
		return result;
	}
	goto __finally4;
	__catch4_epris_error:
	{
		GError * err;
		err = _inner_error_;
		_inner_error_ = NULL;
		{
			/*if (err == Epris.Error.NONE) FIXME*/
			result = 0;
			(err == NULL) ? NULL : (err = (g_error_free (err), NULL));
			(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
			return result;
		}
	}
	__finally4:
	if (_inner_error_ != NULL) {
		(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return 0;
	}
	(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
}


int main (int argc, char ** argv) {
	g_thread_init (NULL);
	g_type_init ();
	return epr_main (argv, argc);
}


Epr* epr_construct (GType object_type) {
	Epr * self;
	self = g_object_newv (object_type, 0, NULL);
	return self;
}


Epr* epr_new (void) {
	return epr_construct (TYPE_EPR);
}


static GObject * epr_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	EprClass * klass;
	GObjectClass * parent_class;
	Epr * self;
	klass = EPR_CLASS (g_type_class_peek (TYPE_EPR));
	parent_class = G_OBJECT_CLASS (g_type_class_peek_parent (klass));
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = EPR (obj);
	{
		GMainLoop* _tmp0_;
		_tmp0_ = NULL;
		self->loop = (_tmp0_ = g_main_loop_new (NULL, FALSE), (self->loop == NULL) ? NULL : (self->loop = (g_main_loop_unref (self->loop), NULL)), _tmp0_);
	}
	return obj;
}


static void epr_class_init (EprClass * klass) {
	epr_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (EprPrivate));
	G_OBJECT_CLASS (klass)->constructor = epr_constructor;
	G_OBJECT_CLASS (klass)->finalize = epr_finalize;
}


static void epr_instance_init (Epr * self) {
	self->priv = EPR_GET_PRIVATE (self);
}


static void epr_finalize (GObject* obj) {
	Epr * self;
	self = EPR (obj);
	(self->priv->conn == NULL) ? NULL : (self->priv->conn = (dbus_g_connection_unref (self->priv->conn), NULL));
	(self->loop == NULL) ? NULL : (self->loop = (g_main_loop_unref (self->loop), NULL));
	(self->priv->client == NULL) ? NULL : (self->priv->client = (g_object_unref (self->priv->client), NULL));
	(self->priv->current == NULL) ? NULL : (self->priv->current = (g_object_unref (self->priv->current), NULL));
	G_OBJECT_CLASS (epr_parent_class)->finalize (obj);
}


GType epr_get_type (void) {
	static GType epr_type_id = 0;
	if (epr_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (EprClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) epr_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (Epr), 0, (GInstanceInitFunc) epr_instance_init, NULL };
		epr_type_id = g_type_register_static (G_TYPE_OBJECT, "Epr", &g_define_type_info, 0);
	}
	return epr_type_id;
}


static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	if ((array != NULL) && (destroy_func != NULL)) {
		int i;
		for (i = 0; i < array_length; i = i + 1) {
			if (((gpointer*) array)[i] != NULL) {
				destroy_func (((gpointer*) array)[i]);
			}
		}
	}
}


static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	_vala_array_destroy (array, array_length, destroy_func);
	g_free (array);
}


static gint _vala_array_length (gpointer array) {
	int length;
	length = 0;
	if (array) {
		while (((gpointer*) array)[length]) {
			length++;
		}
	}
	return length;
}


static int _vala_strcmp0 (const char * str1, const char * str2) {
	if (str1 == NULL) {
		return -(str1 != str2);
	}
	if (str2 == NULL) {
		return str1 != str2;
	}
	return strcmp (str1, str2);
}




