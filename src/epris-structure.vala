using GLib;
using DBus;

namespace Epris {
    public class Structure : GLib.Object {
        public SList<Quark?> fields = null; // list of field name quarks

        protected Quark _name;

        public Quark qname {
            get {
                return _name;
            }
        }

        public string name {
            get {
                return _name.to_string ();
            }
            protected construct set {
                _name = Quark.from_string (value);
            }
		    default = "(null)";
        }

        public Structure (string name) {
            this.name = name;
        }

        construct {
            Value.register_transform_func (typeof (Structure), typeof (string), Structure.value_to_string);
        }

        private static void _unset_and_free (void* p) {
            Value* v = (Value *)p;
            v->unset ();
            g_free (v);
        }

        public virtual void qset (Quark field, owned Value? value) {
            if (value == null) {
                fields.remove (field);
                this.set_qdata (field, null);
            } else {
                if (fields.find (field) == null)
                    fields.append (field);

                this.set_qdata_full (field, Epris.value_to_pointer ((owned) value), _unset_and_free);
            }
        }

        public Value? qget (Quark field) {
            return (Value?)this.get_qdata (field);
        }

        public new void set (string field_name, owned Value? value) {
            qset (Quark.from_string (field_name), value);
        }

		public new Value? get (string field_name) {
            return (Value?)this.get_data (field_name);
        }

        public string to_string () {
            string ret = "%s (".printf (name);
            bool first = true;

            foreach (Quark q in fields) {
                if (!first)
                    ret += ", ";
                else
                    first = false;
                Value *v = this.get_qdata (q);
                ret += "%s = %s".printf (q.to_string (), v->strdup_contents ());
            }

            return ret + ")";
        }

        public static void value_to_string (Value src, out Value dest) {
            Structure s = value_get_structure (src);

            return_if_fail (s != null);

            dest.set_string (s.to_string ());
        }
    }

    public static Structure? value_get_structure (Value value) {
        if (! value.holds (typeof (Structure)))
            return null;
        return (Structure)value.get_object ();
    }
}
