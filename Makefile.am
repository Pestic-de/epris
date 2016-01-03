ACLOCAL_AMFLAGS = -I m4

SUBDIRS = extra src

servicedir = $(DBUS_SERVICES_DIR)
service_in_files = org.mpris.epris.service.in
service_DATA = org.mpris.epris.service

CLEANFILES = $(service_DATA)
EXTRA_DIST = THANKS $(service_in_files) epris-completion.sh

%.service: %.service.in
	@sed -e "s|\@libexecdir\@|$(libexecdir)|" $< > $@

DISTCHECK_CONFIGURE_FLAGS = --with-services-dir='$${prefix}/share/dbus-1/services'

# see build-aux/git-version-get for details
BUILT_SOURCES = $(top_srcdir)/.version
$(top_srcdir)/.version:
	echo $(VERSION) > $@-t && mv $@-t $@
dist-hook:
	echo $(VERSION) > $(distdir)/.tarball-version

update-shave:
	for i in shave.in shave.m4 shave-libtool.in; do \
		wget -O $$i http://git.lespiau.name/cgit/shave/blob/\?path=shave/$$i ; \
	done
	mv shave.m4 m4/
