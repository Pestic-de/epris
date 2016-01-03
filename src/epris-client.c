
#include <glib.h>
#include <glib-object.h>
#include <dbus/dbus-glib-lowlevel.h>
#include <dbus/dbus-glib.h>
#include <stdlib.h>
#include <string.h>


#define EPRIS_TYPE_STRUCTURE (epris_structure_get_type ())
#define EPRIS_STRUCTURE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), EPRIS_TYPE_STRUCTURE, EprisStructure))
#define EPRIS_STRUCTURE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), EPRIS_TYPE_STRUCTURE, EprisStructureClass))
#define EPRIS_IS_STRUCTURE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), EPRIS_TYPE_STRUCTURE))
#define EPRIS_IS_STRUCTURE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), EPRIS_TYPE_STRUCTURE))
#define EPRIS_STRUCTURE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), EPRIS_TYPE_STRUCTURE, EprisStructureClass))

typedef struct _EprisStructure EprisStructure;
typedef struct _EprisStructureClass EprisStructureClass;
typedef struct _EprisStructurePrivate EprisStructurePrivate;

#define EPRIS_TYPE_DBUS_PROXY (epris_dbus_proxy_get_type ())
#define EPRIS_DBUS_PROXY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), EPRIS_TYPE_DBUS_PROXY, EprisDBusProxy))
#define EPRIS_DBUS_PROXY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), EPRIS_TYPE_DBUS_PROXY, EprisDBusProxyClass))
#define EPRIS_IS_DBUS_PROXY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), EPRIS_TYPE_DBUS_PROXY))
#define EPRIS_IS_DBUS_PROXY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), EPRIS_TYPE_DBUS_PROXY))
#define EPRIS_DBUS_PROXY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), EPRIS_TYPE_DBUS_PROXY, EprisDBusProxyClass))

typedef struct _EprisDBusProxy EprisDBusProxy;
typedef struct _EprisDBusProxyClass EprisDBusProxyClass;
typedef struct _EprisDBusProxyPrivate EprisDBusProxyPrivate;

#define EPRIS_TYPE_CLIENT (epris_client_get_type ())
#define EPRIS_CLIENT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), EPRIS_TYPE_CLIENT, EprisClient))
#define EPRIS_CLIENT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), EPRIS_TYPE_CLIENT, EprisClientClass))
#define EPRIS_IS_CLIENT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), EPRIS_TYPE_CLIENT))
#define EPRIS_IS_CLIENT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), EPRIS_TYPE_CLIENT))
#define EPRIS_CLIENT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), EPRIS_TYPE_CLIENT, EprisClientClass))

typedef struct _EprisClient EprisClient;
typedef struct _EprisClientClass EprisClientClass;
typedef struct _EprisClientPrivate EprisClientPrivate;

struct _EprisStructure {
	GObject parent_instance;
	EprisStructurePrivate * priv;
	GSList* fields;
	GQuark _name;
};

struct _EprisStructureClass {
	GObjectClass parent_class;
	void (*qset) (EprisStructure* self, GQuark field, GValue* value);
};

struct _EprisDBusProxy {
	EprisStructure parent_instance;
	EprisDBusProxyPrivate * priv;
	DBusGProxy* iself;
	DBusGProxy* iprop;
};

struct _EprisDBusProxyClass {
	EprisStructureClass parent_class;
};

struct _EprisDBusProxyPrivate {
	DBusGConnection* _conn;
	gboolean _updated;
};

struct _EprisClient {
	EprisDBusProxy parent_instance;
	EprisClientPrivate * priv;
};

struct _EprisClientClass {
	EprisDBusProxyClass parent_class;
};



GType epris_structure_get_type (void);
GType epris_dbus_proxy_get_type (void);
#define EPRIS_DBUS_PROXY_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), EPRIS_TYPE_DBUS_PROXY, EprisDBusProxyPrivate))
enum  {
	EPRIS_DBUS_PROXY_DUMMY_PROPERTY,
	EPRIS_DBUS_PROXY_CONN,
	EPRIS_DBUS_PROXY_UPDATED
};
void epris_dbus_proxy_set_conn (EprisDBusProxy* self, DBusGConnection* value);
void epris_dbus_proxy_set_updated (EprisDBusProxy* self, gboolean value);
EprisDBusProxy* epris_dbus_proxy_new (DBusGConnection* connection);
EprisDBusProxy* epris_dbus_proxy_construct (GType object_type, DBusGConnection* connection);
EprisDBusProxy* epris_dbus_proxy_new (DBusGConnection* connection);
void epris_structure_set_name (EprisStructure* self, const char* value);
DBusGConnection* epris_dbus_proxy_get_conn (EprisDBusProxy* self);
static void _epris_dbus_proxy_get_all_reply (EprisDBusProxy* self, GHashTable* props, GError* err);
void _dynamic_GetAll8 (DBusGProxy* self, const char* param1, gpointer param2, void* param2_target, GError** error);
void epris_dbus_proxy_initialize (EprisDBusProxy* self, const char* name, const char* path, const char* interface, GError** error);
static GValue* _g_value_dup (GValue* self);
void epris_structure_set (EprisStructure* self, const char* field_name, GValue* value);
char* epris_structure_to_string (EprisStructure* self);
gboolean epris_dbus_proxy_get_updated (EprisDBusProxy* self);
static gpointer epris_dbus_proxy_parent_class = NULL;
static void epris_dbus_proxy_finalize (GObject* obj);
static void epris_dbus_proxy_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void epris_dbus_proxy_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);
GType epris_client_get_type (void);
enum  {
	EPRIS_CLIENT_DUMMY_PROPERTY,
	EPRIS_CLIENT_PLAYER
};
EprisClient* epris_client_new (DBusGConnection* connection);
EprisClient* epris_client_construct (GType object_type, DBusGConnection* connection);
EprisClient* epris_client_new (DBusGConnection* connection);
DBusGProxy* epris_client_get_tracklist (EprisClient* self, const char* listname);
void epris_client_initialize (EprisClient* self, const char* name, GError** error);
DBusGProxy* epris_client_get_player (EprisClient* self);
static gpointer epris_client_parent_class = NULL;
static void epris_client_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);



EprisDBusProxy* epris_dbus_proxy_construct (GType object_type, DBusGConnection* connection) {
	GParameter * __params;
	GParameter * __params_it;
	EprisDBusProxy * self;
	g_return_val_if_fail (connection != NULL, NULL);
	__params = g_new0 (GParameter, 1);
	__params_it = __params;
	__params_it->name = "conn";
	g_value_init (&__params_it->value, G_TYPE_POINTER);
	g_value_set_pointer (&__params_it->value, connection);
	__params_it++;
	self = g_object_newv (object_type, __params_it - __params, __params);
	epris_dbus_proxy_set_updated (self, FALSE);
	while (__params_it > __params) {
		--__params_it;
		g_value_unset (&__params_it->value);
	}
	g_free (__params);
	return self;
}


EprisDBusProxy* epris_dbus_proxy_new (DBusGConnection* connection) {
	return epris_dbus_proxy_construct (EPRIS_TYPE_DBUS_PROXY, connection);
}


static void __epris_dbus_proxy_get_all_reply_cb (DBusGProxy* proxy, DBusGProxyCall* call, void* user_data) {
	GError* error;
	GHashTable* props;
	error = NULL;
	dbus_g_proxy_end_call (proxy, call, &error, dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE), &props, G_TYPE_INVALID);
	_epris_dbus_proxy_get_all_reply (user_data, props, error);
}


void _dynamic_GetAll8 (DBusGProxy* self, const char* param1, gpointer param2, void* param2_target, GError** error) {
	dbus_g_proxy_begin_call (self, "GetAll", __epris_dbus_proxy_get_all_reply_cb, param2_target, NULL, G_TYPE_STRING, param1, G_TYPE_INVALID, G_TYPE_INVALID);
	if (*error) {
		return;
	}
}


void epris_dbus_proxy_initialize (EprisDBusProxy* self, const char* name, const char* path, const char* interface, GError** error) {
	GError * _inner_error_;
	DBusGProxy* _tmp0_;
	DBusGProxy* _tmp1_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (name != NULL);
	g_return_if_fail (path != NULL);
	g_return_if_fail (interface != NULL);
	_inner_error_ = NULL;
	epris_structure_set_name ((EprisStructure*) self, path);
	_tmp0_ = NULL;
	self->iself = (_tmp0_ = dbus_g_proxy_new_for_name (self->priv->_conn, name, path, interface), (self->iself == NULL) ? NULL : (self->iself = (g_object_unref (self->iself), NULL)), _tmp0_);
	_tmp1_ = NULL;
	self->iprop = (_tmp1_ = dbus_g_proxy_new_for_name (self->priv->_conn, name, path, "org.freedesktop.DBus.Properties"), (self->iprop == NULL) ? NULL : (self->iprop = (g_object_unref (self->iprop), NULL)), _tmp1_);
	_dynamic_GetAll8 (self->iprop, interface, _epris_dbus_proxy_get_all_reply, self, &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
}


static GValue* _g_value_dup (GValue* self) {
	return g_boxed_copy (G_TYPE_VALUE, self);
}


static void _epris_dbus_proxy_get_all_reply (EprisDBusProxy* self, GHashTable* props, GError* err) {
	char* _tmp6_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (props != NULL);
	if (err != NULL) {
		g_warning (err->message);
		return;
	}
	{
		GList* key_collection;
		GList* key_it;
		key_collection = g_hash_table_get_keys (props);
		for (key_it = key_collection; key_it != NULL; key_it = key_it->next) {
			const char* key;
			key = (const char*) key_it->data;
			{
				GValue* _tmp0_;
				GValue* v;
				char* _tmp4_;
				char* _tmp3_;
				char* _tmp2_;
				char* _tmp1_;
				GValue* _tmp5_;
				_tmp0_ = NULL;
				v = (_tmp0_ = (GValue*) g_hash_table_lookup (props, key), (_tmp0_ == NULL) ? NULL : _g_value_dup (_tmp0_));
				_tmp4_ = NULL;
				_tmp3_ = NULL;
				_tmp2_ = NULL;
				_tmp1_ = NULL;
				g_message (_tmp4_ = g_strconcat (_tmp2_ = g_strconcat (_tmp1_ = g_strconcat ("key ", key, NULL), " ", NULL), _tmp3_ = g_strdup_value_contents (v), NULL));
				_tmp4_ = (g_free (_tmp4_), NULL);
				_tmp3_ = (g_free (_tmp3_), NULL);
				_tmp2_ = (g_free (_tmp2_), NULL);
				_tmp1_ = (g_free (_tmp1_), NULL);
				_tmp5_ = NULL;
				epris_structure_set ((EprisStructure*) self, key, (_tmp5_ = v, (_tmp5_ == NULL) ? NULL : _g_value_dup (_tmp5_)));
				(v == NULL) ? NULL : (v = (g_free (v), NULL));
			}
		}
		(key_collection == NULL) ? NULL : (key_collection = (g_list_free (key_collection), NULL));
	}
	g_hash_table_steal_all (props);
	_tmp6_ = NULL;
	g_message (_tmp6_ = epris_structure_to_string ((EprisStructure*) self));
	_tmp6_ = (g_free (_tmp6_), NULL);
	epris_dbus_proxy_set_updated (self, TRUE);
}


DBusGConnection* epris_dbus_proxy_get_conn (EprisDBusProxy* self) {
	DBusGConnection* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_conn;
	return result;
}


void epris_dbus_proxy_set_conn (EprisDBusProxy* self, DBusGConnection* value) {
	DBusGConnection* _tmp1_;
	DBusGConnection* _tmp0_;
	g_return_if_fail (self != NULL);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	self->priv->_conn = (_tmp1_ = (_tmp0_ = value, (_tmp0_ == NULL) ? NULL : dbus_g_connection_ref (_tmp0_)), (self->priv->_conn == NULL) ? NULL : (self->priv->_conn = (dbus_g_connection_unref (self->priv->_conn), NULL)), _tmp1_);
	g_object_notify ((GObject *) self, "conn");
}


gboolean epris_dbus_proxy_get_updated (EprisDBusProxy* self) {
	gboolean result;
	g_return_val_if_fail (self != NULL, FALSE);
	result = self->priv->_updated;
	return result;
}


void epris_dbus_proxy_set_updated (EprisDBusProxy* self, gboolean value) {
	g_return_if_fail (self != NULL);
	self->priv->_updated = value;
	g_object_notify ((GObject *) self, "updated");
}


static void epris_dbus_proxy_class_init (EprisDBusProxyClass * klass) {
	epris_dbus_proxy_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (EprisDBusProxyPrivate));
	G_OBJECT_CLASS (klass)->get_property = epris_dbus_proxy_get_property;
	G_OBJECT_CLASS (klass)->set_property = epris_dbus_proxy_set_property;
	G_OBJECT_CLASS (klass)->finalize = epris_dbus_proxy_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), EPRIS_DBUS_PROXY_CONN, g_param_spec_pointer ("conn", "conn", "conn", G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE | G_PARAM_CONSTRUCT));
	g_object_class_install_property (G_OBJECT_CLASS (klass), EPRIS_DBUS_PROXY_UPDATED, g_param_spec_boolean ("updated", "updated", "updated", FALSE, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
}


static void epris_dbus_proxy_instance_init (EprisDBusProxy * self) {
	self->priv = EPRIS_DBUS_PROXY_GET_PRIVATE (self);
}


static void epris_dbus_proxy_finalize (GObject* obj) {
	EprisDBusProxy * self;
	self = EPRIS_DBUS_PROXY (obj);
	(self->priv->_conn == NULL) ? NULL : (self->priv->_conn = (dbus_g_connection_unref (self->priv->_conn), NULL));
	(self->iself == NULL) ? NULL : (self->iself = (g_object_unref (self->iself), NULL));
	(self->iprop == NULL) ? NULL : (self->iprop = (g_object_unref (self->iprop), NULL));
	G_OBJECT_CLASS (epris_dbus_proxy_parent_class)->finalize (obj);
}


GType epris_dbus_proxy_get_type (void) {
	static GType epris_dbus_proxy_type_id = 0;
	if (epris_dbus_proxy_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (EprisDBusProxyClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) epris_dbus_proxy_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (EprisDBusProxy), 0, (GInstanceInitFunc) epris_dbus_proxy_instance_init, NULL };
		epris_dbus_proxy_type_id = g_type_register_static (EPRIS_TYPE_STRUCTURE, "EprisDBusProxy", &g_define_type_info, 0);
	}
	return epris_dbus_proxy_type_id;
}


static void epris_dbus_proxy_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	EprisDBusProxy * self;
	gpointer boxed;
	self = EPRIS_DBUS_PROXY (object);
	switch (property_id) {
		case EPRIS_DBUS_PROXY_CONN:
		g_value_set_pointer (value, epris_dbus_proxy_get_conn (self));
		break;
		case EPRIS_DBUS_PROXY_UPDATED:
		g_value_set_boolean (value, epris_dbus_proxy_get_updated (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void epris_dbus_proxy_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	EprisDBusProxy * self;
	self = EPRIS_DBUS_PROXY (object);
	switch (property_id) {
		case EPRIS_DBUS_PROXY_CONN:
		epris_dbus_proxy_set_conn (self, g_value_get_pointer (value));
		break;
		case EPRIS_DBUS_PROXY_UPDATED:
		epris_dbus_proxy_set_updated (self, g_value_get_boolean (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


EprisClient* epris_client_construct (GType object_type, DBusGConnection* connection) {
	GParameter * __params;
	GParameter * __params_it;
	EprisClient * self;
	g_return_val_if_fail (connection != NULL, NULL);
	__params = g_new0 (GParameter, 1);
	__params_it = __params;
	__params_it->name = "conn";
	g_value_init (&__params_it->value, G_TYPE_POINTER);
	g_value_set_pointer (&__params_it->value, connection);
	__params_it++;
	self = g_object_newv (object_type, __params_it - __params, __params);
	while (__params_it > __params) {
		--__params_it;
		g_value_unset (&__params_it->value);
	}
	g_free (__params);
	return self;
}


EprisClient* epris_client_new (DBusGConnection* connection) {
	return epris_client_construct (EPRIS_TYPE_CLIENT, connection);
}


DBusGProxy* epris_client_get_tracklist (EprisClient* self, const char* listname) {
	DBusGProxy* result;
	char* _tmp1_;
	char* _tmp0_;
	DBusGProxy* _tmp2_;
	DBusGProxy* list;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (listname != NULL, NULL);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	_tmp2_ = NULL;
	list = (_tmp2_ = dbus_g_proxy_new_for_name (epris_dbus_proxy_get_conn ((EprisDBusProxy*) self), dbus_g_proxy_get_bus_name (((EprisDBusProxy*) self)->iself), _tmp1_ = g_strconcat (_tmp0_ = g_strconcat (dbus_g_proxy_get_path (((EprisDBusProxy*) self)->iself), "/lists/", NULL), listname, NULL), "org.mpris.EprisTrackList"), _tmp1_ = (g_free (_tmp1_), NULL), _tmp0_ = (g_free (_tmp0_), NULL), _tmp2_);
	result = list;
	return result;
}


void epris_client_initialize (EprisClient* self, const char* name, GError** error) {
	GError * _inner_error_;
	char* _tmp1_;
	char* _tmp0_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (name != NULL);
	_inner_error_ = NULL;
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	epris_dbus_proxy_initialize (EPRIS_DBUS_PROXY (self), _tmp0_ = g_strconcat ("org.mpris.", name, NULL), _tmp1_ = g_strconcat ("/org/mpris/", name, NULL), "org.mpris.EprisPlayer", &_inner_error_);
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	_tmp1_ = (g_free (_tmp1_), NULL);
	_tmp0_ = (g_free (_tmp0_), NULL);
}


DBusGProxy* epris_client_get_player (EprisClient* self) {
	DBusGProxy* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = ((EprisDBusProxy*) self)->iself;
	return result;
}


static void epris_client_class_init (EprisClientClass * klass) {
	epris_client_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->get_property = epris_client_get_property;
	g_object_class_install_property (G_OBJECT_CLASS (klass), EPRIS_CLIENT_PLAYER, g_param_spec_object ("player", "player", "player", DBUS_TYPE_G_PROXY, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE));
}


static void epris_client_instance_init (EprisClient * self) {
}


GType epris_client_get_type (void) {
	static GType epris_client_type_id = 0;
	if (epris_client_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (EprisClientClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) epris_client_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (EprisClient), 0, (GInstanceInitFunc) epris_client_instance_init, NULL };
		epris_client_type_id = g_type_register_static (EPRIS_TYPE_DBUS_PROXY, "EprisClient", &g_define_type_info, 0);
	}
	return epris_client_type_id;
}


static void epris_client_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	EprisClient * self;
	gpointer boxed;
	self = EPRIS_CLIENT (object);
	switch (property_id) {
		case EPRIS_CLIENT_PLAYER:
		g_value_set_object (value, epris_client_get_player (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}




