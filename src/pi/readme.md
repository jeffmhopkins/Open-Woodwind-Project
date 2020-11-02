# Setup Pi for powering on
* Ensure SD card is fully inserted
* Ensure USB Audio interface (the one that came taped to the case) is plugged in to front of Pi (I usually plug it in the middle bottom USB)
* Plug in the Pocket Synth into the front USB
* Plug in your MIDI controller to the front USB
* Plug in the DC power supply to mains voltage
* Plug in the micro USB into the Pi, it’ll start powering on
# Configure iPad
* Power on iPad, ensure you have TouchOSC and VNC installed
* Connect to the ‘OpenSynth’ WiFi network, password is ‘OpenSynth’
** The WiFi network defaults to DHCP, so IP address should automatically be assigned (in the 10.10.10.X range)
** It might take a minute to actually connect and assign an IP address, so give it some time.
* Launch VNC and connect to ’10.10.10.10’ username ‘pi’ password ‘OpenSynth’
# Configure Pi
* The Pi uses Jack to control MIDI patching. Once a Patchbay is saved, it will automagically patch your devices as they are plugged in. The Jack control interface is auto launched at power up. 
* Click on ‘Patch Bay’ in the Jack control interface
* Patch your MIDI controller to match the routing of the ‘Open Woodwind’
* SCREENSHOT GOES HERE
* Save the patch bay and make sure it’s ‘active’
# Test setup
* At this point you should be able to play notes and have the MIDI stream into the Pocket Synth, this can be verified with headphones from the OpenSynth headphone output.
# Configure TouchOSC
* You must transfer the TouchOSC interface to the iPad. File can be found here: LINKY LINKY
* In TouchOSC configure the interface to connect to send OSC messages to 10.10.10.10:3333 and listen on port 3334
# At this point the TouchOSC interface on the iPad should be receiving OSC messages from the Pi. Breath, etc should be visibly changing with your controller values.
* Play and have fun controlling the Synth from the TouchOSC interface
# Shutdown the Pi
* Log into pi via VNC, hit the main menu button and ‘shutdown’
* If you just unplug the USB power, it will work, but you risk corrupting the SD card (I’ve not had this happen even multiple ‘hard shutdowns’ but I try to not to do it)
