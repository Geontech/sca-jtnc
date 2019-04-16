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

from sca.codegen.lang import cpp
from sca.codegen.jinja.mapping import PortMapper

class CppPortMapper(PortMapper):
    def _mapPort(self, port, generator):
        cppport = {}
        cppport['cppname'] = cpp.identifier(port.name())
        cppport['cpptype'] = generator.className()
        cppport['constructor'] = generator.constructor(port.name())
        cppport['multiout'] = generator.supportsMultiOut()
        return cppport
