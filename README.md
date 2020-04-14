# Open-Woodwind-Project

The Open Woodwind Project is aimed at making an open source MIDI Woodwind Controller with onboard synthesizer.

It utilizes a Teensy microcontroller with Audio Breakout, two MPR121s,BNO055 IMU, and MPXV4006GP pressure Transducer. 

OWP_Synth is a sub project utilizing a Teensy Audio Libray based multi oscillator with LFOs, waveshaping, effects, and a complex modulation scheme, controlled over an OSC iPad interface. It will eventually be fully integrated into the onboard synth for the controller.  

The OWP_Synth relies heavily on a TouchOSC interface to control it. This requires an OSC to MIDI bridge. On Windows you can use TouchOSC MIDI bridge, but for linux there's no offering from the TouchOSC developers, so it's a bit more complicated to setup, but all the config files and packages are called out for, and you should be able to get it setup if you want. See https://github.com/jeffmhopkins/Open-Woodwind-Project/tree/master/src/osc_configuration_for_linux_touchosc readme for how to do this.

See https://hackaday.io/project/2992-the-open-woodwind-project for porject log information.

I'll be including source code, and the 3D printing files necessary to reproduce this project in full here.

Jeff

