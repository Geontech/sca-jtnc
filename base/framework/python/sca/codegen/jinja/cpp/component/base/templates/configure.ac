
#{% block license %}
#{# Allow child templates to include license #}
#{% endblock %}
#{% block acInit %}
AC_INIT({{component.name}}, {{component.version}})
AM_INIT_AUTOMAKE([nostdinc foreign])
AC_CONFIG_MACRO_DIR([m4])
#{% if component.impl.module %}
LT_INIT([dlopen])
#{% endif %}
#{% endblock %}

#{% block acChecks %}
AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
#{% endblock %}

#{% block acOssie %}
AC_CORBA_ORB
SCA_CHECK_SCA
SCA_SCAROOT_AS_PREFIX
#{% endblock %}

m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

# Dependencies
#{% block pkgConfigPath %}
#{% endblock %}
#{% block projectDeps %}
PKG_CHECK_MODULES([PROJECTDEPS], [sca >= {{versions.sca}} bulkio >= {{versions.bulkio}} omniORB4 >= {{versions.omniORB4}}#{% endblock %}])
#{% block interfaceDeps %}
#{% if component.interfacedeps %}
PKG_CHECK_MODULES([INTERFACEDEPS], [{{component.interfacedeps|join(', ')}}])
#{% endif %}
#{% endblock %}
#{% block softpkgDeps %}
#{% for dep in component.impl.softpkgdeps %}
RH_SOFTPKG_CXX([{{dep.spd}}]{{',[%s]' % dep.impl if dep.impl}})
#{% endfor %}
#{% endblock %}
#{% block coreDeps %}
SCA_ENABLE_LOG4CXX
AX_BOOST_BASE([{{versions.boost}}])
AX_BOOST_SYSTEM
AX_BOOST_THREAD
AX_BOOST_REGEX
#{% endblock %}

#{% block acConfig %}
AC_CONFIG_FILES([
#%- filter trim|lines|join(' \\\n')|indent(17)
Makefile
#%- block files
#% endblock
#% endfilter
])
AC_OUTPUT
#{% endblock %}
