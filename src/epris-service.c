
#include <glib.h>
#include <glib-object.h>
#include <dbus/dbus-glib-lowlevel.h>
#include <dbus/dbus-glib.h>
#include <stdlib.h>
#include <string.h>
#include <config.h>
#include <dbus/dbus.h>


#define EPRIS_TYPE_STATE (epris_state_get_type ())

#define EPRIS_TYPE_WHENCE (epris_whence_get_type ())

#define EPRIS_TYPE_FORMAT (epris_format_get_type ())

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

#define EPRIS_TYPE_TRACK_LIST_TRICK (epris_track_list_trick_get_type ())
#define EPRIS_TRACK_LIST_TRICK(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), EPRIS_TYPE_TRACK_LIST_TRICK, EprisTrackListTrick))
#define EPRIS_TRACK_LIST_TRICK_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), EPRIS_TYPE_TRACK_LIST_TRICK, EprisTrackListTrickClass))
#define EPRIS_IS_TRACK_LIST_TRICK(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), EPRIS_TYPE_TRACK_LIST_TRICK))
#define EPRIS_IS_TRACK_LIST_TRICK_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), EPRIS_TYPE_TRACK_LIST_TRICK))
#define EPRIS_TRACK_LIST_TRICK_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), EPRIS_TYPE_TRACK_LIST_TRICK, EprisTrackListTrickClass))

typedef struct _EprisTrackListTrick EprisTrackListTrick;
typedef struct _EprisTrackListTrickClass EprisTrackListTrickClass;
typedef struct _EprisTrackListTrickPrivate EprisTrackListTrickPrivate;

#define EPRIS_TYPE_TRACK_LIST (epris_track_list_get_type ())
#define EPRIS_TRACK_LIST(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), EPRIS_TYPE_TRACK_LIST, EprisTrackList))
#define EPRIS_TRACK_LIST_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), EPRIS_TYPE_TRACK_LIST, EprisTrackListClass))
#define EPRIS_IS_TRACK_LIST(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), EPRIS_TYPE_TRACK_LIST))
#define EPRIS_IS_TRACK_LIST_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), EPRIS_TYPE_TRACK_LIST))
#define EPRIS_TRACK_LIST_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), EPRIS_TYPE_TRACK_LIST, EprisTrackListClass))

typedef struct _EprisTrackList EprisTrackList;
typedef struct _EprisTrackListClass EprisTrackListClass;
typedef struct _EprisTrackListPrivate EprisTrackListPrivate;
typedef struct _DBusObjectVTable _DBusObjectVTable;

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

struct _EprisServicePrivate {
	char* _Identity;
	EprisState _state;
};

struct _EprisTrackListTrick {
	EprisPropertiesNotify parent_instance;
	EprisTrackListTrickPrivate * priv;
	GHashTable* _current;
};

struct _EprisTrackListTrickClass {
	EprisPropertiesNotifyClass parent_class;
};

struct _EprisTrackList {
	EprisTrackListTrick parent_instance;
	EprisTrackListPrivate * priv;
};

struct _EprisTrackListClass {
	EprisTrackListTrickClass parent_class;
	void (*AddTracks) (EprisTrackList* self, char** uris, int uris_length1, gboolean immediately, GError** error);
	void (*DelTracks) (EprisTrackList* self, char** uris, int uris_length1, gboolean immediately, GError** error);
	GHashTable** (*ListTracks) (EprisTrackList* self, int* result_length1, GError** error);
	void (*Seek) (EprisTrackList* self, gint offset, EprisWhence whence, GError** error);
};

struct _DBusObjectVTable {
	void (*register_object) (DBusConnection*, const char*, void*);
};



guint _dynamic_request_name9 (DBusGProxy* self, const char* param1, guint param2, GError** error);
gboolean epris_request_name (DBusGConnection* conn, const char* name);
GType epris_state_get_type (void);
GType epris_whence_get_type (void);
GType epris_format_get_type (void);
GType epris_properties_notify_get_type (void);
enum  {
	EPRIS_PROPERTIES_NOTIFY_DUMMY_PROPERTY
};
EprisPropertiesNotify* epris_properties_notify_new (void);
EprisPropertiesNotify* epris_properties_notify_construct (GType object_type);
EprisPropertiesNotify* epris_properties_notify_new (void);
static gpointer epris_properties_notify_parent_class = NULL;
void epris_properties_notify_dbus_register_object (DBusConnection* connection, const char* path, void* object);
void _epris_properties_notify_dbus_unregister (DBusConnection* connection, void* user_data);
DBusHandlerResult epris_properties_notify_dbus_message (DBusConnection* connection, DBusMessage* message, void* object);
static DBusMessage* _dbus_epris_properties_notify_introspect (EprisPropertiesNotify* self, DBusConnection* connection, DBusMessage* message);
static DBusMessage* _dbus_epris_properties_notify_property_get_all (EprisPropertiesNotify* self, DBusConnection* connection, DBusMessage* message);
static void _dbus_epris_properties_notify_changed (GObject* _sender, const char* interface_name, const char* property_name, const GValue* value, DBusConnection* _connection);
GType epris_service_get_type (void);
GQuark epris_error_quark (void);
#define EPRIS_SERVICE_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), EPRIS_TYPE_SERVICE, EprisServicePrivate))
enum  {
	EPRIS_SERVICE_DUMMY_PROPERTY,
	EPRIS_SERVICE_IDENTITY,
	EPRIS_SERVICE_STATE
};
void epris_service_Play (EprisService* self, GError** error);
static void epris_service_real_Play (EprisService* self, GError** error);
void epris_service_Stop (EprisService* self, GError** error);
static void epris_service_real_Stop (EprisService* self, GError** error);
void epris_service_Seek (EprisService* self, EprisFormat format, gint64 position, GError** error);
static void epris_service_real_Seek (EprisService* self, EprisFormat format, gint64 position, GError** error);
const char* epris_service_get_Identity (EprisService* self);
void epris_service_set_Identity (EprisService* self, const char* value);
EprisState epris_service_get_State (EprisService* self);
void epris_service_set_State (EprisService* self, EprisState value);
static GObject * epris_service_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static gpointer epris_service_parent_class = NULL;
void epris_service_dbus_register_object (DBusConnection* connection, const char* path, void* object);
void _epris_service_dbus_unregister (DBusConnection* connection, void* user_data);
DBusHandlerResult epris_service_dbus_message (DBusConnection* connection, DBusMessage* message, void* object);
static DBusMessage* _dbus_epris_service_introspect (EprisService* self, DBusConnection* connection, DBusMessage* message);
static DBusMessage* _dbus_epris_service_property_get (EprisService* self, DBusConnection* connection, DBusMessage* message);
static DBusMessage* _dbus_epris_service_property_set (EprisService* self, DBusConnection* connection, DBusMessage* message);
static DBusMessage* _dbus_epris_service_property_get_all (EprisService* self, DBusConnection* connection, DBusMessage* message);
static DBusMessage* _dbus_epris_service_Play (EprisService* self, DBusConnection* connection, DBusMessage* message);
static DBusMessage* _dbus_epris_service_Stop (EprisService* self, DBusConnection* connection, DBusMessage* message);
static DBusMessage* _dbus_epris_service_Seek (EprisService* self, DBusConnection* connection, DBusMessage* message);
static void epris_service_finalize (GObject* obj);
static void epris_service_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void epris_service_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);
GType epris_track_list_trick_get_type (void);
enum  {
	EPRIS_TRACK_LIST_TRICK_DUMMY_PROPERTY
};
static gpointer epris_track_list_trick_parent_class = NULL;
void epris_track_list_trick_dbus_register_object (DBusConnection* connection, const char* path, void* object);
void _epris_track_list_trick_dbus_unregister (DBusConnection* connection, void* user_data);
DBusHandlerResult epris_track_list_trick_dbus_message (DBusConnection* connection, DBusMessage* message, void* object);
static DBusMessage* _dbus_epris_track_list_trick_introspect (EprisTrackListTrick* self, DBusConnection* connection, DBusMessage* message);
static void epris_track_list_trick_finalize (GObject* obj);
GType epris_track_list_get_type (void);
enum  {
	EPRIS_TRACK_LIST_DUMMY_PROPERTY,
	EPRIS_TRACK_LIST_CURRENT
};
void epris_track_list_AddTracks (EprisTrackList* self, char** uris, int uris_length1, gboolean immediately, GError** error);
static void epris_track_list_real_AddTracks (EprisTrackList* self, char** uris, int uris_length1, gboolean immediately, GError** error);
void epris_track_list_DelTracks (EprisTrackList* self, char** uris, int uris_length1, gboolean immediately, GError** error);
static void epris_track_list_real_DelTracks (EprisTrackList* self, char** uris, int uris_length1, gboolean immediately, GError** error);
GHashTable** epris_track_list_ListTracks (EprisTrackList* self, int* result_length1, GError** error);
static GHashTable** epris_track_list_real_ListTracks (EprisTrackList* self, int* result_length1, GError** error);
void epris_track_list_Seek (EprisTrackList* self, gint offset, EprisWhence whence, GError** error);
static void epris_track_list_real_Seek (EprisTrackList* self, gint offset, EprisWhence whence, GError** error);
GHashTable* epris_track_list_get_current (EprisTrackList* self);
void epris_track_list_set_current (EprisTrackList* self, GHashTable* value);
static gpointer epris_track_list_parent_class = NULL;
void epris_track_list_dbus_register_object (DBusConnection* connection, const char* path, void* object);
void _epris_track_list_dbus_unregister (DBusConnection* connection, void* user_data);
DBusHandlerResult epris_track_list_dbus_message (DBusConnection* connection, DBusMessage* message, void* object);
static DBusMessage* _dbus_epris_track_list_introspect (EprisTrackList* self, DBusConnection* connection, DBusMessage* message);
static DBusMessage* _dbus_epris_track_list_property_get (EprisTrackList* self, DBusConnection* connection, DBusMessage* message);
static DBusMessage* _dbus_epris_track_list_property_set (EprisTrackList* self, DBusConnection* connection, DBusMessage* message);
static DBusMessage* _dbus_epris_track_list_property_get_all (EprisTrackList* self, DBusConnection* connection, DBusMessage* message);
static DBusMessage* _dbus_epris_track_list_AddTracks (EprisTrackList* self, DBusConnection* connection, DBusMessage* message);
static DBusMessage* _dbus_epris_track_list_DelTracks (EprisTrackList* self, DBusConnection* connection, DBusMessage* message);
static DBusMessage* _dbus_epris_track_list_ListTracks (EprisTrackList* self, DBusConnection* connection, DBusMessage* message);
static DBusMessage* _dbus_epris_track_list_Seek (EprisTrackList* self, DBusConnection* connection, DBusMessage* message);
static void epris_track_list_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void epris_track_list_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);
static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);
static void _vala_dbus_register_object (DBusConnection* connection, const char* path, void* object);
static void _vala_dbus_unregister_object (gpointer connection, GObject* object);

static const DBusObjectPathVTable _epris_properties_notify_dbus_path_vtable = {_epris_properties_notify_dbus_unregister, epris_properties_notify_dbus_message};
static const _DBusObjectVTable _epris_properties_notify_dbus_vtable = {epris_properties_notify_dbus_register_object};
static const DBusObjectPathVTable _epris_service_dbus_path_vtable = {_epris_service_dbus_unregister, epris_service_dbus_message};
static const _DBusObjectVTable _epris_service_dbus_vtable = {epris_service_dbus_register_object};
static const DBusObjectPathVTable _epris_track_list_trick_dbus_path_vtable = {_epris_track_list_trick_dbus_unregister, epris_track_list_trick_dbus_message};
static const _DBusObjectVTable _epris_track_list_trick_dbus_vtable = {epris_track_list_trick_dbus_register_object};
static const DBusObjectPathVTable _epris_track_list_dbus_path_vtable = {_epris_track_list_dbus_unregister, epris_track_list_dbus_message};
static const _DBusObjectVTable _epris_track_list_dbus_vtable = {epris_track_list_dbus_register_object};

static void g_cclosure_user_marshal_VOID__STRING_STRING_BOXED (GClosure * closure, GValue * return_value, guint n_param_values, const GValue * param_values, gpointer invocation_hint, gpointer marshal_data);

guint _dynamic_request_name9 (DBusGProxy* self, const char* param1, guint param2, GError** error) {
	guint result;
	dbus_g_proxy_call (self, "RequestName", error, G_TYPE_STRING, param1, G_TYPE_UINT, param2, G_TYPE_INVALID, G_TYPE_UINT, &result, G_TYPE_INVALID);
	if (*error) {
		return 0U;
	}
	return result;
}


gboolean epris_request_name (DBusGConnection* conn, const char* name) {
	gboolean result;
	GError * _inner_error_;
	g_return_val_if_fail (conn != NULL, FALSE);
	g_return_val_if_fail (name != NULL, FALSE);
	_inner_error_ = NULL;
	{
		DBusGProxy* bus;
		guint request_name_result;
		bus = dbus_g_proxy_new_for_name (conn, "org.freedesktop.DBus", "/org/freedesktop/DBus", "org.freedesktop.DBus");
		request_name_result = _dynamic_request_name9 (bus, name, (guint) 0, &_inner_error_);
		if (_inner_error_ != NULL) {
			(bus == NULL) ? NULL : (bus = (g_object_unref (bus), NULL));
			goto __catch17_g_error;
			goto __finally17;
		}
		if (request_name_result != DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER) {
			result = FALSE;
			(bus == NULL) ? NULL : (bus = (g_object_unref (bus), NULL));
			return result;
		}
		result = TRUE;
		(bus == NULL) ? NULL : (bus = (g_object_unref (bus), NULL));
		return result;
	}
	goto __finally17;
	__catch17_g_error:
	{
		GError * foo;
		foo = _inner_error_;
		_inner_error_ = NULL;
		{
			g_error (foo->message);
			result = FALSE;
			(foo == NULL) ? NULL : (foo = (g_error_free (foo), NULL));
			return result;
		}
	}
	__finally17:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return FALSE;
	}
}



GType epris_state_get_type (void) {
	static GType epris_state_type_id = 0;
	if (G_UNLIKELY (epris_state_type_id == 0)) {
		static const GEnumValue values[] = {{EPRIS_STATE_STOPPED, "EPRIS_STATE_STOPPED", "stopped"}, {EPRIS_STATE_PAUSED, "EPRIS_STATE_PAUSED", "paused"}, {EPRIS_STATE_PLAYING, "EPRIS_STATE_PLAYING", "playing"}, {0, NULL, NULL}};
		epris_state_type_id = g_enum_register_static ("EprisState", values);
	}
	return epris_state_type_id;
}



GType epris_whence_get_type (void) {
	static GType epris_whence_type_id = 0;
	if (G_UNLIKELY (epris_whence_type_id == 0)) {
		static const GEnumValue values[] = {{EPRIS_WHENCE_START, "EPRIS_WHENCE_START", "start"}, {EPRIS_WHENCE_CURRENT, "EPRIS_WHENCE_CURRENT", "current"}, {EPRIS_WHENCE_END, "EPRIS_WHENCE_END", "end"}, {0, NULL, NULL}};
		epris_whence_type_id = g_enum_register_static ("EprisWhence", values);
	}
	return epris_whence_type_id;
}



GType epris_format_get_type (void) {
	static GType epris_format_type_id = 0;
	if (G_UNLIKELY (epris_format_type_id == 0)) {
		static const GEnumValue values[] = {{EPRIS_FORMAT_UNDEFINED, "EPRIS_FORMAT_UNDEFINED", "undefined"}, {EPRIS_FORMAT_DEFAULT, "EPRIS_FORMAT_DEFAULT", "default"}, {EPRIS_FORMAT_BYTES, "EPRIS_FORMAT_BYTES", "bytes"}, {EPRIS_FORMAT_TIME, "EPRIS_FORMAT_TIME", "time"}, {EPRIS_FORMAT_BUFFERS, "EPRIS_FORMAT_BUFFERS", "buffers"}, {EPRIS_FORMAT_PERCENT, "EPRIS_FORMAT_PERCENT", "percent"}, {0, NULL, NULL}};
		epris_format_type_id = g_enum_register_static ("EprisFormat", values);
	}
	return epris_format_type_id;
}


EprisPropertiesNotify* epris_properties_notify_construct (GType object_type) {
	EprisPropertiesNotify * self;
	self = g_object_newv (object_type, 0, NULL);
	return self;
}


EprisPropertiesNotify* epris_properties_notify_new (void) {
	return epris_properties_notify_construct (EPRIS_TYPE_PROPERTIES_NOTIFY);
}


void _epris_properties_notify_dbus_unregister (DBusConnection* connection, void* user_data) {
}


static DBusMessage* _dbus_epris_properties_notify_introspect (EprisPropertiesNotify* self, DBusConnection* connection, DBusMessage* message) {
	DBusMessage* reply;
	DBusMessageIter iter;
	GString* xml_data;
	char** children;
	int i;
	reply = dbus_message_new_method_return (message);
	dbus_message_iter_init_append (reply, &iter);
	xml_data = g_string_new ("<!DOCTYPE node PUBLIC \"-//freedesktop//DTD D-BUS Object Introspection 1.0//EN\" \"http://www.freedesktop.org/standards/dbus/1.0/introspect.dtd\">\n");
	g_string_append (xml_data, "<node>\n<interface name=\"org.freedesktop.DBus.Introspectable\">\n  <method name=\"Introspect\">\n    <arg name=\"data\" direction=\"out\" type=\"s\"/>\n  </method>\n</interface>\n<interface name=\"org.freedesktop.DBus.Properties\">\n  <method name=\"Get\">\n    <arg name=\"interface\" direction=\"in\" type=\"s\"/>\n    <arg name=\"propname\" direction=\"in\" type=\"s\"/>\n    <arg name=\"value\" direction=\"out\" type=\"v\"/>\n  </method>\n  <method name=\"Set\">\n    <arg name=\"interface\" direction=\"in\" type=\"s\"/>\n    <arg name=\"propname\" direction=\"in\" type=\"s\"/>\n    <arg name=\"value\" direction=\"in\" type=\"v\"/>\n  </method>\n  <method name=\"GetAll\">\n    <arg name=\"interface\" direction=\"in\" type=\"s\"/>\n    <arg name=\"props\" direction=\"out\" type=\"a{sv}\"/>\n  </method>\n</interface>\n<interface name=\"org.freedesktop.DBus.Properties\">\n  <signal name=\"Changed\">\n    <arg name=\"interface_name\" type=\"s\"/>\n    <arg name=\"property_name\" type=\"s\"/>\n    <arg name=\"value\" type=\"v\"/>\n  </signal>\n</interface>\n");
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


static DBusMessage* _dbus_epris_properties_notify_property_get_all (EprisPropertiesNotify* self, DBusConnection* connection, DBusMessage* message) {
	DBusMessage* reply;
	DBusMessageIter iter, reply_iter, subiter;
	char* interface_name;
	const char* _tmp0_;
	if (strcmp (dbus_message_get_signature (message), "s")) {
		return NULL;
	}
	dbus_message_iter_init (message, &iter);
	reply = dbus_message_new_method_return (message);
	dbus_message_iter_init_append (reply, &reply_iter);
	dbus_message_iter_get_basic (&iter, &_tmp0_);
	dbus_message_iter_next (&iter);
	interface_name = g_strdup (_tmp0_);
	if (strcmp (interface_name, "org.freedesktop.DBus.Properties") == 0) {
		dbus_message_iter_open_container (&reply_iter, DBUS_TYPE_ARRAY, "{sv}", &subiter);
		dbus_message_iter_close_container (&reply_iter, &subiter);
	} else {
		return NULL;
	}
	return reply;
}


DBusHandlerResult epris_properties_notify_dbus_message (DBusConnection* connection, DBusMessage* message, void* object) {
	DBusMessage* reply;
	reply = NULL;
	if (dbus_message_is_method_call (message, "org.freedesktop.DBus.Introspectable", "Introspect")) {
		reply = _dbus_epris_properties_notify_introspect (object, connection, message);
	} else if (dbus_message_is_method_call (message, "org.freedesktop.DBus.Properties", "GetAll")) {
		reply = _dbus_epris_properties_notify_property_get_all (object, connection, message);
	}
	if (reply) {
		dbus_connection_send (connection, reply, NULL);
		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	} else {
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}
}


static void _dbus_epris_properties_notify_changed (GObject* _sender, const char* interface_name, const char* property_name, const GValue* value, DBusConnection* _connection) {
	const char * _path;
	DBusMessage *_message;
	DBusMessageIter _iter;
	const char* _tmp1_;
	const char* _tmp2_;
	DBusMessageIter _tmp3_;
	_path = g_object_get_data (_sender, "dbus_object_path");
	_message = dbus_message_new_signal (_path, "org.freedesktop.DBus.Properties", "Changed");
	dbus_message_iter_init_append (_message, &_iter);
	_tmp1_ = interface_name;
	dbus_message_iter_append_basic (&_iter, DBUS_TYPE_STRING, &_tmp1_);
	_tmp2_ = property_name;
	dbus_message_iter_append_basic (&_iter, DBUS_TYPE_STRING, &_tmp2_);
	if (G_VALUE_TYPE (&(*value)) == G_TYPE_UCHAR) {
		guint8 _tmp4_;
		dbus_message_iter_open_container (&_iter, DBUS_TYPE_VARIANT, "y", &_tmp3_);
		_tmp4_ = g_value_get_uchar (&(*value));
		dbus_message_iter_append_basic (&_tmp3_, DBUS_TYPE_BYTE, &_tmp4_);
		dbus_message_iter_close_container (&_iter, &_tmp3_);
	} else if (G_VALUE_TYPE (&(*value)) == G_TYPE_BOOLEAN) {
		dbus_bool_t _tmp5_;
		dbus_message_iter_open_container (&_iter, DBUS_TYPE_VARIANT, "b", &_tmp3_);
		_tmp5_ = g_value_get_boolean (&(*value));
		dbus_message_iter_append_basic (&_tmp3_, DBUS_TYPE_BOOLEAN, &_tmp5_);
		dbus_message_iter_close_container (&_iter, &_tmp3_);
	} else if (G_VALUE_TYPE (&(*value)) == G_TYPE_INT) {
		dbus_int32_t _tmp6_;
		dbus_message_iter_open_container (&_iter, DBUS_TYPE_VARIANT, "i", &_tmp3_);
		_tmp6_ = g_value_get_int (&(*value));
		dbus_message_iter_append_basic (&_tmp3_, DBUS_TYPE_INT32, &_tmp6_);
		dbus_message_iter_close_container (&_iter, &_tmp3_);
	} else if (G_VALUE_TYPE (&(*value)) == G_TYPE_UINT) {
		dbus_uint32_t _tmp7_;
		dbus_message_iter_open_container (&_iter, DBUS_TYPE_VARIANT, "u", &_tmp3_);
		_tmp7_ = g_value_get_uint (&(*value));
		dbus_message_iter_append_basic (&_tmp3_, DBUS_TYPE_UINT32, &_tmp7_);
		dbus_message_iter_close_container (&_iter, &_tmp3_);
	} else if (G_VALUE_TYPE (&(*value)) == G_TYPE_INT64) {
		dbus_int64_t _tmp8_;
		dbus_message_iter_open_container (&_iter, DBUS_TYPE_VARIANT, "x", &_tmp3_);
		_tmp8_ = g_value_get_int64 (&(*value));
		dbus_message_iter_append_basic (&_tmp3_, DBUS_TYPE_INT64, &_tmp8_);
		dbus_message_iter_close_container (&_iter, &_tmp3_);
	} else if (G_VALUE_TYPE (&(*value)) == G_TYPE_UINT64) {
		dbus_uint64_t _tmp9_;
		dbus_message_iter_open_container (&_iter, DBUS_TYPE_VARIANT, "t", &_tmp3_);
		_tmp9_ = g_value_get_uint64 (&(*value));
		dbus_message_iter_append_basic (&_tmp3_, DBUS_TYPE_UINT64, &_tmp9_);
		dbus_message_iter_close_container (&_iter, &_tmp3_);
	} else if (G_VALUE_TYPE (&(*value)) == G_TYPE_DOUBLE) {
		double _tmp10_;
		dbus_message_iter_open_container (&_iter, DBUS_TYPE_VARIANT, "d", &_tmp3_);
		_tmp10_ = g_value_get_double (&(*value));
		dbus_message_iter_append_basic (&_tmp3_, DBUS_TYPE_DOUBLE, &_tmp10_);
		dbus_message_iter_close_container (&_iter, &_tmp3_);
	} else if (G_VALUE_TYPE (&(*value)) == G_TYPE_STRING) {
		const char* _tmp11_;
		dbus_message_iter_open_container (&_iter, DBUS_TYPE_VARIANT, "s", &_tmp3_);
		_tmp11_ = g_value_get_string (&(*value));
		dbus_message_iter_append_basic (&_tmp3_, DBUS_TYPE_STRING, &_tmp11_);
		dbus_message_iter_close_container (&_iter, &_tmp3_);
	}
	dbus_connection_send (_connection, _message, NULL);
	dbus_message_unref (_message);
}


void epris_properties_notify_dbus_register_object (DBusConnection* connection, const char* path, void* object) {
	if (!g_object_get_data (object, "dbus_object_path")) {
		g_object_set_data (object, "dbus_object_path", g_strdup (path));
		dbus_connection_register_object_path (connection, path, &_epris_properties_notify_dbus_path_vtable, object);
		g_object_weak_ref (object, _vala_dbus_unregister_object, connection);
	}
	g_signal_connect (object, "changed", (GCallback) _dbus_epris_properties_notify_changed, connection);
}


static void epris_properties_notify_class_init (EprisPropertiesNotifyClass * klass) {
	epris_properties_notify_parent_class = g_type_class_peek_parent (klass);
	g_signal_new ("changed", EPRIS_TYPE_PROPERTIES_NOTIFY, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_user_marshal_VOID__STRING_STRING_BOXED, G_TYPE_NONE, 3, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_VALUE);
	g_type_set_qdata (EPRIS_TYPE_PROPERTIES_NOTIFY, g_quark_from_static_string ("DBusObjectVTable"), (void*) (&_epris_properties_notify_dbus_vtable));
}


static void epris_properties_notify_instance_init (EprisPropertiesNotify * self) {
}


GType epris_properties_notify_get_type (void) {
	static GType epris_properties_notify_type_id = 0;
	if (epris_properties_notify_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (EprisPropertiesNotifyClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) epris_properties_notify_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (EprisPropertiesNotify), 0, (GInstanceInitFunc) epris_properties_notify_instance_init, NULL };
		epris_properties_notify_type_id = g_type_register_static (G_TYPE_OBJECT, "EprisPropertiesNotify", &g_define_type_info, 0);
	}
	return epris_properties_notify_type_id;
}


static void epris_service_real_Play (EprisService* self, GError** error) {
	GError * _inner_error_;
	g_return_if_fail (self != NULL);
	_inner_error_ = NULL;
	_inner_error_ = g_error_new_literal (EPRIS_ERROR, EPRIS_ERROR_NOT_SUPPORTED, "Play(): this function is not yet implemented");
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
}


void epris_service_Play (EprisService* self, GError** error) {
	EPRIS_SERVICE_GET_CLASS (self)->Play (self, error);
}


static void epris_service_real_Stop (EprisService* self, GError** error) {
	GError * _inner_error_;
	g_return_if_fail (self != NULL);
	_inner_error_ = NULL;
	_inner_error_ = g_error_new_literal (EPRIS_ERROR, EPRIS_ERROR_NOT_SUPPORTED, "Stop(): this function is not yet implemented");
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
}


void epris_service_Stop (EprisService* self, GError** error) {
	EPRIS_SERVICE_GET_CLASS (self)->Stop (self, error);
}


static void epris_service_real_Seek (EprisService* self, EprisFormat format, gint64 position, GError** error) {
	GError * _inner_error_;
	g_return_if_fail (self != NULL);
	_inner_error_ = NULL;
	_inner_error_ = g_error_new_literal (EPRIS_ERROR, EPRIS_ERROR_NOT_SUPPORTED, "Seek(): this function is not yet implemented");
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
}


void epris_service_Seek (EprisService* self, EprisFormat format, gint64 position, GError** error) {
	EPRIS_SERVICE_GET_CLASS (self)->Seek (self, format, position, error);
}


const char* epris_service_get_Identity (EprisService* self) {
	const char* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_Identity;
	return result;
}


void epris_service_set_Identity (EprisService* self, const char* value) {
	char* _tmp1_;
	const char* _tmp0_;
	g_return_if_fail (self != NULL);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	self->priv->_Identity = (_tmp1_ = (_tmp0_ = value, (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_)), self->priv->_Identity = (g_free (self->priv->_Identity), NULL), _tmp1_);
	g_object_notify ((GObject *) self, "Identity");
}


EprisState epris_service_get_State (EprisService* self) {
	EprisState result;
	g_return_val_if_fail (self != NULL, 0);
	result = self->priv->_state;
	return result;
}


void epris_service_set_State (EprisService* self, EprisState value) {
	GValue _tmp0_ = {0};
	GValue v;
	g_return_if_fail (self != NULL);
	v = (g_value_init (&_tmp0_, EPRIS_TYPE_STATE), _tmp0_);
	self->priv->_state = value;
	g_value_set_enum (&v, (gint) self->priv->_state);
	g_signal_emit_by_name ((EprisPropertiesNotify*) self, "changed", "org.mpris.EprisPlayer", "state", &v);
	G_IS_VALUE (&v) ? (g_value_unset (&v), NULL) : NULL;
	g_object_notify ((GObject *) self, "State");
}


static GObject * epris_service_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	EprisServiceClass * klass;
	GObjectClass * parent_class;
	EprisService * self;
	klass = EPRIS_SERVICE_CLASS (g_type_class_peek (EPRIS_TYPE_SERVICE));
	parent_class = G_OBJECT_CLASS (g_type_class_peek_parent (klass));
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = EPRIS_SERVICE (obj);
	{
		epris_service_set_Identity (self, "epris service " PACKAGE_VERSION);
	}
	return obj;
}


void _epris_service_dbus_unregister (DBusConnection* connection, void* user_data) {
}


static DBusMessage* _dbus_epris_service_introspect (EprisService* self, DBusConnection* connection, DBusMessage* message) {
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


static DBusMessage* _dbus_epris_service_property_get (EprisService* self, DBusConnection* connection, DBusMessage* message) {
	DBusMessage* reply;
	DBusMessageIter iter, reply_iter, subiter;
	char* interface_name;
	const char* _tmp12_;
	char* property_name;
	const char* _tmp13_;
	if (strcmp (dbus_message_get_signature (message), "ss")) {
		return NULL;
	}
	dbus_message_iter_init (message, &iter);
	reply = dbus_message_new_method_return (message);
	dbus_message_iter_init_append (reply, &reply_iter);
	dbus_message_iter_get_basic (&iter, &_tmp12_);
	dbus_message_iter_next (&iter);
	interface_name = g_strdup (_tmp12_);
	dbus_message_iter_get_basic (&iter, &_tmp13_);
	dbus_message_iter_next (&iter);
	property_name = g_strdup (_tmp13_);
	if ((strcmp (interface_name, "org.mpris.EprisPlayer") == 0) && (strcmp (property_name, "Identity") == 0)) {
		const char* _tmp14_;
		dbus_message_iter_open_container (&reply_iter, DBUS_TYPE_VARIANT, "s", &subiter);
		_tmp14_ = epris_service_get_Identity (self);
		dbus_message_iter_append_basic (&subiter, DBUS_TYPE_STRING, &_tmp14_);
		dbus_message_iter_close_container (&reply_iter, &subiter);
	} else if ((strcmp (interface_name, "org.mpris.EprisPlayer") == 0) && (strcmp (property_name, "State") == 0)) {
		dbus_int32_t _tmp15_;
		dbus_message_iter_open_container (&reply_iter, DBUS_TYPE_VARIANT, "i", &subiter);
		_tmp15_ = epris_service_get_State (self);
		dbus_message_iter_append_basic (&subiter, DBUS_TYPE_INT32, &_tmp15_);
		dbus_message_iter_close_container (&reply_iter, &subiter);
	} else {
		return NULL;
	}
	return reply;
}


static DBusMessage* _dbus_epris_service_property_set (EprisService* self, DBusConnection* connection, DBusMessage* message) {
	DBusMessage* reply;
	DBusMessageIter iter, subiter;
	char* interface_name;
	const char* _tmp16_;
	char* property_name;
	const char* _tmp17_;
	if (strcmp (dbus_message_get_signature (message), "ssv")) {
		return NULL;
	}
	dbus_message_iter_init (message, &iter);
	reply = dbus_message_new_method_return (message);
	dbus_message_iter_get_basic (&iter, &_tmp16_);
	dbus_message_iter_next (&iter);
	interface_name = g_strdup (_tmp16_);
	dbus_message_iter_get_basic (&iter, &_tmp17_);
	dbus_message_iter_next (&iter);
	property_name = g_strdup (_tmp17_);
	dbus_message_iter_recurse (&iter, &subiter);
	if ((strcmp (interface_name, "org.mpris.EprisPlayer") == 0) && (strcmp (property_name, "Identity") == 0)) {
		char* value;
		const char* _tmp18_;
		dbus_message_iter_get_basic (&subiter, &_tmp18_);
		dbus_message_iter_next (&subiter);
		value = g_strdup (_tmp18_);
		epris_service_set_Identity (self, value);
	} else if ((strcmp (interface_name, "org.mpris.EprisPlayer") == 0) && (strcmp (property_name, "State") == 0)) {
		EprisState value;
		dbus_int32_t _tmp19_;
		dbus_message_iter_get_basic (&subiter, &_tmp19_);
		dbus_message_iter_next (&subiter);
		value = _tmp19_;
		epris_service_set_State (self, value);
	} else {
		return NULL;
	}
	return reply;
}


static DBusMessage* _dbus_epris_service_property_get_all (EprisService* self, DBusConnection* connection, DBusMessage* message) {
	DBusMessage* reply;
	DBusMessageIter iter, reply_iter, subiter, entry_iter, value_iter;
	char* interface_name;
	const char* _tmp20_;
	const char* property_name;
	if (strcmp (dbus_message_get_signature (message), "s")) {
		return NULL;
	}
	dbus_message_iter_init (message, &iter);
	reply = dbus_message_new_method_return (message);
	dbus_message_iter_init_append (reply, &reply_iter);
	dbus_message_iter_get_basic (&iter, &_tmp20_);
	dbus_message_iter_next (&iter);
	interface_name = g_strdup (_tmp20_);
	if (strcmp (interface_name, "org.mpris.EprisPlayer") == 0) {
		const char* _tmp21_;
		dbus_int32_t _tmp22_;
		dbus_message_iter_open_container (&reply_iter, DBUS_TYPE_ARRAY, "{sv}", &subiter);
		dbus_message_iter_open_container (&subiter, DBUS_TYPE_DICT_ENTRY, NULL, &entry_iter);
		property_name = "Identity";
		dbus_message_iter_append_basic (&entry_iter, DBUS_TYPE_STRING, &property_name);
		dbus_message_iter_open_container (&entry_iter, DBUS_TYPE_VARIANT, "s", &value_iter);
		_tmp21_ = epris_service_get_Identity (self);
		dbus_message_iter_append_basic (&value_iter, DBUS_TYPE_STRING, &_tmp21_);
		dbus_message_iter_close_container (&entry_iter, &value_iter);
		dbus_message_iter_close_container (&subiter, &entry_iter);
		dbus_message_iter_open_container (&subiter, DBUS_TYPE_DICT_ENTRY, NULL, &entry_iter);
		property_name = "State";
		dbus_message_iter_append_basic (&entry_iter, DBUS_TYPE_STRING, &property_name);
		dbus_message_iter_open_container (&entry_iter, DBUS_TYPE_VARIANT, "i", &value_iter);
		_tmp22_ = epris_service_get_State (self);
		dbus_message_iter_append_basic (&value_iter, DBUS_TYPE_INT32, &_tmp22_);
		dbus_message_iter_close_container (&entry_iter, &value_iter);
		dbus_message_iter_close_container (&subiter, &entry_iter);
		dbus_message_iter_close_container (&reply_iter, &subiter);
	} else {
		return NULL;
	}
	return reply;
}


static DBusMessage* _dbus_epris_service_Play (EprisService* self, DBusConnection* connection, DBusMessage* message) {
	DBusMessageIter iter;
	GError* error;
	DBusMessage* reply;
	error = NULL;
	if (strcmp (dbus_message_get_signature (message), "")) {
		return NULL;
	}
	dbus_message_iter_init (message, &iter);
	epris_service_Play (self, &error);
	if (error) {
		reply = dbus_message_new_error (message, DBUS_ERROR_FAILED, error->message);
		return reply;
	}
	reply = dbus_message_new_method_return (message);
	dbus_message_iter_init_append (reply, &iter);
	return reply;
}


static DBusMessage* _dbus_epris_service_Stop (EprisService* self, DBusConnection* connection, DBusMessage* message) {
	DBusMessageIter iter;
	GError* error;
	DBusMessage* reply;
	error = NULL;
	if (strcmp (dbus_message_get_signature (message), "")) {
		return NULL;
	}
	dbus_message_iter_init (message, &iter);
	epris_service_Stop (self, &error);
	if (error) {
		reply = dbus_message_new_error (message, DBUS_ERROR_FAILED, error->message);
		return reply;
	}
	reply = dbus_message_new_method_return (message);
	dbus_message_iter_init_append (reply, &iter);
	return reply;
}


static DBusMessage* _dbus_epris_service_Seek (EprisService* self, DBusConnection* connection, DBusMessage* message) {
	DBusMessageIter iter;
	GError* error;
	EprisFormat format;
	dbus_int32_t _tmp23_;
	gint64 position;
	dbus_int64_t _tmp24_;
	DBusMessage* reply;
	error = NULL;
	if (strcmp (dbus_message_get_signature (message), "ix")) {
		return NULL;
	}
	dbus_message_iter_init (message, &iter);
	format = 0;
	dbus_message_iter_get_basic (&iter, &_tmp23_);
	dbus_message_iter_next (&iter);
	format = _tmp23_;
	position = 0LL;
	dbus_message_iter_get_basic (&iter, &_tmp24_);
	dbus_message_iter_next (&iter);
	position = _tmp24_;
	epris_service_Seek (self, format, position, &error);
	if (error) {
		reply = dbus_message_new_error (message, DBUS_ERROR_FAILED, error->message);
		return reply;
	}
	reply = dbus_message_new_method_return (message);
	dbus_message_iter_init_append (reply, &iter);
	return reply;
}


DBusHandlerResult epris_service_dbus_message (DBusConnection* connection, DBusMessage* message, void* object) {
	DBusMessage* reply;
	reply = NULL;
	if (dbus_message_is_method_call (message, "org.freedesktop.DBus.Introspectable", "Introspect")) {
		reply = _dbus_epris_service_introspect (object, connection, message);
	} else if (dbus_message_is_method_call (message, "org.freedesktop.DBus.Properties", "Get")) {
		reply = _dbus_epris_service_property_get (object, connection, message);
	} else if (dbus_message_is_method_call (message, "org.freedesktop.DBus.Properties", "Set")) {
		reply = _dbus_epris_service_property_set (object, connection, message);
	} else if (dbus_message_is_method_call (message, "org.freedesktop.DBus.Properties", "GetAll")) {
		reply = _dbus_epris_service_property_get_all (object, connection, message);
	} else if (dbus_message_is_method_call (message, "org.mpris.EprisPlayer", "Play")) {
		reply = _dbus_epris_service_Play (object, connection, message);
	} else if (dbus_message_is_method_call (message, "org.mpris.EprisPlayer", "Stop")) {
		reply = _dbus_epris_service_Stop (object, connection, message);
	} else if (dbus_message_is_method_call (message, "org.mpris.EprisPlayer", "Seek")) {
		reply = _dbus_epris_service_Seek (object, connection, message);
	}
	if (reply) {
		dbus_connection_send (connection, reply, NULL);
		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	} else if (epris_properties_notify_dbus_message (connection, message, object) == DBUS_HANDLER_RESULT_HANDLED) {
		return DBUS_HANDLER_RESULT_HANDLED;
	} else {
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}
}


void epris_service_dbus_register_object (DBusConnection* connection, const char* path, void* object) {
	if (!g_object_get_data (object, "dbus_object_path")) {
		g_object_set_data (object, "dbus_object_path", g_strdup (path));
		dbus_connection_register_object_path (connection, path, &_epris_service_dbus_path_vtable, object);
		g_object_weak_ref (object, _vala_dbus_unregister_object, connection);
	}
	epris_properties_notify_dbus_register_object (connection, path, object);
}


static void epris_service_class_init (EprisServiceClass * klass) {
	epris_service_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (EprisServicePrivate));
	EPRIS_SERVICE_CLASS (klass)->Play = epris_service_real_Play;
	EPRIS_SERVICE_CLASS (klass)->Stop = epris_service_real_Stop;
	EPRIS_SERVICE_CLASS (klass)->Seek = epris_service_real_Seek;
	G_OBJECT_CLASS (klass)->get_property = epris_service_get_property;
	G_OBJECT_CLASS (klass)->set_property = epris_service_set_property;
	G_OBJECT_CLASS (klass)->constructor = epris_service_constructor;
	G_OBJECT_CLASS (klass)->finalize = epris_service_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), EPRIS_SERVICE_IDENTITY, g_param_spec_string ("Identity", "Identity", "Identity", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), EPRIS_SERVICE_STATE, g_param_spec_enum ("State", "State", "State", EPRIS_TYPE_STATE, 0, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_type_set_qdata (EPRIS_TYPE_SERVICE, g_quark_from_static_string ("DBusObjectVTable"), (void*) (&_epris_service_dbus_vtable));
}


static void epris_service_instance_init (EprisService * self) {
	self->priv = EPRIS_SERVICE_GET_PRIVATE (self);
}


static void epris_service_finalize (GObject* obj) {
	EprisService * self;
	self = EPRIS_SERVICE (obj);
	self->priv->_Identity = (g_free (self->priv->_Identity), NULL);
	G_OBJECT_CLASS (epris_service_parent_class)->finalize (obj);
}


GType epris_service_get_type (void) {
	static GType epris_service_type_id = 0;
	if (epris_service_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (EprisServiceClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) epris_service_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (EprisService), 0, (GInstanceInitFunc) epris_service_instance_init, NULL };
		epris_service_type_id = g_type_register_static (EPRIS_TYPE_PROPERTIES_NOTIFY, "EprisService", &g_define_type_info, G_TYPE_FLAG_ABSTRACT);
	}
	return epris_service_type_id;
}


static void epris_service_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	EprisService * self;
	gpointer boxed;
	self = EPRIS_SERVICE (object);
	switch (property_id) {
		case EPRIS_SERVICE_IDENTITY:
		g_value_set_string (value, epris_service_get_Identity (self));
		break;
		case EPRIS_SERVICE_STATE:
		g_value_set_enum (value, epris_service_get_State (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void epris_service_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	EprisService * self;
	self = EPRIS_SERVICE (object);
	switch (property_id) {
		case EPRIS_SERVICE_IDENTITY:
		epris_service_set_Identity (self, g_value_get_string (value));
		break;
		case EPRIS_SERVICE_STATE:
		epris_service_set_State (self, g_value_get_enum (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


void _epris_track_list_trick_dbus_unregister (DBusConnection* connection, void* user_data) {
}


static DBusMessage* _dbus_epris_track_list_trick_introspect (EprisTrackListTrick* self, DBusConnection* connection, DBusMessage* message) {
	DBusMessage* reply;
	DBusMessageIter iter;
	GString* xml_data;
	char** children;
	int i;
	reply = dbus_message_new_method_return (message);
	dbus_message_iter_init_append (reply, &iter);
	xml_data = g_string_new ("<!DOCTYPE node PUBLIC \"-//freedesktop//DTD D-BUS Object Introspection 1.0//EN\" \"http://www.freedesktop.org/standards/dbus/1.0/introspect.dtd\">\n");
	g_string_append (xml_data, "<node>\n<interface name=\"org.freedesktop.DBus.Introspectable\">\n  <method name=\"Introspect\">\n    <arg name=\"data\" direction=\"out\" type=\"s\"/>\n  </method>\n</interface>\n<interface name=\"org.freedesktop.DBus.Properties\">\n  <method name=\"Get\">\n    <arg name=\"interface\" direction=\"in\" type=\"s\"/>\n    <arg name=\"propname\" direction=\"in\" type=\"s\"/>\n    <arg name=\"value\" direction=\"out\" type=\"v\"/>\n  </method>\n  <method name=\"Set\">\n    <arg name=\"interface\" direction=\"in\" type=\"s\"/>\n    <arg name=\"propname\" direction=\"in\" type=\"s\"/>\n    <arg name=\"value\" direction=\"in\" type=\"v\"/>\n  </method>\n  <method name=\"GetAll\">\n    <arg name=\"interface\" direction=\"in\" type=\"s\"/>\n    <arg name=\"props\" direction=\"out\" type=\"a{sv}\"/>\n  </method>\n</interface>\n<interface name=\"org.freedesktop.DBus.Properties\">\n  <signal name=\"Changed\">\n    <arg name=\"interface_name\" type=\"s\"/>\n    <arg name=\"property_name\" type=\"s\"/>\n    <arg name=\"value\" type=\"v\"/>\n  </signal>\n</interface>\n");
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


DBusHandlerResult epris_track_list_trick_dbus_message (DBusConnection* connection, DBusMessage* message, void* object) {
	DBusMessage* reply;
	reply = NULL;
	if (dbus_message_is_method_call (message, "org.freedesktop.DBus.Introspectable", "Introspect")) {
		reply = _dbus_epris_track_list_trick_introspect (object, connection, message);
	}
	if (reply) {
		dbus_connection_send (connection, reply, NULL);
		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	} else if (epris_properties_notify_dbus_message (connection, message, object) == DBUS_HANDLER_RESULT_HANDLED) {
		return DBUS_HANDLER_RESULT_HANDLED;
	} else {
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}
}


void epris_track_list_trick_dbus_register_object (DBusConnection* connection, const char* path, void* object) {
	if (!g_object_get_data (object, "dbus_object_path")) {
		g_object_set_data (object, "dbus_object_path", g_strdup (path));
		dbus_connection_register_object_path (connection, path, &_epris_track_list_trick_dbus_path_vtable, object);
		g_object_weak_ref (object, _vala_dbus_unregister_object, connection);
	}
	epris_properties_notify_dbus_register_object (connection, path, object);
}


static void epris_track_list_trick_class_init (EprisTrackListTrickClass * klass) {
	epris_track_list_trick_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->finalize = epris_track_list_trick_finalize;
	g_signal_new ("update_current", EPRIS_TYPE_TRACK_LIST_TRICK, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);
	g_type_set_qdata (EPRIS_TYPE_TRACK_LIST_TRICK, g_quark_from_static_string ("DBusObjectVTable"), (void*) (&_epris_track_list_trick_dbus_vtable));
}


static void epris_track_list_trick_instance_init (EprisTrackListTrick * self) {
}


static void epris_track_list_trick_finalize (GObject* obj) {
	EprisTrackListTrick * self;
	self = EPRIS_TRACK_LIST_TRICK (obj);
	(self->_current == NULL) ? NULL : (self->_current = (g_hash_table_unref (self->_current), NULL));
	G_OBJECT_CLASS (epris_track_list_trick_parent_class)->finalize (obj);
}


GType epris_track_list_trick_get_type (void) {
	static GType epris_track_list_trick_type_id = 0;
	if (epris_track_list_trick_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (EprisTrackListTrickClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) epris_track_list_trick_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (EprisTrackListTrick), 0, (GInstanceInitFunc) epris_track_list_trick_instance_init, NULL };
		epris_track_list_trick_type_id = g_type_register_static (EPRIS_TYPE_PROPERTIES_NOTIFY, "EprisTrackListTrick", &g_define_type_info, G_TYPE_FLAG_ABSTRACT);
	}
	return epris_track_list_trick_type_id;
}


static void epris_track_list_real_AddTracks (EprisTrackList* self, char** uris, int uris_length1, gboolean immediately, GError** error) {
	GError * _inner_error_;
	g_return_if_fail (self != NULL);
	_inner_error_ = NULL;
	_inner_error_ = g_error_new_literal (EPRIS_ERROR, EPRIS_ERROR_NOT_SUPPORTED, "AddTracks(): this function is not yet implemented");
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
}


void epris_track_list_AddTracks (EprisTrackList* self, char** uris, int uris_length1, gboolean immediately, GError** error) {
	EPRIS_TRACK_LIST_GET_CLASS (self)->AddTracks (self, uris, uris_length1, immediately, error);
}


static void epris_track_list_real_DelTracks (EprisTrackList* self, char** uris, int uris_length1, gboolean immediately, GError** error) {
	GError * _inner_error_;
	g_return_if_fail (self != NULL);
	_inner_error_ = NULL;
	_inner_error_ = g_error_new_literal (EPRIS_ERROR, EPRIS_ERROR_NOT_SUPPORTED, "DelTracks(): this function is not yet implemented");
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
}


void epris_track_list_DelTracks (EprisTrackList* self, char** uris, int uris_length1, gboolean immediately, GError** error) {
	EPRIS_TRACK_LIST_GET_CLASS (self)->DelTracks (self, uris, uris_length1, immediately, error);
}


static GHashTable** epris_track_list_real_ListTracks (EprisTrackList* self, int* result_length1, GError** error) {
	GHashTable** result;
	GError * _inner_error_;
	g_return_val_if_fail (self != NULL, NULL);
	_inner_error_ = NULL;
	_inner_error_ = g_error_new_literal (EPRIS_ERROR, EPRIS_ERROR_NOT_SUPPORTED, "ListTracks(): this function is not yet implemented");
	if (_inner_error_ != NULL) {
		if (_inner_error_->domain == EPRIS_ERROR) {
			g_propagate_error (error, _inner_error_);
			return NULL;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
}


GHashTable** epris_track_list_ListTracks (EprisTrackList* self, int* result_length1, GError** error) {
	return EPRIS_TRACK_LIST_GET_CLASS (self)->ListTracks (self, result_length1, error);
}


static void epris_track_list_real_Seek (EprisTrackList* self, gint offset, EprisWhence whence, GError** error) {
	GError * _inner_error_;
	g_return_if_fail (self != NULL);
	_inner_error_ = NULL;
	_inner_error_ = g_error_new_literal (EPRIS_ERROR, EPRIS_ERROR_NOT_SUPPORTED, "Seek(): this function is not yet implemented");
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
}


void epris_track_list_Seek (EprisTrackList* self, gint offset, EprisWhence whence, GError** error) {
	EPRIS_TRACK_LIST_GET_CLASS (self)->Seek (self, offset, whence, error);
}


GHashTable* epris_track_list_get_current (EprisTrackList* self) {
	GHashTable* result;
	g_return_val_if_fail (self != NULL, NULL);
	g_signal_emit_by_name ((EprisTrackListTrick*) self, "update-current");
	result = ((EprisTrackListTrick*) self)->_current;
	return result;
}


void epris_track_list_set_current (EprisTrackList* self, GHashTable* value) {
	GHashTable* _tmp1_;
	GHashTable* _tmp0_;
	GValue _tmp3_ = {0};
	GValue _tmp2_ = {0};
	g_return_if_fail (self != NULL);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	((EprisTrackListTrick*) self)->_current = (_tmp1_ = (_tmp0_ = value, (_tmp0_ == NULL) ? NULL : g_hash_table_ref (_tmp0_)), (((EprisTrackListTrick*) self)->_current == NULL) ? NULL : (((EprisTrackListTrick*) self)->_current = (g_hash_table_unref (((EprisTrackListTrick*) self)->_current), NULL)), _tmp1_);
	g_signal_emit_by_name ((EprisPropertiesNotify*) self, "changed", "org.mpris.EprisTrackList", "current", (_tmp3_ = (g_value_init (&_tmp2_, G_TYPE_HASH_TABLE), g_value_set_boxed (&_tmp2_, ((EprisTrackListTrick*) self)->_current), _tmp2_), &_tmp3_));
	g_object_notify ((GObject *) self, "current");
}


void _epris_track_list_dbus_unregister (DBusConnection* connection, void* user_data) {
}


static DBusMessage* _dbus_epris_track_list_introspect (EprisTrackList* self, DBusConnection* connection, DBusMessage* message) {
	DBusMessage* reply;
	DBusMessageIter iter;
	GString* xml_data;
	char** children;
	int i;
	reply = dbus_message_new_method_return (message);
	dbus_message_iter_init_append (reply, &iter);
	xml_data = g_string_new ("<!DOCTYPE node PUBLIC \"-//freedesktop//DTD D-BUS Object Introspection 1.0//EN\" \"http://www.freedesktop.org/standards/dbus/1.0/introspect.dtd\">\n");
	g_string_append (xml_data, "<node>\n<interface name=\"org.freedesktop.DBus.Introspectable\">\n  <method name=\"Introspect\">\n    <arg name=\"data\" direction=\"out\" type=\"s\"/>\n  </method>\n</interface>\n<interface name=\"org.freedesktop.DBus.Properties\">\n  <method name=\"Get\">\n    <arg name=\"interface\" direction=\"in\" type=\"s\"/>\n    <arg name=\"propname\" direction=\"in\" type=\"s\"/>\n    <arg name=\"value\" direction=\"out\" type=\"v\"/>\n  </method>\n  <method name=\"Set\">\n    <arg name=\"interface\" direction=\"in\" type=\"s\"/>\n    <arg name=\"propname\" direction=\"in\" type=\"s\"/>\n    <arg name=\"value\" direction=\"in\" type=\"v\"/>\n  </method>\n  <method name=\"GetAll\">\n    <arg name=\"interface\" direction=\"in\" type=\"s\"/>\n    <arg name=\"props\" direction=\"out\" type=\"a{sv}\"/>\n  </method>\n</interface>\n<interface name=\"org.freedesktop.DBus.Properties\">\n  <signal name=\"Changed\">\n    <arg name=\"interface_name\" type=\"s\"/>\n    <arg name=\"property_name\" type=\"s\"/>\n    <arg name=\"value\" type=\"v\"/>\n  </signal>\n</interface>\n<interface name=\"org.mpris.EprisTrackList\">\n  <method name=\"AddTracks\">\n    <arg name=\"uris\" type=\"as\" direction=\"in\"/>\n    <arg name=\"immediately\" type=\"b\" direction=\"in\"/>\n  </method>\n  <method name=\"DelTracks\">\n    <arg name=\"uris\" type=\"as\" direction=\"in\"/>\n    <arg name=\"immediately\" type=\"b\" direction=\"in\"/>\n  </method>\n  <method name=\"ListTracks\">\n    <arg name=\"result\" type=\"aa{sv}\" direction=\"out\"/>\n  </method>\n  <method name=\"Seek\">\n    <arg name=\"offset\" type=\"i\" direction=\"in\"/>\n    <arg name=\"whence\" type=\"i\" direction=\"in\"/>\n  </method>\n  <property name=\"Current\" type=\"a{sv}\" access=\"readwrite\"/>\n</interface>\n");
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


static DBusMessage* _dbus_epris_track_list_property_get (EprisTrackList* self, DBusConnection* connection, DBusMessage* message) {
	DBusMessage* reply;
	DBusMessageIter iter, reply_iter, subiter;
	char* interface_name;
	const char* _tmp25_;
	char* property_name;
	const char* _tmp26_;
	if (strcmp (dbus_message_get_signature (message), "ss")) {
		return NULL;
	}
	dbus_message_iter_init (message, &iter);
	reply = dbus_message_new_method_return (message);
	dbus_message_iter_init_append (reply, &reply_iter);
	dbus_message_iter_get_basic (&iter, &_tmp25_);
	dbus_message_iter_next (&iter);
	interface_name = g_strdup (_tmp25_);
	dbus_message_iter_get_basic (&iter, &_tmp26_);
	dbus_message_iter_next (&iter);
	property_name = g_strdup (_tmp26_);
	if ((strcmp (interface_name, "org.mpris.EprisTrackList") == 0) && (strcmp (property_name, "Current") == 0)) {
		DBusMessageIter _tmp27_, _tmp28_;
		GHashTableIter _tmp29_;
		gpointer _tmp30_, _tmp31_;
		dbus_message_iter_open_container (&reply_iter, DBUS_TYPE_VARIANT, "a{sv}", &subiter);
		dbus_message_iter_open_container (&subiter, DBUS_TYPE_ARRAY, "{sv}", &_tmp27_);
		g_hash_table_iter_init (&_tmp29_, epris_track_list_get_current (self));
		while (g_hash_table_iter_next (&_tmp29_, &_tmp30_, &_tmp31_)) {
			char* _key;
			GValue* _value;
			const char* _tmp32_;
			DBusMessageIter _tmp33_;
			dbus_message_iter_open_container (&_tmp27_, DBUS_TYPE_DICT_ENTRY, NULL, &_tmp28_);
			_key = (char*) _tmp30_;
			_value = (GValue*) _tmp31_;
			_tmp32_ = _key;
			dbus_message_iter_append_basic (&_tmp28_, DBUS_TYPE_STRING, &_tmp32_);
			if (G_VALUE_TYPE (&(*_value)) == G_TYPE_UCHAR) {
				guint8 _tmp34_;
				dbus_message_iter_open_container (&_tmp28_, DBUS_TYPE_VARIANT, "y", &_tmp33_);
				_tmp34_ = g_value_get_uchar (&(*_value));
				dbus_message_iter_append_basic (&_tmp33_, DBUS_TYPE_BYTE, &_tmp34_);
				dbus_message_iter_close_container (&_tmp28_, &_tmp33_);
			} else if (G_VALUE_TYPE (&(*_value)) == G_TYPE_BOOLEAN) {
				dbus_bool_t _tmp35_;
				dbus_message_iter_open_container (&_tmp28_, DBUS_TYPE_VARIANT, "b", &_tmp33_);
				_tmp35_ = g_value_get_boolean (&(*_value));
				dbus_message_iter_append_basic (&_tmp33_, DBUS_TYPE_BOOLEAN, &_tmp35_);
				dbus_message_iter_close_container (&_tmp28_, &_tmp33_);
			} else if (G_VALUE_TYPE (&(*_value)) == G_TYPE_INT) {
				dbus_int32_t _tmp36_;
				dbus_message_iter_open_container (&_tmp28_, DBUS_TYPE_VARIANT, "i", &_tmp33_);
				_tmp36_ = g_value_get_int (&(*_value));
				dbus_message_iter_append_basic (&_tmp33_, DBUS_TYPE_INT32, &_tmp36_);
				dbus_message_iter_close_container (&_tmp28_, &_tmp33_);
			} else if (G_VALUE_TYPE (&(*_value)) == G_TYPE_UINT) {
				dbus_uint32_t _tmp37_;
				dbus_message_iter_open_container (&_tmp28_, DBUS_TYPE_VARIANT, "u", &_tmp33_);
				_tmp37_ = g_value_get_uint (&(*_value));
				dbus_message_iter_append_basic (&_tmp33_, DBUS_TYPE_UINT32, &_tmp37_);
				dbus_message_iter_close_container (&_tmp28_, &_tmp33_);
			} else if (G_VALUE_TYPE (&(*_value)) == G_TYPE_INT64) {
				dbus_int64_t _tmp38_;
				dbus_message_iter_open_container (&_tmp28_, DBUS_TYPE_VARIANT, "x", &_tmp33_);
				_tmp38_ = g_value_get_int64 (&(*_value));
				dbus_message_iter_append_basic (&_tmp33_, DBUS_TYPE_INT64, &_tmp38_);
				dbus_message_iter_close_container (&_tmp28_, &_tmp33_);
			} else if (G_VALUE_TYPE (&(*_value)) == G_TYPE_UINT64) {
				dbus_uint64_t _tmp39_;
				dbus_message_iter_open_container (&_tmp28_, DBUS_TYPE_VARIANT, "t", &_tmp33_);
				_tmp39_ = g_value_get_uint64 (&(*_value));
				dbus_message_iter_append_basic (&_tmp33_, DBUS_TYPE_UINT64, &_tmp39_);
				dbus_message_iter_close_container (&_tmp28_, &_tmp33_);
			} else if (G_VALUE_TYPE (&(*_value)) == G_TYPE_DOUBLE) {
				double _tmp40_;
				dbus_message_iter_open_container (&_tmp28_, DBUS_TYPE_VARIANT, "d", &_tmp33_);
				_tmp40_ = g_value_get_double (&(*_value));
				dbus_message_iter_append_basic (&_tmp33_, DBUS_TYPE_DOUBLE, &_tmp40_);
				dbus_message_iter_close_container (&_tmp28_, &_tmp33_);
			} else if (G_VALUE_TYPE (&(*_value)) == G_TYPE_STRING) {
				const char* _tmp41_;
				dbus_message_iter_open_container (&_tmp28_, DBUS_TYPE_VARIANT, "s", &_tmp33_);
				_tmp41_ = g_value_get_string (&(*_value));
				dbus_message_iter_append_basic (&_tmp33_, DBUS_TYPE_STRING, &_tmp41_);
				dbus_message_iter_close_container (&_tmp28_, &_tmp33_);
			}
			dbus_message_iter_close_container (&_tmp27_, &_tmp28_);
		}
		dbus_message_iter_close_container (&subiter, &_tmp27_);
		dbus_message_iter_close_container (&reply_iter, &subiter);
	} else {
		return NULL;
	}
	return reply;
}


static DBusMessage* _dbus_epris_track_list_property_set (EprisTrackList* self, DBusConnection* connection, DBusMessage* message) {
	DBusMessage* reply;
	DBusMessageIter iter, subiter;
	char* interface_name;
	const char* _tmp42_;
	char* property_name;
	const char* _tmp43_;
	if (strcmp (dbus_message_get_signature (message), "ssv")) {
		return NULL;
	}
	dbus_message_iter_init (message, &iter);
	reply = dbus_message_new_method_return (message);
	dbus_message_iter_get_basic (&iter, &_tmp42_);
	dbus_message_iter_next (&iter);
	interface_name = g_strdup (_tmp42_);
	dbus_message_iter_get_basic (&iter, &_tmp43_);
	dbus_message_iter_next (&iter);
	property_name = g_strdup (_tmp43_);
	dbus_message_iter_recurse (&iter, &subiter);
	if ((strcmp (interface_name, "org.mpris.EprisTrackList") == 0) && (strcmp (property_name, "Current") == 0)) {
		GHashTable* value;
		GHashTable* _tmp44_;
		DBusMessageIter _tmp45_;
		DBusMessageIter _tmp46_;
		_tmp44_ = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, NULL);
		dbus_message_iter_recurse (&subiter, &_tmp45_);
		while (dbus_message_iter_get_arg_type (&_tmp45_)) {
			char* _key;
			GValue* _value;
			const char* _tmp47_;
			GValue _tmp48_ = {0};
			DBusMessageIter _tmp49_;
			dbus_message_iter_recurse (&_tmp45_, &_tmp46_);
			dbus_message_iter_get_basic (&_tmp46_, &_tmp47_);
			dbus_message_iter_next (&_tmp46_);
			_key = g_strdup (_tmp47_);
			dbus_message_iter_recurse (&_tmp46_, &_tmp49_);
			if (dbus_message_iter_get_arg_type (&_tmp49_) == DBUS_TYPE_BYTE) {
				guint8 _tmp50_;
				dbus_message_iter_get_basic (&_tmp49_, &_tmp50_);
				g_value_init (&_tmp48_, G_TYPE_UCHAR);
				g_value_set_uchar (&_tmp48_, _tmp50_);
			} else if (dbus_message_iter_get_arg_type (&_tmp49_) == DBUS_TYPE_BOOLEAN) {
				dbus_bool_t _tmp51_;
				dbus_message_iter_get_basic (&_tmp49_, &_tmp51_);
				g_value_init (&_tmp48_, G_TYPE_BOOLEAN);
				g_value_set_boolean (&_tmp48_, _tmp51_);
			} else if (dbus_message_iter_get_arg_type (&_tmp49_) == DBUS_TYPE_INT16) {
				dbus_int16_t _tmp52_;
				dbus_message_iter_get_basic (&_tmp49_, &_tmp52_);
				g_value_init (&_tmp48_, G_TYPE_INT);
				g_value_set_int (&_tmp48_, _tmp52_);
			} else if (dbus_message_iter_get_arg_type (&_tmp49_) == DBUS_TYPE_UINT16) {
				dbus_uint16_t _tmp53_;
				dbus_message_iter_get_basic (&_tmp49_, &_tmp53_);
				g_value_init (&_tmp48_, G_TYPE_UINT);
				g_value_set_uint (&_tmp48_, _tmp53_);
			} else if (dbus_message_iter_get_arg_type (&_tmp49_) == DBUS_TYPE_INT32) {
				dbus_int32_t _tmp54_;
				dbus_message_iter_get_basic (&_tmp49_, &_tmp54_);
				g_value_init (&_tmp48_, G_TYPE_INT);
				g_value_set_int (&_tmp48_, _tmp54_);
			} else if (dbus_message_iter_get_arg_type (&_tmp49_) == DBUS_TYPE_UINT32) {
				dbus_uint32_t _tmp55_;
				dbus_message_iter_get_basic (&_tmp49_, &_tmp55_);
				g_value_init (&_tmp48_, G_TYPE_UINT);
				g_value_set_uint (&_tmp48_, _tmp55_);
			} else if (dbus_message_iter_get_arg_type (&_tmp49_) == DBUS_TYPE_INT64) {
				dbus_int64_t _tmp56_;
				dbus_message_iter_get_basic (&_tmp49_, &_tmp56_);
				g_value_init (&_tmp48_, G_TYPE_INT64);
				g_value_set_int64 (&_tmp48_, _tmp56_);
			} else if (dbus_message_iter_get_arg_type (&_tmp49_) == DBUS_TYPE_UINT64) {
				dbus_uint64_t _tmp57_;
				dbus_message_iter_get_basic (&_tmp49_, &_tmp57_);
				g_value_init (&_tmp48_, G_TYPE_UINT64);
				g_value_set_uint64 (&_tmp48_, _tmp57_);
			} else if (dbus_message_iter_get_arg_type (&_tmp49_) == DBUS_TYPE_DOUBLE) {
				double _tmp58_;
				dbus_message_iter_get_basic (&_tmp49_, &_tmp58_);
				g_value_init (&_tmp48_, G_TYPE_DOUBLE);
				g_value_set_double (&_tmp48_, _tmp58_);
			} else if (dbus_message_iter_get_arg_type (&_tmp49_) == DBUS_TYPE_STRING) {
				const char* _tmp59_;
				dbus_message_iter_get_basic (&_tmp49_, &_tmp59_);
				g_value_init (&_tmp48_, G_TYPE_STRING);
				g_value_take_string (&_tmp48_, g_strdup (_tmp59_));
			} else if (dbus_message_iter_get_arg_type (&_tmp49_) == DBUS_TYPE_OBJECT_PATH) {
				const char* _tmp60_;
				dbus_message_iter_get_basic (&_tmp49_, &_tmp60_);
				g_value_init (&_tmp48_, G_TYPE_STRING);
				g_value_take_string (&_tmp48_, g_strdup (_tmp60_));
			} else if (dbus_message_iter_get_arg_type (&_tmp49_) == DBUS_TYPE_SIGNATURE) {
				const char* _tmp61_;
				dbus_message_iter_get_basic (&_tmp49_, &_tmp61_);
				g_value_init (&_tmp48_, G_TYPE_STRING);
				g_value_take_string (&_tmp48_, g_strdup (_tmp61_));
			}
			dbus_message_iter_next (&_tmp46_);
			_value = g_memdup (&_tmp48_, sizeof (GValue));
			g_hash_table_insert (_tmp44_, _key, _value);
			dbus_message_iter_next (&_tmp45_);
		}
		dbus_message_iter_next (&subiter);
		value = _tmp44_;
		epris_track_list_set_current (self, value);
	} else {
		return NULL;
	}
	return reply;
}


static DBusMessage* _dbus_epris_track_list_property_get_all (EprisTrackList* self, DBusConnection* connection, DBusMessage* message) {
	DBusMessage* reply;
	DBusMessageIter iter, reply_iter, subiter, entry_iter, value_iter;
	char* interface_name;
	const char* _tmp62_;
	const char* property_name;
	if (strcmp (dbus_message_get_signature (message), "s")) {
		return NULL;
	}
	dbus_message_iter_init (message, &iter);
	reply = dbus_message_new_method_return (message);
	dbus_message_iter_init_append (reply, &reply_iter);
	dbus_message_iter_get_basic (&iter, &_tmp62_);
	dbus_message_iter_next (&iter);
	interface_name = g_strdup (_tmp62_);
	if (strcmp (interface_name, "org.mpris.EprisTrackList") == 0) {
		DBusMessageIter _tmp63_, _tmp64_;
		GHashTableIter _tmp65_;
		gpointer _tmp66_, _tmp67_;
		dbus_message_iter_open_container (&reply_iter, DBUS_TYPE_ARRAY, "{sv}", &subiter);
		dbus_message_iter_open_container (&subiter, DBUS_TYPE_DICT_ENTRY, NULL, &entry_iter);
		property_name = "Current";
		dbus_message_iter_append_basic (&entry_iter, DBUS_TYPE_STRING, &property_name);
		dbus_message_iter_open_container (&entry_iter, DBUS_TYPE_VARIANT, "a{sv}", &value_iter);
		dbus_message_iter_open_container (&value_iter, DBUS_TYPE_ARRAY, "{sv}", &_tmp63_);
		g_hash_table_iter_init (&_tmp65_, epris_track_list_get_current (self));
		while (g_hash_table_iter_next (&_tmp65_, &_tmp66_, &_tmp67_)) {
			char* _key;
			GValue* _value;
			const char* _tmp68_;
			DBusMessageIter _tmp69_;
			dbus_message_iter_open_container (&_tmp63_, DBUS_TYPE_DICT_ENTRY, NULL, &_tmp64_);
			_key = (char*) _tmp66_;
			_value = (GValue*) _tmp67_;
			_tmp68_ = _key;
			dbus_message_iter_append_basic (&_tmp64_, DBUS_TYPE_STRING, &_tmp68_);
			if (G_VALUE_TYPE (&(*_value)) == G_TYPE_UCHAR) {
				guint8 _tmp70_;
				dbus_message_iter_open_container (&_tmp64_, DBUS_TYPE_VARIANT, "y", &_tmp69_);
				_tmp70_ = g_value_get_uchar (&(*_value));
				dbus_message_iter_append_basic (&_tmp69_, DBUS_TYPE_BYTE, &_tmp70_);
				dbus_message_iter_close_container (&_tmp64_, &_tmp69_);
			} else if (G_VALUE_TYPE (&(*_value)) == G_TYPE_BOOLEAN) {
				dbus_bool_t _tmp71_;
				dbus_message_iter_open_container (&_tmp64_, DBUS_TYPE_VARIANT, "b", &_tmp69_);
				_tmp71_ = g_value_get_boolean (&(*_value));
				dbus_message_iter_append_basic (&_tmp69_, DBUS_TYPE_BOOLEAN, &_tmp71_);
				dbus_message_iter_close_container (&_tmp64_, &_tmp69_);
			} else if (G_VALUE_TYPE (&(*_value)) == G_TYPE_INT) {
				dbus_int32_t _tmp72_;
				dbus_message_iter_open_container (&_tmp64_, DBUS_TYPE_VARIANT, "i", &_tmp69_);
				_tmp72_ = g_value_get_int (&(*_value));
				dbus_message_iter_append_basic (&_tmp69_, DBUS_TYPE_INT32, &_tmp72_);
				dbus_message_iter_close_container (&_tmp64_, &_tmp69_);
			} else if (G_VALUE_TYPE (&(*_value)) == G_TYPE_UINT) {
				dbus_uint32_t _tmp73_;
				dbus_message_iter_open_container (&_tmp64_, DBUS_TYPE_VARIANT, "u", &_tmp69_);
				_tmp73_ = g_value_get_uint (&(*_value));
				dbus_message_iter_append_basic (&_tmp69_, DBUS_TYPE_UINT32, &_tmp73_);
				dbus_message_iter_close_container (&_tmp64_, &_tmp69_);
			} else if (G_VALUE_TYPE (&(*_value)) == G_TYPE_INT64) {
				dbus_int64_t _tmp74_;
				dbus_message_iter_open_container (&_tmp64_, DBUS_TYPE_VARIANT, "x", &_tmp69_);
				_tmp74_ = g_value_get_int64 (&(*_value));
				dbus_message_iter_append_basic (&_tmp69_, DBUS_TYPE_INT64, &_tmp74_);
				dbus_message_iter_close_container (&_tmp64_, &_tmp69_);
			} else if (G_VALUE_TYPE (&(*_value)) == G_TYPE_UINT64) {
				dbus_uint64_t _tmp75_;
				dbus_message_iter_open_container (&_tmp64_, DBUS_TYPE_VARIANT, "t", &_tmp69_);
				_tmp75_ = g_value_get_uint64 (&(*_value));
				dbus_message_iter_append_basic (&_tmp69_, DBUS_TYPE_UINT64, &_tmp75_);
				dbus_message_iter_close_container (&_tmp64_, &_tmp69_);
			} else if (G_VALUE_TYPE (&(*_value)) == G_TYPE_DOUBLE) {
				double _tmp76_;
				dbus_message_iter_open_container (&_tmp64_, DBUS_TYPE_VARIANT, "d", &_tmp69_);
				_tmp76_ = g_value_get_double (&(*_value));
				dbus_message_iter_append_basic (&_tmp69_, DBUS_TYPE_DOUBLE, &_tmp76_);
				dbus_message_iter_close_container (&_tmp64_, &_tmp69_);
			} else if (G_VALUE_TYPE (&(*_value)) == G_TYPE_STRING) {
				const char* _tmp77_;
				dbus_message_iter_open_container (&_tmp64_, DBUS_TYPE_VARIANT, "s", &_tmp69_);
				_tmp77_ = g_value_get_string (&(*_value));
				dbus_message_iter_append_basic (&_tmp69_, DBUS_TYPE_STRING, &_tmp77_);
				dbus_message_iter_close_container (&_tmp64_, &_tmp69_);
			}
			dbus_message_iter_close_container (&_tmp63_, &_tmp64_);
		}
		dbus_message_iter_close_container (&value_iter, &_tmp63_);
		dbus_message_iter_close_container (&entry_iter, &value_iter);
		dbus_message_iter_close_container (&subiter, &entry_iter);
		dbus_message_iter_close_container (&reply_iter, &subiter);
	} else {
		return NULL;
	}
	return reply;
}


static DBusMessage* _dbus_epris_track_list_AddTracks (EprisTrackList* self, DBusConnection* connection, DBusMessage* message) {
	DBusMessageIter iter;
	GError* error;
	char** uris;
	int uris_length1;
	char** _tmp78_;
	int _tmp78__length;
	int _tmp78__size;
	int _tmp78__length1;
	DBusMessageIter _tmp79_;
	gboolean immediately;
	dbus_bool_t _tmp81_;
	DBusMessage* reply;
	error = NULL;
	if (strcmp (dbus_message_get_signature (message), "asb")) {
		return NULL;
	}
	dbus_message_iter_init (message, &iter);
	uris = NULL;
	uris_length1 = 0;
	_tmp78_ = g_new (char*, 5);
	_tmp78__length = 0;
	_tmp78__size = 4;
	_tmp78__length1 = 0;
	dbus_message_iter_recurse (&iter, &_tmp79_);
	for (; dbus_message_iter_get_arg_type (&_tmp79_); _tmp78__length1++) {
		const char* _tmp80_;
		if (_tmp78__size == _tmp78__length) {
			_tmp78__size = 2 * _tmp78__size;
			_tmp78_ = g_renew (char*, _tmp78_, _tmp78__size + 1);
		}
		dbus_message_iter_get_basic (&_tmp79_, &_tmp80_);
		dbus_message_iter_next (&_tmp79_);
		_tmp78_[_tmp78__length++] = g_strdup (_tmp80_);
	}
	uris_length1 = _tmp78__length1;
	_tmp78_[_tmp78__length] = NULL;
	dbus_message_iter_next (&iter);
	uris = _tmp78_;
	immediately = FALSE;
	dbus_message_iter_get_basic (&iter, &_tmp81_);
	dbus_message_iter_next (&iter);
	immediately = _tmp81_;
	epris_track_list_AddTracks (self, uris, uris_length1, immediately, &error);
	if (error) {
		reply = dbus_message_new_error (message, DBUS_ERROR_FAILED, error->message);
		return reply;
	}
	reply = dbus_message_new_method_return (message);
	dbus_message_iter_init_append (reply, &iter);
	uris = (_vala_array_free (uris, uris_length1, (GDestroyNotify) g_free), NULL);
	return reply;
}


static DBusMessage* _dbus_epris_track_list_DelTracks (EprisTrackList* self, DBusConnection* connection, DBusMessage* message) {
	DBusMessageIter iter;
	GError* error;
	char** uris;
	int uris_length1;
	char** _tmp82_;
	int _tmp82__length;
	int _tmp82__size;
	int _tmp82__length1;
	DBusMessageIter _tmp83_;
	gboolean immediately;
	dbus_bool_t _tmp85_;
	DBusMessage* reply;
	error = NULL;
	if (strcmp (dbus_message_get_signature (message), "asb")) {
		return NULL;
	}
	dbus_message_iter_init (message, &iter);
	uris = NULL;
	uris_length1 = 0;
	_tmp82_ = g_new (char*, 5);
	_tmp82__length = 0;
	_tmp82__size = 4;
	_tmp82__length1 = 0;
	dbus_message_iter_recurse (&iter, &_tmp83_);
	for (; dbus_message_iter_get_arg_type (&_tmp83_); _tmp82__length1++) {
		const char* _tmp84_;
		if (_tmp82__size == _tmp82__length) {
			_tmp82__size = 2 * _tmp82__size;
			_tmp82_ = g_renew (char*, _tmp82_, _tmp82__size + 1);
		}
		dbus_message_iter_get_basic (&_tmp83_, &_tmp84_);
		dbus_message_iter_next (&_tmp83_);
		_tmp82_[_tmp82__length++] = g_strdup (_tmp84_);
	}
	uris_length1 = _tmp82__length1;
	_tmp82_[_tmp82__length] = NULL;
	dbus_message_iter_next (&iter);
	uris = _tmp82_;
	immediately = FALSE;
	dbus_message_iter_get_basic (&iter, &_tmp85_);
	dbus_message_iter_next (&iter);
	immediately = _tmp85_;
	epris_track_list_DelTracks (self, uris, uris_length1, immediately, &error);
	if (error) {
		reply = dbus_message_new_error (message, DBUS_ERROR_FAILED, error->message);
		return reply;
	}
	reply = dbus_message_new_method_return (message);
	dbus_message_iter_init_append (reply, &iter);
	uris = (_vala_array_free (uris, uris_length1, (GDestroyNotify) g_free), NULL);
	return reply;
}


static DBusMessage* _dbus_epris_track_list_ListTracks (EprisTrackList* self, DBusConnection* connection, DBusMessage* message) {
	DBusMessageIter iter;
	GError* error;
	int result_length1;
	GHashTable** result;
	DBusMessage* reply;
	GHashTable** _tmp86_;
	DBusMessageIter _tmp87_;
	int _tmp88_;
	error = NULL;
	if (strcmp (dbus_message_get_signature (message), "")) {
		return NULL;
	}
	dbus_message_iter_init (message, &iter);
	result_length1 = 0;
	result = epris_track_list_ListTracks (self, &result_length1, &error);
	if (error) {
		reply = dbus_message_new_error (message, DBUS_ERROR_FAILED, error->message);
		return reply;
	}
	reply = dbus_message_new_method_return (message);
	dbus_message_iter_init_append (reply, &iter);
	_tmp86_ = result;
	dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "a{sv}", &_tmp87_);
	for (_tmp88_ = 0; _tmp88_ < result_length1; _tmp88_++) {
		DBusMessageIter _tmp89_, _tmp90_;
		GHashTableIter _tmp91_;
		gpointer _tmp92_, _tmp93_;
		dbus_message_iter_open_container (&_tmp87_, DBUS_TYPE_ARRAY, "{sv}", &_tmp89_);
		g_hash_table_iter_init (&_tmp91_, *_tmp86_);
		while (g_hash_table_iter_next (&_tmp91_, &_tmp92_, &_tmp93_)) {
			char* _key;
			GValue* _value;
			const char* _tmp94_;
			DBusMessageIter _tmp95_;
			dbus_message_iter_open_container (&_tmp89_, DBUS_TYPE_DICT_ENTRY, NULL, &_tmp90_);
			_key = (char*) _tmp92_;
			_value = (GValue*) _tmp93_;
			_tmp94_ = _key;
			dbus_message_iter_append_basic (&_tmp90_, DBUS_TYPE_STRING, &_tmp94_);
			if (G_VALUE_TYPE (&(*_value)) == G_TYPE_UCHAR) {
				guint8 _tmp96_;
				dbus_message_iter_open_container (&_tmp90_, DBUS_TYPE_VARIANT, "y", &_tmp95_);
				_tmp96_ = g_value_get_uchar (&(*_value));
				dbus_message_iter_append_basic (&_tmp95_, DBUS_TYPE_BYTE, &_tmp96_);
				dbus_message_iter_close_container (&_tmp90_, &_tmp95_);
			} else if (G_VALUE_TYPE (&(*_value)) == G_TYPE_BOOLEAN) {
				dbus_bool_t _tmp97_;
				dbus_message_iter_open_container (&_tmp90_, DBUS_TYPE_VARIANT, "b", &_tmp95_);
				_tmp97_ = g_value_get_boolean (&(*_value));
				dbus_message_iter_append_basic (&_tmp95_, DBUS_TYPE_BOOLEAN, &_tmp97_);
				dbus_message_iter_close_container (&_tmp90_, &_tmp95_);
			} else if (G_VALUE_TYPE (&(*_value)) == G_TYPE_INT) {
				dbus_int32_t _tmp98_;
				dbus_message_iter_open_container (&_tmp90_, DBUS_TYPE_VARIANT, "i", &_tmp95_);
				_tmp98_ = g_value_get_int (&(*_value));
				dbus_message_iter_append_basic (&_tmp95_, DBUS_TYPE_INT32, &_tmp98_);
				dbus_message_iter_close_container (&_tmp90_, &_tmp95_);
			} else if (G_VALUE_TYPE (&(*_value)) == G_TYPE_UINT) {
				dbus_uint32_t _tmp99_;
				dbus_message_iter_open_container (&_tmp90_, DBUS_TYPE_VARIANT, "u", &_tmp95_);
				_tmp99_ = g_value_get_uint (&(*_value));
				dbus_message_iter_append_basic (&_tmp95_, DBUS_TYPE_UINT32, &_tmp99_);
				dbus_message_iter_close_container (&_tmp90_, &_tmp95_);
			} else if (G_VALUE_TYPE (&(*_value)) == G_TYPE_INT64) {
				dbus_int64_t _tmp100_;
				dbus_message_iter_open_container (&_tmp90_, DBUS_TYPE_VARIANT, "x", &_tmp95_);
				_tmp100_ = g_value_get_int64 (&(*_value));
				dbus_message_iter_append_basic (&_tmp95_, DBUS_TYPE_INT64, &_tmp100_);
				dbus_message_iter_close_container (&_tmp90_, &_tmp95_);
			} else if (G_VALUE_TYPE (&(*_value)) == G_TYPE_UINT64) {
				dbus_uint64_t _tmp101_;
				dbus_message_iter_open_container (&_tmp90_, DBUS_TYPE_VARIANT, "t", &_tmp95_);
				_tmp101_ = g_value_get_uint64 (&(*_value));
				dbus_message_iter_append_basic (&_tmp95_, DBUS_TYPE_UINT64, &_tmp101_);
				dbus_message_iter_close_container (&_tmp90_, &_tmp95_);
			} else if (G_VALUE_TYPE (&(*_value)) == G_TYPE_DOUBLE) {
				double _tmp102_;
				dbus_message_iter_open_container (&_tmp90_, DBUS_TYPE_VARIANT, "d", &_tmp95_);
				_tmp102_ = g_value_get_double (&(*_value));
				dbus_message_iter_append_basic (&_tmp95_, DBUS_TYPE_DOUBLE, &_tmp102_);
				dbus_message_iter_close_container (&_tmp90_, &_tmp95_);
			} else if (G_VALUE_TYPE (&(*_value)) == G_TYPE_STRING) {
				const char* _tmp103_;
				dbus_message_iter_open_container (&_tmp90_, DBUS_TYPE_VARIANT, "s", &_tmp95_);
				_tmp103_ = g_value_get_string (&(*_value));
				dbus_message_iter_append_basic (&_tmp95_, DBUS_TYPE_STRING, &_tmp103_);
				dbus_message_iter_close_container (&_tmp90_, &_tmp95_);
			}
			dbus_message_iter_close_container (&_tmp89_, &_tmp90_);
		}
		dbus_message_iter_close_container (&_tmp87_, &_tmp89_);
		_tmp86_++;
	}
	dbus_message_iter_close_container (&iter, &_tmp87_);
	result = (_vala_array_free (result,  result_length1, (GDestroyNotify) g_hash_table_unref), NULL);
	return reply;
}


static DBusMessage* _dbus_epris_track_list_Seek (EprisTrackList* self, DBusConnection* connection, DBusMessage* message) {
	DBusMessageIter iter;
	GError* error;
	gint offset;
	dbus_int32_t _tmp104_;
	EprisWhence whence;
	dbus_int32_t _tmp105_;
	DBusMessage* reply;
	error = NULL;
	if (strcmp (dbus_message_get_signature (message), "ii")) {
		return NULL;
	}
	dbus_message_iter_init (message, &iter);
	offset = 0;
	dbus_message_iter_get_basic (&iter, &_tmp104_);
	dbus_message_iter_next (&iter);
	offset = _tmp104_;
	whence = 0;
	dbus_message_iter_get_basic (&iter, &_tmp105_);
	dbus_message_iter_next (&iter);
	whence = _tmp105_;
	epris_track_list_Seek (self, offset, whence, &error);
	if (error) {
		reply = dbus_message_new_error (message, DBUS_ERROR_FAILED, error->message);
		return reply;
	}
	reply = dbus_message_new_method_return (message);
	dbus_message_iter_init_append (reply, &iter);
	return reply;
}


DBusHandlerResult epris_track_list_dbus_message (DBusConnection* connection, DBusMessage* message, void* object) {
	DBusMessage* reply;
	reply = NULL;
	if (dbus_message_is_method_call (message, "org.freedesktop.DBus.Introspectable", "Introspect")) {
		reply = _dbus_epris_track_list_introspect (object, connection, message);
	} else if (dbus_message_is_method_call (message, "org.freedesktop.DBus.Properties", "Get")) {
		reply = _dbus_epris_track_list_property_get (object, connection, message);
	} else if (dbus_message_is_method_call (message, "org.freedesktop.DBus.Properties", "Set")) {
		reply = _dbus_epris_track_list_property_set (object, connection, message);
	} else if (dbus_message_is_method_call (message, "org.freedesktop.DBus.Properties", "GetAll")) {
		reply = _dbus_epris_track_list_property_get_all (object, connection, message);
	} else if (dbus_message_is_method_call (message, "org.mpris.EprisTrackList", "AddTracks")) {
		reply = _dbus_epris_track_list_AddTracks (object, connection, message);
	} else if (dbus_message_is_method_call (message, "org.mpris.EprisTrackList", "DelTracks")) {
		reply = _dbus_epris_track_list_DelTracks (object, connection, message);
	} else if (dbus_message_is_method_call (message, "org.mpris.EprisTrackList", "ListTracks")) {
		reply = _dbus_epris_track_list_ListTracks (object, connection, message);
	} else if (dbus_message_is_method_call (message, "org.mpris.EprisTrackList", "Seek")) {
		reply = _dbus_epris_track_list_Seek (object, connection, message);
	}
	if (reply) {
		dbus_connection_send (connection, reply, NULL);
		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	} else if (epris_track_list_trick_dbus_message (connection, message, object) == DBUS_HANDLER_RESULT_HANDLED) {
		return DBUS_HANDLER_RESULT_HANDLED;
	} else {
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}
}


void epris_track_list_dbus_register_object (DBusConnection* connection, const char* path, void* object) {
	if (!g_object_get_data (object, "dbus_object_path")) {
		g_object_set_data (object, "dbus_object_path", g_strdup (path));
		dbus_connection_register_object_path (connection, path, &_epris_track_list_dbus_path_vtable, object);
		g_object_weak_ref (object, _vala_dbus_unregister_object, connection);
	}
	epris_track_list_trick_dbus_register_object (connection, path, object);
}


static void epris_track_list_class_init (EprisTrackListClass * klass) {
	epris_track_list_parent_class = g_type_class_peek_parent (klass);
	EPRIS_TRACK_LIST_CLASS (klass)->AddTracks = epris_track_list_real_AddTracks;
	EPRIS_TRACK_LIST_CLASS (klass)->DelTracks = epris_track_list_real_DelTracks;
	EPRIS_TRACK_LIST_CLASS (klass)->ListTracks = epris_track_list_real_ListTracks;
	EPRIS_TRACK_LIST_CLASS (klass)->Seek = epris_track_list_real_Seek;
	G_OBJECT_CLASS (klass)->get_property = epris_track_list_get_property;
	G_OBJECT_CLASS (klass)->set_property = epris_track_list_set_property;
	g_object_class_install_property (G_OBJECT_CLASS (klass), EPRIS_TRACK_LIST_CURRENT, g_param_spec_pointer ("current", "current", "current", G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_type_set_qdata (EPRIS_TYPE_TRACK_LIST, g_quark_from_static_string ("DBusObjectVTable"), (void*) (&_epris_track_list_dbus_vtable));
}


static void epris_track_list_instance_init (EprisTrackList * self) {
}


GType epris_track_list_get_type (void) {
	static GType epris_track_list_type_id = 0;
	if (epris_track_list_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (EprisTrackListClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) epris_track_list_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (EprisTrackList), 0, (GInstanceInitFunc) epris_track_list_instance_init, NULL };
		epris_track_list_type_id = g_type_register_static (EPRIS_TYPE_TRACK_LIST_TRICK, "EprisTrackList", &g_define_type_info, G_TYPE_FLAG_ABSTRACT);
	}
	return epris_track_list_type_id;
}


static void epris_track_list_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	EprisTrackList * self;
	gpointer boxed;
	self = EPRIS_TRACK_LIST (object);
	switch (property_id) {
		case EPRIS_TRACK_LIST_CURRENT:
		g_value_set_boxed (value, epris_track_list_get_current (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void epris_track_list_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	EprisTrackList * self;
	self = EPRIS_TRACK_LIST (object);
	switch (property_id) {
		case EPRIS_TRACK_LIST_CURRENT:
		epris_track_list_set_current (self, g_value_get_boxed (value));
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



static void g_cclosure_user_marshal_VOID__STRING_STRING_BOXED (GClosure * closure, GValue * return_value, guint n_param_values, const GValue * param_values, gpointer invocation_hint, gpointer marshal_data) {
	typedef void (*GMarshalFunc_VOID__STRING_STRING_BOXED) (gpointer data1, const char* arg_1, const char* arg_2, gpointer arg_3, gpointer data2);
	register GMarshalFunc_VOID__STRING_STRING_BOXED callback;
	register GCClosure * cc;
	register gpointer data1, data2;
	cc = (GCClosure *) closure;
	g_return_if_fail (n_param_values == 4);
	if (G_CCLOSURE_SWAP_DATA (closure)) {
		data1 = closure->data;
		data2 = param_values->data[0].v_pointer;
	} else {
		data1 = param_values->data[0].v_pointer;
		data2 = closure->data;
	}
	callback = (GMarshalFunc_VOID__STRING_STRING_BOXED) (marshal_data ? marshal_data : cc->callback);
	callback (data1, g_value_get_string (param_values + 1), g_value_get_string (param_values + 2), g_value_get_boxed (param_values + 3), data2);
}



