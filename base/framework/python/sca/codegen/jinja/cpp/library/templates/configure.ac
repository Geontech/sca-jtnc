
AC_INIT({{component.name}}, {{component.version}})
AM_INIT_AUTOMAKE([nostdinc foreign])
AC_CONFIG_MACRO_DIR([m4])

AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
LT_INIT([disable-static])

AC_CORBA_ORB
SCA_CHECK_SCA
RH_SOFTPKG_PREFIX([{{component.name}}],[{{component.impl.id}}])

m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

# Dependencies
PKG_CHECK_MODULES([SCA], [sca >= {{versions.sca}}])
#{% for dep in component.impl.softpkgdeps %}
RH_SOFTPKG_CXX([{{dep.spd}}]{{',[%s]' % dep.impl if dep.impl}})
#{% endfor %}
SCA_ENABLE_LOG4CXX
AX_BOOST_BASE([{{versions.boost}}])
AX_BOOST_SYSTEM
AX_BOOST_THREAD
AX_BOOST_REGEX

AC_CONFIG_FILES([Makefile {{component.pcfile}}])
AC_OUTPUT
