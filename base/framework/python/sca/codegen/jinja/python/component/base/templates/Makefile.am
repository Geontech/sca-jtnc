
#% set outputdir = generator.getOutputDir()
#% set componentdir = component.name.replace('.','/')
#% set sdrbranch = component.sdrpath.split('/')[0]
# vim: noet: softtabstop=0
ACLOCAL_AMFLAGS = -I m4 -I${SCAHOME}/share/aclocal/sca
AUTOMAKE_OPTIONS = subdir-objects

xmldir = $(prefix)/{{component.sdrpath}}/{{componentdir}}/
dist_xml_DATA = {{component.profile.values()|relpath(outputdir)|join(' ')}}
{{sdrbranch}}dir = $(prefix)/{{component.sdrpath}}/{{componentdir}}/python/

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

# Sources are auto-included from a file generated by the SCA IDE. You may
# remove the following lines if you wish to manually control these options.
include $(srcdir)/Makefile.am.ide
nobase_dist_{{sdrbranch}}_SCRIPTS = $(sca_SCRIPTS_auto)
nobase_dist_{{sdrbranch}}_DATA = $(sca_DATA_auto)
