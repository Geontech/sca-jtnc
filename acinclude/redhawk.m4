dnl
dnl This file is protected by Copyright. Please refer to the COPYRIGHT file
dnl distributed with this source distribution.
dnl
dnl This file is part of SCA-JTNC core.
dnl
dnl SCA-JTNC core is free software: you can redistribute it and/or modify it under
dnl the terms of the GNU Lesser General Public License as published by the Free
dnl Software Foundation, either version 3 of the License, or (at your option) any
dnl later version.
dnl
dnl SCA-JTNC core is distributed in the hope that it will be useful, but WITHOUT
dnl ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
dnl FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
dnl details.
dnl
dnl You should have received a copy of the GNU Lesser General Public License
dnl along with this program.  If not, see http://www.gnu.org/licenses/.
dnl

# RH_REDHAWK([MIN-VERSION],[MAX-VERSION])
#
# Checks for a REDHAWK installation, with optional version constraint
# [MIN-VERSION,MAX-VERSION)
# -----------------------------------------------------------------------------
AC_DEFUN([RH_REDHAWK],
[
  AC_REQUIRE([OSSIE_CHECK_SCA])
  AC_REQUIRE([PKG_CHECK_EXISTS])
  rh_redhawk_version_check=""
  AS_IF([test "x$1" != "x"], [
    rh_redhawk_version_check=" >= $1"
  ])
  AS_IF([test "x$2" != "x"], [
    rh_redhawk_version_check=" < $2"
  ])
  AC_MSG_CHECKING([for REDHAWK$rh_redhawk_version_check])
  PKG_CHECK_EXISTS([ossie $rh_redhawk_version_check],[
    AC_MSG_RESULT([yes])
  ],[
    AC_MSG_RESULT([no])
    AC_MSG_ERROR([REDHAWK$rh_redhawk_version_check not found])
  ])
])

# RH_SOFTPKG_PREFIX(NAME, [IMPLEMENTATION])
#
# Sets prefix for a shared library soft package
# -----------------------------------------------------------------------------
AC_DEFUN([RH_SOFTPKG_PREFIX],
[
  AC_REQUIRE([OSSIE_SCAROOT])
  AS_IF([test "x${ossie_cv_sca_home}" = "xNONE"], [
    AC_MSG_ERROR([SCAROOT is not set; this is not expected])
   ])
  AC_MSG_CHECKING([for softpkg prefix])
  rh_softpkg_path=`echo $1 | tr "." "/"`
  prefix="${ossie_cv_sdr_root}/dom/deps/${rh_softpkg_path}"
  # Overrule "lib64" suffix
  AS_IF([test "x${gr_libdir_suffix}" = "x64"], [
    libdir=`echo ${libdir} | sed 's/64$//'`
   ])
  AC_MSG_RESULT([${prefix}])
  exec_prefix="\${prefix}/$2"
])

dnl Internal function to update C++ flags using the current list of soft
dnl packages
AC_DEFUN([_RH_SOFTPKG_FLAGS],
[
  rh_pkg_config_path_saved="$PKG_CONFIG_PATH"
  PKG_CONFIG_PATH="$rh_softpkg_pkg_config_path:$PKG_CONFIG_PATH"
  SOFTPKG_CFLAGS=`$PKG_CONFIG --cflags "$rh_softpkg_list"`
  SOFTPKG_LIBS=`$PKG_CONFIG --libs "$rh_softpkg_list"`
  PKG_CONFIG_PATH="$rh_pkg_config_path_saved"

  AC_SUBST([SOFTPKG_CFLAGS])
  AC_SUBST([SOFTPKG_LIBS])
])

# RH_SOFTPKG_CXX(SPDFILE, [IMPLEMENTATION],[MIN-VERSION],[MAX-VERSION])
#
# Check that a C++ soft package is installed, and add its build flags to the
# current set
# -----------------------------------------------------------------------------
AC_DEFUN([RH_SOFTPKG_CXX],
[
  export_sdrroot=false
  AS_IF([test "x${ossie_cv_sdr_root}" = "x"], [
    export_sdrroot=true
  ])
  AC_REQUIRE([OSSIE_SCAROOT_IGNORE_PREFIX])
  AS_IF([test "${export_sdrroot} != false"], [
    export SCAROOT=${ossie_cv_sdr_root}
  ])

  # Test for the existence of the SPD first
  rh_softpkg_spd="${ossie_cv_sdr_root}/dom$1"
  AS_IF([test ! -r $rh_softpkg_spd], [
    AS_IF([test -f $rh_softpkg_spd], [
      _rh_softpkg_error="Permission denied"
    ], [
      _rh_softpkg_error="File not found"
    ])
    AC_MSG_ERROR([Failed to open required soft package library $1: ${_rh_softpkg_error}])
  ])

  rh_softpkg_name=`redhawk-softpkg --name $rh_softpkg_spd`
  rh_softpkg_version_check=""
  AS_IF([test "x$3" != "x"], [
    rh_softpkg_version_check=" >= $3"
  ])
  AS_IF([test "x$4" != "x"], [
    rh_softpkg_version_check=" < $4"
  ])
  
  AS_IF([test "x$2" != "x"], [
    rh_softpkg_spd="$rh_softpkg_spd:$2"
    AC_MSG_CHECKING([for C++ soft package library $rh_softpkg_name$rh_softpkg_version_check ($2)])
  ], [
    AC_MSG_CHECKING([for C++ soft package library $rh_softpkg_name$rh_softpkg_version_check])
  ])

  # Verify the existence of all dependencies
  _rh_softpkg_check_error=`redhawk-softpkg --check $rh_softpkg_spd 2>&1`
  AS_IF([test $? -ne 0], [
    AC_MSG_ERROR([$_rh_softpkg_check_error])
  ])
  
  # Save the prior pkg-config path
  rh_pkg_config_path_saved="$PKG_CONFIG_PATH"
  rh_softpkg_dir=`redhawk-softpkg --pkgconfigpath $rh_softpkg_spd`
  PKG_CONFIG_PATH="$rh_softpkg_dir:$rh_softpkg_pkg_config_path:$PKG_CONFIG_PATH"

  PKG_CHECK_EXISTS([$rh_softpkg_name $rh_softpkg_version_check],[
    AC_MSG_RESULT([yes])
  ],[
    _rh_pkg_check_error=`$PKG_CONFIG --exists --errors-to-stdout --print-errors "$rh_softpkg_name$rh_softpkg_version_check"`
    AC_MSG_ERROR([$_rh_pkg_check_error])
  ])

  # Restore the pkg-config path
  PKG_CONFIG_PATH="$rh_pkg_config_path_saved"

  rh_softpkg_pkg_config_path="$rh_softpkg_dir:$rh_softpkg_pkg_config_path"
  rh_softpkg_list="$rh_softpkg_name $rh_softpkg_list"

  # Update SOFTPKG_CFLAGS and SOFTPKG_LIBS
  _RH_SOFTPKG_FLAGS
])

# RH_SOFTPKG_JAVA(SPDFILE, [IMPLEMENTATION])
#
# Check that a Java soft package is installed, and add it to SOFTPKG_CLASSPATH
# -----------------------------------------------------------------------------
AC_DEFUN([RH_SOFTPKG_JAVA],
[
  export_sdrroot=false
  AS_IF([test "x${ossie_cv_sdr_root}" = "x"], [
    export_sdrroot=true
  ])
  AC_REQUIRE([OSSIE_SCAROOT_IGNORE_PREFIX])
  AS_IF([test "${export_sdrroot} != false"], [
    export SCAROOT=${ossie_cv_sdr_root}
  ])
  rh_softpkg_spd="$1"
  rh_softpkg_name=`redhawk-softpkg --name $rh_softpkg_spd`
  AS_IF([test "x$2" != "x"], [
    rh_softpkg_spd="$rh_softpkg_spd:$2"
    AC_MSG_CHECKING([for Java soft package library $1 ($2)])
  ], [
    AC_MSG_CHECKING([for Java soft package library $1])
  ])

  AS_IF([redhawk-softpkg --exists $rh_softpkg_spd],[
    AC_MSG_RESULT([yes])
    rh_softpkg_java_classpath=`redhawk-softpkg --classpath $rh_softpkg_spd`
    SOFTPKG_CLASSPATH=`echo "$rh_softpkg_java_classpath:$SOFTPKG_CLASSPATH" | sed 's/::*/:/g'`
  ],[
    AC_MSG_ERROR([$rh_softpkg_name not found])
  ])

  AC_SUBST([SOFTPKG_CLASSPATH])
])
