/*
 * The Open Woodwind Project - Teensy Synth for Woodwind Controllers
 * 
 * Uses a Teensy 4.0 + Audio Shield Rev.D
 * 
 * Please use the included TouchOSC GUI for ipad for full control. Lots of CC. 
 */

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <limits.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       wave4;          //xy=139,219
AudioSynthWaveform       wave2;          //xy=146,134
AudioSynthWaveform       wave3;          //xy=146,176
AudioSynthWaveform       wave1;          //xy=150,96
AudioSynthWaveformDc     glide_frequency; //xy=236,509
AudioSynthWaveformDc     filter_frequency; //xy=238,553
AudioSynthWaveformDc     pitchbend;      //xy=244,647
AudioSynthWaveformDc     wave1_width;    //xy=249,695
AudioSynthWaveformDc     wave4_width;    //xy=249,820
AudioSynthWaveformDc     expression;     //xy=250,597
AudioSynthWaveformDc     wave3_width;    //xy=252,782
AudioSynthWaveformDc     modulation;     //xy=252,864
AudioSynthWaveformDc     wave2_width;    //xy=258,732
AudioSynthWaveformDc     breath;         //xy=263,464
AudioMixer4              waveselect;     //xy=297,156
AudioEffectWaveshaper    waveshape1;     //xy=456.00000762939453,276.0000104904175
AudioSynthNoiseWhite     noise_white;    //xy=466,229
AudioSynthNoisePink      noise_pink;     //xy=471,189
AudioMixer4              dc_smoothing1;  //xy=595,486
AudioMixer4              dc_smoothing2;  //xy=600,568
AudioMixer4              dc_smoothing3;  //xy=600,650
AudioMixer4              mixer1;         //xy=691,180
AudioEffectDelay         delay1;         //xy=766.0000228881836,388.00001525878906
AudioFilterBiquad        filter;         //xy=836,181
AudioMixer4              delay_mixer1;         //xy=947.0001907348633,362.00001525878906
AudioEffectChorus        chorus1;        //xy=995.0000305175781,296.00000953674316
AudioEffectFlange        flange1;        //xy=1025.0000305175781,258.0000276565552
AudioMixer4              effect_mixer;   //xy=1204.0000305175781,257.0000476837158
AudioPlaySdWav           wavplayer;     //xy=1223,478.00000953674316
AudioEffectFreeverbStereo reverb;         //xy=1273.0000381469727,364.00000953674316
AudioMixer4              right;          //xy=1431.0000381469727,382.0000114440918
AudioMixer4              left;           //xy=1438.0000381469727,310.00000762939453
AudioOutputI2S           audio_output;   //xy=1592.0000457763672,353.00000953674316
AudioConnection          patchCord1(wave4, 0, waveselect, 3);
AudioConnection          patchCord2(wave2, 0, waveselect, 1);
AudioConnection          patchCord3(wave3, 0, waveselect, 2);
AudioConnection          patchCord4(wave1, 0, waveselect, 0);
AudioConnection          patchCord5(glide_frequency, 0, dc_smoothing1, 1);
AudioConnection          patchCord6(filter_frequency, 0, dc_smoothing1, 2);
AudioConnection          patchCord7(pitchbend, 0, dc_smoothing2, 0);
AudioConnection          patchCord8(wave1_width, 0, dc_smoothing2, 1);
AudioConnection          patchCord9(wave4_width, 0, dc_smoothing3, 0);
AudioConnection          patchCord10(expression, 0, dc_smoothing1, 3);
AudioConnection          patchCord11(wave3_width, 0, dc_smoothing2, 3);
AudioConnection          patchCord12(modulation, 0, dc_smoothing3, 1);
AudioConnection          patchCord13(wave2_width, 0, dc_smoothing2, 2);
AudioConnection          patchCord14(breath, 0, dc_smoothing1, 0);
AudioConnection          patchCord15(waveselect, 0, mixer1, 0);
AudioConnection          patchCord16(waveselect, waveshape1);
AudioConnection          patchCord17(waveshape1, 0, mixer1, 3);
AudioConnection          patchCord18(noise_white, 0, mixer1, 2);
AudioConnection          patchCord19(noise_pink, 0, mixer1, 1);
AudioConnection          patchCord20(mixer1, filter);
AudioConnection          patchCord21(delay1, 0, delay_mixer1, 0);
AudioConnection          patchCord22(delay1, 1, delay_mixer1, 1);
AudioConnection          patchCord23(delay1, 2, delay_mixer1, 2);
AudioConnection          patchCord24(delay1, 3, delay_mixer1, 3);
AudioConnection          patchCord25(filter, 0, effect_mixer, 0);
AudioConnection          patchCord26(filter, flange1);
AudioConnection          patchCord27(filter, chorus1);
AudioConnection          patchCord28(filter, delay1);
AudioConnection          patchCord29(delay_mixer1, 0, effect_mixer, 3);
AudioConnection          patchCord30(chorus1, 0, effect_mixer, 2);
AudioConnection          patchCord31(flange1, 0, effect_mixer, 1);
AudioConnection          patchCord32(effect_mixer, reverb);
AudioConnection          patchCord33(effect_mixer, 0, left, 0);
AudioConnection          patchCord34(effect_mixer, 0, right, 0);
AudioConnection          patchCord35(wavplayer, 0, left, 2);
AudioConnection          patchCord36(wavplayer, 1, right, 2);
AudioConnection          patchCord37(reverb, 0, left, 1);
AudioConnection          patchCord38(reverb, 1, right, 1);
AudioConnection          patchCord39(right, 0, audio_output, 1);
AudioConnection          patchCord40(left, 0, audio_output, 0);
AudioControlSGTL5000     sgtl5000_1;     //xy=1551,65
// GUItool: end automatically generated code

extern float driven_waveform[257];

//Global Variables - Settings (You can change these to set startup conditions)
int   pitchbend_range                = 2;    //0
int   note_offset                    = 16;   //1
float default_tune                   = 1.0;  //2
bool  pitchbend_reset_on_noteon      = true; //3
int   portamento_min                 = 50;   //4
int   portamento_max                 = 500;  //5
float breath_to_pulse_width          = 0.4;  //6
float breath_to_filter_cutoff        = 0.2;  //7
float breath_to_filter_resonance     = 0.0;  //8
float breath_to_overdrive            = 0.0;  //9
float modulation_to_pulse_width      = 0.0;  //10
float modulation_to_filter_cutoff    = 0.25; //11
float modulation_to_filter_resonance = 0.0;  //12
float modulation_to_overdrive        = 0.0;  //13
float expression_to_pulse_width      = 0.0;  //14
float expression_to_filter_cutoff    = 0.0;  //15
float expression_to_filter_resonance = 0.0;  //16
float expression_to_portamento       = 0.75; //17
float expression_to_overdrive        = 0.0;  //18
float wave1_pulse_width              = 0.5;  //19
float wave2_pulse_width              = 0.8;  //20
float wave3_pulse_width              = 0.6;  //21
float wave4_pulse_width              = 0.5;  //22
float wave1_gain                     = 0.8;  //23
float wave2_gain                     = 0.0;  //24
float wave3_gain                     = 0.0;  //25
float wave4_gain                     = 0.0;  //26
float wave1_shape                    = WAVEFORM_TRIANGLE_VARIABLE;
float wave2_shape                    = WAVEFORM_TRIANGLE_VARIABLE;
float wave3_shape                    = WAVEFORM_TRIANGLE_VARIABLE;
float wave4_shape                    = WAVEFORM_TRIANGLE_VARIABLE;
float noise_pink_gain                = 0.0;  //27
float noise_white_gain               = 0.0;  //28
float distortion_gain                = 0.0;  //29
float wave1_detune_multiplier        = 1.0;  //30
float wave2_detune_multiplier        = 1.0;  //31
float wave3_detune_multiplier        = 1.0;  //32
float wave4_detune_multiplier        = 1.0;  //33
float reverb_size                    = 0.9;  //34
float reverb_damping                 = 0.999;//35
float filter_max_frequency           = 20000;//36
float filter_min_frequency           = 10;   //37
float filter_q                       = .707; //38
float filter_passes                  = 0;    //39
int   breath_gamma                   = 1.85; //40
float delay_amount                   = 250;  //41
float master_volume                  = 0.8;
float effects_oscillators            = 1.0;
float effects_flanger                = 0.0;
float effects_chorus                 = 0.0;
float effects_delay                  = 0.0;
float effects_delay_ms               = 0.0;
float wav_gain                       = 1.0;

//Global Variables - Ramp Rates (You shouldn't have to change these)
//These guys smooth out the MIDI values coming in
int breath_ramp_rate            = 20; //42
int breath_ramp_rate_note_off   = 50; //43
int pitch_ramp_rate             = 10; //44
int filter_frequency_ramp_rate  = 10; //45
int expression_ramp_rate        = 30; //46
int pitchbend_ramp_rate         = 10; //47
int modulation_ramp_rate        = 30; //48

//Global Variables - Not Settings (these are 
int  note                       = 0;       
bool noteon                     = false;
float wave_freq                 = 20000;
float portamento                = 0.0;
float pitchbend_multiplier      = 1.0;
float pulsewidth_calculated     = 0.0;
float overdrive_calculated      = 0.0;
float distortion_mix            = 0.0;

//Flange
// Number of samples in each delay line
#define FLANGE_DELAY_LENGTH (6*AUDIO_BLOCK_SAMPLES)
// Allocate the delay lines for left and right channels
short delayline[FLANGE_DELAY_LENGTH];
int s_idx = FLANGE_DELAY_LENGTH/4;
int s_depth = FLANGE_DELAY_LENGTH/4;
double s_freq = .5;


//Chorus
// Number of samples in each delay line
#define CHORUS_DELAY_LENGTH (16*AUDIO_BLOCK_SAMPLES)
short chorus_delayline[CHORUS_DELAY_LENGTH];
int n_chorus = 4;


void setup() {

  Serial.begin(115200);
  delay(5000);

  configureSD();
  
  sgtl5000_1.enable();
  sgtl5000_1.volume(master_volume);
  AudioMemory(1500);
  sgtl5000_1.audioPostProcessorEnable();

  AudioNoInterrupts();

 
  wave1.begin(0.0, 440, WAVEFORM_TRIANGLE_VARIABLE);
  wave1.pulseWidth(wave1_width.read());
  wave2.begin(0.0, 440, WAVEFORM_TRIANGLE_VARIABLE);
  wave2.pulseWidth(wave2_width.read());
  wave3.begin(0.0, 440, WAVEFORM_TRIANGLE_VARIABLE);
  wave3.pulseWidth(wave3_width.read());
  wave4.begin(0.0, 440, WAVEFORM_TRIANGLE_VARIABLE);
  wave4.pulseWidth(wave4_width.read());
  noise_pink.amplitude(0.0);
  noise_white.amplitude(0.0);
  wave1_width.amplitude(wave1_pulse_width);
  wave2_width.amplitude(wave2_pulse_width);
  wave3_width.amplitude(wave3_pulse_width);
  wave4_width.amplitude(wave4_pulse_width);
  waveselect.gain(0, wave1_gain);
  waveselect.gain(1, wave2_gain);
  waveselect.gain(2, wave3_gain);
  waveselect.gain(3, wave4_gain);
  filter.setLowpass(0, 800, filter_q);
  reverb.roomsize(reverb_size);
  reverb.damping(reverb_damping);
  left.gain(0, 0.85);
  left.gain(1, 0.15);
  left.gain(2, 1);
  right.gain(0, 0.85);
  right.gain(1, 0.15);
  right.gain(2, 1);
  mixer1.gain(0, 1);//waveforms
  mixer1.gain(1, noise_pink_gain);//pink noise
  mixer1.gain(2, noise_white_gain);//white noise
  mixer1.gain(3, distortion_gain);//waveshape1
      waveshape1.shape(driven_waveform, 257);
 
  
  effect_mixer.gain(0,1);//normal

  effect_mixer.gain(1,0);//flange
      flange1.begin(delayline,FLANGE_DELAY_LENGTH,s_idx,s_depth,s_freq);
  effect_mixer.gain(2,0);//chorus
      chorus1.begin(chorus_delayline,CHORUS_DELAY_LENGTH,n_chorus);
  effect_mixer.gain(3,0);//delay
      delay_mixer1.gain(0,0.5);
      delay_mixer1.gain(1,0.2);
      delay_mixer1.gain(2,0.07);
      delay_mixer1.gain(3,0.04);
      delay1.delay(0, delay_amount);
      delay1.delay(1, delay_amount*2);
      delay1.delay(2, delay_amount*3);
      delay1.delay(3, delay_amount*4);
 
  glide_frequency.amplitude(0.0);
  filter_frequency.amplitude(0.0);

  breath.amplitude(0.0);
  expression.amplitude(0.0);
  pitchbend.amplitude(0.0);
  modulation.amplitude(0.0);

  AudioInterrupts();
}

void loop() {
  pitchbend_multiplier = pow(2.0, (pitchbend_range * (pitchbend.read())/12.0));
  
  pulsewidth_calculated = bound1(breath.read()* breath_to_pulse_width + 
                                 modulation.read() * modulation_to_pulse_width + 
                                 expression.read() * expression_to_pulse_width);
  overdrive_calculated = bound1(distortion_mix + 
                                breath.read() * breath_to_overdrive +
                                modulation.read() * modulation_to_overdrive +
                                expression.read() * expression_to_overdrive);
         
  AudioNoInterrupts();
  wave1.amplitude(breath.read());
  wave2.amplitude(breath.read());
  wave3.amplitude(breath.read());
  wave4.amplitude(breath.read());
  wave1.pulseWidth(bound1(wave1_width.read() + pulsewidth_calculated));
  wave2.pulseWidth(bound1(wave2_width.read() + pulsewidth_calculated));
  wave3.pulseWidth(bound1(wave3_width.read() + pulsewidth_calculated));
  wave4.pulseWidth(bound1(wave4_width.read() + pulsewidth_calculated));
  wave1.frequency(glide_frequency.read() * pitchbend_multiplier * wave1_detune_multiplier * wave_freq * default_tune);
  wave2.frequency(glide_frequency.read() * pitchbend_multiplier * wave2_detune_multiplier * wave_freq * default_tune);
  wave3.frequency(glide_frequency.read() * pitchbend_multiplier * wave3_detune_multiplier * wave_freq * default_tune);
  wave4.frequency(glide_frequency.read() * pitchbend_multiplier * wave4_detune_multiplier * wave_freq * default_tune);
  waveselect.gain(0, wave1_gain);
  waveselect.gain(1, wave2_gain);
  waveselect.gain(2, wave3_gain);
  waveselect.gain(3, wave4_gain);
  noise_pink.amplitude(breath.read());
  noise_white.amplitude(breath.read());

  
  filter_frequency.amplitude(bound1(breath_to_filter_cutoff * breath.read() + 
                             modulation_to_filter_cutoff * modulation.read() +
                             expression_to_filter_cutoff * expression.read()), filter_frequency_ramp_rate);
                             
  filter.setLowpass(filter_passes, 
                    filter_max_frequency * filter_frequency.read() + filter_min_frequency, 
                    bound1(filter_q + breath_to_filter_resonance * breath.read() +
                                      modulation_to_filter_resonance * modulation.read() +
                                      expression_to_filter_resonance * expression.read()));
                                      
  mixer1.gain(0, 1.0-overdrive_calculated);
  mixer1.gain(1, noise_pink_gain);
  mixer1.gain(2, noise_white_gain);                             
  mixer1.gain(3, overdrive_calculated);
  
  effect_mixer.gain(0, effects_oscillators);
  effect_mixer.gain(1, effects_flanger);
  effect_mixer.gain(2, effects_chorus);
  effect_mixer.gain(3, effects_delay);

  sgtl5000_1.volume(master_volume);
  reverb.roomsize(reverb_size);
  
  AudioInterrupts();
  
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
        glide_frequency.amplitude((pow(2.0, ((float)(data1+note_offset)/12.0))/wave_freq), portamento_min + expression.read() * (portamento_max - portamento_min) * expression_to_portamento);
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
        expression.amplitude(data2/127.0, expression_ramp_rate);
      }
      if(data1==20) {
        breath_to_pulse_width = data2/127.0;
      }
      if(data1==21) {
        breath_to_filter_cutoff = data2/127.0;
      }
      if(data1==22) {
        breath_to_filter_resonance = data2/127.0;
      }
      if(data1==23) {
        breath_to_overdrive = data2/127.0;
      }
      if(data1==24) {
        modulation_to_pulse_width = data2/127.0;
      }
      if(data1==25) {
        modulation_to_filter_cutoff = data2/127.0;
      }
      if(data1==26) {
        modulation_to_filter_resonance = data2/127.0;
      }
      if(data1==27) {
        modulation_to_overdrive = data2/127.0;
      }
      if(data1==28) {
        expression_to_pulse_width = data2/127.0;
      }
      if(data1==29) {
        expression_to_filter_cutoff = data2/127.0;
      }
      if(data1==30) {
        expression_to_filter_resonance = data2/127.0;
      }
      if(data1==31) {
        expression_to_portamento = data2/127.0;
      }
      if(data1==32) {
        expression_to_overdrive = data2/127.0;
      }
      if(data1==33) {
        portamento_min = data2/127.0*250;
      }
      if(data1==34) {
        if(data2==0) {
          wavplayer.stop();
        } else {
          if(data2/127.0)
          if(wavplayer.isPlaying()) {
              wavplayer.stop();
          }
          wavplayer.play(String(String(data2, DEC) +".WAV").c_str());
        }
         
      }
      if(data1==35) {
        wav_gain = data2/127.0;
        left.gain(2, wav_gain);
        right.gain(2, wav_gain);
      }
      if(data1==36) {
        AudioNoInterrupts();
        loadPatch(data2);
        AudioInterrupts();
      }
      if(data1==37) {
        AudioNoInterrupts();
        savePatch(data2);
        AudioInterrupts();
      }
      if(data1==41) {//Oscillator Shapes (41-44)
        if(data2 < 32) {
          wave1.begin(WAVEFORM_SINE);
          wave1_shape = WAVEFORM_SINE;
        } else if(data2 < 64) {
          wave1.begin(WAVEFORM_SQUARE);
          wave1_shape = WAVEFORM_SQUARE;
        } else if(data2 < 96) {
          wave1.begin(WAVEFORM_SAWTOOTH);
          wave1_shape = WAVEFORM_SAWTOOTH;
        } else {
          wave1.begin(WAVEFORM_TRIANGLE_VARIABLE);
          wave1_shape = WAVEFORM_TRIANGLE_VARIABLE;
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
        
        wave1_gain = (data2/127.0);
      }
      if(data1==52) {
        wave2_gain = (data2/127.0);
      }
      if(data1==53) {
        wave3_gain = (data2/127.0);
      }
      if(data1==54) {
        wave4_gain = (data2/127.0);
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
        wave4_detune_multiplier = data2/127.0*0.75+0.25;
      }
      if(data1==70) {//Breath to Pulse Width
        breath_to_pulse_width = data2/127.0;
      }
      if(data1==71) {//Oscilator Pulse Widths (71-74)
        wave1_width.amplitude(data2/127.0);
        wave1_pulse_width = (data2/127.0);
      }
      if(data1==72) {
        wave2_width.amplitude(data2/127.0);
        wave2_pulse_width = (data2/127.0);
      }
      if(data1==73) {
        wave3_width.amplitude(data2/127.0);
        wave3_pulse_width = (data2/127.0);
      }
      if(data1==74) {
        wave4_width.amplitude(data2/127.0);
        wave4_pulse_width = (data2/127.0);
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
      if(data1==81) {//vol
        master_volume = data2/127.0;
      }
      if(data1==82) {//FilterOffset
        filter_min_frequency = data2/127.0*5000.0;
      }
      if(data1==83) {//Pink Noise Mix
        noise_pink_gain = data2/127.0;
      }
      if(data1==84) {//White Noise Mix
        noise_white_gain = data2/127.0;
      }
      if(data1==85) {//Clean
        effects_oscillators = data2/127.0;
      }
      if(data1==86) {//flange mix
        effects_flanger = data2/127.0;
      }
      if(data1==87) {//chorus mix
         effects_chorus = data2/127.0;
      }
      if(data1==89) {//Distortion from waveshape1
        distortion_mix = data2/127.0;
        
      }
      if(data1==90) {//Delay mix
        effects_delay = data2/127.0;
      }
      
      if(data1==91) {//Reverb Roomsize
        reverb_size = data2/127.0;
        
      }
      if(data1==92){//delay milliseconds
        //Not setting this in the loo
        AudioNoInterrupts();
        effects_delay_ms = data2/127.0 * 250;
        delay1.delay(0, effects_delay_ms);
        delay1.delay(1, effects_delay_ms*2);
        delay1.delay(2, effects_delay_ms*3);
        delay1.delay(3, effects_delay_ms*4);
        AudioInterrupts();
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
