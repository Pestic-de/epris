
#include <glib.h>
#include <glib-object.h>
#include <gst/gst.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


#define TYPE_AUDIO_PLAYER (audio_player_get_type ())
#define AUDIO_PLAYER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_AUDIO_PLAYER, AudioPlayer))
#define AUDIO_PLAYER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_AUDIO_PLAYER, AudioPlayerClass))
#define IS_AUDIO_PLAYER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_AUDIO_PLAYER))
#define IS_AUDIO_PLAYER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_AUDIO_PLAYER))
#define AUDIO_PLAYER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_AUDIO_PLAYER, AudioPlayerClass))

typedef struct _AudioPlayer AudioPlayer;
typedef struct _AudioPlayerClass AudioPlayerClass;
typedef struct _AudioPlayerPrivate AudioPlayerPrivate;

#define EPRIS_TYPE_STATE (epris_state_get_type ())

#define AUDIO_PLAYER_TYPE_GST_PLAY_FLAGS (audio_player_gst_play_flags_get_type ())

struct _AudioPlayer {
	GObject parent_instance;
	AudioPlayerPrivate * priv;
};

struct _AudioPlayerClass {
	GObjectClass parent_class;
};

typedef enum  {
	EPRIS_STATE_STOPPED,
	EPRIS_STATE_PAUSED,
	EPRIS_STATE_PLAYING
} EprisState;

struct _AudioPlayerPrivate {
	GstPipeline* pipeline;
	EprisState _state;
	GstTagList* _taglist;
	double _rate;
};

typedef enum  {
	AUDIO_PLAYER_GST_PLAY_FLAGS_VIDEO = 1 << 0,
	AUDIO_PLAYER_GST_PLAY_FLAGS_AUDIO = 1 << 1,
	AUDIO_PLAYER_GST_PLAY_FLAGS_TEXT = 1 << 2,
	AUDIO_PLAYER_GST_PLAY_FLAGS_VIS = 1 << 3,
	AUDIO_PLAYER_GST_PLAY_FLAGS_SOFT_VOLUME = 1 << 4,
	AUDIO_PLAYER_GST_PLAY_FLAGS_NATIVE_AUDIO = 1 << 5,
	AUDIO_PLAYER_GST_PLAY_FLAGS_NATIVE_VIDEO = 1 << 6
} AudioPlayerGstPlayFlags;



GType audio_player_get_type (void);
GType epris_state_get_type (void);
#define AUDIO_PLAYER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_AUDIO_PLAYER, AudioPlayerPrivate))
enum  {
	AUDIO_PLAYER_DUMMY_PROPERTY,
	AUDIO_PLAYER_STATE,
	AUDIO_PLAYER_TAGLIST,
	AUDIO_PLAYER_RATE,
	AUDIO_PLAYER_DURATION,
	AUDIO_PLAYER_POSITION
};
GType audio_player_gst_play_flags_get_type (void);
void audio_player_set_rate (AudioPlayer* self, double value);
static void audio_player_set_state (AudioPlayer* self, EprisState value);
AudioPlayer* audio_player_new (void);
AudioPlayer* audio_player_construct (GType object_type);
AudioPlayer* audio_player_new (void);
EprisState audio_player_get_state (AudioPlayer* self);
GstTagList* audio_player_get_taglist (AudioPlayer* self);
static void audio_player_set_taglist (AudioPlayer* self, GstTagList* value);
static gboolean audio_player_bus_func (AudioPlayer* self, GstBus* bus, GstMessage* message);
static gboolean _lambda0_ (AudioPlayer* self);
static gboolean __lambda0__gsource_func (gpointer self);
static void _audio_player_about_to_finish (AudioPlayer* self);
static gboolean _audio_player_bus_func_gst_bus_func (GstBus* bus, GstMessage* message, gpointer self);
static void audio_player_setup_pipeline (AudioPlayer* self);
void audio_player_request_state (AudioPlayer* self, EprisState state);
void audio_player_request_location (AudioPlayer* self, const char* location, gboolean immediately);
gint64 audio_player_get_duration (AudioPlayer* self);
double audio_player_get_rate (AudioPlayer* self);
void audio_player_request_seek (AudioPlayer* self, GstFormat format, gint64 position);
gint64 audio_player_get_position (AudioPlayer* self);
static gpointer audio_player_parent_class = NULL;
static void audio_player_finalize (GObject* obj);
static void audio_player_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void audio_player_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);




GType audio_player_gst_play_flags_get_type (void) {
	static GType audio_player_gst_play_flags_type_id = 0;
	if (G_UNLIKELY (audio_player_gst_play_flags_type_id == 0)) {
		static const GFlagsValue values[] = {{AUDIO_PLAYER_GST_PLAY_FLAGS_VIDEO, "AUDIO_PLAYER_GST_PLAY_FLAGS_VIDEO", "video"}, {AUDIO_PLAYER_GST_PLAY_FLAGS_AUDIO, "AUDIO_PLAYER_GST_PLAY_FLAGS_AUDIO", "audio"}, {AUDIO_PLAYER_GST_PLAY_FLAGS_TEXT, "AUDIO_PLAYER_GST_PLAY_FLAGS_TEXT", "text"}, {AUDIO_PLAYER_GST_PLAY_FLAGS_VIS, "AUDIO_PLAYER_GST_PLAY_FLAGS_VIS", "vis"}, {AUDIO_PLAYER_GST_PLAY_FLAGS_SOFT_VOLUME, "AUDIO_PLAYER_GST_PLAY_FLAGS_SOFT_VOLUME", "soft-volume"}, {AUDIO_PLAYER_GST_PLAY_FLAGS_NATIVE_AUDIO, "AUDIO_PLAYER_GST_PLAY_FLAGS_NATIVE_AUDIO", "native-audio"}, {AUDIO_PLAYER_GST_PLAY_FLAGS_NATIVE_VIDEO, "AUDIO_PLAYER_GST_PLAY_FLAGS_NATIVE_VIDEO", "native-video"}, {0, NULL, NULL}};
		audio_player_gst_play_flags_type_id = g_flags_register_static ("AudioPlayerGstPlayFlags", values);
	}
	return audio_player_gst_play_flags_type_id;
}


AudioPlayer* audio_player_construct (GType object_type) {
	GParameter * __params;
	GParameter * __params_it;
	AudioPlayer * self;
	GstPipeline* _tmp0_;
	__params = g_new0 (GParameter, 1);
	__params_it = __params;
	__params_it->name = "rate";
	g_value_init (&__params_it->value, G_TYPE_DOUBLE);
	g_value_set_double (&__params_it->value, 1.0);
	__params_it++;
	self = g_object_newv (object_type, __params_it - __params, __params);
	audio_player_set_state (self, EPRIS_STATE_STOPPED);
	_tmp0_ = NULL;
	self->priv->pipeline = (_tmp0_ = NULL, (self->priv->pipeline == NULL) ? NULL : (self->priv->pipeline = (gst_object_unref (self->priv->pipeline), NULL)), _tmp0_);
	while (__params_it > __params) {
		--__params_it;
		g_value_unset (&__params_it->value);
	}
	g_free (__params);
	return self;
}


AudioPlayer* audio_player_new (void) {
	return audio_player_construct (TYPE_AUDIO_PLAYER);
}


/* this.eos.connect (() => {
 Idle.add ( () => {
 request_state (Epris.State.STOPPED);
 } );
 } );*/
static gboolean audio_player_bus_func (AudioPlayer* self, GstBus* bus, GstMessage* message) {
	gboolean result;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (bus != NULL, FALSE);
	g_return_val_if_fail (message != NULL, FALSE);
	if (message->src != GST_OBJECT (self->priv->pipeline)) {
		result = TRUE;
		return result;
	}
	switch (message->type) {
		case GST_MESSAGE_STATE_CHANGED:
		{
			GstState new_state;
			GstState old_state;
			GstState pending_state;
			gboolean _tmp0_;
			new_state = 0;
			old_state = 0;
			pending_state = 0;
			gst_message_parse_state_changed (message, &old_state, &new_state, &pending_state);
			g_debug ("audio-player.vala:85: state changed: old %d new %d pending %d", (gint) old_state, (gint) new_state, (gint) pending_state);
			_tmp0_ = FALSE;
			if (new_state == GST_STATE_PLAYING) {
				_tmp0_ = self->priv->_state != EPRIS_STATE_PLAYING;
			} else {
				_tmp0_ = FALSE;
			}
			if (_tmp0_) {
				audio_player_set_state (self, EPRIS_STATE_PLAYING);
			} else {
				gboolean _tmp1_;
				_tmp1_ = FALSE;
				if (new_state != GST_STATE_PLAYING) {
					_tmp1_ = self->priv->_state != EPRIS_STATE_STOPPED;
				} else {
					_tmp1_ = FALSE;
				}
				if (_tmp1_) {
					audio_player_set_state (self, EPRIS_STATE_STOPPED);
				}
			}
			break;
		}
		case GST_MESSAGE_TAG:
		{
			GstTagList* tag_list;
			GstTagList* _tmp3_;
			GstTagList* _tmp2_;
			gboolean _tmp4_;
			tag_list = NULL;
			_tmp3_ = NULL;
			_tmp2_ = NULL;
			gst_message_parse_tag (message, &_tmp2_);
			tag_list = (_tmp3_ = _tmp2_, (tag_list == NULL) ? NULL : (tag_list = (gst_tag_list_free (tag_list), NULL)), _tmp3_);
			_tmp4_ = FALSE;
			if (audio_player_get_taglist (self) == NULL) {
				_tmp4_ = tag_list != NULL;
			} else {
				_tmp4_ = FALSE;
			}
			if (_tmp4_) {
				audio_player_set_taglist (self, tag_list);
			} else {
				GstTagList* _tmp5_;
				_tmp5_ = NULL;
				_tmp5_ = gst_tag_list_merge (audio_player_get_taglist (self), tag_list, GST_TAG_MERGE_REPLACE);
				(_tmp5_ == NULL) ? NULL : (_tmp5_ = (gst_tag_list_free (_tmp5_), NULL));
			}
			(tag_list == NULL) ? NULL : (tag_list = (gst_tag_list_free (tag_list), NULL));
			break;
		}
		case GST_MESSAGE_DURATION:
		{
			gint64 duration;
			GstFormat format;
			duration = 0LL;
			format = 0;
			gst_message_parse_duration (message, &format, &duration);
			switch (format) {
				case GST_FORMAT_TIME:
				{
					g_message ("audio-player.vala:114: duration %lli", duration);
					break;
				}
				default:
				{
					g_debug ("audio-player.vala:117: unhandled duration report");
					break;
				}
			}
			break;
		}
		case GST_MESSAGE_ERROR:
		{
			GError* _error_;
			char* debug;
			char* _tmp9_;
			char* _tmp8_;
			GError* _tmp7_;
			GError* _tmp6_;
			_error_ = NULL;
			debug = NULL;
			_tmp9_ = NULL;
			_tmp8_ = NULL;
			_tmp7_ = NULL;
			_tmp6_ = NULL;
			(gst_message_parse_error (message, &_tmp6_, &_tmp8_), _error_ = (_tmp7_ = _tmp6_, (_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL)), _tmp7_));
			debug = (_tmp9_ = _tmp8_, debug = (g_free (debug), NULL), _tmp9_);
			g_debug (_error_->message);
			g_debug (debug);
			(_error_ == NULL) ? NULL : (_error_ = (g_error_free (_error_), NULL));
			debug = (g_free (debug), NULL);
			break;
		}
		case GST_MESSAGE_EOS:
		{
			g_signal_emit_by_name (self, "eos");
			break;
		}
		default:
		{
			char* _tmp10_;
			_tmp10_ = NULL;
			g_debug (_tmp10_ = g_strconcat ("unhandled: ", gst_message_type_get_name (message->type), NULL));
			_tmp10_ = (g_free (_tmp10_), NULL);
			break;
		}
	}
	result = TRUE;
	return result;
}


static gboolean _lambda0_ (AudioPlayer* self) {
	gboolean result;
	g_signal_emit_by_name (self, "about-to-finish");
	result = FALSE;
	return result;
}


static gboolean __lambda0__gsource_func (gpointer self) {
	return _lambda0_ (self);
}


static void _audio_player_about_to_finish (AudioPlayer* self) {
	g_return_if_fail (self != NULL);
	g_idle_add (__lambda0__gsource_func, self);
}


static gboolean _audio_player_bus_func_gst_bus_func (GstBus* bus, GstMessage* message, gpointer self) {
	return audio_player_bus_func (self, bus, message);
}


static void audio_player_setup_pipeline (AudioPlayer* self) {
	GstPipeline* _tmp0_;
	GstElement* _tmp1_;
	GstBus* _tmp2_;
	g_return_if_fail (self != NULL);
	if (self->priv->pipeline != NULL) {
		return;
	}
	_tmp0_ = NULL;
	self->priv->pipeline = (_tmp0_ = GST_PIPELINE (gst_element_factory_make ("playbin2", "playbin")), (self->priv->pipeline == NULL) ? NULL : (self->priv->pipeline = (gst_object_unref (self->priv->pipeline), NULL)), _tmp0_);
	_tmp1_ = NULL;
	g_object_set (G_OBJECT (self->priv->pipeline), "video-sink", _tmp1_ = gst_element_factory_make ("fakesink", NULL), "flags", AUDIO_PLAYER_GST_PLAY_FLAGS_AUDIO, NULL, NULL);
	(_tmp1_ == NULL) ? NULL : (_tmp1_ = (gst_object_unref (_tmp1_), NULL));
	_tmp2_ = NULL;
	gst_bus_add_watch (_tmp2_ = gst_pipeline_get_bus (self->priv->pipeline), _audio_player_bus_func_gst_bus_func, self);
	(_tmp2_ == NULL) ? NULL : (_tmp2_ = (gst_object_unref (_tmp2_), NULL));
	g_object_connect ((GObject*) self->priv->pipeline, "swapped-object-signal::about-to-finish", _audio_player_about_to_finish, self, NULL, NULL);
	audio_player_set_taglist (self, NULL);
}


void audio_player_request_location (AudioPlayer* self, const char* location, gboolean immediately) {
	gboolean playing;
	gboolean _tmp0_;
	gboolean _tmp1_;
	gboolean _tmp2_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (location != NULL);
	playing = FALSE;
	audio_player_setup_pipeline (self);
	_tmp0_ = FALSE;
	if (((GstElement*) self->priv->pipeline)->current_state == GST_STATE_PLAYING) {
		_tmp0_ = TRUE;
	} else {
		_tmp0_ = ((GstElement*) self->priv->pipeline)->pending_state == GST_STATE_PLAYING;
	}
	playing = _tmp0_;
	_tmp1_ = FALSE;
	if (playing) {
		_tmp1_ = immediately;
	} else {
		_tmp1_ = FALSE;
	}
	if (_tmp1_) {
		gst_element_set_state ((GstElement*) self->priv->pipeline, GST_STATE_READY);
	}
	audio_player_set_taglist (self, NULL);
	g_object_set (G_OBJECT (self->priv->pipeline), "uri", location, NULL, NULL);
	_tmp2_ = FALSE;
	if (playing) {
		_tmp2_ = immediately;
	} else {
		_tmp2_ = FALSE;
	}
	if (_tmp2_) {
		audio_player_request_state (self, EPRIS_STATE_PLAYING);
	}
	g_debug ("audio-player.vala:176: loc refcnt %u", ((GObject*) self->priv->pipeline)->ref_count);
}


void audio_player_request_state (AudioPlayer* self, EprisState state) {
	g_return_if_fail (self != NULL);
	if (self->priv->pipeline == NULL) {
		return;
	}
	g_debug ("audio-player.vala:183: req refcnt %u", ((GObject*) self->priv->pipeline)->ref_count);
	switch (state) {
		case EPRIS_STATE_PLAYING:
		{
			gst_element_set_state ((GstElement*) self->priv->pipeline, GST_STATE_PLAYING);
			return;
		}
		case EPRIS_STATE_STOPPED:
		{
			gst_element_set_state ((GstElement*) self->priv->pipeline, GST_STATE_NULL);
			return;
		}
		default:
		{
			return;
		}
	}
}


void audio_player_request_seek (AudioPlayer* self, GstFormat format, gint64 position) {
	g_return_if_fail (self != NULL);
	if (format == GST_FORMAT_PERCENT) {
		position = (position * audio_player_get_duration (self)) / 100;
		format = GST_FORMAT_TIME;
	}
	if (!gst_element_seek ((GstElement*) self->priv->pipeline, audio_player_get_rate (self), format, GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_KEY_UNIT, GST_SEEK_TYPE_SET, position, GST_SEEK_TYPE_NONE, (gint64) GST_CLOCK_TIME_NONE)) {
		g_warning ("audio-player.vala:210: seek_simple() failed");
	}
}


EprisState audio_player_get_state (AudioPlayer* self) {
	EprisState result;
	g_return_val_if_fail (self != NULL, 0);
	result = self->priv->_state;
	return result;
}


static void audio_player_set_state (AudioPlayer* self, EprisState value) {
	g_return_if_fail (self != NULL);
	self->priv->_state = value;
	g_object_notify ((GObject *) self, "state");
}


GstTagList* audio_player_get_taglist (AudioPlayer* self) {
	GstTagList* result;
	g_return_val_if_fail (self != NULL, NULL);
	result = self->priv->_taglist;
	return result;
}


static void audio_player_set_taglist (AudioPlayer* self, GstTagList* value) {
	g_return_if_fail (self != NULL);
	if (value != NULL) {
		GstTagList* _tmp0_;
		_tmp0_ = NULL;
		self->priv->_taglist = (_tmp0_ = gst_tag_list_copy (value), (self->priv->_taglist == NULL) ? NULL : (self->priv->_taglist = (gst_tag_list_free (self->priv->_taglist), NULL)), _tmp0_);
	} else {
		GstTagList* _tmp1_;
		_tmp1_ = NULL;
		self->priv->_taglist = (_tmp1_ = NULL, (self->priv->_taglist == NULL) ? NULL : (self->priv->_taglist = (gst_tag_list_free (self->priv->_taglist), NULL)), _tmp1_);
	}
	g_object_notify ((GObject *) self, "taglist");
}


double audio_player_get_rate (AudioPlayer* self) {
	double result;
	g_return_val_if_fail (self != NULL, 0.0);
	result = self->priv->_rate;
	return result;
}


void audio_player_set_rate (AudioPlayer* self, double value) {
	g_return_if_fail (self != NULL);
	self->priv->_rate = value;
	g_object_notify ((GObject *) self, "rate");
}


gint64 audio_player_get_duration (AudioPlayer* self) {
	gint64 result;
	gint64 _result_;
	GstFormat format;
	gboolean _tmp0_;
	g_return_val_if_fail (self != NULL, 0LL);
	_result_ = 0LL;
	format = GST_FORMAT_TIME;
	_tmp0_ = FALSE;
	if (!gst_element_query_duration ((GstElement*) self->priv->pipeline, &format, &_result_)) {
		_tmp0_ = TRUE;
	} else {
		_tmp0_ = format != GST_FORMAT_TIME;
	}
	if (_tmp0_) {
		result = (gint64) GST_CLOCK_TIME_NONE;
		return result;
	}
	result = _result_;
	return result;
}


gint64 audio_player_get_position (AudioPlayer* self) {
	gint64 result;
	gint64 _result_;
	GstFormat format;
	gboolean _tmp0_;
	g_return_val_if_fail (self != NULL, 0LL);
	_result_ = 0LL;
	format = GST_FORMAT_TIME;
	_tmp0_ = FALSE;
	if (!gst_element_query_position ((GstElement*) self->priv->pipeline, &format, &_result_)) {
		_tmp0_ = TRUE;
	} else {
		_tmp0_ = format != GST_FORMAT_TIME;
	}
	if (_tmp0_) {
		result = (gint64) GST_CLOCK_TIME_NONE;
		return result;
	}
	result = _result_;
	return result;
}


static void audio_player_class_init (AudioPlayerClass * klass) {
	audio_player_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (AudioPlayerPrivate));
	G_OBJECT_CLASS (klass)->get_property = audio_player_get_property;
	G_OBJECT_CLASS (klass)->set_property = audio_player_set_property;
	G_OBJECT_CLASS (klass)->finalize = audio_player_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), AUDIO_PLAYER_STATE, g_param_spec_enum ("state", "state", "state", EPRIS_TYPE_STATE, 0, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), AUDIO_PLAYER_TAGLIST, g_param_spec_pointer ("taglist", "taglist", "taglist", G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), AUDIO_PLAYER_RATE, g_param_spec_double ("rate", "rate", "rate", -G_MAXDOUBLE, G_MAXDOUBLE, 0.0, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE | G_PARAM_CONSTRUCT));
	g_object_class_install_property (G_OBJECT_CLASS (klass), AUDIO_PLAYER_DURATION, g_param_spec_int64 ("duration", "duration", "duration", G_MININT64, G_MAXINT64, 0, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), AUDIO_PLAYER_POSITION, g_param_spec_int64 ("position", "position", "position", G_MININT64, G_MAXINT64, 0, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE));
	g_signal_new ("eos", TYPE_AUDIO_PLAYER, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);
	g_signal_new ("about_to_finish", TYPE_AUDIO_PLAYER, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);
}


static void audio_player_instance_init (AudioPlayer * self) {
	self->priv = AUDIO_PLAYER_GET_PRIVATE (self);
}


static void audio_player_finalize (GObject* obj) {
	AudioPlayer * self;
	self = AUDIO_PLAYER (obj);
	(self->priv->pipeline == NULL) ? NULL : (self->priv->pipeline = (gst_object_unref (self->priv->pipeline), NULL));
	(self->priv->_taglist == NULL) ? NULL : (self->priv->_taglist = (gst_tag_list_free (self->priv->_taglist), NULL));
	G_OBJECT_CLASS (audio_player_parent_class)->finalize (obj);
}


GType audio_player_get_type (void) {
	static GType audio_player_type_id = 0;
	if (audio_player_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (AudioPlayerClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) audio_player_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (AudioPlayer), 0, (GInstanceInitFunc) audio_player_instance_init, NULL };
		audio_player_type_id = g_type_register_static (G_TYPE_OBJECT, "AudioPlayer", &g_define_type_info, 0);
	}
	return audio_player_type_id;
}


static void audio_player_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	AudioPlayer * self;
	gpointer boxed;
	self = AUDIO_PLAYER (object);
	switch (property_id) {
		case AUDIO_PLAYER_STATE:
		g_value_set_enum (value, audio_player_get_state (self));
		break;
		case AUDIO_PLAYER_TAGLIST:
		g_value_set_pointer (value, audio_player_get_taglist (self));
		break;
		case AUDIO_PLAYER_RATE:
		g_value_set_double (value, audio_player_get_rate (self));
		break;
		case AUDIO_PLAYER_DURATION:
		g_value_set_int64 (value, audio_player_get_duration (self));
		break;
		case AUDIO_PLAYER_POSITION:
		g_value_set_int64 (value, audio_player_get_position (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void audio_player_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	AudioPlayer * self;
	self = AUDIO_PLAYER (object);
	switch (property_id) {
		case AUDIO_PLAYER_STATE:
		audio_player_set_state (self, g_value_get_enum (value));
		break;
		case AUDIO_PLAYER_TAGLIST:
		audio_player_set_taglist (self, g_value_get_pointer (value));
		break;
		case AUDIO_PLAYER_RATE:
		audio_player_set_rate (self, g_value_get_double (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}




