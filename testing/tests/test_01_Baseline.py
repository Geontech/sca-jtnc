#
# This file is protected by Copyright. Please refer to the COPYRIGHT file
# distributed with this source distribution.
#
# This file is part of REDHAWK core.
#
# REDHAWK core is free software: you can redistribute it and/or modify it under
# the terms of the GNU Lesser General Public License as published by the Free
# Software Foundation, either version 3 of the License, or (at your option) any
# later version.
#
# REDHAWK core is distributed in the hope that it will be useful, but WITHOUT
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

from sca.bulkio import BULKIO

class SBTestTest(scatest.CorbaTestCase):
    def setUp(self):
        if sb.domainless._sandbox:
            sb.domainless._sandbox.shutdown()
            sb.domainless._sandbox = None

    def tearDown(self):
        sb.release()

    def test_btd(self):
        comp = sb.launch('BasicTestDevice_cpp')
        print 'BasicTestDevice_cpp', comp.query([])
        print 'BasicTestDevice_cpp', comp._get_identifier()

    def test_runtime(self):
        comp = sb.launch('cpp_dev')
        print 'cpp_dev', comp.query([])
        print 'cpp_dev', comp._get_identifier()

