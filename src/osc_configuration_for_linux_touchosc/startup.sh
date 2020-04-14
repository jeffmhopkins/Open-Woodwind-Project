#!/bin/bash

qjackctl -s & 
sleep 15 && osc2midi -p 3333 -m /usr/local/share/osc2midi/osc2midi.omm &
sleep 30 && a2jmidid &
sleep 45 && python ~/Desktop/midi2osc.py & 
