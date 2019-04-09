
#{% extends "base/Makefile.am" %}

#{% block extensions %}
mdir = {{impldir}}
dist_m_DATA = *.m
#{% endblock %}

#{% block compileFlags %}
{{ super() -}}
{{amtarget}}_CXXFLAGS += $(OCTAVE_CPPFLAGS)
{{amtarget}}_LDFLAGS += $(BOOST_FILESYSTEM_LIB) $(OCTAVE_LIBS)
#{% endblock %}
