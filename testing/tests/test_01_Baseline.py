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
import Queue
import unittest
import sys
import commands
import cStringIO
import time
import copy
import threading
import warnings
import subprocess
import commands
import struct
import tempfile

from omniORB import CORBA, any, tcInternal

from sca import properties
from sca.cf import CF, StandardEvent
from sca.utils import sb, type_helpers
from sca.utils.bulkio import bulkio_helpers
from sca.events import ChannelManager, Subscriber, Publisher
from sca.utils.bulkio import bulkio_data_helpers

from _unitTestHelpers import scatest, runtestHelpers
import traceback

import time

from sca.bulkio import BULKIO
from sca.cf import CF
from omniORB import any as _any

class SBTestTest(scatest.CorbaTestCase):
    def setUp(self):
        if sb.domainless._sandbox:
            sb.domainless._sandbox.shutdown()
            sb.domainless._sandbox = None

    def tearDown(self):
        sb.release()

    def test_programmable(self):
        comp = sb.launch('ProgrammableDevice')
        print dir(comp)
        print comp.__class__
        print '======================='
        a = CF.ExecutableInterface.ExecutionID_Type(1,2,'hello',[])
        print CF.ExecutableInterface.ExecutionID_Type
        print a
        print dir(a)
        print '======================='
        comp_2 = sb.launch('PersonaDevice', host=comp)
        raw_input('press any key')
        #print dir(comp)
        print comp._get_compositeDevice()
        print comp_2._get_compositeDevice()
        raw_input('press any key')

    def test_btd(self):
        comp = sb.launch('BasicTestDevice_cpp')
        print 'BasicTestDevice_cpp', comp.query([])
        print 'BasicTestDevice_cpp', comp._get_identifier()

    def test_runtime(self):
        #print dir(sb)
        comp = sb.launch('cpp_dev')
        #print 'cpp_dev', comp.query([])
        teststring = CF.DataType(id='teststring', value=_any.to_any('foo'))
        comp.configure([teststring])
        teststring = CF.DataType(id='teststring', value=_any.to_any(None))
        #print 'cpp_dev', comp.query([])
        retval = comp.query([teststring])
        self.assertEquals(retval[0].value._v, 'foo')
        comp.teststring = 'hello'
        retval = comp.query([teststring])
        self.assertEquals(retval[0].value._v, 'hello')
        #snk=sb.DataSink()
        snk=sb.DataSink()
        comp.connect(snk)
        sb.start()
        time.sleep(2)
        print len(snk.getData())
        #print 'cpp_dev', comp._get_identifier()

