# -*- coding: utf-8 -*-

"""Unittests for Janitoo-Samsung Server.
"""
__license__ = """
    This file is part of Janitoo.

    Janitoo is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Janitoo is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Janitoo. If not, see <http://www.gnu.org/licenses/>.

"""
__author__ = 'Sébastien GALLET aka bibi21000'
__email__ = 'bibi21000@gmail.com'
__copyright__ = "Copyright © 2013-2014-2015 Sébastien GALLET aka bibi21000"

import sys, os
import time, datetime
import unittest
import mock

from janitoo_nosetests.certification import JNTTCertification, JNTTCertificationCommon

from janitoo.utils import json_dumps, json_loads, HADD_SEP, HADD

class TestArduinoRGB(JNTTCertification, JNTTCertificationCommon):
    """Test the arduino rgb
    """

    #~ hadd_network = 1111
    #~ hadd_ctrl = HADD%(hadd_network, 0)
    ip = '192.168.14.69'
    hadds = ['1111/0000']

    def test_101_arduino_rgb_dht1_poll(self):
        self.skipNoPingTest(self.ip)
        for hadd in self.hadds:
            self.assertHeartbeatNode(hadd=hadd)
            #Enable poll and update its delay
            poll = 15
            self.assertUpdateValue(type="config", cmd_class=0x70, uuid='dht_in_enabled', data=True, genre=0x03, is_writeonly=True, node_hadd=hadd, client_hadd=self.client_hadd)
            self.assertUpdateValue(type="config", cmd_class=0x70, uuid='dht_in_poll', data=poll, genre=0x03, is_writeonly=True, node_hadd=hadd, client_hadd=self.client_hadd)
            self.assertWaitValue(type="user", cmd_class=0x32, uuid='dht_in_temp', genre=0x02, is_writeonly=True, node_hadd=hadd, client_hadd=self.client_hadd, timeout=poll+2)
            #Disable poll
            self.assertUpdateValue(type="config", cmd_class=0x70, uuid='dht_in_poll', data=0, genre=0x03, is_writeonly=True, node_hadd=hadd, client_hadd=self.client_hadd)
            self.assertNotWaitValue(type="user", cmd_class=0x32, uuid='dht_in_temp', genre=0x02, is_writeonly=True, node_hadd=hadd, client_hadd=self.client_hadd, timeout=2*poll)
            #Enable poll and disable sensor
            self.assertUpdateValue(type="config", cmd_class=0x70, uuid='dht_in_enabled', data=False, genre=0x03, is_writeonly=True, node_hadd=hadd, client_hadd=self.client_hadd)
            self.assertUpdateValue(type="config", cmd_class=0x70, uuid='dht_in_poll', data=15, genre=0x03, is_writeonly=True, node_hadd=hadd, client_hadd=self.client_hadd)
            self.assertNotWaitValue(type="user", cmd_class=0x32, uuid='dht_in_temp', genre=0x02, is_writeonly=True, node_hadd=hadd, client_hadd=self.client_hadd, timeout=2*poll)
            #Enable poll and update its delay
            poll = 60
            self.assertUpdateValue(type="config", cmd_class=0x70, uuid='dht_in_enabled', data=True, genre=0x03, is_writeonly=True, node_hadd=hadd, client_hadd=self.client_hadd)
            self.assertUpdateValue(type="config", cmd_class=0x70, uuid='dht_in_poll', data=poll, genre=0x03, is_writeonly=True, node_hadd=hadd, client_hadd=self.client_hadd)
            self.assertWaitValue(type="user", cmd_class=0x32, uuid='dht_in_temp', genre=0x02, is_writeonly=True, node_hadd=hadd, client_hadd=self.client_hadd, timeout=poll+2)

    def test_101_arduino_rgb_dht1_request(self):
        self.skipNoPingTest(self.ip)
        for hadd in self.hadds:
            self.assertHeartbeatNode(hadd=hadd)
            #Enable sensor
            self.assertUpdateValue(type="config", cmd_class=0x70, uuid='dht_in_enabled', data=True, genre=0x03, is_writeonly=True, node_hadd=hadd, client_hadd=self.client_hadd)
            self.assertUpdateValue(type="user", cmd_class=0x32, uuid='dht_in_temp', genre=0x02, is_readonly=True, node_hadd=hadd, client_hadd=self.client_hadd)
            #Disable sensor
            self.assertUpdateValue(type="config", cmd_class=0x70, uuid='dht_in_enabled', data=False, genre=0x03, is_writeonly=True, node_hadd=hadd, client_hadd=self.client_hadd)
            self.assertNotUpdateValue(type="user", cmd_class=0x32, uuid='dht_in_temp', genre=0x02, is_readonly=True, node_hadd=hadd, client_hadd=self.client_hadd)
            #Re-Enable sensor
            self.assertUpdateValue(type="config", cmd_class=0x70, uuid='dht_in_enabled', data=True, genre=0x03, is_writeonly=True, node_hadd=hadd, client_hadd=self.client_hadd)

