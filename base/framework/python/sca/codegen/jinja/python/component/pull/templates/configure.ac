AC_INIT({{component.name}}, {{component.version}})
AM_INIT_AUTOMAKE([nostdinc foreign])
AC_CONFIG_MACRO_DIR([m4])

AC_PROG_INSTALL

AC_CORBA_ORB
SCA_CHECK_SCA
SCA_SCAROOT_AS_PREFIX
AM_PATH_PYTHON([{{versions.python}}])

PKG_CHECK_MODULES([SCA], [sca >= {{versions.sca}}])
AC_CHECK_PYMODULE(sca, [], [AC_MSG_ERROR([the python sca module is required])])
PKG_CHECK_MODULES([OMNIORB], [omniORB4 >= {{versions.omniORB4}}])
AC_CHECK_PYMODULE(omniORB, [], [AC_MSG_ERROR([the python omniORB module is required])])

#{% for interface in component.interfacedeps %}
PKG_CHECK_MODULES({{interface.name}}, {{interface.requires}}) 
AC_CHECK_PYMODULE({{interface.module}}, [], [AC_MSG_ERROR([the python {{interface.module}} module is required])])
#{% endfor %}

AC_CONFIG_FILES(Makefile)

AC_OUTPUT
