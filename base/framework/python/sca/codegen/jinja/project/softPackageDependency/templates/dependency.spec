
#$ set name = component.name
#$ set basename = component.basename
#$ set dirname = component.name.replace('.','/')
# By default, the RPM will install to the standard SCA SDR root location (/var/sca/sdr)
%{!?_scaroot: %global _scaroot /var/sca/sdr}
#{$ if component.implementations[0].id == 'octave' $}
%define _prefix %{_scaroot}
#{$ else $}
%define _prefix %{_scaroot}/{{component.sdrpath}}/{{dirname}}
#{$ endif $}

# Point install paths to locations within our target SDR root
#{$ if component.implementations[0].id != 'octave' $}
%define _libdir        %{_prefix}/{{component.implementations[0].outputdir}}/lib
#{$ endif $}
%define _sysconfdir    %{_prefix}/etc
%define _localstatedir %{_prefix}/var
%define _mandir        %{_prefix}/man
%define _infodir       %{_prefix}/info

#{$ block variableExtensions $}
#{$ endblock $}
Name:           {{name}}{{generator.variant}}
Version:        {{component.version}}
Release:        1%{?dist}
Summary:        Shared package %{name}{{' '+component.title if component.title}}

Group:          SCA/Shared Packages
License:        None
Source0:        %{name}-%{version}.tar.gz
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

BuildRequires:  sca-devel >= 2.0
BuildRequires:  autoconf automake libtool

#{$ block requireExtensions $}
#{$ endblock $}

#{$ for impl in component.implementations $}
#{$ for softpkgdep in impl.softpkgdeps $}
BuildRequires:  {{softpkgdep.name}}-devel
Requires:       {{softpkgdep.name}}
#{$ endfor $}
#{$ endfor $}

#{$ if component.interfaces $}
# Interface requirements
BuildRequires:  {{component.interfaces|join(' ')}}
Requires:       {{component.interfaces|join(' ')}}

#{$ endif $}
#{$ if 'C++' not in component.languages and component.languages $}
BuildArch: noarch

#{$ endif $}
%description
#{$ if component.description $}
{{component.description}}
#{$ else $}
Shared package %{name}
#{$ endif $}

%package devel
Summary:        Shared package %{name}
Group:          SCA/Shared Packages
Requires:       %{name} = %{version}-%{release}

%description devel
Libraries and header files for shared package %{name}

%prep
%setup -q


%build
#{$ block build $}
#{$ for impl in component.implementations $}
# Implementation {{impl.id}}
pushd {{impl.outputdir}}
./reconf
%configure --with-sdr=%{_scaroot}
make %{?_smp_mflags}
popd
#{$ endfor $}
#{$ endblock  $}


%install
#{$ block install $}
rm -rf $RPM_BUILD_ROOT
#{$ for impl in component.implementations $}
# Implementation {{impl.id}}
pushd {{impl.outputdir}}
make install DESTDIR=$RPM_BUILD_ROOT
popd
#{$ endfor $}
#{$ endblock $}


%clean
rm -rf $RPM_BUILD_ROOT

%files
#{$ block files $}
%defattr(-,sca,sca,-)
#{$ set subdirs = component.sdrpath $}
#{$ for subdir in component.name.split('.') $}
#{$ set subdirs = subdirs+'/'+subdir $}
%dir %{_scaroot}/{{subdirs}}
#{$ endfor $}
#{$ for xmlfile in component.profile.values() $}
#{$ if component.implementations[0].id == 'octave' $}
%{_prefix}/{{component.sdrpath}}/{{dirname}}/{{xmlfile}}
#{$ else $}
%{_prefix}/{{xmlfile}}
#{$ endif $}
#{$ endfor $}
#{$ for impl in component.implementations $}
#{$ if component.implementations[0].id == 'octave' $}
%{_prefix}/{{component.sdrpath}}/{{dirname}}/{{impl.outputdir}}
#{$ else $}
%{_prefix}/{{impl.outputdir}}
#{$ endif $}
#{$ endfor $}
#{$ if component.implementations[0].id != 'octave' $}
%exclude %{_libdir}/lib{{basename}}.la
%exclude %{_libdir}/lib{{basename}}.so
%exclude %{_libdir}/pkgconfig
#{$ endif $}
#{$ endblock $}

%files devel
#{$ block filesdevel $}
%defattr(-,sca,sca,-)
#{$ if component.implementations[0].id != 'octave' $}
%{_libdir}/lib{{basename}}.la
%{_libdir}/lib{{basename}}.so
%{_libdir}/pkgconfig
%{_prefix}/include
#{$ endif $}
#{$ endblock $}
