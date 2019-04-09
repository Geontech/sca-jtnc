
#$ set name = component.name
#$ set dirname = component.name.replace('.','/')
# By default, the RPM will install to the standard SCA SDR root location (/var/sca/sdr)
# You can override this at install time using --prefix /new/sdr/root when invoking rpm (preferred method, if you must)
%{!?_scaroot: %global _scaroot /var/sca/sdr}
%define _prefix %{_scaroot}
Prefix:         %{_prefix}

# Point install paths to locations within our target SDR root
%define _sysconfdir    %{_prefix}/etc
%define _localstatedir %{_prefix}/var
%define _mandir        %{_prefix}/man
%define _infodir       %{_prefix}/info

#{$ block variableExtensions $}
#{$ endblock $}
Name:           {{name}}
Version:        {{component.version}}
Release:        1%{?dist}
Summary:        {{component.type}} %{name}{{' '+component.title if component.title}}

Group:          SCA/{{component.type}}s
License:        None
Source0:        %{name}-%{version}.tar.gz
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

BuildRequires:  sca-devel >= {{versions.sca}}
Requires:       sca >= {{versions.sca}}
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
#{$ for impl in component.implementations if impl.requires or impl.buildrequires $}
# Implementation {{impl.id}}
#{$   if impl.requires $}
Requires: {{impl.requires|join(' ')}}
#{$   endif $}
#{$   if impl.buildrequires $}
BuildRequires: {{impl.buildrequires|join(' ')}}
#{$   endif $}
#{$ endfor $}

%description
#{$ if component.description $}
{{component.description}}
#{$ else $}
{{component.type}} %{name}
 * Commit: __REVISION__
 * Source Date/Time: __DATETIME__
#{$ endif $}


%prep
%setup -q


%build
#{$ block build $}
#{$ for impl in component.implementations $}
# Implementation {{impl.id}}
pushd {{impl.outputdir}}
./reconf
%define _bindir %{_prefix}/{{component.sdrpath}}/{{dirname}}/{{impl.outputdir}}
%configure
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
%define _bindir %{_prefix}/{{component.sdrpath}}/{{dirname}}/{{impl.outputdir}}
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
%{_prefix}/{{component.sdrpath}}/{{dirname}}/{{xmlfile}}
#{$ endfor $}
#{$ for impl in component.implementations $}
%{_prefix}/{{component.sdrpath}}/{{dirname}}/{{impl.outputdir}}
#{$ endfor $}
#{$ endblock $}
