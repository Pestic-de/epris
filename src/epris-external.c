#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <string.h>

#include <glib.h>
#include <glib-object.h>

#include "epris-external.h"

static const char*
epris_version (void)
{
    static const char version[] = PACKAGE_VERSION;

    return version;
}

gint epris_debug_level;

void
epris_log_handler (const char    *log_domain,
                   GLogLevelFlags log_level,
                   const char    *message)
{
    const char *prefix;
    GString *gstr;
    gint level = 5;
    gchar   *str_time;
    time_t  the_time;

    if (log_level & G_LOG_FLAG_RECURSION) {
        return;
    }

    switch (log_level & G_LOG_LEVEL_MASK) {
    case G_LOG_LEVEL_ERROR:
        prefix = "ERROR";
        level = 0;
        break;
    case G_LOG_LEVEL_CRITICAL:
        prefix = "CRITICAL";
        level = 1;
        break;
    case G_LOG_LEVEL_WARNING:
        prefix = "WARNING";
        level = 2;
        break;
    case G_LOG_LEVEL_MESSAGE:
        prefix = "Message";
        level = 3;
        break;
    case G_LOG_LEVEL_INFO:
        prefix = "info";
        level = 4;
        break;
    case G_LOG_LEVEL_DEBUG:
        prefix = "debug";
        level = 4;
        break;
    default:
        prefix = "";
        break;
    }

    if (level >= epris_debug_level)
        return;

    gstr = g_string_new (PACKAGE_NAME " ");

    time (&the_time);
    str_time = g_new0 (gchar, 255);
    strftime (str_time, 254, "%H:%M:%S", localtime (&the_time));

    g_string_append_printf (gstr, "%-8s %8s (%s): %s", prefix, log_domain, str_time, message);

    /* no newline here, the print_debug_func is supposed to add it */
    if (gstr->str[gstr->len - 1] == '\n') {
        g_string_erase (gstr, gstr->len - 1, 1);
    }

    g_printerr ("%s\n", gstr->str);
    g_string_free (gstr, TRUE);
    g_free (str_time);
}

gboolean
epris_uri_is_valid (const gchar * uri)
{
    gchar *check = (gchar *) uri;

    g_assert (uri != NULL);

    if (g_ascii_isalpha (*check)) {
        check++;
        while (g_ascii_isalnum (*check) || *check == '+'
               || *check == '-' || *check == '.')
            check++;
    }

    return *check == ':';
}

void*
epris_value_to_pointer (GValue *v)
{
    return v;
}

#ifndef GST_FORMAT_TIME
typedef guint64	GstClockTime;
# define GST_SECOND  (G_USEC_PER_SEC * G_GINT64_CONSTANT (1000))
# define GST_FORMAT_TIME "u:%02u:%02u.%09u"
# define GST_CLOCK_TIME_NONE             ((GstClockTime) -1)
# define GST_CLOCK_TIME_IS_VALID(time)   (((GstClockTime)(time)) != GST_CLOCK_TIME_NONE)
# define GST_TIME_ARGS(t)                                               \
        GST_CLOCK_TIME_IS_VALID (t) ?                                   \
        (guint) (((GstClockTime)(t)) / (GST_SECOND * 60 * 60)) : 99,    \
        GST_CLOCK_TIME_IS_VALID (t) ?                                   \
        (guint) ((((GstClockTime)(t)) / (GST_SECOND * 60)) % 60) : 99,  \
        GST_CLOCK_TIME_IS_VALID (t) ?                                   \
        (guint) ((((GstClockTime)(t)) / GST_SECOND) % 60) : 99,         \
        GST_CLOCK_TIME_IS_VALID (t) ?                                   \
        (guint) (((GstClockTime)(t)) % GST_SECOND) : 999999999
#endif

gchar*
epris_time_to_string (gint64 t)
{
    return g_strdup_printf ("%" GST_FORMAT_TIME, GST_TIME_ARGS (t));
}

/*
 * Local Variables:
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 * vim:set expandtab shiftwidth=4:
 */
