#!/usr/bin/env python
#encoding: utf-8
"""
--------------------------------------------------------------------------------------------------------
The Open Woodwind Project - https://github.com/jeffmhopkins/Open-Woodwind-Project
--------------------------------------------------------------------------------------------------------
This python script runs on my Raspberry Pi headless synth and receives MIDI messages from OWP_Synth 
and converts them to OSC messags for the iPad. This is mainly so that when you load patches the GUI
of the ipad updates.

It has the added benefit of allowing feedback of breath, modulation, expression etc if you want.

It maps CC values to /1/cc{i} float value. (CC 0-127 is mapped from 0.0-1.0)

--------------------------------------------------------------------------------------------------------
Midi to OSC Router
Copyleft Jean-Emmanuel Doucet (http://ammd.net) Modified by Jeff Hopkins
Released under GNU/GPL License v3 (http://www.gnu.org/)
--------------------------------------------------------------------------------------------------------

"""

from mididings import *
from mididings.engine import output_event
from mididings.event import CtrlEvent
import liblo as _liblo

# Config

midiBackend = 'alsa'    # jack or alsa
feedBackMidi = 1        # monitor oscInPort to send Midi CC to the device > feedback midi is sent on channel 1
oscOutPort = "osc.udp://192.168.0.2:3334"       # output port
oscInPort = 3334        # input port (used to control the midi device with osc messages)

# OSC -> MIDI

class osc2midi(object):
    def __init__(self, port=None):
        self.port = port

    def on_start(self):
        if self.port is not None:
            self.server = _liblo.ServerThread(self.port)
            self.server.register_methods(self)
            self.server.start()

    def on_exit(self):
        if self.port is not None:
            self.server.stop()
            del self.server
            
    @_liblo.make_method(None, 'f')
    def sendMidi(self, path, args):
        value = int(max(0,min(1,args[0]))*127)
        #output_event(CtrlEvent('Midi2oscOut',1,self.patch[path[len(oscPrefix):]],value)) 
        
# MIDI -> OSC

def routeOsc(e):
        _liblo.send(oscOutPort, '/1/cc' + str(e.ctrl), e.value / 127.)
        
config(
    backend = midiBackend,
    client_name = 'Midi2osc',
    in_ports=['Midi2oscIn'],
    out_ports=['Midi2oscOut']
)
if feedBackMidi == 1:
    hook(
        osc2midi(port=oscInPort)
    )
run(
    Filter(CTRL) >> Call(routeOsc)
)
