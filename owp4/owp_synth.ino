#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

/*
 * The Open Woodwind Project - Teensy Synth for Woodwind Controllers
 * 
 * Uses a Teensy 4.0 + Audio Shield Rev.D
 * 
 * Takes MIDI input over USB.
 * 
 * Modulation and Breath affect volume and filter
 * Expression is mapped to portamento
 * 
 * It defaults to a single oscillator with a variable triangle wave.
 * Variable triangle waves have less aliasing at the top of the range vs sawtooth, and just sound good ;)
 * 
 * Some settings can be customized down below in the Global Variables (settings) section.
 * 
 * CC 41 is Oscillator 1 Shape (Sine, Square, Sawtooth, Variable Triangle)
 * CC 42 is Oscillator 1 Shape (Sine, Square, Sawtooth, Variable Triangle)
 * CC 43 is Oscillator 1 Shape (Sine, Square, Sawtooth, Variable Triangle)
 * CC 44 is Oscillator 1 Shape (Sine, Square, Sawtooth, Variable Triangle)
 * CC 51 is Oscillator 1 Volume
 * CC 52 is Oscillator 2 Volume
 * CC 53 is Oscillator 3 Volume
 * CC 54 is Oscillator 4 Volume
 * CC 61 is Oscillator 1 Detune
 * CC 62 is Oscillator 2 Detune
 * CC 63 is Oscillator 3 Detune
 * CC 64 is Oscillator 4 Detune
 * CC 70 is Breath to Oscillator (all four) Pulse Width
 * CC 71 is Oscillator 1 Pulse Width
 * CC 72 is Oscillator 2 Pulse Width
 * CC 73 is Oscillator 3 Pulse Width
 * CC 74 is Oscillator 4 Pulse Width
 * CC 75 is Modulation to Oscillator 1 Pulse Width
 * CC 76 is Filter Resonance (Q)
 * CC 77 is Note Offset
 * CC 78 is Fine Tuning (of entire instrument, not individual oscillators)
 * CC 91 is Reverb Size
 * 
 */

// GUItool: begin automatically generated code
AudioSynthWaveformDc     glide_frequency;            //xy=203.00000762939453,505.00001525878906
AudioSynthWaveformDc     filter_frequency;            //xy=205.00000762939453,549.0000152587891
AudioSynthWaveformDc     pitchbend;            //xy=211,643
AudioSynthWaveformDc     wave1_width;            //xy=216.00000762939453,691.0000200271606
AudioSynthWaveformDc     wave4_width;            //xy=216.00000381469727,816.3333358764648
AudioSynthWaveformDc     portamento;            //xy=217.00000762939453,593.0000171661377
AudioSynthWaveform       wave1;      //xy=220.00000762939453,188.0000057220459
AudioSynthWaveform       wave4;      //xy=220.00000762939453,315.0000114440918
AudioSynthWaveformDc     wave3_width;            //xy=219,778
AudioSynthWaveformDc     modulation;           //xy=219.00000762939453,860.3333387374878
AudioSynthWaveform       wave2;      //xy=222.00000762939453,229.00000762939453
AudioSynthWaveform       wave3;      //xy=222.00002670288086,272.00000762939453
AudioSynthWaveformDc     wave2_width;            //xy=225,728
AudioSynthWaveformDc     breath;            //xy=230.00000762939453,460.00001335144043
AudioMixer4              waveselect;         //xy=387.00000762939453,249.0000457763672
AudioMixer4              dc_smoothing1;         //xy=562.0000152587891,482.00001335144043
AudioMixer4              dc_smoothing2;         //xy=567.0000152587891,564.0000190734863
AudioMixer4              dc_smoothing3;         //xy=567.0000152587891,646.0000190734863
AudioFilterBiquad        filter;        //xy=898.0001411437988,264.0000286102295
AudioEffectFreeverbStereo reverb;     //xy=1077.0000305175781,366.00000953674316
AudioMixer4              right;          //xy=1355.0000343322754,380.0000114440918
AudioMixer4              left;           //xy=1357.0000343322754,309.00000762939453
AudioOutputI2S           audio_output;   //xy=1499.00004196167,345.00000953674316
AudioConnection          patchCord1(glide_frequency, 0, dc_smoothing1, 1);
AudioConnection          patchCord2(filter_frequency, 0, dc_smoothing1, 2);
AudioConnection          patchCord3(pitchbend, 0, dc_smoothing2, 0);
AudioConnection          patchCord4(wave1_width, 0, dc_smoothing2, 1);
AudioConnection          patchCord5(wave4_width, 0, dc_smoothing3, 0);
AudioConnection          patchCord6(portamento, 0, dc_smoothing1, 3);
AudioConnection          patchCord7(wave1, 0, waveselect, 0);
AudioConnection          patchCord8(wave4, 0, waveselect, 3);
AudioConnection          patchCord9(wave3_width, 0, dc_smoothing2, 3);
AudioConnection          patchCord10(modulation, 0, dc_smoothing3, 1);
AudioConnection          patchCord11(wave2, 0, waveselect, 1);
AudioConnection          patchCord12(wave3, 0, waveselect, 2);
AudioConnection          patchCord13(wave2_width, 0, dc_smoothing2, 2);
AudioConnection          patchCord14(breath, 0, dc_smoothing1, 0);
AudioConnection          patchCord15(waveselect, filter);
AudioConnection          patchCord16(filter, reverb);
AudioConnection          patchCord17(filter, 0, left, 0);
AudioConnection          patchCord18(filter, 0, right, 0);
AudioConnection          patchCord19(reverb, 0, left, 1);
AudioConnection          patchCord20(reverb, 1, right, 1);
AudioConnection          patchCord21(right, 0, audio_output, 1);
AudioConnection          patchCord22(left, 0, audio_output, 0);
AudioControlSGTL5000     sgtl5000_1;     //xy=1518.0000457763672,61.0000057220459
// GUItool: end automatically generated code


//Global Variables - Settings (You can change these to set startup conditions)
int   pitchbend_range           = 2;
int   note_offset               = 16;
float default_tune              = 1.0;
bool  pitchbend_reset_on_noteon = true;
int   portamento_min            = 50;
int   portamento_max            = 500;
float breath_to_filter          = 0.4;
float breath_to_pulse_width     = 0.01;
float modulation_to_filter      = 0.25;
float modulation_to_pulse_width = 0.0;
float wave1_pulse_width         = 0.9;
float wave2_pulse_width         = 0.8;
float wave3_pulse_width         = 0.6;
float wave4_pulse_width         = 0.5;
float wave1_starting_gain       = 0.8;
float wave2_starting_gain       = 0.0;
float wave3_starting_gain       = 0.0;
float wave4_starting_gain       = 65.0/127.0;
float wave1_detune_multiplier   = 1.0;
float wave2_detune_multiplier   = 1.0;
float wave3_detune_multiplier   = 1.0;
float wave4_detune_multiplier   = 001.0;
float reverb_starting_size      = 0.9;
float reverb_starting_damping   = 0.999;
float filter_max_frequency      = 20000;
float filter_min_frequency      = 10;
float filter_q                  = .707;
float filter_passes             = 0;
int   breath_gamma              = 1.85; //This makes the breath more logarithmic 

//Global Variables - Ramp Rates (You shouldn't have to change these)
//These guys smooth out the MIDI values coming in
int breath_ramp_rate            = 20; 
int breath_ramp_rate_note_off   = 50;
int pitch_ramp_rate             = 10;
int filter_frequency_ramp_rate  = 10;
int portamento_ramp_rate        = 30;
int pitchbend_ramp_rate         = 10;
int modulation_ramp_rate        = 30;

//Global Variables - Not Settings (these are 
int  note                       = 0;       
bool noteon                     = false;
float wave_freq                 = 20000;
float pitchbend_multiplier      = 1.0;


void setup() {

/* Uncomment to load the multioscillator patch 
modulation_to_pulse_width = 92.0/127.0;
wave1_pulse_width         = 105.0/127.0;
wave2_pulse_width         = 108.0/127.0;
wave3_pulse_width         = 104.0/127.0;
wave4_pulse_width         = 97.0/127.0;
wave1_starting_gain       = 61.0/127.0;
wave2_starting_gain       = 66.0/127.0;
wave3_starting_gain       = 64.0/127.0;
wave4_starting_gain       = 65.0/127.0;
filter_q                  = 2;
wave1_detune_multiplier   = 127.0/127.0*0.75+0.25;
wave2_detune_multiplier   = 42.0/127.0*0.75+0.25;
wave3_detune_multiplier   = 127.0/127.0*0.75+0.25;
wave4_detune_multiplier   = 0.0;
*/

  
  Serial.begin(115200);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8);
  AudioMemory(20);
  sgtl5000_1.audioPostProcessorEnable();
  wave1.begin(0.0, 440, WAVEFORM_TRIANGLE_VARIABLE);
  wave1.pulseWidth(wave1_width.read());
  wave2.begin(0.0, 440, WAVEFORM_TRIANGLE_VARIABLE);
  wave2.pulseWidth(wave2_width.read());
  wave3.begin(0.0, 440, WAVEFORM_TRIANGLE_VARIABLE);
  wave3.pulseWidth(wave3_width.read());
  wave4.begin(0.0, 440, WAVEFORM_TRIANGLE_VARIABLE);
  wave4.pulseWidth(wave4_width.read());
  wave1_width.amplitude(wave1_pulse_width);
  wave2_width.amplitude(wave2_pulse_width);
  wave3_width.amplitude(wave3_pulse_width);
  wave4_width.amplitude(wave4_pulse_width);
  waveselect.gain(0, wave1_starting_gain);
  waveselect.gain(1, wave2_starting_gain);
  waveselect.gain(2, wave3_starting_gain);
  waveselect.gain(3, wave4_starting_gain);
  filter.setLowpass(0, 800, filter_q);
  reverb.roomsize(reverb_starting_size);
  reverb.damping(reverb_starting_damping);
  left.gain(0, 0.85);
  left.gain(1, 0.15);
  right.gain(0, 0.85);
  right.gain(1, 0.15);

  breath.amplitude(0.0);
  glide_frequency.amplitude(0.0);
  filter_frequency.amplitude(0.0);
  portamento.amplitude(0.0);
  pitchbend.amplitude(0.0);
  modulation.amplitude(0.0);
}

void loop() {
  pitchbend_multiplier = pow(2.0, (pitchbend_range * (pitchbend.read() ) /12.0));
  
  wave1.amplitude(breath.read());
  wave2.amplitude(breath.read());
  wave3.amplitude(breath.read());
  wave4.amplitude(breath.read());
  wave1.pulseWidth(bound1(wave1_width.read()+breath.read()*breath_to_pulse_width+modulation.read()*modulation_to_pulse_width));
  wave2.pulseWidth(bound1(wave2_width.read()+breath.read()*breath_to_pulse_width+modulation.read()*modulation_to_pulse_width));
  wave3.pulseWidth(bound1(wave3_width.read()+breath.read()*breath_to_pulse_width+modulation.read()*modulation_to_pulse_width));
  wave4.pulseWidth(bound1(wave4_width.read()+breath.read()*breath_to_pulse_width+modulation.read()*modulation_to_pulse_width));
  wave1.frequency(glide_frequency.read() * pitchbend_multiplier * wave1_detune_multiplier * wave_freq * default_tune);
  wave2.frequency(glide_frequency.read() * pitchbend_multiplier * wave2_detune_multiplier * wave_freq * default_tune);
  wave3.frequency(glide_frequency.read() * pitchbend_multiplier * wave3_detune_multiplier * wave_freq * default_tune);
  wave4.frequency(glide_frequency.read() * pitchbend_multiplier * wave4_detune_multiplier * wave_freq * default_tune);
  
  filter_frequency.amplitude(breath_to_filter * breath.read() + modulation_to_filter * modulation.read(), filter_frequency_ramp_rate);
  filter.setLowpass(filter_passes, filter_max_frequency * filter_frequency.read() + filter_min_frequency, filter_q);
  
  if (usbMIDI.read()) {
    processMIDI();
  }
}

void processMIDI(void) {
  byte type, channel, data1, data2, cable;
  type = usbMIDI.getType();       // which MIDI message, 128-255
  channel = usbMIDI.getChannel(); // which MIDI channel, 1-16
  data1 = usbMIDI.getData1();     // first data byte of message, 0-127
  data2 = usbMIDI.getData2();     // second data byte of message, 0-127
  cable = usbMIDI.getCable();     // which virtual cable with MIDIx8, 0-7

  switch (type) {
    case usbMIDI.NoteOff: // 0x80
      if(note == data1) { //if this noteOff message matches are currently playing note
        breath.amplitude(0.0, breath_ramp_rate_note_off);
        noteon = false;
      }
      break;

    case usbMIDI.NoteOn: // 0x90
      if(noteon) {
        if(pitchbend_reset_on_noteon) {
          pitchbend.amplitude(0.0);
        }
        glide_frequency.amplitude((pow(2.0, ((float)(data1+note_offset)/12.0))/wave_freq), portamento_min + (portamento.read() * portamento_max - portamento_min));
      } else {
        glide_frequency.amplitude((pow(2.0, ((float)(data1+note_offset)/12.0))/wave_freq));
      }
      note = data1;
      noteon = true;
      break;

    case usbMIDI.ControlChange: // 0xB0
      if(data1==1) {//Modulation Wheel
        modulation.amplitude(data2/127.0, modulation_ramp_rate);
      }
      if(data1==2) {//Breath
        if(noteon) {
          breath.amplitude(lin_to_log(data2, 127, breath_gamma)/127.0, breath_ramp_rate);
        }
      }
      if(data1==11) {//Expression
        portamento.amplitude(data2/127.0, portamento_ramp_rate);
      }
      if(data1==41) {//Oscillator Shapes (41-44)
        if(data2 < 32) {
          wave1.begin(WAVEFORM_SINE);
        } else if(data2 < 64) {
          wave1.begin(WAVEFORM_SQUARE);
        } else if(data2 < 96) {
          wave1.begin(WAVEFORM_SAWTOOTH);
        } else {
          wave1.begin(WAVEFORM_TRIANGLE_VARIABLE);
        }
      }
      if(data1==42) {
        if(data2 < 32) {
          wave2.begin(WAVEFORM_SINE);
        } else if(data2 < 64) {
          wave2.begin(WAVEFORM_SQUARE);
        } else if(data2 < 96) {
          wave2.begin(WAVEFORM_SAWTOOTH);
        } else {
          wave2.begin(WAVEFORM_TRIANGLE_VARIABLE);
        }
      }
      if(data1==43) {
        if(data2 < 32) {
          wave3.begin(WAVEFORM_SINE);
        } else if(data2 < 64) {
          wave3.begin(WAVEFORM_SQUARE);
        } else if(data2 < 96) {
          wave3.begin(WAVEFORM_SAWTOOTH);
        } else {
          wave3.begin(WAVEFORM_TRIANGLE_VARIABLE);
        }
      }
      if(data1==44) {
        if(data2 < 32) {
          wave4.begin(WAVEFORM_SINE);
        } else if(data2 < 64) {
          wave4.begin(WAVEFORM_SQUARE);
        } else if(data2 < 96) {
          wave4.begin(WAVEFORM_SAWTOOTH);
        } else {
          wave4.begin(WAVEFORM_TRIANGLE_VARIABLE);
        }
      }
      
      if(data1==51) {//Oscillator Gains (51-54)
        waveselect.gain(0, data2/127.0);
      }
      if(data1==52) {
        waveselect.gain(1, data2/127.0);
      }
      if(data1==53) {
        waveselect.gain(2, data2/127.0);
      }
      if(data1==54) {
        waveselect.gain(3, data2/127.0);
      }
      if(data1==61) {//Oscillator Detune (61-64)
        wave1_detune_multiplier = data2/127.0*0.75+0.25;
      }
      if(data1==62) {
        wave2_detune_multiplier = data2/127.0*0.75+0.25;
      }
      if(data1==63) {
        wave3_detune_multiplier = data2/127.0*0.75+0.25;
      }
      if(data1==64) {
        wave1_detune_multiplier = data2/127.0*0.75+0.25;
      }
      if(data1==70) {//Breath to Pulse Width
        breath_to_pulse_width = data2/127.0;
      }
      if(data1==71) {//Oscilator Pulse Widths (71-74)
        wave1_width.amplitude(data2/127.0);
      }
      if(data1==72) {
        wave2_width.amplitude(data2/127.0);
      }
      if(data1==73) {
        wave3_width.amplitude(data2/127.0);
      }
      if(data1==74) {
        wave4_width.amplitude(data2/127.0);
      }
      if(data1==75) {//Modulation to Pulse Width
        modulation_to_pulse_width = data2/127.0;
      }
      if(data1==76) {//Filter Resonance
        filter_q = data2/127.0*3;
      }
      if(data1==77) {//Note Offset
        note_offset=data2/127.0 * 24;
      }
      if(data1==78) {//Fine Tuning
        default_tune=(data2/127.0/2+0.75);
      }
      
      if(data1==91) {//Reverb Roomsize
      
        reverb.roomsize(data2/127.0);
      }
      break;


    case usbMIDI.PitchBend: // 0xE0
      pitchbend.amplitude((data1+data2*128.0-8192.0)/8192.0, pitchbend_ramp_rate);
      break;

    default:
      break;
  }
}

//This function converts linear to expo, using gamma as the exponential amount
float lin_to_log( int input, int input_max, float gamma) {
  return (float) (0.5 + pow ((float)input / (float)input_max, (float)gamma) * (float)input_max);
}

//Just a bounding function
float bound1(float val) {
  if(val > 1) return 1;
  if(val < 0) return 0;
  return val;
}
