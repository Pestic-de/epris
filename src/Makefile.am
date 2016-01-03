bin_PROGRAMS = epr
libexec_PROGRAMS = epris

AM_CPPFLAGS =					\
	-I$(top_srcdir)

epris_VALASOURCES =				\
	audio-player.vala			\
	epr.vala				\
	epris.vala				\
	epris-track-list.vala			\
	epris-common.vala			\
	epris-client.vala			\
	epris-service.vala			\
	epris-storage.vala			\
	epris-structure.vala

epris_SOURCES =					\
	audio-player.c				\
	epris.c					\
	epris-track-list.c			\
	epris-common.c				\
	epris-external.c			\
	epris-external.h			\
	epris-external.vapi			\
	epris-service.c				\
	epris-storage.c				\
	epris-structure.c

epris_CFLAGS =					\
	-DG_LOG_DOMAIN=\"epris\"		\
	$(DBUS_CFLAGS)				\
	$(GST_CFLAGS)
epris_LDADD =					\
	$(DBUS_LIBS)				\
	$(GST_LIBS)

epr_SOURCES =					\
	epr.c					\
	epris-client.c				\
	epris-common.c				\
	epris-external.c			\
	epris-structure.c

epr_CFLAGS =					\
	-DG_LOG_DOMAIN=\"epr\"			\
	$(DBUS_CFLAGS)
epr_LDADD =					\
	$(DBUS_LIBS)

epris.vala.stamp: $(epris_VALASOURCES)
	$(VALAC) --thread --vapidir $(srcdir) --pkg epris-external --pkg dbus-glib-1 --pkg gstreamer-0.10 --pkg posix \
		-C --basedir $(top_srcdir) --library epris $^
	touch $@

BUILT_SOURCES =					\
	epris.vala.stamp

EXTRA_DIST =					\
	$(BUILT_SOURCES)			\
	$(epris_VALASOURCES:.vala=.c)		\
	$(epris_VALASOURCES)

dist-hook: epris.vala.stamp
