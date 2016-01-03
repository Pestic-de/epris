
#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <epris-external.h>


#define EPRIS_TYPE_STRUCTURE (epris_structure_get_type ())
#define EPRIS_STRUCTURE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), EPRIS_TYPE_STRUCTURE, EprisStructure))
#define EPRIS_STRUCTURE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), EPRIS_TYPE_STRUCTURE, EprisStructureClass))
#define EPRIS_IS_STRUCTURE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), EPRIS_TYPE_STRUCTURE))
#define EPRIS_IS_STRUCTURE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), EPRIS_TYPE_STRUCTURE))
#define EPRIS_STRUCTURE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), EPRIS_TYPE_STRUCTURE, EprisStructureClass))

typedef struct _EprisStructure EprisStructure;
typedef struct _EprisStructureClass EprisStructureClass;
typedef struct _EprisStructurePrivate EprisStructurePrivate;

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



GType epris_structure_get_type (void);
enum  {
	EPRIS_STRUCTURE_DUMMY_PROPERTY,
	EPRIS_STRUCTURE_NAME
};
static void _g_slist_free_g_free (GSList* self);
void epris_structure_set_name (EprisStructure* self, const char* value);
EprisStructure* epris_structure_new (const char* name);
EprisStructure* epris_structure_construct (GType object_type, const char* name);
EprisStructure* epris_structure_new (const char* name);
static void _epris_structure_unset_and_free (void* p);
static GQuark* _g_quark_dup (GQuark* self);
static void __epris_structure_unset_and_free_gdestroy_notify (void* data);
void epris_structure_qset (EprisStructure* self, GQuark field, GValue* value);
static void epris_structure_real_qset (EprisStructure* self, GQuark field, GValue* value);
static GValue* _g_value_dup (GValue* self);
GValue* epris_structure_qget (EprisStructure* self, GQuark field);
void epris_structure_set (EprisStructure* self, const char* field_name, GValue* value);
GValue* epris_structure_get (EprisStructure* self, const char* field_name);
const char* epris_structure_get_name (EprisStructure* self);
char* epris_structure_to_string (EprisStructure* self);
EprisStructure* epris_value_get_structure (const GValue* value);
void epris_structure_value_to_string (const GValue* src, GValue* dest);
GQuark epris_structure_get_qname (EprisStructure* self);
static void _epris_structure_value_to_string_gvalue_transform (const GValue* src_value, GValue* dest_value);
static GObject * epris_structure_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static gpointer epris_structure_parent_class = NULL;
static void epris_structure_finalize (GObject* obj);
static void epris_structure_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void epris_structure_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);



static void _g_slist_free_g_free (GSList* self) {
	g_slist_foreach (self, (GFunc) g_free, NULL);
	g_slist_free (self);
}


EprisStructure* epris_structure_construct (GType object_type, const char* name) {
	GParameter * __params;
	GParameter * __params_it;
	EprisStructure * self;
	g_return_val_if_fail (name != NULL, NULL);
	__params = g_new0 (GParameter, 1);
	__params_it = __params;
	__params_it->name = "name";
	g_value_init (&__params_it->value, G_TYPE_STRING);
	g_value_set_string (&__params_it->value, name);
	__params_it++;
	self = g_object_newv (object_type, __params_it - __params, __params);
	while (__params_it > __params) {
		--__params_it;
		g_value_unset (&__params_it->value);
	}
	g_free (__params);
	return self;
}


EprisStructure* epris_structure_new (const char* name) {
	return epris_structure_construct (EPRIS_TYPE_STRUCTURE, name);
}


static void _epris_structure_unset_and_free (void* p) {
	GValue* v;
	v = (GValue*) p;
	g_value_unset (v);
	g_free (v);
}


static GQuark* _g_quark_dup (GQuark* self) {
	GQuark* dup;
	dup = g_new0 (GQuark, 1);
	memcpy (dup, self, sizeof (GQuark));
	return dup;
}


static void __epris_structure_unset_and_free_gdestroy_notify (void* data) {
	_epris_structure_unset_and_free (data);
}


static void epris_structure_real_qset (EprisStructure* self, GQuark field, GValue* value) {
	g_return_if_fail (self != NULL);
	if (value == NULL) {
		self->fields = g_slist_remove (self->fields, &field);
		g_object_set_qdata ((GObject*) self, field, NULL);
	} else {
		GValue* _tmp1_;
		if (g_slist_find (self->fields, &field) == NULL) {
			GQuark* _tmp0_;
			_tmp0_ = NULL;
			self->fields = g_slist_append (self->fields, (_tmp0_ = &field, (_tmp0_ == NULL) ? NULL : _g_quark_dup (_tmp0_)));
		}
		_tmp1_ = NULL;
		g_object_set_qdata_full ((GObject*) self, field, epris_value_to_pointer ((_tmp1_ = value, value = NULL, _tmp1_)), __epris_structure_unset_and_free_gdestroy_notify);
	}
	(value == NULL) ? NULL : (value = (g_free (value), NULL));
}


void epris_structure_qset (EprisStructure* self, GQuark field, GValue* value) {
	EPRIS_STRUCTURE_GET_CLASS (self)->qset (self, field, value);
}


static GValue* _g_value_dup (GValue* self) {
	return g_boxed_copy (G_TYPE_VALUE, self);
}


GValue* epris_structure_qget (EprisStructure* self, GQuark field) {
	GValue* result;
	GValue* _tmp0_;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = NULL;
	result = (_tmp0_ = (GValue*) g_object_get_qdata ((GObject*) self, field), (_tmp0_ == NULL) ? NULL : _g_value_dup (_tmp0_));
	return result;
}


void epris_structure_set (EprisStructure* self, const char* field_name, GValue* value) {
	GValue* _tmp0_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (field_name != NULL);
	_tmp0_ = NULL;
	epris_structure_qset (self, g_quark_from_string (field_name), (_tmp0_ = value, (_tmp0_ == NULL) ? NULL : _g_value_dup (_tmp0_)));
	(value == NULL) ? NULL : (value = (g_free (value), NULL));
}


GValue* epris_structure_get (EprisStructure* self, const char* field_name) {
	GValue* result;
	GValue* _tmp0_;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (field_name != NULL, NULL);
	_tmp0_ = NULL;
	result = (_tmp0_ = (GValue*) g_object_get_data ((GObject*) self, field_name), (_tmp0_ == NULL) ? NULL : _g_value_dup (_tmp0_));
	return result;
}


char* epris_structure_to_string (EprisStructure* self) {
	char* result;
	char* ret;
	gboolean first;
	g_return_val_if_fail (self != NULL, NULL);
	ret = g_strdup_printf ("%s (", epris_structure_get_name (self));
	first = TRUE;
	{
		GSList* q_collection;
		GSList* q_it;
		q_collection = self->fields;
		for (q_it = q_collection; q_it != NULL; q_it = q_it->next) {
			GQuark q;
			q = *((GQuark*) q_it->data);
			{
				GValue* v;
				char* _tmp3_;
				char* _tmp2_;
				char* _tmp1_;
				if (!first) {
					char* _tmp0_;
					_tmp0_ = NULL;
					ret = (_tmp0_ = g_strconcat (ret, ", ", NULL), ret = (g_free (ret), NULL), _tmp0_);
				} else {
					first = FALSE;
				}
				v = g_object_get_qdata ((GObject*) self, q);
				_tmp3_ = NULL;
				_tmp2_ = NULL;
				_tmp1_ = NULL;
				ret = (_tmp3_ = g_strconcat (ret, _tmp2_ = g_strdup_printf ("%s = %s", g_quark_to_string (q), _tmp1_ = g_strdup_value_contents (v)), NULL), ret = (g_free (ret), NULL), _tmp3_);
				_tmp2_ = (g_free (_tmp2_), NULL);
				_tmp1_ = (g_free (_tmp1_), NULL);
			}
		}
	}
	result = g_strconcat (ret, ")", NULL);
	ret = (g_free (ret), NULL);
	return result;
}


void epris_structure_value_to_string (const GValue* src, GValue* dest) {
	EprisStructure* s;
	char* _tmp0_;
	s = epris_value_get_structure (&(*src));
	g_return_if_fail (s != NULL);
	_tmp0_ = NULL;
	g_value_set_string (&(*dest), _tmp0_ = epris_structure_to_string (s));
	_tmp0_ = (g_free (_tmp0_), NULL);
	(s == NULL) ? NULL : (s = (g_object_unref (s), NULL));
}


GQuark epris_structure_get_qname (EprisStructure* self) {
	GQuark result;
	g_return_val_if_fail (self != NULL, 0U);
	result = self->_name;
	return result;
}


const char* epris_structure_get_name (EprisStructure* self) {
	const char* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = g_quark_to_string (self->_name);
	return result;
}


void epris_structure_set_name (EprisStructure* self, const char* value) {
	g_return_if_fail (self != NULL);
	self->_name = g_quark_from_string (value);
	g_object_notify ((GObject *) self, "name");
}


static void _epris_structure_value_to_string_gvalue_transform (const GValue* src_value, GValue* dest_value) {
	epris_structure_value_to_string (src_value, dest_value);
}


static GObject * epris_structure_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	EprisStructureClass * klass;
	GObjectClass * parent_class;
	EprisStructure * self;
	klass = EPRIS_STRUCTURE_CLASS (g_type_class_peek (EPRIS_TYPE_STRUCTURE));
	parent_class = G_OBJECT_CLASS (g_type_class_peek_parent (klass));
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = EPRIS_STRUCTURE (obj);
	{
		g_value_register_transform_func (EPRIS_TYPE_STRUCTURE, G_TYPE_STRING, _epris_structure_value_to_string_gvalue_transform);
	}
	return obj;
}


static void epris_structure_class_init (EprisStructureClass * klass) {
	epris_structure_parent_class = g_type_class_peek_parent (klass);
	EPRIS_STRUCTURE_CLASS (klass)->qset = epris_structure_real_qset;
	G_OBJECT_CLASS (klass)->get_property = epris_structure_get_property;
	G_OBJECT_CLASS (klass)->set_property = epris_structure_set_property;
	G_OBJECT_CLASS (klass)->constructor = epris_structure_constructor;
	G_OBJECT_CLASS (klass)->finalize = epris_structure_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), EPRIS_STRUCTURE_NAME, g_param_spec_string ("name", "name", "name", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE | G_PARAM_CONSTRUCT));
}


static void epris_structure_instance_init (EprisStructure * self) {
	self->fields = NULL;
}


static void epris_structure_finalize (GObject* obj) {
	EprisStructure * self;
	self = EPRIS_STRUCTURE (obj);
	(self->fields == NULL) ? NULL : (self->fields = (_g_slist_free_g_free (self->fields), NULL));
	G_OBJECT_CLASS (epris_structure_parent_class)->finalize (obj);
}


GType epris_structure_get_type (void) {
	static GType epris_structure_type_id = 0;
	if (epris_structure_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (EprisStructureClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) epris_structure_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (EprisStructure), 0, (GInstanceInitFunc) epris_structure_instance_init, NULL };
		epris_structure_type_id = g_type_register_static (G_TYPE_OBJECT, "EprisStructure", &g_define_type_info, 0);
	}
	return epris_structure_type_id;
}


static void epris_structure_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	EprisStructure * self;
	gpointer boxed;
	self = EPRIS_STRUCTURE (object);
	switch (property_id) {
		case EPRIS_STRUCTURE_NAME:
		g_value_set_string (value, epris_structure_get_name (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void epris_structure_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	EprisStructure * self;
	self = EPRIS_STRUCTURE (object);
	switch (property_id) {
		case EPRIS_STRUCTURE_NAME:
		epris_structure_set_name (self, g_value_get_string (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


EprisStructure* epris_value_get_structure (const GValue* value) {
	EprisStructure* result;
	EprisStructure* _tmp0_;
	if (!G_VALUE_HOLDS (&(*value), EPRIS_TYPE_STRUCTURE)) {
		result = NULL;
		return result;
	}
	_tmp0_ = NULL;
	result = (_tmp0_ = EPRIS_STRUCTURE (g_value_get_object (&(*value))), (_tmp0_ == NULL) ? NULL : g_object_ref (_tmp0_));
	return result;
}




