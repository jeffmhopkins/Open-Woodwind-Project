/*
 * The Open Woodwind Project - Teensy Synth for Woodwind Controllers
 * 
 * Uses a Teensy 4.0 + Audio Shield Rev.D
 * 
 * Please use the included TouchOSC GUI for ipad for full control. Lots of CC. 
 */

#define CC_MODULATION_WHEEL               1
#define CC_BREATH                         2
#define CC_EXPRESSION                     11
#define CC_BREATH_TO_PULSE_WIDTH          20
#define CC_BREATH_TO_FILTER_CUTOFF        21
#define CC_BREATH_TO_FILTER_RESONANCE     22
#define CC_BREATH_TO_OVERDRIVE            23
#define CC_MODULATION_TO_PULSE_WIDTH      24
#define CC_MODULATION_TO_FILTER_CUTOFF    25
#define CC_MODULATION_TO_FILTER_RESONANCE 26
#define CC_MODULATION_TO_OVERDRIVE        27
#define CC_EXPRESSION_TO_PULSE_WIDTH      28
#define CC_EXPRESSION_TO_FILTER_CUTOFF    29
#define CC_EXPRESSION_TO_FILTER_RESONANCE 30
#define CC_EXPRESSION_TO_PORTAMENTO       31
#define CC_EXPRESSION_TO_OVERDRIVE        32
#define CC_PORTAMENTO_MIN                 33
#define CC_WAV_PLAYER                     34
#define CC_WAV_PLAYER_GAIN                35
#define CC_LOAD_PATCH                     36
#define CC_SAVE_PATCH                     37
#define CC_WAVE1_SHAPE                    41
#define CC_WAVE2_SHAPE                    42
#define CC_WAVE3_SHAPE                    43
#define CC_WAVE4_SHAPE                    44
#define CC_WAVE1_GAIN                     51
#define CC_WAVE2_GAIN                     52
#define CC_WAVE3_GAIN                     53
#define CC_WAVE4_GAIN                     54
#define CC_WAVE1_DETUNE_MULTIPLIER        61
#define CC_WAVE2_DETUNE_MULTIPLIER        62
#define CC_WAVE3_DETUNE_MULTIPLIER        63
#define CC_WAVE4_DETUNE_MULTIPLIER        64
#define CC_WAVE1_PULSE_WIDTH              71
#define CC_WAVE2_PULSE_WIDTH              72
#define CC_WAVE3_PULSE_WIDTH              73
#define CC_WAVE4_PULSE_WIDTH              74
#define CC_FILTER_RESONANCE_OFFSET        76
#define CC_NOTE_OFFSET                    77
#define CC_FINE_TUNING                    78
#define CC_MASTER_VOLUME                  81
#define CC_FILTER_FREQUENCY_OFFSET        82
#define CC_NOISE_PINK_GAIN                83
#define CC_NOISE_WHITE_GAIN               84
#define CC_EFFECTS_MIXER_CLEAN            85
#define CC_EFFECTS_MIXER_FLANGE           86
#define CC_EFFECTS_MIXER_CHORUS           87
#define CC_OSCILLATOR_OVERDRIVE           89
#define CC_EFFECTS_MIXER_DELAY            90
#define CC_REVERB_ROOM_SIZE               91
#define CC_EFFECTS_MIXER_DELAY_MS         92

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <limits.h>

extern float driven_waveform[257];

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

//Global Variables - Settings (You can change these to set startup conditions)
int   pitchbend_range                = 2;    
int   note_offset                    = 16;   
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
float effects_flange                 = 0.0;
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
  effect_mixer.gain(1, effects_flange);
  effect_mixer.gain(2, effects_chorus);
  effect_mixer.gain(3, effects_delay);
  left.gain(2, wav_gain);
  right.gain(2, wav_gain);
  sgtl5000_1.volume(master_volume);
  reverb.roomsize(reverb_size);
  AudioInterrupts();
  if (usbMIDI.read()) {
    processMIDI();
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
