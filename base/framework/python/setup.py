#! /usr/bin/env python
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

from setuptools import setup
import sys

try:
    import tabnanny
except ImportError:
    pass
else:
    import StringIO
    stdout, stderr = sys.stdout, sys.stderr
    sys.stdout = co = StringIO.StringIO()
    sys.stderr = ce = StringIO.StringIO()
    # Tabnanny doesn't provide any mechanism other than print outs so we have
    # to capture the output
    tabnanny.check("sca")
    sys.stdout = stdout
    sys.stderr = stderr
    if len(co.getvalue().strip()) != 0:
        print "Incosistent tab usage:"
        print co.getvalue()
        sys.exit(-1)

import sca.version

setup(name='scapy',
      version=sca.version.__version__,
      description='OSSIE Python',
      packages=['sca',
                'sca/apps',
                'sca/apps/qtbrowse',
                'sca/apps/rhlauncher',
                'sca/apps/rhlauncher/ui',
                'sca/bulkio',
                'sca/bulkio/BULKIO',
                'sca/bulkio/BULKIO__POA',
                'sca/cf',
                'sca/cf/CF',
                'sca/cf/CF__POA',
                'sca/cf/Extended_CF',
                'sca/cf/Extended_CF__POA',
                'sca/cf/ExtendedCF',
                'sca/cf/ExtendedCF__POA',
                'sca/cf/PortTypes',
                'sca/cf/PortTypes__POA',
                'sca/cf/StandardEvent',
                'sca/cf/StandardEvent__POA',
                'sca/events',
                'sca/logger',
                'sca/parsers',
                'sca/utils',
                'sca/utils/bluefile',
                'sca/utils/bulkio',
                'sca/utils/log4py',
                'sca/utils/model',
                'sca/utils/redhawk',
                'sca/utils/sandbox',
                'sca/utils/sb',
                'sca/utils/verifyspec',
                'sca/utils/testing',
                'sca/utils/tools',
                'sca/utils/sdds',
                'sca/utils/rhtime',
                'sca/utils/rhconnection',
                'sca/utils/allocations'],
      package_data={'sca/apps/domlauncher':['ui/*.ui',
                                             'ui/icons/*']},
      scripts=['sca/utils/tools/prf2py.py',
               'sca/apps/qtbrowse/qtbrowse',
               'sca/apps/rhlauncher/rhlauncher',
               'sca/apps/scaclt',
               'sca/apps/py2prf',
               'sca/apps/eventviewer',
               'sca/apps/rh_net_diag',
               'sca/apps/cleanns',
               'sca/apps/cleanes',
               'sca/apps/cleanomni',
               'sca/apps/sdrlint'],
      entry_points={'redhawk.sandbox.helpers':['SoundSink=sca.utils.sb.audio:SoundSink',
                                               'LinePlot=sca.utils.sb.plots:LinePlot',
                                               'LinePSD=sca.utils.sb.plots:LinePSD',
                                               'RasterPlot=sca.utils.sb.plots:RasterPlot',
                                               'RasterPSD=sca.utils.sb.plots:RasterPSD',
                                               'XYPlot=sca.utils.sb.plots:XYPlot']}
      )
