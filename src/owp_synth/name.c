/*
 * The Open Woodwind Project - OWP_Synth for Woodwind Controllers by Jeff Hopkins
 * 
 * =============================================================================================================================================
 * 
 * Just naming the USB iteration.
 * 
 */

#include "usb_names.h"

#define MIDI_NAME   {'O', 'W', 'P',' ','S','y','n','t','h'}
#define MIDI_NAME_LEN  9

struct usb_string_descriptor_struct usb_string_product_name = {
        2 + MIDI_NAME_LEN * 2,
        3,
        MIDI_NAME
};
