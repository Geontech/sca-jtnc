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

from frontend import tuner_device

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

    def test_frontend(self):
        allocation_id = "TEST"
        sample_rate=1.0e6
        bandwidth=0.5e6
        center_frequency=500.0e6

        fei_dev = sb.launch('BasicFEI')
        fei_alloc = tuner_device.createTunerAllocation(
            allocation_id=allocation_id,
            sample_rate=sample_rate,
            bandwidth=bandwidth,
            center_frequency=center_frequency
        )
        self.assertTrue(fei_dev.allocateCapacity(fei_alloc))

    def test_programmable(self):
        prog_dev = sb.launch('ProgrammableDevice')
        pers_dev_1 = sb.launch('PersonaDevice', host=prog_dev)
        self.assertEquals(prog_dev._get_identifier(),pers_dev_1._get_compositeDevice()._get_identifier())
        self.assertEquals(len(prog_dev.ref._get_devices()), 1)
        pers_dev_2 = sb.launch('PersonaDevice', host=prog_dev)
        self.assertEquals(prog_dev._get_identifier(),pers_dev_2._get_compositeDevice()._get_identifier())
        self.assertEquals(len(prog_dev.ref._get_devices()), 2)
        identifiers = []
        for _comp in prog_dev.ref._get_devices():
            identifiers.append(_comp._get_identifier())
        self.assertNotEqual(identifiers[0], identifiers[1])

    def test_exec_pers(self):
        prog_dev = sb.launch('ProgrammableDevice')
        pers_dev_1 = sb.launch('PersonaExecutableDevice', host=prog_dev)
        self.assertEquals(prog_dev._get_identifier(),pers_dev_1._get_compositeDevice()._get_identifier())
        self.assertEquals(len(prog_dev.ref._get_devices()), 1)
        pers_dev_2 = sb.launch('PersonaExecutableDevice', host=prog_dev)
        self.assertEquals(prog_dev._get_identifier(),pers_dev_2._get_compositeDevice()._get_identifier())
        self.assertEquals(len(prog_dev.ref._get_devices()), 2)
        identifiers = []
        for _comp in prog_dev.ref._get_devices():
            identifiers.append(_comp._get_identifier())
        self.assertNotEqual(identifiers[0], identifiers[1])
        
        self.assertEquals(len(prog_dev.ref.query([])), 4)
        self.assertEquals(len(pers_dev_1.ref.query([])), 3)
        self.assertEquals(len(pers_dev_2.ref.query([])), 3)
        comp_1 = sb.launch('alloc_shm', host=pers_dev_1)
        self.assertEquals(len(comp_1.ref.query([])), 0)

    def test_btd(self):
        comp = sb.launch('BasicTestDevice_cpp')
        props = comp.query([])
        self.assertEquals(len(props), 4)
        prop_1 = None
        prop_2 = None
        prop_3 = None
        prop_4 = None
        for prop in props:
            if prop.id == 'DCE:5bf37e47-afa5-4865-9653-9d427ffa55d2':
                prop_1 = prop #33
            elif prop.id == 'DCE:9607a8db-2ce1-4e71-9dee-9bb18377127c':
                prop_2 = prop
            elif prop.id == 'DCE:7aeaace8-350e-48da-8d77-f97c2e722e06':
                prop_3 = prop
            else:
                prop_4 = prop
        self.assertEquals(prop_1.value._v, 33)
        self.assertEquals(prop_2.value._v, 45654)
        self.assertEquals(prop_3.value._v, 0)
        self.assertEquals(prop_4.value._v, 0)
        self.assertNotEqual(comp._get_identifier(), None)

    def test_runtime(self):
        comp = sb.launch('cpp_dev')
        teststring = CF.DataType(id='teststring', value=_any.to_any('foo'))
        comp.configure([teststring])
        teststring = CF.DataType(id='teststring', value=_any.to_any(None))
        retval = comp.query([teststring])
        self.assertEquals(retval[0].value._v, 'foo')
        comp.teststring = 'hello'
        retval = comp.query([teststring])
        self.assertEquals(retval[0].value._v, 'hello')
        snk=sb.DataSink()
        comp.connect(snk)
        sb.start()
        self.assertTrue(comp._get_started())
        time.sleep(2)
        self.assertTrue(len(snk.getData())>10000)

