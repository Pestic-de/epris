AC_INIT([epris],
	m4_esyscmd([GNOME_TAG_PATTERN=v build-aux/git-version-gen .tarball-version]),
	[marcandre.lureau@gmail.com])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([-Wall -Werror foreign])

if type -p stow > /dev/null && test -d /usr/local/stow ; then
   AC_MSG_NOTICE([*** Found /usr/local/stow: default install prefix set to /usr/local/stow/${PACKAGE_NAME}-${PACKAGE_VERSION} ***])
   ac_default_prefix="/usr/local/stow/${PACKAGE_NAME}-${PACKAGE_VERSION}"
fi

AC_PROG_CC
AC_PATH_PROG(VALAC, [valac], [valac])
AC_SUBST(VALAC)

PKG_CHECK_MODULES(DBUS, [dbus-glib-1 >= 0.70 dbus-1 >= 0.70 gthread-2.0])
AC_SUBST(DBUS_CFLAGS)
AC_SUBST(DBUS_LIBS)

PKG_CHECK_MODULES(GST, [gstreamer-0.10])
AC_SUBST(GST_CFLAGS)
AC_SUBST(GST_LIBS)

dnl DBus services dir
AC_ARG_WITH([services_dir],
            AS_HELP_STRING([--with-services-dir], [Path to DBus services directory]))

if test "x$with_services_dir" = "x" ; then
   with_services_dir="`pkg-config --variable session_bus_services_dir dbus-1`"
fi

DBUS_SERVICES_DIR="$with_services_dir"
AC_SUBST(DBUS_SERVICES_DIR)


AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
  Makefile
  extra/Makefile
  src/Makefile
])

test "x$exec_prefix" = xNONE && exec_prefix='${prefix}'
LIBEXECDIR=`eval eval echo $libexecdir`
AC_DEFINE_UNQUOTED([LIBEXECDIR], "$LIBEXECDIR", [$libexecdir])

AC_OUTPUT

echo "
$PACKAGE_NAME $PACKAGE_VERSION:

        prefix:                                 ${prefix}
        execdir:                                ${libexecdir}
        source code location:                   ${srcdir}
        compiler:                               ${CC}
        service dir:                            ${with_services_dir}
"
