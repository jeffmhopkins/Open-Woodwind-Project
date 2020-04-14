# OSC Configuration

There are a couple things needed to control the OWP_Synth with the iPad OSC interface.

1. TouchOSC on an iPad (loaded with the owp_synth.touchosc file)
2. Linux install (I'm using a Raspberry Pi) running the midi2osc and osc2midi bridges and patching the controller to these bridges
3. Configuration files for the bridges
4. Autostart the services at boot

# Install Services

1. midi2osc bridge is a Python script and located here: https://github.com/jeffmhopkins/Open-Woodwind-Project/blob/master/src/osc_configuration_for_linux_touchosc/midi2osc.py This needs to be modified to point at the ip/port of your iPad

2. osc2midi bridge is a separate github project, located at https://github.com/ssj71/OSC2MIDI it is configured with https://github.com/jeffmhopkins/Open-Woodwind-Project/blob/master/src/osc_configuration_for_linux_touchosc/osc2midi.omm

3. You then probably need an ALSA MIDI bridge, aj2midid (**sudo apt-get install aj2midid**)

# Configure services to Autostart

All these services need started at boot (as well as qjackctl for auto MIDI patching)

1. Modify the **~/.config/autostart/.desktop** to run the **startup.sh** script (https://github.com/jeffmhopkins/Open-Woodwind-Project/blob/master/src/osc_configuration_for_linux_touchosc/startup.sh) 

This can be done by adding:

>[Desktop Entry]  
>Type=application  
>Exec=/home/pi/Desktop/startup.sh  

to **~/.config/autostart/.desktop** (this is the autostart script for the Raspbian window manager)

# Configure Patchbay for auto MIDI Routing

Jack then needs a patchbay setup where it auto patches the MIDI as follows:
1. Controller (ALSA) to Synth (ALSA) (this allows your controller to send MIDI to the synth)
2. osc2midi (MIDI) to aj2midi (MIDI), aj2midi (ALSA) to Synth (ALSA) (this is required because you can't patch MIDI to ALSA, and allows the iPad to control the synth via CC messages)
3. Synth (ALSA) to midi2osc (ALSA) (this allows the synth to send updates to the iPad to update sliders on patch load)

Once the patchbay is setup, jack should auto patch everything as it starts.
