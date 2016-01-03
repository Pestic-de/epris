
#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <gobject/gvaluecollector.h>


#define EPRIS_TYPE_PAIR (epris_pair_get_type ())
#define EPRIS_PAIR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), EPRIS_TYPE_PAIR, EprisPair))
#define EPRIS_PAIR_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), EPRIS_TYPE_PAIR, EprisPairClass))
#define EPRIS_IS_PAIR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), EPRIS_TYPE_PAIR))
#define EPRIS_IS_PAIR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), EPRIS_TYPE_PAIR))
#define EPRIS_PAIR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), EPRIS_TYPE_PAIR, EprisPairClass))

typedef struct _EprisPair EprisPair;
typedef struct _EprisPairClass EprisPairClass;
typedef struct _EprisPairPrivate EprisPairPrivate;
typedef struct _EprisParamSpecPair EprisParamSpecPair;

typedef enum  {
	EPRIS_ERROR_NONE,
	EPRIS_ERROR_NOT_SUPPORTED,
	EPRIS_ERROR_STATE,
	EPRIS_ERROR_ARGUMENT
} EprisError;
#define EPRIS_ERROR epris_error_quark ()
struct _EprisPair {
	GTypeInstance parent_instance;
	volatile int ref_count;
	EprisPairPrivate * priv;
	gpointer first;
	gpointer second;
};

struct _EprisPairClass {
	GTypeClass parent_class;
	void (*finalize) (EprisPair *self);
};

struct _EprisPairPrivate {
	GType t1_type;
	GBoxedCopyFunc t1_dup_func;
	GDestroyNotify t1_destroy_func;
	GType t2_type;
	GBoxedCopyFunc t2_dup_func;
	GDestroyNotify t2_destroy_func;
};

struct _EprisParamSpecPair {
	GParamSpec parent_instance;
};



GQuark epris_error_quark (void);
gpointer epris_pair_ref (gpointer instance);
void epris_pair_unref (gpointer instance);
GParamSpec* epris_param_spec_pair (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags);
void epris_value_set_pair (GValue* value, gpointer v_object);
gpointer epris_value_get_pair (const GValue* value);
GType epris_pair_get_type (void);
#define EPRIS_PAIR_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), EPRIS_TYPE_PAIR, EprisPairPrivate))
enum  {
	EPRIS_PAIR_DUMMY_PROPERTY
};
EprisPair* epris_pair_new (GType t1_type, GBoxedCopyFunc t1_dup_func, GDestroyNotify t1_destroy_func, GType t2_type, GBoxedCopyFunc t2_dup_func, GDestroyNotify t2_destroy_func, gpointer first, gpointer second);
EprisPair* epris_pair_construct (GType object_type, GType t1_type, GBoxedCopyFunc t1_dup_func, GDestroyNotify t1_destroy_func, GType t2_type, GBoxedCopyFunc t2_dup_func, GDestroyNotify t2_destroy_func, gpointer first, gpointer second);
EprisPair* epris_pair_new (GType t1_type, GBoxedCopyFunc t1_dup_func, GDestroyNotify t1_destroy_func, GType t2_type, GBoxedCopyFunc t2_dup_func, GDestroyNotify t2_destroy_func, gpointer first, gpointer second);
static gpointer epris_pair_parent_class = NULL;
static void epris_pair_finalize (EprisPair* obj);
char** epris_strv_from_list (GList* list, int* result_length1);
gboolean epris_bool_from_string (const char* str);
gboolean epris_keyfile_save (GKeyFile* key_file, const char* file_path);
gboolean epris_type_is_glib_dbus (GType t);
extern char* epris_hsv_to_string_rv;
char* epris_hsv_to_string_rv = NULL;
extern char* epris_hsv_to_string_format;
char* epris_hsv_to_string_format = NULL;
extern char* epris_hsv_to_string_exclude;
char* epris_hsv_to_string_exclude = NULL;
static void _lambda1_ (void* s, void* v);
static void __lambda1__gh_func (void* key, void* value, gpointer self);
char* epris_hsv_to_string (GHashTable* hsv, const char* format, const char* exclude_prefix);
static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);
static int _vala_strcmp0 (const char * str1, const char * str2);



GQuark epris_error_quark (void) {
	return g_quark_from_static_string ("epris_error-quark");
}


EprisPair* epris_pair_construct (GType object_type, GType t1_type, GBoxedCopyFunc t1_dup_func, GDestroyNotify t1_destroy_func, GType t2_type, GBoxedCopyFunc t2_dup_func, GDestroyNotify t2_destroy_func, gpointer first, gpointer second) {
	EprisPair* self;
	gpointer _tmp1_;
	gpointer _tmp0_;
	gpointer _tmp3_;
	gpointer _tmp2_;
	self = (EprisPair*) g_type_create_instance (object_type);
	self->priv->t1_type = t1_type;
	self->priv->t1_dup_func = t1_dup_func;
	self->priv->t1_destroy_func = t1_destroy_func;
	self->priv->t2_type = t2_type;
	self->priv->t2_dup_func = t2_dup_func;
	self->priv->t2_destroy_func = t2_destroy_func;
	_tmp1_ = NULL;
	_tmp0_ = NULL;
	self->first = (_tmp1_ = (_tmp0_ = first, first = NULL, _tmp0_), ((self->first == NULL) || (self->priv->t1_destroy_func == NULL)) ? NULL : (self->first = (self->priv->t1_destroy_func (self->first), NULL)), _tmp1_);
	_tmp3_ = NULL;
	_tmp2_ = NULL;
	self->second = (_tmp3_ = (_tmp2_ = second, second = NULL, _tmp2_), ((self->second == NULL) || (self->priv->t2_destroy_func == NULL)) ? NULL : (self->second = (self->priv->t2_destroy_func (self->second), NULL)), _tmp3_);
	((first == NULL) || (self->priv->t1_destroy_func == NULL)) ? NULL : (first = (self->priv->t1_destroy_func (first), NULL));
	((second == NULL) || (self->priv->t2_destroy_func == NULL)) ? NULL : (second = (self->priv->t2_destroy_func (second), NULL));
	return self;
}


EprisPair* epris_pair_new (GType t1_type, GBoxedCopyFunc t1_dup_func, GDestroyNotify t1_destroy_func, GType t2_type, GBoxedCopyFunc t2_dup_func, GDestroyNotify t2_destroy_func, gpointer first, gpointer second) {
	return epris_pair_construct (EPRIS_TYPE_PAIR, t1_type, t1_dup_func, t1_destroy_func, t2_type, t2_dup_func, t2_destroy_func, first, second);
}


static void epris_value_pair_init (GValue* value) {
	value->data[0].v_pointer = NULL;
}


static void epris_value_pair_free_value (GValue* value) {
	if (value->data[0].v_pointer) {
		epris_pair_unref (value->data[0].v_pointer);
	}
}


static void epris_value_pair_copy_value (const GValue* src_value, GValue* dest_value) {
	if (src_value->data[0].v_pointer) {
		dest_value->data[0].v_pointer = epris_pair_ref (src_value->data[0].v_pointer);
	} else {
		dest_value->data[0].v_pointer = NULL;
	}
}


static gpointer epris_value_pair_peek_pointer (const GValue* value) {
	return value->data[0].v_pointer;
}


static gchar* epris_value_pair_collect_value (GValue* value, guint n_collect_values, GTypeCValue* collect_values, guint collect_flags) {
	if (collect_values[0].v_pointer) {
		EprisPair* object;
		object = collect_values[0].v_pointer;
		if (object->parent_instance.g_class == NULL) {
			return g_strconcat ("invalid unclassed object pointer for value type `", G_VALUE_TYPE_NAME (value), "'", NULL);
		} else if (!g_value_type_compatible (G_TYPE_FROM_INSTANCE (object), G_VALUE_TYPE (value))) {
			return g_strconcat ("invalid object type `", g_type_name (G_TYPE_FROM_INSTANCE (object)), "' for value type `", G_VALUE_TYPE_NAME (value), "'", NULL);
		}
		value->data[0].v_pointer = epris_pair_ref (object);
	} else {
		value->data[0].v_pointer = NULL;
	}
	return NULL;
}


static gchar* epris_value_pair_lcopy_value (const GValue* value, guint n_collect_values, GTypeCValue* collect_values, guint collect_flags) {
	EprisPair** object_p;
	object_p = collect_values[0].v_pointer;
	if (!object_p) {
		return g_strdup_printf ("value location for `%s' passed as NULL", G_VALUE_TYPE_NAME (value));
	}
	if (!value->data[0].v_pointer) {
		*object_p = NULL;
	} else if (collect_flags && G_VALUE_NOCOPY_CONTENTS) {
		*object_p = value->data[0].v_pointer;
	} else {
		*object_p = epris_pair_ref (value->data[0].v_pointer);
	}
	return NULL;
}


GParamSpec* epris_param_spec_pair (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags) {
	EprisParamSpecPair* spec;
	g_return_val_if_fail (g_type_is_a (object_type, EPRIS_TYPE_PAIR), NULL);
	spec = g_param_spec_internal (G_TYPE_PARAM_OBJECT, name, nick, blurb, flags);
	G_PARAM_SPEC (spec)->value_type = object_type;
	return G_PARAM_SPEC (spec);
}


gpointer epris_value_get_pair (const GValue* value) {
	g_return_val_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, EPRIS_TYPE_PAIR), NULL);
	return value->data[0].v_pointer;
}


void epris_value_set_pair (GValue* value, gpointer v_object) {
	EprisPair* old;
	g_return_if_fail (G_TYPE_CHECK_VALUE_TYPE (value, EPRIS_TYPE_PAIR));
	old = value->data[0].v_pointer;
	if (v_object) {
		g_return_if_fail (G_TYPE_CHECK_INSTANCE_TYPE (v_object, EPRIS_TYPE_PAIR));
		g_return_if_fail (g_value_type_compatible (G_TYPE_FROM_INSTANCE (v_object), G_VALUE_TYPE (value)));
		value->data[0].v_pointer = v_object;
		epris_pair_ref (value->data[0].v_pointer);
	} else {
		value->data[0].v_pointer = NULL;
	}
	if (old) {
		epris_pair_unref (old);
	}
}


static void epris_pair_class_init (EprisPairClass * klass) {
	epris_pair_parent_class = g_type_class_peek_parent (klass);
	EPRIS_PAIR_CLASS (klass)->finalize = epris_pair_finalize;
	g_type_class_add_private (klass, sizeof (EprisPairPrivate));
}


static void epris_pair_instance_init (EprisPair * self) {
	self->priv = EPRIS_PAIR_GET_PRIVATE (self);
	self->ref_count = 1;
}


static void epris_pair_finalize (EprisPair* obj) {
	EprisPair * self;
	self = EPRIS_PAIR (obj);
	((self->first == NULL) || (self->priv->t1_destroy_func == NULL)) ? NULL : (self->first = (self->priv->t1_destroy_func (self->first), NULL));
	((self->second == NULL) || (self->priv->t2_destroy_func == NULL)) ? NULL : (self->second = (self->priv->t2_destroy_func (self->second), NULL));
}


GType epris_pair_get_type (void) {
	static GType epris_pair_type_id = 0;
	if (epris_pair_type_id == 0) {
		static const GTypeValueTable g_define_type_value_table = { epris_value_pair_init, epris_value_pair_free_value, epris_value_pair_copy_value, epris_value_pair_peek_pointer, "p", epris_value_pair_collect_value, "p", epris_value_pair_lcopy_value };
		static const GTypeInfo g_define_type_info = { sizeof (EprisPairClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) epris_pair_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (EprisPair), 0, (GInstanceInitFunc) epris_pair_instance_init, &g_define_type_value_table };
		static const GTypeFundamentalInfo g_define_type_fundamental_info = { (G_TYPE_FLAG_CLASSED | G_TYPE_FLAG_INSTANTIATABLE | G_TYPE_FLAG_DERIVABLE | G_TYPE_FLAG_DEEP_DERIVABLE) };
		epris_pair_type_id = g_type_register_fundamental (g_type_fundamental_next (), "EprisPair", &g_define_type_info, &g_define_type_fundamental_info, 0);
	}
	return epris_pair_type_id;
}


gpointer epris_pair_ref (gpointer instance) {
	EprisPair* self;
	self = instance;
	g_atomic_int_inc (&self->ref_count);
	return instance;
}


void epris_pair_unref (gpointer instance) {
	EprisPair* self;
	self = instance;
	if (g_atomic_int_dec_and_test (&self->ref_count)) {
		EPRIS_PAIR_GET_CLASS (self)->finalize (self);
		g_type_free_instance ((GTypeInstance *) self);
	}
}


char** epris_strv_from_list (GList* list, int* result_length1) {
	char** result;
	char** _tmp1_;
	gint rv_size;
	gint rv_length1;
	gint _tmp0_;
	char** rv;
	guint i;
	char** _tmp5_;
	_tmp1_ = NULL;
	rv = (_tmp1_ = g_new0 (char*, (_tmp0_ = g_list_length (list) + 1) + 1), rv_length1 = _tmp0_, rv_size = rv_length1, _tmp1_);
	i = (guint) 0;
	{
		GList* s_collection;
		GList* s_it;
		s_collection = list;
		for (s_it = s_collection; s_it != NULL; s_it = s_it->next) {
			const char* _tmp4_;
			char* s;
			_tmp4_ = NULL;
			s = (_tmp4_ = (const char*) s_it->data, (_tmp4_ == NULL) ? NULL : g_strdup (_tmp4_));
			{
				char* _tmp3_;
				const char* _tmp2_;
				_tmp3_ = NULL;
				_tmp2_ = NULL;
				rv[i] = (_tmp3_ = (_tmp2_ = s, (_tmp2_ == NULL) ? NULL : g_strdup (_tmp2_)), rv[i] = (g_free (rv[i]), NULL), _tmp3_);
				i = i + 1;
				s = (g_free (s), NULL);
			}
		}
	}
	_tmp5_ = NULL;
	result = (_tmp5_ = rv, *result_length1 = rv_length1, _tmp5_);
	return result;
	rv = (_vala_array_free (rv, rv_length1, (GDestroyNotify) g_free), NULL);
}


gboolean epris_bool_from_string (const char* str) {
	gboolean result;
	gboolean _tmp0_;
	gboolean _tmp1_;
	if (str == NULL) {
		result = FALSE;
		return result;
	}
	_tmp0_ = FALSE;
	_tmp1_ = FALSE;
	if (_vala_strcmp0 (str, "true") == 0) {
		_tmp1_ = TRUE;
	} else {
		_tmp1_ = _vala_strcmp0 (str, "yes") == 0;
	}
	if (_tmp1_) {
		_tmp0_ = TRUE;
	} else {
		_tmp0_ = _vala_strcmp0 (str, "1") == 0;
	}
	if (_tmp0_) {
		result = TRUE;
		return result;
	}
	result = FALSE;
	return result;
}


gboolean epris_keyfile_save (GKeyFile* key_file, const char* file_path) {
	gboolean result;
	GError * _inner_error_;
	FILE* file;
	g_return_val_if_fail (key_file != NULL, FALSE);
	g_return_val_if_fail (file_path != NULL, FALSE);
	_inner_error_ = NULL;
	file = fopen (file_path, "w");
	{
		char* data;
		data = g_key_file_to_data (key_file, NULL, NULL);
		fputs (data, file);
		data = (g_free (data), NULL);
	}
	goto __finally16;
	__catch16_g_key_file_error:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		{
			/* file = null;*/
			g_warning (_error_->message);
			result = FALSE;
			(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
			(file == NULL) ? NULL : (file = (fclose (file), NULL));
			return result;
		}
	}
	__finally16:
	if (_inner_error_ != NULL) {
		(file == NULL) ? NULL : (file = (fclose (file), NULL));
		g_critical ("file %s: line %d: uncaught error: %s", __FILE__, __LINE__, _inner_error_->message);
		g_clear_error (&_inner_error_);
		return FALSE;
	}
	result = TRUE;
	(file == NULL) ? NULL : (file = (fclose (file), NULL));
	return result;
}


gboolean epris_type_is_glib_dbus (GType t) {
	gboolean result;
	gboolean _tmp0_;
	gboolean _tmp1_;
	gboolean _tmp2_;
	_tmp0_ = FALSE;
	_tmp1_ = FALSE;
	_tmp2_ = FALSE;
	if (t == G_TYPE_STRING) {
		_tmp2_ = TRUE;
	} else {
		_tmp2_ = t == G_TYPE_INT;
	}
	if (_tmp2_) {
		_tmp1_ = TRUE;
	} else {
		_tmp1_ = t == G_TYPE_UINT;
	}
	if (_tmp1_) {
		_tmp0_ = TRUE;
	} else {
		_tmp0_ = t == G_TYPE_BOOLEAN;
	}
	result = _tmp0_;
	return result;
}


static void _lambda1_ (void* s, void* v) {
	gboolean _tmp0_;
	char* _tmp4_;
	char* _tmp3_;
	char* _tmp2_;
	char* _tmp1_;
	_tmp0_ = FALSE;
	if (s == NULL) {
		_tmp0_ = TRUE;
	} else {
		_tmp0_ = v == NULL;
	}
	if (_tmp0_) {
		return;
	}
	if (g_str_has_prefix ((const char*) s, epris_hsv_to_string_exclude)) {
		return;
	}
	_tmp4_ = NULL;
	_tmp3_ = NULL;
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	epris_hsv_to_string_rv = (_tmp4_ = g_strconcat (epris_hsv_to_string_rv, _tmp3_ = g_strdup_printf (epris_hsv_to_string_format, _tmp1_ = g_strconcat ((const char*) s, ":", NULL), _tmp2_ = g_strdup_value_contents ((GValue*) v)), NULL), epris_hsv_to_string_rv = (g_free (epris_hsv_to_string_rv), NULL), _tmp4_);
	_tmp3_ = (g_free (_tmp3_), NULL);
	_tmp2_ = (g_free (_tmp2_), NULL);
	_tmp1_ = (g_free (_tmp1_), NULL);
}


static void __lambda1__gh_func (void* key, void* value, gpointer self) {
	_lambda1_ (key, value);
}


/* get closure...*/
char* epris_hsv_to_string (GHashTable* hsv, const char* format, const char* exclude_prefix) {
	char* result;
	char* _tmp0_;
	char* _tmp2_;
	const char* _tmp1_;
	char* _tmp4_;
	const char* _tmp3_;
	const char* _tmp5_;
	g_return_val_if_fail (hsv != NULL, NULL);
	g_return_val_if_fail (format != NULL, NULL);
	g_return_val_if_fail (exclude_prefix != NULL, NULL);
	_tmp0_ = NULL;
	epris_hsv_to_string_rv = (_tmp0_ = g_strdup (""), epris_hsv_to_string_rv = (g_free (epris_hsv_to_string_rv), NULL), _tmp0_);
	_tmp2_ = NULL;
	_tmp1_ = NULL;
	epris_hsv_to_string_format = (_tmp2_ = (_tmp1_ = format, (_tmp1_ == NULL) ? NULL : g_strdup (_tmp1_)), epris_hsv_to_string_format = (g_free (epris_hsv_to_string_format), NULL), _tmp2_);
	_tmp4_ = NULL;
	_tmp3_ = NULL;
	epris_hsv_to_string_exclude = (_tmp4_ = (_tmp3_ = exclude_prefix, (_tmp3_ == NULL) ? NULL : g_strdup (_tmp3_)), epris_hsv_to_string_exclude = (g_free (epris_hsv_to_string_exclude), NULL), _tmp4_);
	g_hash_table_foreach (hsv, __lambda1__gh_func, NULL);
	_tmp5_ = NULL;
	result = (_tmp5_ = epris_hsv_to_string_rv, (_tmp5_ == NULL) ? NULL : g_strdup (_tmp5_));
	return result;
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




