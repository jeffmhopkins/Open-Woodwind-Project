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
#define CC_LFO1_FREQUENCY                 38
#define CC_LFO1_AMOUNT                    39
#define CC_LFO1_RANGE                     40
#define CC_WAVE1_SHAPE                    41
#define CC_WAVE2_SHAPE                    42
#define CC_WAVE3_SHAPE                    43
#define CC_WAVE4_SHAPE                    44
#define CC_LFO2_FREQUENCY                 45
#define CC_LFO2_AMOUNT                    46
#define CC_LFO2_RANGE                     47
#define CC_MODULATION_TO_LFO1_GAIN        48
#define CC_BREATH_TO_LFO1_GAIN            49
#define CC_EXPRESSION_TO_LFO1_GAIN        50
#define CC_WAVE1_GAIN                     51
#define CC_WAVE2_GAIN                     52
#define CC_WAVE3_GAIN                     53
#define CC_WAVE4_GAIN                     54
#define CC_MODULATION_TO_LFO1_FREQ        55
#define CC_BREATH_TO_LFO1_FREQ            56
#define CC_EXPRESSION_TO_LFO1_FREQ        57
#define CC_MODULATION_TO_LFO2_GAIN        58
#define CC_BREATH_TO_LFO2_GAIN            59
#define CC_EXPRESSION_TO_LFO2_GAIN        60
#define CC_WAVE1_DETUNE_MULTIPLIER        61
#define CC_WAVE2_DETUNE_MULTIPLIER        62
#define CC_WAVE3_DETUNE_MULTIPLIER        63
#define CC_WAVE4_DETUNE_MULTIPLIER        64
#define CC_MODULATION_TO_LFO2_FREQ        65
#define CC_BREATH_TO_LFO2_FREQ            66
#define CC_EXPRESSION_TO_LFO2_FREQ        67
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

extern float driven_waveform[257];

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformDc     wave3_width;    //xy=100.00003814697266,203.00002002716064
AudioSynthWaveformDc     wave4_width;    //xy=100.00005340576172,235.00007343292236
AudioSynthWaveformDc     wave2_width;    //xy=101.00005340576172,135.00002813339233
AudioSynthWaveformDc     wave1_width;    //xy=102.00006103515625,103.00000095367432
AudioSynthWaveformSine   lfo2; //xy=116.03125,170.03125476837158
AudioSynthWaveformSine   lfo1;          //xy=120,71.03129196166992
AudioSynthWaveformModulated wave2; //xy=302.03125,134.03125
AudioSynthWaveformModulated wave1;   //xy=303.0312957763672,87.03129863739014
AudioSynthWaveformModulated wave4; //xy=304.03125,224.03125
AudioSynthWaveformModulated wave3; //xy=308.03125,178.03125
AudioSynthWaveformDc     glide_frequency; //xy=317.00006103515625,578.0000581741333
AudioSynthWaveformDc     filter_frequency; //xy=319.00006103515625,627.0000281333923
AudioSynthWaveformDc     expression;     //xy=337.0000534057617,499.0000276565552
AudioSynthWaveformDc     modulation;     //xy=338.0000686645508,417.99999809265137
AudioSynthWaveformDc     pitchbend;      //xy=340.00006103515625,537.9999976158142
AudioSynthWaveformDc     breath;         //xy=344.000057220459,459.0000047683716
AudioMixer4              waveselect;     //xy=458.00006103515625,154.0000057220459
AudioEffectWaveshaper    waveshape1;     //xy=617.0000686645508,274.0000162124634
AudioSynthNoisePink      noise_pink;     //xy=624.0000705718994,179.0000057220459
AudioSynthNoiseWhite     noise_white;    //xy=627.0000610351562,227.0000057220459
AudioMixer4              dc_smoothing1;  //xy=676.000057220459,481.0000047683716
AudioMixer4              dc_smoothing2;  //xy=681.000057220459,563.0000047683716
AudioMixer4              mixer1;         //xy=772.000057220459,175.00000476837158
AudioEffectDelay         delay1;         //xy=847.0000801086426,383.00002002716064
AudioFilterBiquad        filter;         //xy=917.000057220459,176.00000476837158
AudioMixer4              delay_mixer1;         //xy=1028.0002479553223,357.00002002716064
AudioEffectChorus        chorus1;        //xy=1076.000087738037,291.00001430511475
AudioEffectFlange        flange1;        //xy=1106.000087738037,253.00003242492676
AudioMixer4              effect_mixer;   //xy=1285.000087738037,252.0000524520874
AudioPlaySdWav           wavplayer;     //xy=1304.000057220459,473.00001430511475
AudioEffectFreeverbStereo reverb;         //xy=1354.0000953674316,359.00001430511475
AudioMixer4              right;          //xy=1512.0000953674316,377.0000162124634
AudioMixer4              left;           //xy=1519.0000953674316,305.0000123977661
AudioOutputI2S           audio_output;   //xy=1592.0000457763672,353.00000953674316
AudioConnection          patchCord1(wave3_width, 0, wave3, 1);
AudioConnection          patchCord2(wave4_width, 0, wave4, 1);
AudioConnection          patchCord3(wave2_width, 0, wave2, 1);
AudioConnection          patchCord4(wave1_width, 0, wave1, 1);
AudioConnection          patchCord5(lfo2, 0, wave3, 0);
AudioConnection          patchCord6(lfo2, 0, wave4, 0);
AudioConnection          patchCord7(lfo1, 0, wave1, 0);
AudioConnection          patchCord8(lfo1, 0, wave2, 0);
AudioConnection          patchCord9(wave2, 0, waveselect, 1);
AudioConnection          patchCord10(wave1, 0, waveselect, 0);
AudioConnection          patchCord11(wave4, 0, waveselect, 3);
AudioConnection          patchCord12(wave3, 0, waveselect, 2);
AudioConnection          patchCord13(glide_frequency, 0, dc_smoothing2, 1);
AudioConnection          patchCord14(filter_frequency, 0, dc_smoothing2, 2);
AudioConnection          patchCord15(expression, 0, dc_smoothing1, 2);
AudioConnection          patchCord16(modulation, 0, dc_smoothing1, 0);
AudioConnection          patchCord17(pitchbend, 0, dc_smoothing2, 0);
AudioConnection          patchCord18(breath, 0, dc_smoothing1, 1);
AudioConnection          patchCord19(waveselect, 0, mixer1, 0);
AudioConnection          patchCord20(waveselect, waveshape1);
AudioConnection          patchCord21(waveshape1, 0, mixer1, 3);
AudioConnection          patchCord22(noise_pink, 0, mixer1, 1);
AudioConnection          patchCord23(noise_white, 0, mixer1, 2);
AudioConnection          patchCord24(mixer1, filter);
AudioConnection          patchCord25(delay1, 0, delay_mixer1, 0);
AudioConnection          patchCord26(delay1, 1, delay_mixer1, 1);
AudioConnection          patchCord27(delay1, 2, delay_mixer1, 2);
AudioConnection          patchCord28(delay1, 3, delay_mixer1, 3);
AudioConnection          patchCord29(filter, 0, effect_mixer, 0);
AudioConnection          patchCord30(filter, flange1);
AudioConnection          patchCord31(filter, chorus1);
AudioConnection          patchCord32(filter, delay1);
AudioConnection          patchCord33(delay_mixer1, 0, effect_mixer, 3);
AudioConnection          patchCord34(chorus1, 0, effect_mixer, 2);
AudioConnection          patchCord35(flange1, 0, effect_mixer, 1);
AudioConnection          patchCord36(effect_mixer, reverb);
AudioConnection          patchCord37(effect_mixer, 0, left, 0);
AudioConnection          patchCord38(effect_mixer, 0, right, 0);
AudioConnection          patchCord39(wavplayer, 0, left, 2);
AudioConnection          patchCord40(wavplayer, 1, right, 2);
AudioConnection          patchCord41(reverb, 0, left, 1);
AudioConnection          patchCord42(reverb, 1, right, 1);
AudioConnection          patchCord43(right, 0, audio_output, 1);
AudioConnection          patchCord44(left, 0, audio_output, 0);
AudioControlSGTL5000     sgtl5000_1;     //xy=1632.000057220459,60.00000476837158
// GUItool: end automatically generated code

//Global Variables - Settings (You can change these to set startup conditions)
int   pitchbend_range                = 2;   
int   lfo_max_range                  = 2;//octaves 
int   lfo_max_freq                   = 20;//20hz
int   note_offset                    = 16;   
float default_tune                   = 1.0;
bool  pitchbend_reset_on_noteon      = true;
int   portamento_min                 = 50;   
int   portamento_max                 = 500;  
float breath_to_pulse_width          = 0.4;  
float breath_to_filter_cutoff        = 0.2;  
float breath_to_filter_resonance     = 0.0;  
float breath_to_overdrive            = 0.0;  
float breath_to_lfo1_gain            = 0.0;
float breath_to_lfo1_freq            = 0.0;
float breath_to_lfo2_gain            = 0.0;
float breath_to_lfo2_freq            = 0.0;
float modulation_to_pulse_width      = 0.0;  
float modulation_to_filter_cutoff    = 0.25; 
float modulation_to_filter_resonance = 0.0; 
float modulation_to_overdrive        = 0.0; 
float modulation_to_lfo1_gain        = 0.0;
float modulation_to_lfo1_freq        = 0.0;
float modulation_to_lfo2_gain        = 0.0;
float modulation_to_lfo2_freq        = 0.0;
float expression_to_pulse_width      = 0.0; 
float expression_to_filter_cutoff    = 0.0; 
float expression_to_filter_resonance = 0.0; 
float expression_to_portamento       = 0.75; 
float expression_to_overdrive        = 0.0; 
float expression_to_lfo1_gain        = 0.0;
float expression_to_lfo1_freq        = 0.0;
float expression_to_lfo2_gain        = 0.0;
float expression_to_lfo2_freq        = 0.0;
float wave1_pulse_width              = 0.5;  
float wave2_pulse_width              = 0.8;
float wave3_pulse_width              = 0.6;
float wave4_pulse_width              = 0.5;
float wave1_gain                     = 0.8; 
float wave2_gain                     = 0.0;
float wave3_gain                     = 0.0;
float wave4_gain                     = 0.0;
float wave1_shape                    = WAVEFORM_TRIANGLE_VARIABLE;
float wave2_shape                    = WAVEFORM_TRIANGLE_VARIABLE;
float wave3_shape                    = WAVEFORM_TRIANGLE_VARIABLE;
float wave4_shape                    = WAVEFORM_TRIANGLE_VARIABLE;
float noise_pink_gain                = 0.0; 
float noise_white_gain               = 0.0; 
float distortion_gain                = 0.0; 
float wave1_detune_multiplier        = 1.0; 
float wave2_detune_multiplier        = 1.0; 
float wave3_detune_multiplier        = 1.0; 
float wave4_detune_multiplier        = 1.0; 
float reverb_size                    = 0.9;
float reverb_damping                 = 0.999;
float filter_max_frequency           = 20000;
float filter_min_frequency           = 10;
float filter_q                       = .707;
float filter_passes                  = 0;   
int   breath_gamma                   = 1.85; 
float delay_amount                   = 250; 
float master_volume                  = 0.8;
float effects_oscillators            = 1.0;
float effects_flange                 = 0.0;
float effects_chorus                 = 0.0;
float effects_delay                  = 0.0;
float effects_delay_ms               = 0.0;
float wav_gain                       = 1.0;
float lfo1_gain                      = 0.0;
float lfo1_freq                      = 0.0;
float lfo1_range                     = 0.0;
float lfo2_gain                      = 0.0;
float lfo2_freq                      = 0.0;
float lfo2_range                     = 0.0;

//Global Variables - Ramp Rates (You shouldn't have to change these)
//These guys smooth out the MIDI values coming in
int breath_ramp_rate            = 20;
int breath_ramp_rate_note_off   = 50;
int pitch_ramp_rate             = 10;
int filter_frequency_ramp_rate  = 10;
int expression_ramp_rate        = 30; 
int pitchbend_ramp_rate         = 10;
int modulation_ramp_rate        = 30;

//Global Variables
int  note                       = 0;       
bool noteon                     = false;
float wave_freq                 = 20000;
float portamento                = 0.0;
float pitchbend_multiplier      = 1.0;
float pulsewidth_calculated     = 0.0;
float overdrive_calculated      = 0.0;
float distortion_mix            = 0.0;

//Flange specific
#define FLANGE_DELAY_LENGTH (6*AUDIO_BLOCK_SAMPLES)
short delayline[FLANGE_DELAY_LENGTH];
int s_idx = FLANGE_DELAY_LENGTH/4;
int s_depth = FLANGE_DELAY_LENGTH/4;
double s_freq = .5;

//Chorus specific
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
  lfo1.frequency(4);//4hz
  lfo1.amplitude(1);//for testing
  wave1.begin(0.0, 440, WAVEFORM_TRIANGLE_VARIABLE);
  wave1.frequencyModulation(1);//1 octave range from LFO
  wave2.begin(0.0, 440, WAVEFORM_TRIANGLE_VARIABLE);
  wave2.frequencyModulation(1);//1 octave range from LFO
  wave3.begin(0.0, 440, WAVEFORM_TRIANGLE_VARIABLE);
  wave3.frequencyModulation(1);//1 octave range from LFO
  wave4.begin(0.0, 440, WAVEFORM_TRIANGLE_VARIABLE);
  wave4.frequencyModulation(1);//1 octave range from LFO
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
  wave1_width.amplitude(wave1_pulse_width + pulsewidth_calculated);
  wave2_width.amplitude(wave2_pulse_width + pulsewidth_calculated);
  wave3_width.amplitude(wave3_pulse_width + pulsewidth_calculated);
  wave4_width.amplitude(wave4_pulse_width + pulsewidth_calculated);
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
  //LFO1
  lfo1.frequency(lfo_max_freq * (lfo1_freq + bound1(breath_to_lfo1_freq * breath.read() + modulation_to_lfo1_freq * modulation.read() + expression_to_lfo1_freq * expression.read())));
  lfo1.amplitude(bound1(lfo1_gain + bound1(breath_to_lfo1_gain * breath.read() + modulation_to_lfo1_gain * modulation.read() + expression_to_lfo1_gain * expression.read())));
  wave1.frequencyModulation(lfo1_range * lfo_max_range);
  wave2.frequencyModulation(lfo1_range * lfo_max_range);
  //LFO2
  lfo2.frequency(lfo_max_freq * (lfo2_freq + bound1(breath_to_lfo2_freq * breath.read() + modulation_to_lfo2_freq * modulation.read() + expression_to_lfo2_freq * expression.read())));
  lfo2.amplitude(bound1(lfo2_gain + bound1(breath_to_lfo2_gain * breath.read() + modulation_to_lfo2_gain * modulation.read() + expression_to_lfo2_gain * expression.read())));
  wave3.frequencyModulation(lfo2_range * lfo_max_range) ;
  wave4.frequencyModulation(lfo2_range * lfo_max_range)  ;      
            
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
