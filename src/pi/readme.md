1.	Setup Pi for powering on
    a.	Ensure SD card is fully inserted
    b.	Ensure USB Audio interface (the one that came taped to the case) is plugged in to front of Pi (I usually plug it in the middle bottom USB)
    c.	Plug in the Pocket Synth into the front USB
    d.	Plug in your MIDI controller to the front USB
    e.	Plug in the DC power supply to mains voltage
    f.	Plug in the micro USB into the Pi, it’ll start powering on
2.	Configure iPad
    a.	Power on iPad, ensure you have TouchOSC and VNC installed
    b.	Connect to the ‘OpenSynth’ WiFi network, password is ‘OpenSynth’
        i.	The WiFi network defaults to DHCP, so IP address should automatically be assigned (in the 10.10.10.X range)
        ii.	It might take a minute to actually connect and assign an IP address, so give it some time.
    c.	Launch VNC and connect to ’10.10.10.10’ username ‘pi’ password ‘OpenSynth’
3.	Configure Pi
    a.	The Pi uses Jack to control MIDI patching. Once a Patchbay is saved, it will automagically patch your devices as they are plugged in. The Jack control interface is auto launched at power up. 
    b.	Click on ‘Patch Bay’ in the Jack control interface
    c.	Patch your MIDI controller to match the routing of the ‘Open Woodwind’
    d.	SCREENSHOT GOES HERE
    e.	Save the patch bay and make sure it’s ‘active’
4.	Test setup
    a.	At this point you should be able to play notes and have the MIDI stream into the Pocket Synth, this can be verified with headphones from the OpenSynth headphone output.
5.	Configure TouchOSC
    a.	You must transfer the TouchOSC interface to the iPad. File can be found here: LINKY LINKY
    b.	In TouchOSC configure the interface to connect to send OSC messages to 10.10.10.10:3333 and listen on port 3334
6.	At this point the TouchOSC interface on the iPad should be receiving OSC messages from the Pi. Breath, etc should be visibly changing with your controller values.
7.	Play and have fun controlling the Synth from the TouchOSC interface
8.	Shutdown the Pi
    a.	Log into pi via VNC, hit the main menu button and ‘shutdown’
    b.	If you just unplug the USB power, it will work, but you risk corrupting the SD card (I’ve not had this happen even multiple ‘hard shutdowns’ but I try to not to do it)
