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

import os
from setuptools import setup
from distutils.command.install_lib import install_lib

from sca.codegen import versions

class filtered_install_lib(install_lib):
    def byte_compile(self, files):
        # The default 'install_lib' implementation will attempt to compile all
        # '.py' files in the build tree, including any template files that
        # happen to end in '.py'; filter out everything from a 'templates'
        # directory to prevent this unwanted behavior.
        files = [f for f in files if not os.path.dirname(f).endswith('templates')]
        return install_lib.byte_compile(self,files)

import os
scahome = os.getenv('SCAHOME')
import sys
homeSys = False
buildArg = False
if 'build' in sys.argv:
    buildArg = True
for arg in sys.argv:
    if '--home' in arg:
        homeSys = True
        
if not homeSys and scahome != None and not buildArg:
    sys.argv.append('--home='+scahome)
if not ('--old-and-unmanageable' in sys.argv) and not buildArg:
    sys.argv.append('--old-and-unmanageable')

setup(name='sca-codegen',
      version=versions.codegen,
      install_requires = ['jinja2'],
      scripts=['sca-codegen','codegen_version','update_project','createBinaryComponent','moveComponentNamespace'],
      cmdclass={'install_lib':filtered_install_lib},
      packages=['sca',
                'sca.codegen',
                'sca.codegen.model',
                'sca.codegen.lang',
                'sca.codegen.jinja',
                'sca.codegen.jinja.common',
                'sca.codegen.jinja.project',
                'sca.codegen.jinja.project.component',
                'sca.codegen.jinja.project.softPackageDependency',
                'sca.codegen.jinja.project.softPackageDependency.directory',
                'sca.codegen.jinja.unitTests',
                'sca.codegen.jinja.unitTests.resource',
                'sca.codegen.jinja.unitTests.resource.sca',
                'sca.codegen.jinja.python',
                'sca.codegen.jinja.python.component',
                'sca.codegen.jinja.python.component.base',
                'sca.codegen.jinja.python.component.pull',
                'sca.codegen.jinja.python.component.frontend',
                'sca.codegen.jinja.python.component.binary',
                'sca.codegen.jinja.python.ports',
                'sca.codegen.jinja.python.service',
                'sca.codegen.jinja.cpp',
                'sca.codegen.jinja.cpp.component',
                'sca.codegen.jinja.cpp.component.base',
                'sca.codegen.jinja.cpp.component.pull',
                'sca.codegen.jinja.cpp.component.frontend',
                'sca.codegen.jinja.cpp.library',
                'sca.codegen.jinja.cpp.ports',
                'sca.codegen.jinja.cpp.service',
                'sca.codegen.jinja.cpp.properties',
                'sca.codegen.jinja.cpp.component.persona',
                'sca.codegen.jinja.cpp.component.programmable',
                'sca.packagegen',
                'sca.packagegen.templates'],
      package_data={'sca.codegen.jinja.common':['templates/*'],
                    'sca.codegen.jinja.project.component':['templates/*'],
                    'sca.codegen.jinja.project.softPackageDependency':['templates/*'],
                    'sca.codegen.jinja.project.softPackageDependency.directory':['templates/*'],
                    'sca.codegen.jinja.unitTests.resource.sca':['templates/*'],
                    'sca.codegen.jinja.python.component.base':['templates/*'],
                    'sca.codegen.jinja.python.component.pull':['templates/*'],
                    'sca.codegen.jinja.python.component.frontend':['templates/*'],
                    'sca.codegen.jinja.python.component.binary':['templates/*'],
                    'sca.codegen.jinja.python.ports':['templates/*.py'],
                    'sca.codegen.jinja.python.service':['templates/*'],
                    'sca.codegen.jinja.cpp.component.base':['templates/*'],
                    'sca.codegen.jinja.cpp.component.pull':['templates/*'],
                    'sca.codegen.jinja.cpp.component.frontend':['templates/*'],
                    'sca.codegen.jinja.cpp.library':['templates/*'],
                    'sca.codegen.jinja.cpp.ports':['templates/*.cpp', 'templates/*.h'],
                    'sca.codegen.jinja.cpp.service':['templates/*'],
                    'sca.codegen.jinja.cpp.component.persona':['templates/*'],
                    'sca.codegen.jinja.cpp.component.programmable':['templates/*'],
                    'sca.codegen.jinja.cpp.properties':['templates/*.cpp'],
                    'sca.packagegen':['templates/*xml']}
      )
