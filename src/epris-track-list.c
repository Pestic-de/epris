
#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <gst/gst.h>
#include <stdio.h>
#include <errno.h>
#include <gobject/gvaluecollector.h>
#include <dbus/dbus.h>
#include <dbus/dbus-glib.h>
#include <dbus/dbus-glib-lowlevel.h>


#define EPRIS_TYPE_PROPERTIES_NOTIFY (epris_properties_notify_get_type ())
#define EPRIS_PROPERTIES_NOTIFY(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), EPRIS_TYPE_PROPERTIES_NOTIFY, EprisPropertiesNotify))
#define EPRIS_PROPERTIES_NOTIFY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), EPRIS_TYPE_PROPERTIES_NOTIFY, EprisPropertiesNotifyClass))
#define EPRIS_IS_PROPERTIES_NOTIFY(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), EPRIS_TYPE_PROPERTIES_NOTIFY))
#define EPRIS_IS_PROPERTIES_NOTIFY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), EPRIS_TYPE_PROPERTIES_NOTIFY))
#define EPRIS_PROPERTIES_NOTIFY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), EPRIS_TYPE_PROPERTIES_NOTIFY, EprisPropertiesNotifyClass))

typedef struct _EprisPropertiesNotify EprisPropertiesNotify;
typedef struct _EprisPropertiesNotifyClass EprisPropertiesNotifyClass;
typedef struct _EprisPropertiesNotifyPrivate EprisPropertiesNotifyPrivate;

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

#define EPRIS_TYPE_WHENCE (epris_whence_get_type ())

#define TYPE_TRACK_LIST (track_list_get_type ())
#define TRACK_LIST(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_TRACK_LIST, TrackList))
#define TRACK_LIST_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_TRACK_LIST, TrackListClass))
#define IS_TRACK_LIST(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_TRACK_LIST))
#define IS_TRACK_LIST_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_TRACK_LIST))
#define TRACK_LIST_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_TRACK_LIST, TrackListClass))

typedef struct _TrackList TrackList;
typedef struct _TrackListClass TrackListClass;
typedef struct _TrackListPrivate TrackListPrivate;

#define TRACK_LIST_TYPE_TRACK (track_list_track_get_type ())
#define TRACK_LIST_TRACK(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TRACK_LIST_TYPE_TRACK, TrackListTrack))
#define TRACK_LIST_TRACK_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TRACK_LIST_TYPE_TRACK, TrackListTrackClass))
#define TRACK_LIST_IS_TRACK(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TRACK_LIST_TYPE_TRACK))
#define TRACK_LIST_IS_TRACK_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TRACK_LIST_TYPE_TRACK))
#define TRACK_LIST_TRACK_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TRACK_LIST_TYPE_TRACK, TrackListTrackClass))

typedef struct _TrackListTrack TrackListTrack;
typedef struct _TrackListTrackClass TrackListTrackClass;
typedef struct _TrackListTrackPrivate TrackListTrackPrivate;
typedef struct _TrackListParamSpecTrack TrackListParamSpecTrack;
typedef struct _DBusObjectVTable _DBusObjectVTable;

struct _EprisPropertiesNotify {
	GObject parent_instance;
	EprisPropertiesNotifyPrivate * priv;
};

struct _EprisPropertiesNotifyClass {
	GObjectClass parent_class;
};

struct _EprisTrackListTrick {
	EprisPropertiesNotify parent_instance;
	EprisTrackListTrickPrivate * priv;
	GHashTable* _current;
};

struct _EprisTrackListTrickClass {
	EprisPropertiesNotifyClass parent_class;
};

typedef enum  {
	EPRIS_ERROR_NONE,
	EPRIS_ERROR_NOT_SUPPORTED,
	EPRIS_ERROR_STATE,
	EPRIS_ERROR_ARGUMENT
} EprisError;
#define EPRIS_ERROR epris_error_quark ()
typedef enum  {
	EPRIS_WHENCE_START,
	EPRIS_WHENCE_CURRENT,
	EPRIS_WHENCE_END
} EprisWhence;

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

struct _TrackList {
	EprisTrackList parent_instance;
	TrackListPrivate * priv;
	GList* tracklist;
};

struct _TrackListClass {
	EprisTrackListClass parent_class;
};

struct _TrackListPrivate {
	TrackListTrack* _current_track;
	char* _name;
	char* _path;
	guint _position;
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

struct _TrackListParamSpecTrack {
	GParamSpec parent_instance;
};

struct _DBusObjectVTable {
	void (*register_object) (DBusConnection*, const char*, void*);
};



GType epris_properties_notify_get_type (void);
GType epris_track_list_trick_get_type (void);
GType epris_track_list_get_type (void);
GQuark epris_error_quark (void);
GType epris_whence_get_type (void);
GType track_list_get_type (void);
gpointer track_list_track_ref (gpointer instance);
void track_list_track_unref (gpointer instance);
GParamSpec* track_list_param_spec_track (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void track_list_value_set_track (GValue* value, gpointer v_object);
gpointer track_list_value_get_track (const GValue* value);
GType track_list_track_get_type (void);
#define TRACK_LIST_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_TRACK_LIST, TrackListPrivate))
enum  {
	TRACK_LIST_DUMMY_PROPERTY,
	TRACK_LIST_CURRENT_TRACK,
	TRACK_LIST_NAME,
	TRACK_LIST_PATH,
	TRACK_LIST_POSITION
};
static void _g_list_free_track_list_track_unref (GList* self);
void track_list_set_path (TrackList* self, const char* value);
static void track_list_set_current_track (TrackList* self, TrackListTrack* value);
TrackList* track_list_new (const char* path);
TrackList* track_list_construct (GType object_type, const char* path);
TrackList* track_list_new (const char* path);
TrackListTrack* track_list_track_new (const char* uri);
TrackListTrack* track_list_track_construct (GType object_type, const char* uri);
static gint _track_list_track_cmp_uri (TrackListTrack* a, TrackListTrack* b);
static gboolean track_list_add (TrackList* self, const char* uri, GError** error);
gboolean track_list_save (TrackList* self, gboolean save_list, gboolean save_keyfile);
static void track_list_real_AddTracks (EprisTrackList* base, char** uris, int uris_length1, gboolean immediately, GError** error);
static gboolean track_list_rm (TrackList* self, const char* uri, GError** error);
static void track_list_real_DelTracks (EprisTrackList* base, char** uris, int uris_length1, gboolean immediately, GError** error);
GHashTable* track_list_track_get_hsv (TrackListTrack* self);
guint track_list_get_position (TrackList* self);
static GValue* _g_value_dup (GValue* self);
static GHashTable** track_list_real_ListTracks (EprisTrackList* base, int* result_length1, GError** error);
const char* track_list_get_path (TrackList* self);
gboolean epris_keyfile_save (GKeyFile* key_file, const char* file_path);
void track_list_set_position (TrackList* self, guint value);
gboolean track_list_load (TrackList* self);
TrackListTrack* track_list_seek (TrackList* self, gint offset, EprisWhence whence, GError** error);
static void track_list_real_Seek (EprisTrackList* base, gint offset, EprisWhence whence, GError** error);
TrackListTrack* track_list_get_current_track (TrackList* self);
const char* track_list_get_name (TrackList* self);
void track_list_set_name (TrackList* self, const char* value);
void epris_track_list_set_current (EprisTrackList* self, GHashTable* value);
enum  {
	TRACK_LIST_TRACK_DUMMY_PROPERTY
};
TrackListTrack* track_list_track_new (const char* uri);
static gpointer track_list_track_parent_class = NULL;
static void track_list_track_finalize (TrackListTrack* obj);
static gpointer track_list_parent_class = NULL;
void track_list_dbus_register_object (DBusConnection* connection, const char* path, void* object);
void _track_list_dbus_unregister (DBusConnection* connection, void* user_data);
DBusHandlerResult track_list_dbus_message (DBusConnection* connection, DBusMessage* message, void* object);
static DBusMessage* _dbus_track_list_introspect (TrackList* self, DBusConnection* connection, DBusMessage* message);
static void track_list_finalize (GObject* obj);
static void track_list_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void track_list_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);
static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);
static int _vala_strcmp0 (const char * str1, const char * str2);
static void _vala_dbus_register_object (DBusConnection* connection, const char* path, void* object);
static void _vala_dbus_unregister_object (gpointer connection, GObject* object);

static const DBusObjectPathVTable _track_list_dbus_path_vtable = {_track_list_dbus_unregister, track_list_dbus_message};
static const _DBusObjectVTable _track_list_dbus_vtable = {track_list_dbus_register_object};


static void _g_list_free_track_list_track_unref (GList* self) {
	g_list_foreach (self, (GFunc) track_list_track_unref, NULL);
	g_list_free (self);
}


TrackList* track_list_construct (GType object_type, const char* path) {
	TrackList * self;
	char* _tmp0_;
	gboolean _tmp1_;
	g_return_val_if_fail (path != NULL, NULL);
	self = g_object_newv (object_type, 0, NULL);
	track_list_set_path (self, path);
	_tmp0_ = NULL;
	if ((_tmp1_ = g_mkdir_with_parents (_tmp0_ = g_path_get_dirname (path), 0700) != 0, _tmp0_ = (g_free (_tmp0_), NULL), _tmp1_)) {
		char* _tmp2_;
		_tmp2_ = NULL;
		g_warning ("epris-track-list.vala:40: Failed to create %s", _tmp2_ = g_path_get_dirname (path));
		_tmp2_ = (g_free (_tmp2_), NULL);
	}
	track_list_set_current_track (self, NULL);
	return self;
}


TrackList* track_list_new (const char* path) {
	return track_list_construct (TYPE_TRACK_LIST, path);
}


static gboolean track_list_add (TrackList* self, const char* uri, GError** error) {
	gboolean result;
	TrackListTrack* track;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (uri != NULL, FALSE);
	g_strstrip (uri);
	if (_vala_strcmp0 (uri, "") == 0) {
		result = FALSE;
		return result;
	}
	if (gst_uri_is_valid (uri) == FALSE) {
		g_warning ("epris-track-list.vala:52: Uri is not valid: %s", uri);
	}
	track = track_list_track_new (uri);
	if (g_list_find_custom (self->tracklist, track, (GCompareFunc) _track_list_track_cmp_uri) == NULL) {
		TrackListTrack* _tmp0_;
		_tmp0_ = NULL;
		self->tracklist = g_list_insert (self->tracklist, (_tmp0_ = track, (_tmp0_ == NULL) ? NULL : track_list_track_ref (_tmp0_)), -1);
	}
	result = TRUE;
	(track == NULL) ? NULL : (track = (track_list_track_unref (track), NULL));
	return result;
}


static gint _track_list_track_cmp_uri (TrackListTrack* a, TrackListTrack* b) {
	gint result;
	g_return_val_if_fail (a != NULL, 0);
	g_return_val_if_fail (b != NULL, 0);
	result = strcmp (a->uri, b->uri);
	return result;
}


static void track_list_real_AddTracks (EprisTrackList* base, char** uris, int uris_length1, gboolean immediately, GError** error) {
	TrackList * self;
	GError * _inner_error_;
	self = (TrackList*) base;
	_inner_error_ = NULL;
	{
		char** uri_collection;
		int uri_collection_length1;
		int uri_it;
		uri_collection = uris;
		uri_collection_length1 = uris_length1;
		for (uri_it = 0; uri_it < uris_length1; uri_it = uri_it + 1) {
			const char* _tmp0_;
			char* uri;
			_tmp0_ = NULL;
			uri = (_tmp0_ = uri_collection[uri_it], (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_));
			{
				{
					track_list_add (self, uri, &_inner_error_);
					if (_inner_error_ != NULL) {
						goto __catch11_g_error;
						goto __finally11;
					}
				}
				goto __finally11;
				__catch11_g_error:
				{
					GError * _error_;
					_error_ = _inner_error_;
					_inner_error_ = NULL;
					{
						g_warning (_error_->message);
						(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
					}
				}
				__finally11:
				if (_inner_error_ != NULL) {
					if (_inner_error_->domain == EPRIS_ERROR) {
						g_propagate_error (error, _inner_error_);
						uri = (g_free (uri), NULL);
						return;
					} else {
						uri = (g_free (uri), NULL);
						g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
						g_clear_error (&_inner_error_);
						return;
					}
				}
				uri = (g_free (uri), NULL);
			}
		}
	}
	track_list_save (self, TRUE, FALSE);
}


static gboolean track_list_rm (TrackList* self, const char* uri, GError** error) {
	gboolean result;
	TrackListTrack* track;
	GList* link;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (uri != NULL, FALSE);
	track = track_list_track_new (uri);
	link = g_list_find_custom (self->tracklist, track, (GCompareFunc) _track_list_track_cmp_uri);
	if (link != NULL) {
		self->tracklist = g_list_remove_link (self->tracklist, link);
		result = TRUE;
		(track == NULL) ? NULL : (track = (track_list_track_unref (track), NULL));
		return result;
	}
	g_debug ("epris-track-list.vala:87: track %s not found", uri);
	result = FALSE;
	(track == NULL) ? NULL : (track = (track_list_track_unref (track), NULL));
	return result;
}


static void track_list_real_DelTracks (EprisTrackList* base, char** uris, int uris_length1, gboolean immediately, GError** error) {
	TrackList * self;
	GError * _inner_error_;
	self = (TrackList*) base;
	_inner_error_ = NULL;
	{
		char** uri_collection;
		int uri_collection_length1;
		int uri_it;
		uri_collection = uris;
		uri_collection_length1 = uris_length1;
		for (uri_it = 0; uri_it < uris_length1; uri_it = uri_it + 1) {
			const char* _tmp0_;
			char* uri;
			_tmp0_ = NULL;
			uri = (_tmp0_ = uri_collection[uri_it], (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_));
			{
				{
					track_list_rm (self, uri, &_inner_error_);
					if (_inner_error_ != NULL) {
						goto __catch12_g_error;
						goto __finally12;
					}
				}
				goto __finally12;
				__catch12_g_error:
				{
					GError * _error_;
					_error_ = _inner_error_;
					_inner_error_ = NULL;
					{
						g_warning (_error_->message);
						(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
					}
				}
				__finally12:
				if (_inner_error_ != NULL) {
					if (_inner_error_->domain == EPRIS_ERROR) {
						g_propagate_error (error, _inner_error_);
						uri = (g_free (uri), NULL);
						return;
					} else {
						uri = (g_free (uri), NULL);
						g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
						g_clear_error (&_inner_error_);
						return;
					}
				}
				uri = (g_free (uri), NULL);
			}
		}
	}
	track_list_save (self, TRUE, TRUE);
}


static GValue* _g_value_dup (GValue* self) {
	return g_boxed_copy (G_TYPE_VALUE, self);
}


static GHashTable** track_list_real_ListTracks (EprisTrackList* base, int* result_length1, GError** error) {
	TrackList * self;
	GHashTable** result;
	gint len;
	GHashTable** _tmp0_;
	gint list_size;
	gint list_length1;
	GHashTable** list;
	guint i;
	GHashTable** _tmp5_;
	self = (TrackList*) base;
	len = (gint) g_list_length (self->tracklist);
	g_debug ("epris-track-list.vala:106: listtracks len: %d", len);
	_tmp0_ = NULL;
	list = (_tmp0_ = g_new0 (GHashTable*, len + 1), list_length1 = len, list_size = list_length1, _tmp0_);
	i = (guint) 0;
	{
		GList* t_collection;
		GList* t_it;
		t_collection = self->tracklist;
		for (t_it = t_collection; t_it != NULL; t_it = t_it->next) {
			TrackListTrack* _tmp4_;
			TrackListTrack* t;
			_tmp4_ = NULL;
			t = (_tmp4_ = (TrackListTrack*) t_it->data, (_tmp4_ == NULL) ? NULL : track_list_track_ref (_tmp4_));
			{
				GHashTable* _tmp1_;
				_tmp1_ = NULL;
				list[i] = (_tmp1_ = track_list_track_get_hsv (t), (list[i] == NULL) ? NULL : (list[i] = (g_hash_table_unref (list[i]), NULL)), _tmp1_);
				if (track_list_get_position (self) == i) {
					GValue _tmp2_ = {0};
					GValue vb;
					GValue* _tmp3_;
					vb = (g_value_init (&_tmp2_, G_TYPE_BOOLEAN), _tmp2_);
					g_value_set_boolean (&vb, TRUE);
					_tmp3_ = NULL;
					g_hash_table_insert (list[i], g_strdup ("current"), (_tmp3_ = &vb, (_tmp3_ == NULL) ? NULL : _g_value_dup (_tmp3_)));
					G_IS_VALUE (&vb) ? (g_value_unset (&vb), NULL) : NULL;
				}
				i = i + ((guint) 1);
				(t == NULL) ? NULL : (t = (track_list_track_unref (t), NULL));
			}
		}
	}
	_tmp5_ = NULL;
	result = (_tmp5_ = list, *result_length1 = list_length1, _tmp5_);
	return result;
	list = (_vala_array_free (list, list_length1, (GDestroyNotify) g_hash_table_unref), NULL);
}


gboolean track_list_save (TrackList* self, gboolean save_list, gboolean save_keyfile) {
	gboolean result;
	gboolean success;
	g_return_val_if_fail (self != NULL, FALSE);
	success = TRUE;
	if (save_list) {
		FILE* f;
		g_message ("epris-track-list.vala:127: Saving tracklist at %s", self->priv->_path);
		f = fopen (self->priv->_path, "w+");
		if (f == NULL) {
		}
		/*throw new FileError.INVAL (strerror (errno));*/
		{
			GList* track_collection;
			GList* track_it;
			track_collection = self->tracklist;
			for (track_it = track_collection; track_it != NULL; track_it = track_it->next) {
				TrackListTrack* _tmp0_;
				TrackListTrack* track;
				_tmp0_ = NULL;
				track = (_tmp0_ = (TrackListTrack*) track_it->data, (_tmp0_ == NULL) ? NULL : track_list_track_ref (_tmp0_));
				{
					fputs (track->uri, f);
					fputc ('\n', f);
					(track == NULL) ? NULL : (track = (track_list_track_unref (track), NULL));
				}
			}
		}
		fflush (f);
		(f == NULL) ? NULL : (f = (fclose (f), NULL));
	}
	if (save_keyfile) {
		GKeyFile* keyfile;
		char* _tmp1_;
		keyfile = g_key_file_new ();
		g_key_file_set_integer (keyfile, "List", "position", (gint) track_list_get_position (self));
		_tmp1_ = NULL;
		success = epris_keyfile_save (keyfile, _tmp1_ = g_strconcat (self->priv->_path, ".ini", NULL));
		_tmp1_ = (g_free (_tmp1_), NULL);
		(keyfile == NULL) ? NULL : (keyfile = (g_key_file_free (keyfile), NULL));
	}
	result = success;
	return result;
}


gboolean track_list_load (TrackList* self) {
	gboolean result;
	GError * _inner_error_;
	GKeyFile* keyfile;
	g_return_val_if_fail (self != NULL, FALSE);
	_inner_error_ = NULL;
	g_message ("epris-track-list.vala:150: Opening tracklist at %s", self->priv->_path);
	{
		FILE* f;
		gchar* _tmp0_;
		gint c_size;
		gint c_length1;
		gchar* c;
		const char* _tmp1_;
		char* s;
		f = fopen (self->priv->_path, "r");
		if (f == NULL) {
			_inner_error_ = g_error_new_literal (G_FILE_ERROR, G_FILE_ERROR_INVAL, g_strerror (errno));
			if (_inner_error_ != NULL) {
				(f == NULL) ? NULL : (f = (fclose (f), NULL));
				goto __catch13_g_error;
				goto __finally13;
			}
		}
		_tmp0_ = NULL;
		c = (_tmp0_ = g_new0 (gchar, 4096), c_length1 = 4096, c_size = c_length1, _tmp0_);
		_tmp1_ = NULL;
		s = (_tmp1_ = fgets (c, c_length1, f), (_tmp1_ == NULL) ? NULL : g_strdup (_tmp1_));
		while (TRUE) {
			char* _tmp3_;
			const char* _tmp2_;
			if (!(s != NULL)) {
				break;
			}
			track_list_add (self, s, &_inner_error_);
			if (_inner_error_ != NULL) {
				(f == NULL) ? NULL : (f = (fclose (f), NULL));
				c = (g_free (c), NULL);
				s = (g_free (s), NULL);
				goto __catch13_g_error;
				goto __finally13;
			}
			_tmp3_ = NULL;
			_tmp2_ = NULL;
			s = (_tmp3_ = (_tmp2_ = fgets (c, c_length1, f), (_tmp2_ == NULL) ? NULL : g_strdup (_tmp2_)), s = (g_free (s), NULL), _tmp3_);
		}
		(f == NULL) ? NULL : (f = (fclose (f), NULL));
		c = (g_free (c), NULL);
		s = (g_free (s), NULL);
	}
	goto __finally13;
	__catch13_g_error:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		{
			g_warning (_error_->message);
			(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
		}
	}
	__finally13:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return FALSE;
	}
	keyfile = g_key_file_new ();
	{
		char* _tmp4_;
		_tmp4_ = NULL;
		g_key_file_load_from_file (keyfile, _tmp4_ = g_strconcat (self->priv->_path, ".ini", NULL), G_KEY_FILE_KEEP_COMMENTS | G_KEY_FILE_KEEP_TRANSLATIONS, &_inner_error_);
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == G_KEY_FILE_ERROR) {
				goto __catch14_g_key_file_error;
			}
			goto __catch14_g_error;
			goto __finally14;
		}
		_tmp4_ = (g_free (_tmp4_), NULL);
	}
	goto __finally14;
	__catch14_g_key_file_error:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		{
			/* if (error.code != KeyFileError.NOT_FOUND)*/
			g_warning ("epris-track-list.vala:174: %s (while loading playlist)", _error_->message);
			(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
		}
	}
	goto __finally14;
	__catch14_g_error:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		{
			g_warning ("epris-track-list.vala:176: %s (while loading playlist)", _error_->message);
			(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
		}
	}
	__finally14:
	if (_inner_error_ != NULL) {
		(keyfile == NULL) ? NULL : (keyfile = (g_key_file_free (keyfile), NULL));
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return FALSE;
	}
	{
		gint _tmp5_;
		track_list_set_position (self, (guint) 0);
		_tmp5_ = g_key_file_get_integer (keyfile, "List", "position", &_inner_error_);
		if (_inner_error_ != NULL) {
			goto __catch15_g_error;
			goto __finally15;
		}
		track_list_set_position (self, (guint) _tmp5_);
	}
	goto __finally15;
	__catch15_g_error:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		{
			g_warning (_error_->message);
			(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
		}
	}
	__finally15:
	if (_inner_error_ != NULL) {
		(keyfile == NULL) ? NULL : (keyfile = (g_key_file_free (keyfile), NULL));
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return FALSE;
	}
	result = TRUE;
	(keyfile == NULL) ? NULL : (keyfile = (g_key_file_free (keyfile), NULL));
	return result;
}


TrackListTrack* track_list_seek (TrackList* self, gint offset, EprisWhence whence, GError** error) {
	TrackListTrack* result;
	GError * _inner_error_;
	TrackListTrack* _tmp0_;
	TrackListTrack* t;
	g_return_val_if_fail (self != NULL, NULL);
	_inner_error_ = NULL;
	if (g_list_length (self->tracklist) <= 0) {
		track_list_set_position (self, (guint) 0);
		track_list_set_current_track (self, NULL);
		_inner_error_ = g_error_new_literal (EPRIS_ERROR, EPRIS_ERROR_STATE, "Cannot seek: empty playlist");
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
	switch (whence) {
		case EPRIS_WHENCE_CURRENT:
		{
			track_list_set_position (self, (track_list_get_position (self) + offset) % g_list_length (self->tracklist));
			break;
		}
		case EPRIS_WHENCE_START:
		{
			track_list_set_position (self, offset % g_list_length (self->tracklist));
			break;
		}
		case EPRIS_WHENCE_END:
		{
			track_list_set_position (self, (g_list_length (self->tracklist) + offset) % g_list_length (self->tracklist));
			break;
		}
		default:
		{
			_inner_error_ = g_error_new_literal (EPRIS_ERROR, EPRIS_ERROR_ARGUMENT, "Invalid whence type");
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
	}
	_tmp0_ = NULL;
	t = (_tmp0_ = (TrackListTrack*) g_list_nth_data (self->tracklist, track_list_get_position (self)), (_tmp0_ == NULL) ? NULL : track_list_track_ref (_tmp0_));
	track_list_set_current_track (self, t);
	result = t;
	return result;
}


static void track_list_real_Seek (EprisTrackList* base, gint offset, EprisWhence whence, GError** error) {
	TrackList * self;
	GError * _inner_error_;
	TrackListTrack* _tmp0_;
	self = (TrackList*) base;
	_inner_error_ = NULL;
	_tmp0_ = NULL;
	_tmp0_ = track_list_seek (self, offset, whence, &_inner_error_);
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
}


TrackListTrack* track_list_get_current_track (TrackList* self) {
	TrackListTrack* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_current_track;
	return result;
}


static void track_list_set_current_track (TrackList* self, TrackListTrack* value) {
	TrackListTrack* _tmp1_;
	TrackListTrack* _tmp0_;
	g_return_if_fail (self != NULL);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	self->priv->_current_track = (_tmp1_ = (_tmp0_ = value, (_tmp0_ == NULL) ? NULL : track_list_track_ref (_tmp0_)), (self->priv->_current_track == NULL) ? NULL : (self->priv->_current_track = (track_list_track_unref (self->priv->_current_track), NULL)), _tmp1_);
	g_object_notify ((GObject *) self, "current-track");
}


const char* track_list_get_name (TrackList* self) {
	const char* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_name;
	return result;
}


void track_list_set_name (TrackList* self, const char* value) {
	char* _tmp1_;
	const char* _tmp0_;
	g_return_if_fail (self != NULL);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	self->priv->_name = (_tmp1_ = (_tmp0_ = value, (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_)), self->priv->_name = (g_free (self->priv->_name), NULL), _tmp1_);
	g_object_notify ((GObject *) self, "name");
}


const char* track_list_get_path (TrackList* self) {
	const char* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_path;
	return result;
}


void track_list_set_path (TrackList* self, const char* value) {
	char* _tmp1_;
	const char* _tmp0_;
	g_return_if_fail (self != NULL);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	self->priv->_path = (_tmp1_ = (_tmp0_ = value, (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_)), self->priv->_path = (g_free (self->priv->_path), NULL), _tmp1_);
	g_object_notify ((GObject *) self, "path");
}


guint track_list_get_position (TrackList* self) {
	guint result;
	g_return_val_if_fail (self != NULL, 0U);
	result = self->priv->_position;
	return result;
}


void track_list_set_position (TrackList* self, guint value) {
	g_return_if_fail (self != NULL);
	self->priv->_position = value;
	if (((TrackListTrack*) g_list_nth_data (self->tracklist, value)) != NULL) {
		GHashTable* _tmp0_;
		_tmp0_ = NULL;
		epris_track_list_set_current ((EprisTrackList*) self, _tmp0_ = track_list_track_get_hsv (TRACK_LIST_TRACK ((TrackListTrack*) g_list_nth_data (self->tracklist, value))));
		(_tmp0_ == NULL) ? NULL : (_tmp0_ = (g_hash_table_unref (_tmp0_), NULL));
	}
	track_list_save (self, FALSE, TRUE);
	g_object_notify ((GObject *) self, "position");
}


TrackListTrack* track_list_track_construct (GType object_type, const char* uri) {
	TrackListTrack* self;
	char* _tmp1_;
	const char* _tmp0_;
	g_return_val_if_fail (uri != NULL, NULL);
	self = (TrackListTrack*) g_type_create_instance (object_type);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	self->uri = (_tmp1_ = (_tmp0_ = uri, (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_)), self->uri = (g_free (self->uri), NULL), _tmp1_);
	return self;
}


TrackListTrack* track_list_track_new (const char* uri) {
	return track_list_track_construct (TRACK_LIST_TYPE_TRACK, uri);
}


GHashTable* track_list_track_get_hsv (TrackListTrack* self) {
	GHashTable* result;
	GValue* _tmp3_;
	GValue _tmp2_ = {0};
	GValue _tmp1_ = {0};
	GValue _tmp0_ = {0};
	GValue* _tmp4_;
	GValue* v;
	GHashTable* res;
	GValue* _tmp5_;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp3_ = NULL;
	_tmp4_ = NULL;
	v = (_tmp4_ = (_tmp3_ = (_tmp2_ = _tmp1_ = (g_value_init (&_tmp0_, G_TYPE_STRING), _tmp0_), &_tmp2_), (_tmp3_ == NULL) ? NULL : _g_value_dup (_tmp3_)), G_IS_VALUE (&_tmp1_) ? (g_value_unset (&_tmp1_), NULL) : NULL, _tmp4_);
	g_value_set_string (v, self->uri);
	res = g_hash_table_new (g_str_hash, g_str_equal);
	_tmp5_ = NULL;
	g_hash_table_insert (res, g_strdup ("uri"), (_tmp5_ = v, v = NULL, _tmp5_));
	result = res;
	(v == NULL) ? NULL : (v = (g_free (v), NULL));
	return result;
}


static void track_list_value_track_init (GValue* value) {
	value->data[0].v_pointer = NULL;
}


static void track_list_value_track_free_value (GValue* value) {
	if (value->data[0].v_pointer) {
		track_list_track_unref (value->data[0].v_pointer);
	}
}


static void track_list_value_track_copy_value (const GValue* src_value, GValue* dest_value) {
	if (src_value->data[0].v_pointer) {
		dest_value->data[0].v_pointer = track_list_track_ref (src_value->data[0].v_pointer);
	} else {
		dest_value->data[0].v_pointer = NULL;
	}
}


static gpointer track_list_value_track_peek_pointer (const GValue* value) {
	return value->data[0].v_pointer;
}


static gchar* track_list_value_track_collect_value (GValue* value, guint n_collect_values, GTypeCValue* collect_values, guint collect_flags) {
	if (collect_values[0].v_pointer) {
		TrackListTrack* object;
		object = collect_values[0].v_pointer;
		if (object->parent_instance.g_class == NULL) {
			return g_strconcat ("invalid unclassed object pointer for value type `", G_VALUE_TYPE_NAME (value), "'", NULL);
		} else if (!g_value_type_compatible (G_TYPE_FROM_INSTANCE (object), G_VALUE_TYPE (value))) {
			return g_strconcat ("invalid object type `", g_type_name (G_TYPE_FROM_INSTANCE (object)), "' for value type `", G_VALUE_TYPE_NAME (value), "'", NULL);
		}
		value->data[0].v_pointer = track_list_track_ref (object);
	} else {
		value->data[0].v_pointer = NULL;
	}
	return NULL;
}


static gchar* track_list_value_track_lcopy_value (const GValue* value, guint n_collect_values, GTypeCValue* collect_values, guint collect_flags) {
	TrackListTrack** object_p;
	object_p = collect_values[0].v_pointer;
	if (!object_p) {
		return g_strdup_printf ("value location for `%s' passed as NULL", G_VALUE_TYPE_NAME (value));
	}
	if (!value->data[0].v_pointer) {
		*object_p = NULL;
	} else if (collect_flags && G_VALUE_NOCOPY_CONTENTS) {
		*object_p = value->data[0].v_pointer;
	} else {
		*object_p = track_list_track_ref (value->data[0].v_pointer);
	}
	return NULL;
}


GParamSpec* track_list_param_spec_track (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags) {
	TrackListParamSpecTrack* spec;
	g_return_val_if_fail (g_type_is_a (object_type, TRACK_LIST_TYPE_TRACK), NULL);
	spec = g_param_spec_internal (G_TYPE_PARAM_OBJECT, name, nick, blurb, flags);
	G_PARAM_SPEC (spec)->value_type = object_type;
	return G_PARAM_SPEC (spec);
}


gpointer track_list_value_get_track (const GValue* value) {
	g_return_val_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, TRACK_LIST_TYPE_TRACK), NULL);
	return value->data[0].v_pointer;
}


void track_list_value_set_track (GValue* value, gpointer v_object) {
	TrackListTrack* old;
	g_return_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, TRACK_LIST_TYPE_TRACK));
	old = value->data[0].v_pointer;
	if (v_object) {
		g_return_if_fail (G_TYPE_CHECK_INSTANCE_TYPE (v_object, TRACK_LIST_TYPE_TRACK));
		g_return_if_fail (g_value_type_compatible (G_TYPE_FROM_INSTANCE (v_object), G_VALUE_TYPE (value)));
		value->data[0].v_pointer = v_object;
		track_list_track_ref (value->data[0].v_pointer);
	} else {
		value->data[0].v_pointer = NULL;
	}
	if (old) {
		track_list_track_unref (old);
	}
}


static void track_list_track_class_init (TrackListTrackClass * klass) {
	track_list_track_parent_class = g_type_class_peek_parent (klass);
	TRACK_LIST_TRACK_CLASS (klass)->finalize = track_list_track_finalize;
}


static void track_list_track_instance_init (TrackListTrack * self) {
	self->ref_count = 1;
}


static void track_list_track_finalize (TrackListTrack* obj) {
	TrackListTrack * self;
	self = TRACK_LIST_TRACK (obj);
	self->uri = (g_free (self->uri), NULL);
}


GType track_list_track_get_type (void) {
	static GType track_list_track_type_id = 0;
	if (track_list_track_type_id == 0) {
		static const GTypeValueTable g_define_type_value_table = { track_list_value_track_init, track_list_value_track_free_value, track_list_value_track_copy_value, track_list_value_track_peek_pointer, "p", track_list_value_track_collect_value, "p", track_list_value_track_lcopy_value };
		static const GTypeInfo g_define_type_info = { sizeof (TrackListTrackClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) track_list_track_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (TrackListTrack), 0, (GInstanceInitFunc) track_list_track_instance_init, &g_define_type_value_table };
		static const GTypeFundamentalInfo g_define_type_fundamental_info = { (G_TYPE_FLAG_CLASSED | G_TYPE_FLAG_INSTANTIATABLE | G_TYPE_FLAG_DERIVABLE | G_TYPE_FLAG_DEEP_DERIVABLE) };
		track_list_track_type_id = g_type_register_fundamental (g_type_fundamental_next (), "TrackListTrack", &g_define_type_info, &g_define_type_fundamental_info, 0);
	}
	return track_list_track_type_id;
}


gpointer track_list_track_ref (gpointer instance) {
	TrackListTrack* self;
	self = instance;
	g_atomic_int_inc (&self->ref_count);
	return instance;
}


void track_list_track_unref (gpointer instance) {
	TrackListTrack* self;
	self = instance;
	if (g_atomic_int_dec_and_test (&self->ref_count)) {
		TRACK_LIST_TRACK_GET_CLASS (self)->finalize (self);
		g_type_free_instance ((GTypeInstance *) self);
	}
}


void _track_list_dbus_unregister (DBusConnection* connection, void* user_data) {
}


static DBusMessage* _dbus_track_list_introspect (TrackList* self, DBusConnection* connection, DBusMessage* message) {
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


DBusHandlerResult track_list_dbus_message (DBusConnection* connection, DBusMessage* message, void* object) {
	DBusMessage* reply;
	reply = NULL;
	if (dbus_message_is_method_call (message, "org.freedesktop.DBus.Introspectable", "Introspect")) {
		reply = _dbus_track_list_introspect (object, connection, message);
	}
	if (reply) {
		dbus_connection_send (connection, reply, NULL);
		dbus_message_unref (reply);
		return DBUS_HANDLER_RESULT_HANDLED;
	} else if (epris_track_list_dbus_message (connection, message, object) == DBUS_HANDLER_RESULT_HANDLED) {
		return DBUS_HANDLER_RESULT_HANDLED;
	} else {
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}
}


void track_list_dbus_register_object (DBusConnection* connection, const char* path, void* object) {
	if (!g_object_get_data (object, "dbus_object_path")) {
		g_object_set_data (object, "dbus_object_path", g_strdup (path));
		dbus_connection_register_object_path (connection, path, &_track_list_dbus_path_vtable, object);
		g_object_weak_ref (object, _vala_dbus_unregister_object, connection);
	}
	epris_track_list_dbus_register_object (connection, path, object);
}


static void track_list_class_init (TrackListClass * klass) {
	track_list_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (TrackListPrivate));
	EPRIS_TRACK_LIST_CLASS (klass)->AddTracks = track_list_real_AddTracks;
	EPRIS_TRACK_LIST_CLASS (klass)->DelTracks = track_list_real_DelTracks;
	EPRIS_TRACK_LIST_CLASS (klass)->ListTracks = track_list_real_ListTracks;
	EPRIS_TRACK_LIST_CLASS (klass)->Seek = track_list_real_Seek;
	G_OBJECT_CLASS (klass)->get_property = track_list_get_property;
	G_OBJECT_CLASS (klass)->set_property = track_list_set_property;
	G_OBJECT_CLASS (klass)->finalize = track_list_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), TRACK_LIST_CURRENT_TRACK, track_list_param_spec_track ("current-track", "current-track", "current-track", TRACK_LIST_TYPE_TRACK, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), TRACK_LIST_NAME, g_param_spec_string ("name", "name", "name", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), TRACK_LIST_PATH, g_param_spec_string ("path", "path", "path", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), TRACK_LIST_POSITION, g_param_spec_uint ("position", "position", "position", 0, G_MAXUINT, 0U, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_type_set_qdata (TYPE_TRACK_LIST, g_quark_from_static_string ("DBusObjectVTable"), (void*) (&_track_list_dbus_vtable));
}


static void track_list_instance_init (TrackList * self) {
	self->priv = TRACK_LIST_GET_PRIVATE (self);
}


static void track_list_finalize (GObject* obj) {
	TrackList * self;
	self = TRACK_LIST (obj);
	(self->priv->_current_track == NULL) ? NULL : (self->priv->_current_track = (track_list_track_unref (self->priv->_current_track), NULL));
	self->priv->_name = (g_free (self->priv->_name), NULL);
	self->priv->_path = (g_free (self->priv->_path), NULL);
	(self->tracklist == NULL) ? NULL : (self->tracklist = (_g_list_free_track_list_track_unref (self->tracklist), NULL));
	G_OBJECT_CLASS (track_list_parent_class)->finalize (obj);
}


GType track_list_get_type (void) {
	static GType track_list_type_id = 0;
	if (track_list_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (TrackListClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) track_list_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (TrackList), 0, (GInstanceInitFunc) track_list_instance_init, NULL };
		track_list_type_id = g_type_register_static (EPRIS_TYPE_TRACK_LIST, "TrackList", &g_define_type_info, 0);
	}
	return track_list_type_id;
}


static void track_list_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	TrackList * self;
	gpointer boxed;
	self = TRACK_LIST (object);
	switch (property_id) {
		case TRACK_LIST_CURRENT_TRACK:
		track_list_value_set_track (value, track_list_get_current_track (self));
		break;
		case TRACK_LIST_NAME:
		g_value_set_string (value, track_list_get_name (self));
		break;
		case TRACK_LIST_PATH:
		g_value_set_string (value, track_list_get_path (self));
		break;
		case TRACK_LIST_POSITION:
		g_value_set_uint (value, track_list_get_position (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void track_list_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	TrackList * self;
	self = TRACK_LIST (object);
	switch (property_id) {
		case TRACK_LIST_CURRENT_TRACK:
		track_list_set_current_track (self, track_list_value_get_track (value));
		break;
		case TRACK_LIST_NAME:
		track_list_set_name (self, g_value_get_string (value));
		break;
		case TRACK_LIST_PATH:
		track_list_set_path (self, g_value_get_string (value));
		break;
		case TRACK_LIST_POSITION:
		track_list_set_position (self, g_value_get_uint (value));
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




