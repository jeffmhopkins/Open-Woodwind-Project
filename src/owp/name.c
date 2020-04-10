#include "usb_names.h"

#define MIDI_NAME   {'O','p','e','n',' ','W','o','o','d','w','i','n','d'}
#define MIDI_NAME_LEN  13

struct usb_string_descriptor_struct usb_string_product_name = {
        2 + MIDI_NAME_LEN * 2,
        3,
        MIDI_NAME
};
