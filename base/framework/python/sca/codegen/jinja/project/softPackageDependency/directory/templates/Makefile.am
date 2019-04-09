# vim: noet: softtabstop=0
ACLOCAL_AMFLAGS = -I m4 -I${SCAHOME}/share/aclocal/sca
AUTOMAKE_OPTIONS = subdir-objects

xmldir = $(prefix)/{{component.sdrpath}}/{{component.name}}{{generator.variant}}/
dist_xml_DATA = ../{{component.name}}.spd.xml

mdir = $(prefix)/{{component.sdrpath}}/{{component.name}}{{generator.variant}}/{{component.impl.outputdir}}/share/
dist_m_DATA = share/*

distclean-local:
	rm -rf m4
	rm -f config.*
	rm -rf autom4te.cache
	rm -f acinclude.m4
	rm -f aclocal.m4
	rm -f configure
	rm -f depcomp
	rm -f install-sh
	rm -f ltmain.sh
	rm -f Makefile.in
	rm -f missing
	rm -rf .deps
