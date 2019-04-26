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
import logging
import re

logging.basicConfig(level=logging.INFO)
log = logging.getLogger(__name__)

def convert(wavedev_path):
    '''
    "Converts" a .wavedev file to SCA codegen compliance
    '''
    content = None
    with open(wavedev_path, 'r') as f:
        content = f.read()
    
    FINDREPLACE_LIST = [
        ( re.compile(r'redhawk\.codegen\.jinja', re.M), r'sca.codegen.jinja' ),
        ( re.compile(r'gov\.redhawk\.ide\.codegen', re.M), r'gov.sca.ide.codegen' )
    ]
    for fr in FINDREPLACE_LIST:
        tem = re.subn(fr[0], fr[1], content)
        content = tem[0]
    
    with open(wavedev_path, 'w') as f:
        f.write(content)
