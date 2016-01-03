
#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <dbus/dbus-glib-lowlevel.h>
#include <dbus/dbus-glib.h>
#include <epris-external.h>
#include <gst/gst.h>
#include <stdio.h>
#include <config.h>
#include <dbus/dbus.h>


#define EPRIS_TYPE_PROPERTIES_NOTIFY (epris_properties_notify_get_type ())
#define EPRIS_PROPERTIES_NOTIFY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), EPRIS_TYPE_PROPERTIES_NOTIFY, EprisPropertiesNotify))
#define EPRIS_PROPERTIES_NOTIFY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), EPRIS_TYPE_PROPERTIES_NOTIFY, EprisPropertiesNotifyClass))
#define EPRIS_IS_PROPERTIES_NOTIFY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), EPRIS_TYPE_PROPERTIES_NOTIFY))
#define EPRIS_IS_PROPERTIES_NOTIFY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), EPRIS_TYPE_PROPERTIES_NOTIFY))
#define EPRIS_PROPERTIES_NOTIFY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), EPRIS_TYPE_PROPERTIES_NOTIFY, EprisPropertiesNotifyClass))

typedef struct _EprisPropertiesNotify EprisPropertiesNotify;
typedef struct _EprisPropertiesNotifyClass EprisPropertiesNotifyClass;
typedef struct _EprisPropertiesNotifyPrivate EprisPropertiesNotifyPrivate;

#define EPRIS_TYPE_SERVICE (epris_service_get_type ())
#define EPRIS_SERVICE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), EPRIS_TYPE_SERVICE, EprisService))
#define EPRIS_SERVICE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), EPRIS_TYPE_SERVICE, EprisServiceClass))
#define EPRIS_IS_SERVICE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), EPRIS_TYPE_SERVICE))
#define EPRIS_IS_SERVICE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), EPRIS_TYPE_SERVICE))
#define EPRIS_SERVICE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), EPRIS_TYPE_SERVICE, EprisServiceClass))

typedef struct _EprisService EprisService;
typedef struct _EprisServiceClass EprisServiceClass;
typedef struct _EprisServicePrivate EprisServicePrivate;

#define EPRIS_TYPE_FORMAT (epris_format_get_type ())

#define TYPE_SERVICE (service_get_type ())
#define SERVICE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_SERVICE, Service))
#define SERVICE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_SERVICE, ServiceClass))
#define IS_SERVICE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_SERVICE))
#define IS_SERVICE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_SERVICE))
#define SERVICE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_SERVICE, ServiceClass))

typedef struct _Service Service;
typedef struct _ServiceClass ServiceClass;
typedef struct _ServicePrivate ServicePrivate;

#define TYPE_AUDIO_PLAYER (audio_player_get_type ())
#define AUDIO_PLAYER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_AUDIO_PLAYER, AudioPlayer))
#define AUDIO_PLAYER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_AUDIO_PLAYER, AudioPlayerClass))
#define IS_AUDIO_PLAYER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_AUDIO_PLAYER))
#define IS_AUDIO_PLAYER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_AUDIO_PLAYER))
#define AUDIO_PLAYER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_AUDIO_PLAYER, AudioPlayerClass))

typedef struct _AudioPlayer AudioPlayer;
typedef struct _AudioPlayerClass AudioPlayerClass;

#define EPRIS_TYPE_TRACK_LIST_TRICK (epris_track_list_trick_get_type ())
#define EPRIS_TRACK_LIST_TRICK(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), EPRIS_TYPE_TRACK_LIST_TRICK, EprisTrackListTrick))
#define EPRIS_TRACK_LIST_TRICK_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), EPRIS_TYPE_TRACK_LIST_TRICK, EprisTrackListTrickClass))
#define EPRIS_IS_TRACK_LIST_TRICK(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), EPRIS_TYPE_TRACK_LIST_TRICK))
#define EPRIS_IS_TRACK_LIST_TRICK_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), EPRIS_TYPE_TRACK_LIST_TRICK))
#define EPRIS_TRACK_LIST_TRICK_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), EPRIS_TYPE_TRACK_LIST_TRICK, EprisTrackListTrickClass))

typedef struct _EprisTrackListTrick EprisTrackListTrick;
typedef struct _EprisTrackListTrickClass EprisTrackListTrickClass;

#define EPRIS_TYPE_TRACK_LIST (epris_track_list_get_type ())
#define EPRIS_TRACK_LIST(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), EPRIS_TYPE_TRACK_LIST, EprisTrackList))
#define EPRIS_TRACK_LIST_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), EPRIS_TYPE_TRACK_LIST, EprisTrackListClass))
#define EPRIS_IS_TRACK_LIST(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), EPRIS_TYPE_TRACK_LIST))
#define EPRIS_IS_TRACK_LIST_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), EPRIS_TYPE_TRACK_LIST))
#define EPRIS_TRACK_LIST_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), EPRIS_TYPE_TRACK_LIST, EprisTrackListClass))

typedef struct _EprisTrackList EprisTrackList;
typedef struct _EprisTrackListClass EprisTrackListClass;

#define TYPE_TRACK_LIST (track_list_get_type ())
#define TRACK_LIST(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_TRACK_LIST, TrackList))
#define TRACK_LIST_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_TRACK_LIST, TrackListClass))
#define IS_TRACK_LIST(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_TRACK_LIST))
#define IS_TRACK_LIST_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_TRACK_LIST))
#define TRACK_LIST_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_TRACK_LIST, TrackListClass))

typedef struct _TrackList TrackList;
typedef struct _TrackListClass TrackListClass;
typedef struct _EprisTrackListTrickPrivate EprisTrackListTrickPrivate;

#define TRACK_LIST_TYPE_TRACK (track_list_track_get_type ())
#define TRACK_LIST_TRACK(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TRACK_LIST_TYPE_TRACK, TrackListTrack))
#define TRACK_LIST_TRACK_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TRACK_LIST_TYPE_TRACK, TrackListTrackClass))
#define TRACK_LIST_IS_TRACK(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TRACK_LIST_TYPE_TRACK))
#define TRACK_LIST_IS_TRACK_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TRACK_LIST_TYPE_TRACK))
#define TRACK_LIST_TRACK_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TRACK_LIST_TYPE_TRACK, TrackListTrackClass))

typedef struct _TrackListTrack TrackListTrack;
typedef struct _TrackListTrackClass TrackListTrackClass;
typedef struct _TrackListTrackPrivate TrackListTrackPrivate;

#define EPRIS_TYPE_WHENCE (epris_whence_get_type ())

#define EPRIS_TYPE_STATE (epris_state_get_type ())
typedef struct _DBusObjectVTable _DBusObjectVTable;

struct _EprisPropertiesNotify {
	GObject parent_instance;
	EprisPropertiesNotifyPrivate * priv;
};

struct _EprisPropertiesNotifyClass {
	GObjectClass parent_class;
};

typedef enum  {
	EPRIS_ERROR_NONE,
	EPRIS_ERROR_NOT_SUPPORTED,
	EPRIS_ERROR_STATE,
	EPRIS_ERROR_ARGUMENT
} EprisError;
#define EPRIS_ERROR epris_error_quark ()
typedef enum  {
	EPRIS_FORMAT_UNDEFINED,
	EPRIS_FORMAT_DEFAULT,
	EPRIS_FORMAT_BYTES,
	EPRIS_FORMAT_TIME,
	EPRIS_FORMAT_BUFFERS,
	EPRIS_FORMAT_PERCENT
} EprisFormat;

struct _EprisService {
	EprisPropertiesNotify parent_instance;
	EprisServicePrivate * priv;
};

struct _EprisServiceClass {
	EprisPropertiesNotifyClass parent_class;
	void (*Play) (EprisService* self, GError** error);
	void (*Stop) (EprisService* self, GError** error);
	void (*Seek) (EprisService* self, EprisFormat format, gint64 position, GError** error);
};

struct _Service {
	EprisService parent_instance;
	ServicePrivate * priv;
	GMainLoop* loop;
	AudioPlayer* player;
	GHashTable* tracklists;
	TrackList* current_tracklist;
	GKeyFile* config;
	char* config_file;
	char* data_dir;
};

struct _ServiceClass {
	EprisServiceClass parent_class;
};

struct _ServicePrivate {
	DBusGConnection* _connection;
	guint timeout_quit_id;
	gint rv;
};

struct _EprisTrackListTrick {
	EprisPropertiesNotify parent_instance;
	EprisTrackListTrickPrivate * priv;
	GHashTable* _current;
};

struct _EprisTrackListTrickClass {
	EprisPropertiesNotifyClass parent_class;
};

struct _TrackListTrack {
	GTypeInstance parent_instance;
	volatile int ref_count;
	TrackListTrackPrivate * priv;
	char* uri;
};

struct _TrackListTrackClass {
	GTypeClass parent_class;
	void (*finalize) (TrackListTrack *self);
};

typedef enum  {
	EPRIS_WHENCE_START,
	EPRIS_WHENCE_CURRENT,
	EPRIS_WHENCE_END
} EprisWhence;

typedef enum  {
	EPRIS_STATE_STOPPED,
	EPRIS_STATE_PAUSED,
	EPRIS_STATE_PLAYING
} EprisState;

struct _DBusObjectVTable {
	void (*register_object) (DBusConnection*, const char*, void*);
};



GType epris_properties_notify_get_type (void);
GType epris_service_get_type (void);
GQuark epris_error_quark (void);
GType epris_format_get_type (void);
GType service_get_type (void);
GType audio_player_get_type (void);
GType epris_track_list_trick_get_type (void);
GType epris_track_list_get_type (void);
GType track_list_get_type (void);
#define SERVICE_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_SERVICE, ServicePrivate))
enum  {
	SERVICE_DUMMY_PROPERTY,
	SERVICE_CONNECTION
};
static gint service_timeout_quit;
static gint service_timeout_quit = 5;
static gboolean service_opversion;
static gboolean service_opversion = FALSE;
void service_set_connection (Service* self, DBusGConnection* value);
AudioPlayer* audio_player_new (void);
AudioPlayer* audio_player_construct (GType object_type);
static void service_audio_player_about_to_finish (Service* self);
static void _service_audio_player_about_to_finish_audio_player_about_to_finish (AudioPlayer* _sender, gpointer self);
GstTagList* audio_player_get_taglist (AudioPlayer* self);
static GValue* _g_value_dup (GValue* self);
gboolean epris_type_is_glib_dbus (GType t);
static void _lambda4_ (GstTagList* tl, const char* tag, Service* self);
static void __lambda4__gst_tag_foreach_func (GstTagList* list, const char* tag, gpointer self);
static void _lambda3_ (AudioPlayer* s, GParamSpec* p, Service* self);
static void __lambda3__g_object_notify (AudioPlayer* _sender, GParamSpec* pspec, gpointer self);
Service* service_new (DBusGConnection* connection);
Service* service_construct (GType object_type, DBusGConnection* connection);
Service* service_new (DBusGConnection* connection);
TrackList* track_list_new (const char* path);
TrackList* track_list_construct (GType object_type, const char* path);
gboolean track_list_load (TrackList* self);
gpointer track_list_track_ref (gpointer instance);
void track_list_track_unref (gpointer instance);
GParamSpec* track_list_param_spec_track (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void track_list_value_set_track (GValue* value, gpointer v_object);
gpointer track_list_value_get_track (const GValue* value);
GType track_list_track_get_type (void);
TrackListTrack* track_list_get_current_track (TrackList* self);
void audio_player_request_location (AudioPlayer* self, const char* location, gboolean immediately);
static void _lambda5_ (TrackList* s, GParamSpec* p, Service* self);
static void __lambda5__g_object_notify (TrackList* _sender, GParamSpec* pspec, gpointer self);
gint64 audio_player_get_duration (AudioPlayer* self);
gint64 audio_player_get_position (AudioPlayer* self);
static void _lambda6_ (Service* self);
static void __lambda6__epris_track_list_trick_update_current (TrackList* _sender, gpointer self);
DBusGConnection* service_get_connection (Service* self);
gboolean service_set_current_tracklist_by_name (Service* self, const char* name, GError** error);
GType epris_whence_get_type (void);
TrackListTrack* track_list_seek (TrackList* self, gint offset, EprisWhence whence, GError** error);
GType epris_state_get_type (void);
void audio_player_request_state (AudioPlayer* self, EprisState state);
void epris_service_set_State (EprisService* self, EprisState value);
static void service_set_idle (Service* self, gboolean value);
static void service_real_Play (EprisService* base, GError** error);
void audio_player_request_seek (AudioPlayer* self, GstFormat format, gint64 position);
static void service_real_Seek (EprisService* base, EprisFormat format, gint64 position, GError** error);
static gboolean _service_quit_cb (Service* self);
static void service_real_Stop (EprisService* base, GError** error);
gboolean epris_request_name (DBusGConnection* conn, const char* name);
static gboolean service_register (Service* self);
gint service_run (Service* self);
static void _epris_log_handler_glog_func (const char* log_domain, GLogLevelFlags log_levels, const char* message, gpointer self);
static gint service_main (char** args, int args_length1);
static gboolean __service_quit_cb_gsource_func (gpointer self);
static gpointer service_parent_class = NULL;
void service_dbus_register_object (DBusConnection* connection, const char* path, void* object);
void _service_dbus_unregister (DBusConnection* connection, void* user_data);
DBusHandlerResult service_dbus_message (DBusConnection* connection, DBusMessage* message, void* object);
static DBusMessage* _dbus_service_introspect (Service* self, DBusConnection* connection, DBusMessage* message);
static void service_finalize (GObject* obj);
static void service_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void service_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);
static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);
static int _vala_strcmp0 (const char * str1, const char * str2);
static void _vala_dbus_register_object (DBusConnection* connection, const char* path, void* object);
static void _vala_dbus_unregister_object (gpointer connection, GObject* object);

static const GOptionEntry SERVICE_main_options[] = {{"version", (gchar) 0, 0, G_OPTION_ARG_NONE, &service_opversion, "Display version number", NULL}, {"debug-level", (gchar) 0, 0, G_OPTION_ARG_INT, &epris_debug_level, "Debug level (1-5)", "INT"}, {"idle", 'i', 0, G_OPTION_ARG_INT, &service_timeout_quit, "Exit when idle (-1 = no timeout)", "SECS"}, {NULL}};
static const DBusObjectPathVTable _service_dbus_path_vtable = {_service_dbus_unregister, service_dbus_message};
static const _DBusObjectVTable _service_dbus_vtable = {service_dbus_register_object};


static void _service_audio_player_about_to_finish_audio_player_about_to_finish (AudioPlayer* _sender, gpointer self) {
	service_audio_player_about_to_finish (self);
}


static GValue* _g_value_dup (GValue* self) {
	return g_boxed_copy (G_TYPE_VALUE, self);
}


static void _lambda4_ (GstTagList* tl, const char* tag, Service* self) {
	GValue* _tmp0_;
	GValue* value;
	char* _tmp1_;
	g_return_if_fail (tl != NULL);
	g_return_if_fail (tag != NULL);
	_tmp0_ = NULL;
	value = (_tmp0_ = (GValue*) gst_structure_get_value ((const GstStructure*) tl, tag), (_tmp0_ == NULL) ? NULL : _g_value_dup (_tmp0_));
	_tmp1_ = NULL;
	g_debug ("epris.vala:50: %s %s", tag, _tmp1_ = g_strdup_value_contents (value));
	_tmp1_ = (g_free (_tmp1_), NULL);
	if (epris_type_is_glib_dbus (G_VALUE_TYPE (value))) {
		GValue _tmp2_ = {0};
		GValue copy;
		GValue* _tmp4_;
		const char* _tmp3_;
		copy = (g_value_init (&_tmp2_, G_VALUE_TYPE (value)), _tmp2_);
		g_value_copy (value, &copy);
		_tmp4_ = NULL;
		_tmp3_ = NULL;
		g_hash_table_replace (((EprisTrackListTrick*) self->current_tracklist)->_current, (_tmp3_ = tag, (_tmp3_ == NULL) ? NULL : g_strdup (_tmp3_)), (_tmp4_ = &copy, (_tmp4_ == NULL) ? NULL : _g_value_dup (_tmp4_)));
		G_IS_VALUE (&copy) ? (g_value_unset (&copy), NULL) : NULL;
	} else {
		GValue _tmp5_ = {0};
		GValue copy;
		GValue _tmp8_ = {0};
		GValue _tmp7_ = {0};
		char* _tmp6_;
		GValue* _tmp10_;
		const char* _tmp9_;
		/* current_tracklist.current.insert (tag, value.strdup_contents ()); <- mising g_value_dup*/
		copy = (g_value_init (&_tmp5_, G_TYPE_STRING), _tmp5_);
		_tmp6_ = NULL;
		copy = (_tmp8_ = (g_value_init (&_tmp7_, G_TYPE_STRING), g_value_set_string (&_tmp7_, _tmp6_ = g_strdup_value_contents (value)), _tmp7_), G_IS_VALUE (&copy) ? (g_value_unset (&copy), NULL) : NULL, _tmp8_);
		_tmp6_ = (g_free (_tmp6_), NULL);
		_tmp10_ = NULL;
		_tmp9_ = NULL;
		g_hash_table_replace (((EprisTrackListTrick*) self->current_tracklist)->_current, (_tmp9_ = tag, (_tmp9_ == NULL) ? NULL : g_strdup (_tmp9_)), (_tmp10_ = &copy, (_tmp10_ == NULL) ? NULL : _g_value_dup (_tmp10_)));
		G_IS_VALUE (&copy) ? (g_value_unset (&copy), NULL) : NULL;
	}
	(value == NULL) ? NULL : (value = (g_free (value), NULL));
}


static void __lambda4__gst_tag_foreach_func (GstTagList* list, const char* tag, gpointer self) {
	_lambda4_ (list, tag, self);
}


static void _lambda3_ (AudioPlayer* s, GParamSpec* p, Service* self) {
	g_return_if_fail (s != NULL);
	g_return_if_fail (p != NULL);
	/* STATE*/
	if (_vala_strcmp0 (p->name, "state") == 0) {
	} else {
		if (_vala_strcmp0 (p->name, "taglist") == 0) {
			if (audio_player_get_taglist (self->player) == NULL) {
				return;
			}
			gst_tag_list_foreach (audio_player_get_taglist (self->player), __lambda4__gst_tag_foreach_func, self);
		}
	}
}


static void __lambda3__g_object_notify (AudioPlayer* _sender, GParamSpec* pspec, gpointer self) {
	_lambda3_ (_sender, pspec, self);
}


Service* service_construct (GType object_type, DBusGConnection* connection) {
	GError * _inner_error_;
	GParameter * __params;
	GParameter * __params_it;
	Service * self;
	GMainLoop* _tmp0_;
	AudioPlayer* _tmp1_;
	GHashTable* _tmp2_;
	GKeyFile* _tmp3_;
	char* _tmp4_;
	char** _tmp7_;
	gint s_size;
	gint s_length1;
	char** _tmp6_;
	const char* _tmp5_;
	char** s;
	g_return_val_if_fail (connection != NULL, NULL);
	_inner_error_ = NULL;
	__params = g_new0 (GParameter, 1);
	__params_it = __params;
	__params_it->name = "connection";
	g_value_init (&__params_it->value, G_TYPE_POINTER);
	g_value_set_pointer (&__params_it->value, connection);
	__params_it++;
	self = g_object_newv (object_type, __params_it - __params, __params);
	self->priv->rv = 0;
	_tmp0_ = NULL;
	self->loop = (_tmp0_ = g_main_loop_new (NULL, FALSE), (self->loop == NULL) ? NULL : (self->loop = (g_main_loop_unref (self->loop), NULL)), _tmp0_);
	_tmp1_ = NULL;
	self->player = (_tmp1_ = audio_player_new (), (self->player == NULL) ? NULL : (self->player = (g_object_unref (self->player), NULL)), _tmp1_);
	g_signal_connect_object (self->player, "about-to-finish", (GCallback) _service_audio_player_about_to_finish_audio_player_about_to_finish, self, 0);
	_tmp2_ = NULL;
	self->tracklists = (_tmp2_ = g_hash_table_new (g_str_hash, g_str_equal), (self->tracklists == NULL) ? NULL : (self->tracklists = (g_hash_table_unref (self->tracklists), NULL)), _tmp2_);
	g_signal_connect ((GObject*) self->player, "notify", (GCallback) __lambda3__g_object_notify, self);
	_tmp3_ = NULL;
	self->config = (_tmp3_ = g_key_file_new (), (self->config == NULL) ? NULL : (self->config = (g_key_file_free (self->config), NULL)), _tmp3_);
	_tmp4_ = NULL;
	self->data_dir = (_tmp4_ = g_build_filename (g_get_user_data_dir (), "epris", NULL), self->data_dir = (g_free (self->data_dir), NULL), _tmp4_);
	_tmp7_ = NULL;
	_tmp6_ = NULL;
	_tmp5_ = NULL;
	s = (_tmp7_ = (_tmp6_ = g_new0 (char*, 1 + 1), _tmp6_[0] = (_tmp5_ = g_get_user_config_dir (), (_tmp5_ == NULL) ? NULL : g_strdup (_tmp5_)), _tmp6_), s_length1 = 1, s_size = s_length1, _tmp7_);
	{
		char* _tmp10_;
		gboolean _tmp9_;
		char* _tmp8_;
		_tmp10_ = NULL;
		_tmp8_ = NULL;
		_tmp9_ = g_key_file_load_from_dirs (self->config, "epris", s, &_tmp8_, G_KEY_FILE_KEEP_COMMENTS | G_KEY_FILE_KEEP_TRANSLATIONS, &_inner_error_);
		self->config_file = (_tmp10_ = _tmp8_, self->config_file = (g_free (self->config_file), NULL), _tmp10_);
		_tmp9_;
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == G_KEY_FILE_ERROR) {
				goto __catch6_g_key_file_error;
			}
			goto __finally6;
		}
	}
	goto __finally6;
	__catch6_g_key_file_error:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		{
			g_warning ("epris.vala:76: %s (while loading config)", _error_->message);
			(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
		}
	}
	__finally6:
	if (_inner_error_ != NULL) {
		s = (_vala_array_free (s, s_length1, (GDestroyNotify) g_free), NULL);
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return NULL;
	}
	if (self->config_file == NULL) {
		char* _tmp11_;
		_tmp11_ = NULL;
		self->config_file = (_tmp11_ = g_build_filename (g_get_user_config_dir (), "epris", NULL), self->config_file = (g_free (self->config_file), NULL), _tmp11_);
	}
	s = (_vala_array_free (s, s_length1, (GDestroyNotify) g_free), NULL);
	while (__params_it > __params) {
		--__params_it;
		g_value_unset (&__params_it->value);
	}
	g_free (__params);
	return self;
}


Service* service_new (DBusGConnection* connection) {
	return service_construct (TYPE_SERVICE, connection);
}


static void _lambda5_ (TrackList* s, GParamSpec* p, Service* self) {
	g_return_if_fail (s != NULL);
	g_return_if_fail (p != NULL);
	/* CURRENT TRACK*/
	if (_vala_strcmp0 (p->name, "current-track") == 0) {
		if (track_list_get_current_track (self->current_tracklist) == NULL) {
			return;
		}
		g_debug ("epris.vala:113: Current track changed %s", track_list_get_current_track (self->current_tracklist)->uri);
		audio_player_request_location (self->player, track_list_get_current_track (self->current_tracklist)->uri, TRUE);
	}
}


static void __lambda5__g_object_notify (TrackList* _sender, GParamSpec* pspec, gpointer self) {
	_lambda5_ (_sender, pspec, self);
}


static void _lambda6_ (Service* self) {
	GValue _tmp0_ = {0};
	GValue d;
	GValue* _tmp1_;
	GValue* _tmp2_;
	g_message ("epris.vala:119: update current position..");
	d = (g_value_init (&_tmp0_, G_TYPE_INT64), _tmp0_);
	g_value_set_int64 (&d, audio_player_get_duration (self->player));
	_tmp1_ = NULL;
	g_hash_table_replace (((EprisTrackListTrick*) self->current_tracklist)->_current, g_strdup ("x-duration"), (_tmp1_ = &d, (_tmp1_ == NULL) ? NULL : _g_value_dup (_tmp1_)));
	g_value_set_int64 (&d, audio_player_get_position (self->player));
	_tmp2_ = NULL;
	g_hash_table_replace (((EprisTrackListTrick*) self->current_tracklist)->_current, g_strdup ("x-position"), (_tmp2_ = &d, (_tmp2_ == NULL) ? NULL : _g_value_dup (_tmp2_)));
	G_IS_VALUE (&d) ? (g_value_unset (&d), NULL) : NULL;
}


static void __lambda6__epris_track_list_trick_update_current (TrackList* _sender, gpointer self) {
	_lambda6_ (self);
}


gboolean service_set_current_tracklist_by_name (Service* self, const char* name, GError** error) {
	gboolean result;
	TrackList* _tmp1_;
	TrackList* _tmp0_;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (name != NULL, FALSE);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	self->current_tracklist = (_tmp1_ = (_tmp0_ = (TrackList*) g_hash_table_lookup (self->tracklists, name), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_)), (self->current_tracklist == NULL) ? NULL : (self->current_tracklist = (g_object_unref (self->current_tracklist), NULL)), _tmp1_);
	if (self->current_tracklist == NULL) {
		TrackList* _tmp3_;
		char* _tmp2_;
		_tmp3_ = NULL;
		_tmp2_ = NULL;
		self->current_tracklist = (_tmp3_ = track_list_new (_tmp2_ = g_build_filename (self->data_dir, "lists", name, NULL)), (self->current_tracklist == NULL) ? NULL : (self->current_tracklist = (g_object_unref (self->current_tracklist), NULL)), _tmp3_);
		_tmp2_ = (g_free (_tmp2_), NULL);
		track_list_load (self->current_tracklist);
	}
	g_signal_connect ((GObject*) self->current_tracklist, "notify", (GCallback) __lambda5__g_object_notify, self);
	g_signal_connect ((EprisTrackListTrick*) self->current_tracklist, "update-current", (GCallback) __lambda6__epris_track_list_trick_update_current, self);
	_vala_dbus_register_object (dbus_g_connection_get_connection (self->priv->_connection), "/org/mpris/epris/lists/current", (GObject*) self->current_tracklist);
	result = TRUE;
	return result;
}


static void service_audio_player_about_to_finish (Service* self) {
	GError * _inner_error_;
	g_return_if_fail (self != NULL);
	_inner_error_ = NULL;
	g_debug ("epris.vala:135: about-to-finish");
	{
		TrackListTrack* t;
		t = track_list_seek (self->current_tracklist, +1, EPRIS_WHENCE_CURRENT, &_inner_error_);
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == EPRIS_ERROR) {
				goto __catch7_epris_error;
			}
			goto __finally7;
		}
		if (t == NULL) {
			(t == NULL) ? NULL : (t = (track_list_track_unref (t), NULL));
			return;
		}
		audio_player_request_location (self->player, t->uri, FALSE);
		(t == NULL) ? NULL : (t = (track_list_track_unref (t), NULL));
	}
	goto __finally7;
	__catch7_epris_error:
	{
		GError * err;
		err = _inner_error_;
		_inner_error_ = NULL;
		{
			g_message ("epris.vala:142: End of list, or list empty: %s", err->message);
			(err == NULL) ? NULL : (err = (g_error_free (err), NULL));
		}
	}
	__finally7:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return;
	}
}


static void service_real_Play (EprisService* base, GError** error) {
	Service * self;
	GError * _inner_error_;
	TrackListTrack* _tmp0_;
	self = (Service*) base;
	_inner_error_ = NULL;
	g_message ("epris.vala:147: let's pump up the speakers!");
	_tmp0_ = NULL;
	_tmp0_ = track_list_seek (self->current_tracklist, 0, EPRIS_WHENCE_CURRENT, &_inner_error_);
	if (_inner_error_ != NULL) {
		if (_inner_error_->domain == EPRIS_ERROR) {
			g_propagate_error (error, _inner_error_);
			return;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
			g_clear_error (&_inner_error_);
			return;
		}
	}
	(_tmp0_ == NULL) ? NULL : (_tmp0_ = (track_list_track_unref (_tmp0_), NULL));
	if (track_list_get_current_track (self->current_tracklist) == NULL) {
		return;
	}
	audio_player_request_state (self->player, EPRIS_STATE_PLAYING);
	epris_service_set_State ((EprisService*) self, EPRIS_STATE_PLAYING);
	service_set_idle (self, FALSE);
}


static void service_real_Seek (EprisService* base, EprisFormat format, gint64 position, GError** error) {
	Service * self;
	char* _tmp4_;
	char* _tmp3_;
	char* _tmp2_;
	char* _tmp1_;
	char* _tmp0_;
	self = (Service*) base;
	_tmp4_ = NULL;
	_tmp3_ = NULL;
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	g_message (_tmp4_ = g_strconcat (_tmp2_ = g_strconcat (_tmp1_ = g_strconcat ("I like to move it, move it! ", _tmp0_ = g_strdup_printf ("%i", (gint) format), NULL), " ", NULL), _tmp3_ = g_strdup_printf ("%lli", position), NULL));
	_tmp4_ = (g_free (_tmp4_), NULL);
	_tmp3_ = (g_free (_tmp3_), NULL);
	_tmp2_ = (g_free (_tmp2_), NULL);
	_tmp1_ = (g_free (_tmp1_), NULL);
	_tmp0_ = (g_free (_tmp0_), NULL);
	audio_player_request_seek (self->player, (GstFormat) format, position);
}


static gboolean _service_quit_cb (Service* self) {
	gboolean result;
	g_return_val_if_fail (self != NULL, FALSE);
	g_message ("epris.vala:165: That was a pleasant time, take care");
	g_main_loop_quit (self->loop);
	result = FALSE;
	return result;
}


static void service_real_Stop (EprisService* base, GError** error) {
	Service * self;
	self = (Service*) base;
	g_message ("epris.vala:173: Nothing strengthens authority so much as silence.");
	audio_player_request_state (self->player, EPRIS_STATE_STOPPED);
	epris_service_set_State ((EprisService*) self, EPRIS_STATE_STOPPED);
	service_set_idle (self, TRUE);
}


static gboolean service_register (Service* self) {
	gboolean result;
	g_return_val_if_fail (self != NULL, FALSE);
	if (epris_request_name (self->priv->_connection, "org.mpris.epris") == TRUE) {
		_vala_dbus_register_object (dbus_g_connection_get_connection (self->priv->_connection), "/org/mpris/epris", (GObject*) self);
		/* TODO: namespace object path*/
		result = TRUE;
		return result;
	}
	result = FALSE;
	return result;
}


gint service_run (Service* self) {
	gint result;
	GError * _inner_error_;
	g_return_val_if_fail (self != NULL, 0);
	_inner_error_ = NULL;
	if (service_register (self) == FALSE) {
		g_message ("epris.vala:194: Cannot request name, exiting");
		result = 0;
		return result;
	}
	{
		char* tl;
		tl = g_key_file_get_string (self->config, "General", "tracklist", &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch8_g_error;
			goto __finally8;
		}
		service_set_current_tracklist_by_name (self, tl, &_inner_error_);
		if (_inner_error_ != NULL) {
			tl = (g_free (tl), NULL);
			goto __catch8_g_error;
			goto __finally8;
		}
		tl = (g_free (tl), NULL);
	}
	goto __finally8;
	__catch8_g_error:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		{
			GTimeVal _tmp0_ = {0};
			GTimeVal time;
			GDate _tmp1_ = {0};
			GDate date;
			gchar* _tmp2_;
			gint s_size;
			gint s_length1;
			gchar* s;
			time = (g_get_current_time (&_tmp0_), _tmp0_);
			date = (memset (&_tmp1_, 0, sizeof (GDate)), _tmp1_);
			g_warning (_error_->message);
			g_get_current_time (&time);
			g_date_set_time_val (&date, &time);
			_tmp2_ = NULL;
			s = (_tmp2_ = g_new0 (gchar, 20), s_length1 = 20, s_size = s_length1, _tmp2_);
			g_date_strftime (s, s_length1, "%Y-%m-%d", &date);
			{
				service_set_current_tracklist_by_name (self, (const char*) s, &_inner_error_);
				if (_inner_error_ != NULL) {
					goto __catch9_g_error;
					goto __finally9;
				}
			}
			goto __finally9;
			__catch9_g_error:
			{
				GError * e;
				e = _inner_error_;
				_inner_error_ = NULL;
				{
					g_critical (e->message);
					self->priv->rv = 1;
					(e == NULL) ? NULL : (e = (g_error_free (e), NULL));
				}
			}
			__finally9:
			if (_inner_error_ != NULL) {
				(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
				s = (g_free (s), NULL);
				g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
				g_clear_error (&_inner_error_);
				return 0;
			}
			(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
			s = (g_free (s), NULL);
		}
	}
	__finally8:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return 0;
	}
	g_main_loop_run (self->loop);
	audio_player_request_state (self->player, EPRIS_STATE_STOPPED);
	result = self->priv->rv;
	return result;
}


static void _epris_log_handler_glog_func (const char* log_domain, GLogLevelFlags log_levels, const char* message, gpointer self) {
	epris_log_handler (log_domain, log_levels, message);
}


static gint service_main (char** args, int args_length1) {
	gint result;
	GError * _inner_error_;
	Service* epris;
	GOptionContext* opt_context;
	DBusGConnection* _tmp0_;
	Service* _tmp2_;
	DBusGConnection* _tmp1_;
	_inner_error_ = NULL;
	epris = NULL;
	g_log_set_default_handler (_epris_log_handler_glog_func, NULL);
	opt_context = g_option_context_new ("- Epris audio player service");
	g_option_context_set_help_enabled (opt_context, TRUE);
	g_option_context_add_main_entries (opt_context, SERVICE_main_options, NULL);
	g_option_context_add_group (opt_context, gst_init_get_option_group ());
	{
		g_option_context_parse (opt_context, &args_length1, &args, &_inner_error_);
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == G_OPTION_ERROR) {
				goto __catch10_g_option_error;
			}
			goto __finally10;
		}
	}
	goto __finally10;
	__catch10_g_option_error:
	{
		GError * e;
		e = _inner_error_;
		_inner_error_ = NULL;
		{
			fprintf (stdout, "%s\n", e->message);
			fprintf (stdout, "Run '%s --help' to see a full list of available command line options.\n", g_get_prgname ());
			result = 1;
			(e == NULL) ? NULL : (e = (g_error_free (e), NULL));
			(epris == NULL) ? NULL : (epris = (g_object_unref (epris), NULL));
			(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
			return result;
		}
	}
	__finally10:
	if (_inner_error_ != NULL) {
		(epris == NULL) ? NULL : (epris = (g_object_unref (epris), NULL));
		(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return 0;
	}
	if (service_opversion) {
		fprintf (stdout, "Epris %s\n", PACKAGE_VERSION);
		result = 0;
		(epris == NULL) ? NULL : (epris = (g_object_unref (epris), NULL));
		(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
		return result;
	}
	_tmp0_ = dbus_g_bus_get (DBUS_BUS_SESSION, &_inner_error_);
	if (_inner_error_ != NULL) {
		(epris == NULL) ? NULL : (epris = (g_object_unref (epris), NULL));
		(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return 0;
	}
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	epris = (_tmp2_ = service_new (_tmp1_ = _tmp0_), (epris == NULL) ? NULL : (epris = (g_object_unref (epris), NULL)), _tmp2_);
	(_tmp1_ == NULL) ? NULL : (_tmp1_ = (dbus_g_connection_unref (_tmp1_), NULL));
	g_message ("epris.vala:259: Using %s config file", epris->config_file);
	g_message ("epris.vala:260: And %s data dir", epris->data_dir);
	result = service_run (epris);
	(epris == NULL) ? NULL : (epris = (g_object_unref (epris), NULL));
	(opt_context == NULL) ? NULL : (opt_context = (g_option_context_free (opt_context), NULL));
	return result;
}


int main (int argc, char ** argv) {
	g_thread_init (NULL);
	g_type_init ();
	return service_main (argv, argc);
}


DBusGConnection* service_get_connection (Service* self) {
	DBusGConnection* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_connection;
	return result;
}


void service_set_connection (Service* self, DBusGConnection* value) {
	DBusGConnection* _tmp1_;
	DBusGConnection* _tmp0_;
	g_return_if_fail (self != NULL);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	self->priv->_connection = (_tmp1_ = (_tmp0_ = value, (_tmp0_ == NULL) ? NULL : dbus_g_connection_ref (_tmp0_)), (self->priv->_connection == NULL) ? NULL : (self->priv->_connection = (dbus_g_connection_unref (self->priv->_connection), NULL)), _tmp1_);
	g_object_notify ((GObject *) self, "connection");
}


static char* bool_to_string (gboolean self) {
	char* result;
	if (self) {
		result = g_strdup ("true");
		return result;
	} else {
		result = g_strdup ("false");
		return result;
	}
}


static gboolean __service_quit_cb_gsource_func (gpointer self) {
	return _service_quit_cb (self);
}


static void service_set_idle (Service* self, gboolean value) {
	char* _tmp0_;
	gboolean _tmp1_;
	gboolean _tmp2_;
	g_return_if_fail (self != NULL);
	_tmp0_ = NULL;
	g_message ("epris.vala:84: idle %s", _tmp0_ = bool_to_string (value));
	_tmp0_ = (g_free (_tmp0_), NULL);
	_tmp1_ = FALSE;
	if (self->priv->timeout_quit_id != 0) {
		_tmp1_ = value == FALSE;
	} else {
		_tmp1_ = FALSE;
	}
	if (_tmp1_) {
		g_source_remove (self->priv->timeout_quit_id);
		self->priv->timeout_quit_id = (guint) 0;
	}
	if (service_timeout_quit == (-1)) {
		return;
	}
	_tmp2_ = FALSE;
	if (self->priv->timeout_quit_id == 0) {
		_tmp2_ = value == TRUE;
	} else {
		_tmp2_ = FALSE;
	}
	if (_tmp2_) {
		self->priv->timeout_quit_id = g_timeout_add_seconds ((guint) service_timeout_quit, __service_quit_cb_gsource_func, self);
	}
}


void _service_dbus_unregister (DBusConnection* connection, void* user_data) {
}


static DBusMessage* _dbus_service_introspect (Service* self, DBusConnection* connection, DBusMessage* message) {
	DBusMessage* reply;
	DBusMessageIter iter;
	GString* xml_data;
	char** children;
	int i;
	reply = dbus_message_new_method_return (message);
	dbus_message_iter_init_append (reply, &iter);
	xml_data = g_string_new ("<!DOCTYPE node PUBLIC \"-//freedesktop//DTD D-BUS Object Introspection 1.0//EN\" \"http://www.freedesktop.org/standards/dbus/1.0/introspect.dtd\">\n");
	g_string_append (xml_data, "<node>\n<interface name=\"org.freedesktop.DBus.Introspectable\">\n  <method name=\"Introspect\">\n    <arg name=\"data\" direction=\"out\" type=\"s\"/>\n  </method>\n</interface>\n<interface name=\"org.freedesktop.DBus.Properties\">\n  <method name=\"Get\">\n    <arg name=\"interface\" direction=\"in\" type=\"s\"/>\n    <arg name=\"propname\" direction=\"in\" type=\"s\"/>\n    <arg name=\"value\" direction=\"out\" type=\"v\"/>\n  </method>\n  <method name=\"Set\">\n    <arg name=\"interface\" direction=\"in\" type=\"s\"/>\n    <arg name=\"propname\" direction=\"in\" type=\"s\"/>\n    <arg name=\"value\" direction=\"in\" type=\"v\"/>\n  </method>\n  <method name=\"GetAll\">\n    <arg name=\"interface\" direction=\"in\" type=\"s\"/>\n    <arg name=\"props\" direction=\"out\" type=\"a{sv}\"/>\n  </method>\n</interface>\n<interface name=\"org.freedesktop.DBus.Properties\">\n  <signal name=\"Changed\">\n    <arg name=\"interface_name\" type=\"s\"/>\n    <arg name=\"property_name\" type=\"s\"/>\n    <arg name=\"value\" type=\"v\"/>\n  </signal>\n</interface>\n<interface name=\"org.mpris.EprisPlayer\">\n  <method name=\"Play\">\n  </method>\n  <method name=\"Stop\">\n  </method>\n  <method name=\"Seek\">\n    <arg name=\"format\" type=\"i\" direction=\"in\"/>\n    <arg name=\"position\" type=\"x\" direction=\"in\"/>\n  </method>\n  <property name=\"Identity\" type=\"s\" access=\"readwrite\"/>\n  <property name=\"State\" type=\"i\" access=\"readwrite\"/>\n</interface>\n");
	dbus_connection_list_registered (connection, g_object_get_data ((GObject *) self, "dbus_object_path"), &children);
	for (i = 0; children[i]; i++) {
		g_string_append_printf (xml_data, "<node name=\"%s\"/>\n", children[i]);
	}
	dbus_free_string_array (children);
	g_string_append (xml_data, "</node>\n");
	dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &xml_data->str);
	g_string_free (xml_data, TRUE);
	return reply;
}


DBusHandlerResult service_dbus_message (DBusConnection* connection, DBusMessage* message, void* object) {
	DBusMessage* reply;
	reply = NULL;
	if (dbus_message_is_method_call (message, "org.freedesktop.DBus.Introspectable", "Introspect")) {
		reply = _dbus_service_introspect (object, connection, message);
	}
	if (reply) {
		dbus_connection_send (connection, reply, NULL);
		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	} else if (epris_service_dbus_message (connection, message, object) == DBUS_HANDLER_RESULT_HANDLED) {
		return DBUS_HANDLER_RESULT_HANDLED;
	} else {
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}
}


void service_dbus_register_object (DBusConnection* connection, const char* path, void* object) {
	if (!g_object_get_data (object, "dbus_object_path")) {
		g_object_set_data (object, "dbus_object_path", g_strdup (path));
		dbus_connection_register_object_path (connection, path, &_service_dbus_path_vtable, object);
		g_object_weak_ref (object, _vala_dbus_unregister_object, connection);
	}
	epris_service_dbus_register_object (connection, path, object);
}


static void service_class_init (ServiceClass * klass) {
	service_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (ServicePrivate));
	EPRIS_SERVICE_CLASS (klass)->Play = service_real_Play;
	EPRIS_SERVICE_CLASS (klass)->Seek = service_real_Seek;
	EPRIS_SERVICE_CLASS (klass)->Stop = service_real_Stop;
	G_OBJECT_CLASS (klass)->get_property = service_get_property;
	G_OBJECT_CLASS (klass)->set_property = service_set_property;
	G_OBJECT_CLASS (klass)->finalize = service_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), SERVICE_CONNECTION, g_param_spec_pointer ("connection", "connection", "connection", G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE | G_PARAM_CONSTRUCT));
	g_type_set_qdata (TYPE_SERVICE, g_quark_from_static_string ("DBusObjectVTable"), (void*) (&_service_dbus_vtable));
}


static void service_instance_init (Service * self) {
	self->priv = SERVICE_GET_PRIVATE (self);
	self->priv->timeout_quit_id = (guint) 0;
}


static void service_finalize (GObject* obj) {
	Service * self;
	self = SERVICE (obj);
	(self->priv->_connection == NULL) ? NULL : (self->priv->_connection = (dbus_g_connection_unref (self->priv->_connection), NULL));
	(self->loop == NULL) ? NULL : (self->loop = (g_main_loop_unref (self->loop), NULL));
	(self->player == NULL) ? NULL : (self->player = (g_object_unref (self->player), NULL));
	(self->tracklists == NULL) ? NULL : (self->tracklists = (g_hash_table_unref (self->tracklists), NULL));
	(self->current_tracklist == NULL) ? NULL : (self->current_tracklist = (g_object_unref (self->current_tracklist), NULL));
	(self->config == NULL) ? NULL : (self->config = (g_key_file_free (self->config), NULL));
	self->config_file = (g_free (self->config_file), NULL);
	self->data_dir = (g_free (self->data_dir), NULL);
	G_OBJECT_CLASS (service_parent_class)->finalize (obj);
}


GType service_get_type (void) {
	static GType service_type_id = 0;
	if (service_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (ServiceClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) service_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (Service), 0, (GInstanceInitFunc) service_instance_init, NULL };
		service_type_id = g_type_register_static (EPRIS_TYPE_SERVICE, "Service", &g_define_type_info, 0);
	}
	return service_type_id;
}


static void service_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	Service * self;
	gpointer boxed;
	self = SERVICE (object);
	switch (property_id) {
		case SERVICE_CONNECTION:
		g_value_set_pointer (value, service_get_connection (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void service_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	Service * self;
	self = SERVICE (object);
	switch (property_id) {
		case SERVICE_CONNECTION:
		service_set_connection (self, g_value_get_pointer (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
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


static int _vala_strcmp0 (const char * str1, const char * str2) {
	if (str1 == NULL) {
		return -(str1 != str2);
	}
	if (str2 == NULL) {
		return str1 != str2;
	}
	return strcmp (str1, str2);
}


static void _vala_dbus_register_object (DBusConnection* connection, const char* path, void* object) {
	const _DBusObjectVTable * vtable;
	vtable = g_type_get_qdata (G_TYPE_FROM_INSTANCE (object), g_quark_from_static_string ("DBusObjectVTable"));
	if (vtable) {
		vtable->register_object (connection, path, object);
	} else {
		g_warning ("Object does not implement any D-Bus interface");
	}
}


static void _vala_dbus_unregister_object (gpointer connection, GObject* object) {
	char* path;
	path = g_object_steal_data ((GObject*) object, "dbus_object_path");
	dbus_connection_unregister_object_path (connection, path);
	g_free (path);
}




