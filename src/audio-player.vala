using GLib;
using Gst;

public class AudioPlayer: GLib.Object {

	[Flags]
	public enum GstPlayFlags {
		VIDEO         = 1 << 0,
		AUDIO         = 1 << 1,
		TEXT          = 1 << 2,
		VIS           = 1 << 3,
		SOFT_VOLUME   = 1 << 4,
		NATIVE_AUDIO  = 1 << 5,
		NATIVE_VIDEO  = 1 << 6
	}

	Pipeline pipeline;

	public Epris.State state { get; private set; }

	TagList _taglist;
	public TagList taglist { get { return _taglist; }
		private set {
			if (value != null) {
				_taglist = value.copy ();
			} else
				_taglist = null;
		}
	}

	double _rate;
	public double rate { get { return _rate; }
		construct set {
			_rate = value;
		}
	}

	public int64 duration { get {
			int64 result;
			var format = Gst.Format.TIME;

			if (!pipeline.query_duration (ref format, out result) ||
				format != Gst.Format.TIME)
				return CLOCK_TIME_NONE;

			return result;
		}
	}

	public int64 position { get {
			int64 result;
			var format = Gst.Format.TIME;

			if (!pipeline.query_position (ref format, out result) ||
				format != Gst.Format.TIME)
				return CLOCK_TIME_NONE;

			return result;
		}
	}

	public signal void eos ();
	public signal void about_to_finish ();

	public AudioPlayer() {
		rate = 1.0;
		state = Epris.State.STOPPED;
		pipeline = null;
		// this.eos.connect (() => {
		// 		Idle.add ( () => {
		// 				request_state (Epris.State.STOPPED);
		// 			} );
		// 	} );
	}

	bool bus_func (Gst.Bus bus, Gst.Message message) {
		if (message.src != pipeline)
			return true;

		switch (message.type) {
		case MessageType.STATE_CHANGED:
			Gst.State new_state, old_state, pending_state;

			message.parse_state_changed (out old_state, out new_state, out pending_state);
			debug ("state changed: old %d new %d pending %d", old_state, new_state, pending_state);

			if (new_state == Gst.State.PLAYING && state != Epris.State.PLAYING)
				state = Epris.State.PLAYING;
			else if (new_state != Gst.State.PLAYING && state != Epris.State.STOPPED)
				state = Epris.State.STOPPED;

			break;

		case MessageType.TAG:
			TagList tag_list;

			message.parse_tag (out tag_list);

			if (taglist == null && tag_list != null)
				taglist = tag_list;
			else
				taglist.merge (tag_list, TagMergeMode.REPLACE);

			break;

		case MessageType.DURATION:
			int64 duration;
			Gst.Format format;

			message.parse_duration (out format, out duration);

			switch (format) {
			case Format.TIME:
				GLib.message ("duration %lli", duration);
				break;
			default:
				debug ("unhandled duration report");
				break;
			}

			break;

		case MessageType.ERROR:
			Error error;
			string debug;

			message.parse_error (out error, out debug);

			GLib.debug (error.message);
			GLib.debug (debug);

			break;

		case MessageType.EOS:
			eos ();
			break;

		default:
			debug ("unhandled: " + message.type.to_string ());
			break;
		}
		return true;
	}

	void _about_to_finish () { Idle.add ( () => { this.about_to_finish (); return false; });	}
	void setup_pipeline () {
		if (pipeline != null)
			return;
		pipeline = (Pipeline)ElementFactory.make ("playbin2", "playbin");
		((GLib.Object)pipeline).set (
			"video-sink", ElementFactory.make ("fakesink", null),
			"flags", GstPlayFlags.AUDIO,
			null);
		pipeline.get_bus ().add_watch (bus_func);
		pipeline.connect ("swapped-object-signal::about-to-finish", _about_to_finish, this, null);

		taglist = null;
	}

	public void request_location (string location, bool immediately = false) {
		bool playing;

		setup_pipeline ();

		playing = (pipeline.current_state == Gst.State.PLAYING || pipeline.pending_state == Gst.State.PLAYING);

		if (playing && immediately)
			pipeline.set_state (Gst.State.READY);

		taglist = null;
		((GLib.Object)pipeline).set ("uri", location, null);

		if (playing && immediately)
			request_state (Epris.State.PLAYING);

		debug ("loc refcnt %u", pipeline.ref_count);
	}

	public void request_state (Epris.State state) {
		if (pipeline == null)
			return;

		debug ("req refcnt %u", pipeline.ref_count);

		switch (state) {
		case Epris.State.PLAYING:
			pipeline.set_state (Gst.State.PLAYING);
			return;

		case Epris.State.STOPPED:
			pipeline.set_state (Gst.State.NULL);
			return;

		default:
			return;
		}
	}

	public void request_seek (Gst.Format format, int64 position) {
		if (format == Gst.Format.PERCENT) {
			position = position * duration / 100;
			format = Gst.Format.TIME;
		}

		if (!pipeline.seek (rate,
							format,
							SeekFlags.FLUSH | SeekFlags.KEY_UNIT,
							Gst.SeekType.SET, position,
							Gst.SeekType.NONE, CLOCK_TIME_NONE))
			warning ("seek_simple() failed");
	}

}
