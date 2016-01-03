
#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>


#define EPRIS_TYPE_STORAGE (epris_storage_get_type ())
#define EPRIS_STORAGE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), EPRIS_TYPE_STORAGE, EprisStorage))
#define EPRIS_STORAGE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), EPRIS_TYPE_STORAGE, EprisStorageClass))
#define EPRIS_IS_STORAGE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), EPRIS_TYPE_STORAGE))
#define EPRIS_IS_STORAGE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), EPRIS_TYPE_STORAGE))
#define EPRIS_STORAGE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), EPRIS_TYPE_STORAGE, EprisStorageClass))

typedef struct _EprisStorage EprisStorage;
typedef struct _EprisStorageClass EprisStorageClass;
typedef struct _EprisStoragePrivate EprisStoragePrivate;

struct _EprisStorage {
	GObject parent_instance;
	EprisStoragePrivate * priv;
};

struct _EprisStorageClass {
	GObjectClass parent_class;
};

struct _EprisStoragePrivate {
	char* _dirname;
};



GType epris_storage_get_type (void);
#define EPRIS_STORAGE_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), EPRIS_TYPE_STORAGE, EprisStoragePrivate))
enum  {
	EPRIS_STORAGE_DUMMY_PROPERTY,
	EPRIS_STORAGE_DIRNAME
};
void epris_storage_set_dirname (EprisStorage* self, const char* value);
EprisStorage* epris_storage_new (const char* dirname);
EprisStorage* epris_storage_construct (GType object_type, const char* dirname);
EprisStorage* epris_storage_new (const char* dirname);
const char* epris_storage_get_dirname (EprisStorage* self);
static char* epris_storage_get_path_for_string (EprisStorage* self, const char* key);
gboolean epris_storage_write (EprisStorage* self, const char* key, void* buf, gsize* count);
gboolean epris_storage_read (EprisStorage* self, const char* key, void* buf, gsize* count);
static gpointer epris_storage_parent_class = NULL;
static void epris_storage_finalize (GObject* obj);
static void epris_storage_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void epris_storage_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);



EprisStorage* epris_storage_construct (GType object_type, const char* dirname) {
	EprisStorage * self;
	g_return_val_if_fail (dirname != NULL, NULL);
	self = g_object_newv (object_type, 0, NULL);
	epris_storage_set_dirname (self, dirname);
	return self;
}


EprisStorage* epris_storage_new (const char* dirname) {
	return epris_storage_construct (EPRIS_TYPE_STORAGE, dirname);
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


static char* epris_storage_get_path_for_string (EprisStorage* self, const char* key) {
	char* result;
	char* sha1;
	char* _tmp1_;
	char* _tmp0_;
	char* _tmp2_;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (key != NULL, NULL);
	sha1 = g_compute_checksum_for_string (G_CHECKSUM_SHA1, key, (gsize) (-1));
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	_tmp2_ = NULL;
	result = (_tmp2_ = g_build_filename (self->priv->_dirname, _tmp0_ = string_substring (sha1, (glong) 0, (glong) 2), _tmp1_ = string_substring (sha1, (glong) 2, -1), NULL), _tmp1_ = (g_free (_tmp1_), NULL), _tmp0_ = (g_free (_tmp0_), NULL), _tmp2_);
	sha1 = (g_free (sha1), NULL);
	return result;
	sha1 = (g_free (sha1), NULL);
}


gboolean epris_storage_write (EprisStorage* self, const char* key, void* buf, gsize* count) {
	gboolean result;
	char* path;
	char* _tmp0_;
	FILE* file;
	gssize c;
	gboolean _result_;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (key != NULL, FALSE);
	path = epris_storage_get_path_for_string (self, key);
	_tmp0_ = NULL;
	g_mkdir_with_parents (_tmp0_ = g_path_get_dirname (path), 0700);
	_tmp0_ = (g_free (_tmp0_), NULL);
	file = fopen (path, "w");
	c = write (fileno (file), buf, (*count));
	_result_ = c == (*count);
	(*count) = (gsize) c;
	result = _result_;
	path = (g_free (path), NULL);
	(file == NULL) ? NULL : (file = (fclose (file), NULL));
	return result;
}


gboolean epris_storage_read (EprisStorage* self, const char* key, void* buf, gsize* count) {
	gboolean result;
	char* path;
	FILE* file;
	gssize c;
	gboolean _result_;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (key != NULL, FALSE);
	path = epris_storage_get_path_for_string (self, key);
	file = fopen (path, "r");
	c = read (fileno (file), buf, (*count));
	_result_ = c == (*count);
	(*count) = (gsize) c;
	result = _result_;
	path = (g_free (path), NULL);
	(file == NULL) ? NULL : (file = (fclose (file), NULL));
	return result;
}


const char* epris_storage_get_dirname (EprisStorage* self) {
	const char* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_dirname;
	return result;
}


void epris_storage_set_dirname (EprisStorage* self, const char* value) {
	char* _tmp1_;
	const char* _tmp0_;
	g_return_if_fail (self != NULL);
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	self->priv->_dirname = (_tmp1_ = (_tmp0_ = value, (_tmp0_ == NULL) ? NULL : g_strdup (_tmp0_)), self->priv->_dirname = (g_free (self->priv->_dirname), NULL), _tmp1_);
	g_object_notify ((GObject *) self, "dirname");
}


static void epris_storage_class_init (EprisStorageClass * klass) {
	epris_storage_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (EprisStoragePrivate));
	G_OBJECT_CLASS (klass)->get_property = epris_storage_get_property;
	G_OBJECT_CLASS (klass)->set_property = epris_storage_set_property;
	G_OBJECT_CLASS (klass)->finalize = epris_storage_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), EPRIS_STORAGE_DIRNAME, g_param_spec_string ("dirname", "dirname", "dirname", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
}


static void epris_storage_instance_init (EprisStorage * self) {
	self->priv = EPRIS_STORAGE_GET_PRIVATE (self);
}


static void epris_storage_finalize (GObject* obj) {
	EprisStorage * self;
	self = EPRIS_STORAGE (obj);
	self->priv->_dirname = (g_free (self->priv->_dirname), NULL);
	G_OBJECT_CLASS (epris_storage_parent_class)->finalize (obj);
}


GType epris_storage_get_type (void) {
	static GType epris_storage_type_id = 0;
	if (epris_storage_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (EprisStorageClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) epris_storage_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (EprisStorage), 0, (GInstanceInitFunc) epris_storage_instance_init, NULL };
		epris_storage_type_id = g_type_register_static (G_TYPE_OBJECT, "EprisStorage", &g_define_type_info, 0);
	}
	return epris_storage_type_id;
}


static void epris_storage_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	EprisStorage * self;
	gpointer boxed;
	self = EPRIS_STORAGE (object);
	switch (property_id) {
		case EPRIS_STORAGE_DIRNAME:
		g_value_set_string (value, epris_storage_get_dirname (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void epris_storage_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	EprisStorage * self;
	self = EPRIS_STORAGE (object);
	switch (property_id) {
		case EPRIS_STORAGE_DIRNAME:
		epris_storage_set_dirname (self, g_value_get_string (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}




