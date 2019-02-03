#
# This file is protected by Copyright. Please refer to the COPYRIGHT file
# distributed with this source distribution.
#
# This file is part of SCA-JTNC core.
#
# SCA-JTNC core is free software: you can redistribute it and/or modify it under
# the terms of the GNU Lesser General Public License as published by the Free
# Software Foundation, either version 3 of the License, or (at your option) any
# later version.
#
# SCA-JTNC core is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
# details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see http://www.gnu.org/licenses/.
#

dnl Update this version number immedately after a release
AC_INIT([sca],[4.1.0])
#AM_INIT_AUTOMAKE(nostdinc)
# allows filenames over 99 characters long during dist
AM_INIT_AUTOMAKE([1.9 tar-pax subdir-objects])
dnl Update these verion numbers immedately before a release
dnl
dnl The version number is in the format "current:revision:age"
dnl
dnl Follow these steps (in order) to correctly update the
dnl version info:
dnl
dnl 1. If any source code has changed at all, increment revision
dnl 2. If any interfaces have been added, modified, or removed
dnl    then increment current and set revision to 0
dnl 3. If any interfaces have been addded then increment age
dnl 4. If any interfaces have been removed or changed, then set
dnl    age to 0
AC_SUBST([LIBSCACF_VERSION_INFO], [4:1:0])
AC_SUBST([LIBOSSIEPARSER_VERSION_INFO], [3:0:0])
AC_SUBST([LIBOMNIJNI_VERSION_INFO], [1:0:1])
AC_SUBST([LIBOSSIECFJNI_VERSION_INFO], [1:0:0])
AC_SUBST([LIBREDHAWK_LOGGING_VERSION_INFO], [1:0:0])
AC_SUBST([BULKIO_API_VERSION], [2.2])
AC_SUBST([BULKIO_SO_VERSION], [0:0:0])

dnl AC_CONFIG_MACRO_DIR([m4])
dnl LT_INIT

AC_PREFIX_DEFAULT([/usr/local/redhawk/core])
OSSIE_SCAHOME_AS_PREFIX
OSSIE_SCAROOT_IGNORE_PREFIX

AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL
PKG_PROG_PKG_CONFIG
AC_HEADER_SYS_WAIT

AC_CORBA_ORB

AC_LANG_PUSH([C++])

AX_BOOST_BASE([1.35])
AX_BOOST_SYSTEM
AX_BOOST_FILESYSTEM
AX_BOOST_SERIALIZATION
AX_BOOST_REGEX
AX_BOOST_THREAD
AX_BOOST_DATE_TIME

m4_include(acinclude/unitdir.m4)
m4_include(acinclude/testdir.m4)

AX_LIB_EXPAT([1.95.8])
if test x"$HAVE_EXPAT" = xno ; then
        AC_MSG_ERROR([The Expat XML parser library and header files are required])
fi

PKG_CHECK_MODULES([OMNIORB], [omniORB4 >= 4.0.0])
OMNIORB_INCLUDEDIR=`pkg-config --variable=includedir omniORB4`
AC_SUBST(OMNIORB_INCLUDEDIR)
PKG_CHECK_EXISTS([omniORB4 >= 4.2.0],[AC_DEFINE([OMNIORB4_2],[1],[])])
PKG_CHECK_MODULES([OMNITHREAD], [omnithread3 >= 4.0.0])
PKG_CHECK_MODULES([OMNIDYNAMIC], [omniDynamic4 >= 4.0.0])

dnl Use PKG_CHECK_EXISTS because it won't throw error messages like PKG_CHECK_MODULES will
AC_MSG_CHECKING([for COS library])
PKG_CHECK_EXISTS([omniCOS4 >= 4.0.0], [libomnicos_exist=yes], [libomnicos_exist=no])
dnl Use PKG_CHECK_MODULES to declare the CFLAGS and LIBS varible
AC_MSG_RESULT([yes])
PKG_CHECK_MODULES([OMNICOS], [omniCOS4 >= 4.0.0])
OMNICOS_IDLDIR=`pkg-config --variable=idldir omniCOS4`
AC_SUBST(OMNICOS_IDLDIR)

AC_DEFINE(ENABLE_EVENTS, 1, [Define if events are enabled])
AC_SUBST(ENABLE_EVENTS_FLAGS, [-DENABLE_EVENTS=1])
AM_CONDITIONAL(ENABLE_EVENTS, [true])

AC_CHECK_PROG([IDL], [omniidl], [omniidl], [no])
if test "$IDL" = no; then
  AC_MSG_ERROR([cannot find omniidl program])
fi

AC_MSG_CHECKING([for default IDL path])
idldir=`pkg-config --variable=idldir omniORB4`
AC_MSG_RESULT([$idldir])
AC_SUBST(IDLDIR, [$idldir])

dnl Executable is named xsdcxx in Fedora epel repo, REDHAWK dep is named xsd
AC_CHECK_PROGS([XSD], [xsdcxx xsd], [no])
if test x"$XSD" = xno ; then
	AC_MSG_ERROR([Required program 'xsdcxx' is missing.])
fi
# Get the XSD version
AC_MSG_CHECKING([xsd version])
xsd_version=`${XSD} version 2>&1 | head -n 1 | awk '{print $8}'`
oldest_version=`echo -e "${xsd_version}\n3.3.0" | sort -t '.' -k 1,1 -k 2,2 -k 3,3 -k 4,4 -g | head -n 1`
if test "x$oldest_version" != "x3.3.0"; then
    AC_MSG_FAILURE([XSD version 3.3.0 required])
else
    AC_MSG_RESULT([$xsd_version])
fi
AC_CHECK_HEADER([xsd/cxx/config.hxx], [], [AC_MSG_ERROR([missing XSD headers])])
AC_CHECK_PROG([XMLCATALOG], [xmlcatalog], [xmlcatalog], [no])
AM_CONDITIONAL(HAVE_XMLCATALOG, test $XMLCATALOG != "no")

# add numa support to affinity module
AC_ARG_ENABLE([affinity], AS_HELP_STRING([--enable-affinity], [Enable numa affinity processing]))
   AC_MSG_CHECKING([Adding support for numa affinity processing])
if test "x$enable_affinity" = "xyes"; then
   dnl  determine if numa library support is available
   AC_SUBST(OSSIE_AFFINITY, "yes")
   AC_MSG_RESULT([yes])
else
  AC_MSG_RESULT([no])
fi

if test "x$enable_affinity" = "xyes"; then
   AC_CHECK_LIB( numa, numa_available )
fi


# Find a Posix-compliant sed
# We attempt to use AC_PROG_SED, but it's only available in autoconf >= 2.59b
# Otherwise, settle for finding it by executable name
ifdef([AC_PROG_SED], [AC_PROG_SED], [AC_CHECK_PROGS(SED, [gsed sed])])

OSSIE_PYTHON_INSTALL_SCHEME
OSSIE_ENABLE_LOG4CXX
OSSIE_ENABLE_TRACE
OSSIE_ENABLE_PERSISTENCE

m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

# Allow user to explictly prevent JAVA compilation
AC_ARG_ENABLE([java], AS_HELP_STRING([--disable-java], [Disable framework java support]))

HAVE_JAVASUPPORT=no
if test "x$enable_java" != "xno"; then
  # configure was run with java enabled

  # Ensure JAVA_HOME is set
  RH_JAVA_HOME

  # Minimum Java version
  java_source_version=1.8

  # Locate tools we need based on JAVA_HOME
  RH_PROG_JAVAC([$java_source_version])
  RH_PROG_JAR
  RH_PROG_IDLJ

  # Enable Java Automake-like build rules
  RH_JARFILE_RULES

  # Enable IDL-to-Java build rules
  RH_IDLJ_RULES

  # Check vendor
  RH_JAVA_VENDOR

  # Locate headers we need
  RH_JAVA_JNI_H

  if test "$JAVA_HOME" != "no" -a \
          "$JAVAC" != "no" -a \
          "$JAR" != "no" -a \
          "$IDLJ" != "no" -a \
          "$JAVA_VENDOR" == "yes" -a \
          "$HAVE_JNI_H" == "yes"; then
    HAVE_JAVASUPPORT="yes"
    AC_SUBST(javadir, '${prefix}/lib')

    # Set the -source flag to the minimum Java version
    AC_SUBST(AM_JAVACFLAGS, "-source $java_source_version")
  else
    AC_MSG_WARN([Java support was enabled, but Java requirements were not met])
  fi
fi

AC_SUBST([HAVE_JAVASUPPORT], $HAVE_JAVASUPPORT)
AM_CONDITIONAL(HAVE_JAVASUPPORT, test $HAVE_JAVASUPPORT = yes)

AM_PATH_PYTHON([2.4])

AC_CHECK_PYMODULE(logging ,[], [AC_MSG_ERROR([the python logging module is required])])
AC_CHECK_PYMODULE(subprocess, [], [AC_MSG_ERROR([the python subprocess module is required])])
AC_CHECK_PYMODULE(omniORB, [], [AC_MSG_ERROR([the python omniORB module is required])])
if test -d /usr/lib/omniidl; then # for debian-based systems
  export PYTHONPATH=${PYTHONPATH}:/usr/lib/omniidl
fi
AC_CHECK_PYMODULE(omniidl, [], [AC_MSG_ERROR([the python omniidl module is required])])

AC_LANG_POP
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS(time.h)
AC_HEADER_DIRENT
AX_CXX_GCC_ABI_DEMANGLE

if test "x$cross_compiling" == "xyes"; then
# Cross our fingers and hope
  ac_cv_func_fork_works="yes"
else
  AC_FUNC_FORK
  if test "$ac_cv_func_fork_works" != yes; then
     AC_MSG_ERROR([working fork test failed. Try running /sbin/ldconfig.])
  fi
fi

# Use libuuid from e2fsprogs to generate UUIDs.
AC_CHECK_HEADER([uuid/uuid.h], [], [AC_MSG_ERROR([uuid/uuid.h is required])])
AC_CHECK_LIB([uuid], [uuid_generate], [], [AC_MSG_ERROR([libuuid is required])])

# Set flags for building against the main C++ library.
AC_SUBST(SCA_CFLAGS, '-I$(top_srcdir)/base/include')
AC_SUBST(SCA_IDLDIR, '$(top_srcdir)/idl')
AC_SUBST(SCAIDL_LIBS, '$(top_builddir)/base/framework/idl/libscaidl.la')

# For test components with a generated Makefile.am, set the expected flags
AC_SUBST(PROJECTDEPS_CFLAGS, '$(SCA_CFLAGS) -I$(top_srcdir)/base/include/sca')
AC_SUBST(PROJECTDEPS_LIBS, '$(top_builddir)/base/framework/libscacf.la $(OSSIEIDL_LIBS)')

# Undefine the PACKAGE_ variables to avoid warnings when omniORB is installed outside of
# /usr.  OSSIE doesn't use these variables anyways...and even if it did
# they would get undefined in any file that included CORBA.h (because ossieconfig.h
# undefines them)
CPPFLAGS="${CPPFLAGS} -UPACKAGE_NAME -UPACKAGE_BUGREPORT -UPACKAGE_TARNAME -UPACKAGE_STRING -UPACKAGE_VERSION"


AC_CONFIG_FILES(Makefile \
                base/Makefile \
                base/bulkio/Makefile \
                base/framework/Makefile \
                base/framework/python/Makefile \
                base/framework/idl/CF/Makefile \
                base/framework/idl/BULKIO/Makefile \
                idl/Makefile )

AM_COND_IF( [BUILD_TESTS], [
AC_CONFIG_FILES( [testing/Makefile \
                testing/sdr/dev/devices/BasicTestDevice_cpp/BasicTestDevice_cpp_impl1/Makefile \
                testing/sdr/dev/devices/cpp_dev/cpp/Makefile \
                testing/sdr/dev/devices/PersonaDevice/cpp/Makefile \
                testing/sdr/dev/devices/ProgrammableDevice/cpp/Makefile ])
])

AC_OUTPUT

