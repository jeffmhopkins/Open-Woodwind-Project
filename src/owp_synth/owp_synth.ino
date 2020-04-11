/*
 * The Open Woodwind Project - OWP_Synth for Woodwind Controllers by Jeff Hopkins
 * 
 * Uses a Teensy 4.0 + Audio Shield Rev.D
 * 
 * https://github.com/jeffmhopkins/Open-Woodwind-Project
 * https://hackaday.io/project/2992-the-open-woodwind-project
 * 
 * This version is meant to run as a standalone MIDI synth box for woodwind controllers.
 * There are a LOT of CC channels. These are meant to be controlled via an OSC interface on an iPad.
 * 
 * I created a TouchOSC interface that controls this synth.
 * See https://github.com/jeffmhopkins/Open-Woodwind-Project/tree/master/touchosc
 * 
 * I run an osc2midi bridge on a linux box for the mapping.The osc2midi config file is located here:
 * https://github.com/jeffmhopkins/Open-Woodwind-Project/blob/master/touchosc/custom.omm
 * 
 * You can easily create custom OSC interfaces for your setup with ease, just look at the CC mapping below.
 * 
 * You can view the signal routing of the synth by going to https://www.pjrc.com/teensy/gui/index.html and
 * loading in the auto generated portion of the audio library patching below.
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
#define CC_MODULATION_TO_LFO1_RANGE       68
#define CC_BREATH_TO_LFO1_RANGE           69
#define CC_EXPRESSION_TO_LFO1_RANGE       70
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
#define CC_EFFECTS_MIXER_DELAY            90
#define CC_REVERB_ROOM_SIZE               91
#define CC_EFFECTS_MIXER_DELAY_MS         92
#define CC_MODULATION_TO_LFO2_RANGE       93
#define CC_BREATH_TO_LFO2_RANGE           94
#define CC_EXPRESSION_TO_LFO2_RANGE       95
#define CC_WAVESHAPE1_GAIN                96
#define CC_WAVESHAPE2_GAIN                97
#define CC_WAVESHAPE3_GAIN                98
#define CC_WAVESHAPE4_GAIN                99
#define CC_WAVESHAPE_MODULATION_MULTIPLIER       100
#define CC_WAVESHAPE_MODULATION_MULTIPLER_OFFSET 101

extern float driven_waveform[257];

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformDc     glide_frequency; //xy=232.0001106262207,476.00011444091797
AudioSynthWaveformDc     filter_frequency; //xy=234.0001106262207,525.000084400177
AudioSynthWaveformDc     expression;     //xy=252.00010299682617,397.00008392333984
AudioSynthWaveformDc     wave3_width;    //xy=253.00003051757812,233.00004386901855
AudioSynthWaveformDc     wave4_width;    //xy=253.0000457763672,265.0000972747803
AudioSynthWaveformDc     modulation;     //xy=253.00011825561523,316.00005435943604
AudioSynthWaveformDc     wave2_width;    //xy=254.0000457763672,165.00005197525024
AudioSynthWaveformDc     wave1_width;    //xy=255.00005340576172,133.00002479553223
AudioSynthWaveformDc     pitchbend;      //xy=255.0001106262207,436.0000538825989
AudioSynthWaveformDc     breath;         //xy=259.00010681152344,357.00006103515625
AudioSynthWaveformSine   lfo2; //xy=269.03124237060547,200.0312786102295
AudioSynthWaveformSine   lfo1;          //xy=272.99999237060547,101.03131580352783
AudioMixer4              dc_smoothing2;  //xy=427.0001220703125,483.00006103515625
AudioMixer4              dc_smoothing1;  //xy=431.00010681152344,370.0000762939453
AudioSynthWaveformModulated wave2; //xy=455.03124237060547,164.0312738418579
AudioSynthWaveformModulated wave1;   //xy=456.03128814697266,117.03132247924805
AudioSynthWaveformModulated wave4; //xy=457.03124237060547,254.0312738418579
AudioSynthWaveformModulated wave3; //xy=461.03124237060547,208.0312738418579
AudioSynthNoisePink      noise_pink;     //xy=610.0000839233398,242.00003242492676
AudioMixer4              waveselect;     //xy=611.0000534057617,184.0000295639038
AudioSynthNoiseWhite     noise_white;    //xy=617.0000839233398,284.00004291534424
AudioMixer4              mixer1;         //xy=781.000072479248,235.0000343322754
AudioEffectWaveshaper    waveshape1;     //xy=979.0000915527344,299.9999990463257
AudioEffectWaveshaper    waveshape2;     //xy=979.0312194824219,335.0312957763672
AudioEffectWaveshaper    waveshape3;     //xy=981.0312194824219,374.03126430511475
AudioEffectWaveshaper    waveshape4;     //xy=984.0312194824219,417.03125
AudioMixer4              waveshape_mixer1; //xy=1177.03125,357.03131103515625
AudioMixer4              waveshape_mixer2; //xy=1427.03125,256.03131103515625
AudioFilterBiquad        filter;         //xy=1588,251.00003051757812
AudioEffectDelay         delay1;         //xy=1639.0001220703125,420.00006103515625
AudioEffectFlange        flange1;        //xy=1775.0001220703125,286.00006103515625
AudioEffectChorus        chorus1;        //xy=1782,326.0000305175781
AudioMixer4              delay_mixer1;         //xy=1790.0001983642578,394.00003814697266
AudioMixer4              effect_mixer;   //xy=1938.000015258789,288.0000886917114
AudioPlaySdWav           wavplayer;     //xy=2111.0002059936523,423.0000810623169
AudioEffectFreeverbStereo reverb;         //xy=2116.0002670288086,284.0000739097595
AudioMixer4              left;           //xy=2314.000087738037,310.0000648498535
AudioMixer4              right;          //xy=2318.000144958496,383.0000877380371
AudioOutputI2S           audio_output;   //xy=2472.0003929138184,340.0000514984131
AudioConnection          patchCord1(glide_frequency, 0, dc_smoothing2, 1);
AudioConnection          patchCord2(filter_frequency, 0, dc_smoothing2, 2);
AudioConnection          patchCord3(expression, 0, dc_smoothing1, 2);
AudioConnection          patchCord4(wave3_width, 0, wave3, 1);
AudioConnection          patchCord5(wave4_width, 0, wave4, 1);
AudioConnection          patchCord6(modulation, 0, dc_smoothing1, 0);
AudioConnection          patchCord7(wave2_width, 0, wave2, 1);
AudioConnection          patchCord8(wave1_width, 0, wave1, 1);
AudioConnection          patchCord9(pitchbend, 0, dc_smoothing2, 0);
AudioConnection          patchCord10(breath, 0, dc_smoothing1, 1);
AudioConnection          patchCord11(lfo2, 0, wave3, 0);
AudioConnection          patchCord12(lfo2, 0, wave4, 0);
AudioConnection          patchCord13(lfo1, 0, wave1, 0);
AudioConnection          patchCord14(lfo1, 0, wave2, 0);
AudioConnection          patchCord15(wave2, 0, waveselect, 1);
AudioConnection          patchCord16(wave1, 0, waveselect, 0);
AudioConnection          patchCord17(wave4, 0, waveselect, 3);
AudioConnection          patchCord18(wave3, 0, waveselect, 2);
AudioConnection          patchCord19(noise_pink, 0, mixer1, 1);
AudioConnection          patchCord20(waveselect, 0, mixer1, 0);
AudioConnection          patchCord21(noise_white, 0, mixer1, 2);
AudioConnection          patchCord22(mixer1, waveshape1);
AudioConnection          patchCord23(mixer1, waveshape2);
AudioConnection          patchCord24(mixer1, 0, waveshape_mixer2, 0);
AudioConnection          patchCord25(mixer1, waveshape3);
AudioConnection          patchCord26(mixer1, waveshape4);
AudioConnection          patchCord27(waveshape1, 0, waveshape_mixer1, 0);
AudioConnection          patchCord28(waveshape2, 0, waveshape_mixer1, 1);
AudioConnection          patchCord29(waveshape3, 0, waveshape_mixer1, 2);
AudioConnection          patchCord30(waveshape4, 0, waveshape_mixer1, 3);
AudioConnection          patchCord31(waveshape_mixer1, 0, waveshape_mixer2, 1);
AudioConnection          patchCord32(waveshape_mixer2, filter);
AudioConnection          patchCord33(filter, 0, effect_mixer, 0);
AudioConnection          patchCord34(filter, flange1);
AudioConnection          patchCord35(filter, chorus1);
AudioConnection          patchCord36(filter, delay1);
AudioConnection          patchCord37(delay1, 0, delay_mixer1, 0);
AudioConnection          patchCord38(delay1, 1, delay_mixer1, 1);
AudioConnection          patchCord39(delay1, 2, delay_mixer1, 2);
AudioConnection          patchCord40(delay1, 3, delay_mixer1, 3);
AudioConnection          patchCord41(flange1, 0, effect_mixer, 1);
AudioConnection          patchCord42(chorus1, 0, effect_mixer, 2);
AudioConnection          patchCord43(delay_mixer1, 0, effect_mixer, 3);
AudioConnection          patchCord44(effect_mixer, reverb);
AudioConnection          patchCord45(effect_mixer, 0, left, 0);
AudioConnection          patchCord46(effect_mixer, 0, right, 0);
AudioConnection          patchCord47(wavplayer, 0, left, 2);
AudioConnection          patchCord48(wavplayer, 1, right, 2);
AudioConnection          patchCord49(reverb, 0, left, 1);
AudioConnection          patchCord50(reverb, 1, right, 1);
AudioConnection          patchCord51(left, 0, audio_output, 0);
AudioConnection          patchCord52(right, 0, audio_output, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=267.00006103515625,47.000003814697266
// GUItool: end automatically generated code

//Global Variables - Settings (You can change these to set startup conditions)
int   pitchbend_range                = 2;   
int   lfo_max_range                  = 3;//octaves 
int   lfo_max_freq                   = 60;//20hz
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
float breath_to_lfo1_range           = 0.0;
float breath_to_lfo2_gain            = 0.0;
float breath_to_lfo2_freq            = 0.0;
float breath_to_lfo2_range           = 0.0;
float modulation_to_pulse_width      = 0.0;  
float modulation_to_filter_cutoff    = 0.25; 
float modulation_to_filter_resonance = 0.0; 
float modulation_to_overdrive        = 0.0; 
float modulation_to_lfo1_gain        = 0.0;
float modulation_to_lfo1_freq        = 0.0;
float modulation_to_lfo1_range       = 0.0;
float modulation_to_lfo2_gain        = 0.0;
float modulation_to_lfo2_freq        = 0.0;
float modulation_to_lfo2_range       = 0.0;
float expression_to_pulse_width      = 0.0; 
float expression_to_filter_cutoff    = 0.0; 
float expression_to_filter_resonance = 0.0; 
float expression_to_portamento       = 0.75; 
float expression_to_overdrive        = 0.0; 
float expression_to_lfo1_gain        = 0.0;
float expression_to_lfo1_freq        = 0.0;
float expression_to_lfo1_range       = 0.0;
float expression_to_lfo2_gain        = 0.0;
float expression_to_lfo2_freq        = 0.0;
float expression_to_lfo2_range       = 0.0;
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
float waveshape1_gain                = 0.0;
float waveshape2_gain                = 0.0;
float waveshape3_gain                = 0.0;
float waveshape4_gain                = 0.0;
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
float waveshape_modulation_multiplier        = 0.0;
float waveshape_modulation_multiplier_offset = 0.0;

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
  lfo1.frequency(4);
  lfo1.amplitude(0);
  lfo2.frequency(4);
  lfo2.amplitude(0);
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
  mixer1.gain(3, 0);//nc
  waveshape_mixer1.gain(0, waveshape1_gain);
        waveshape1.shape(driven_waveform, 257);
  waveshape_mixer1.gain(1, waveshape2_gain);      
        waveshape2.shape(driven_waveform, 257);
  waveshape_mixer1.gain(2, waveshape3_gain);
        waveshape3.shape(driven_waveform, 257);
  waveshape_mixer1.gain(3, waveshape4_gain);
        waveshape4.shape(driven_waveform, 257);
  waveshape_mixer2.gain(0, 1);
  waveshape_mixer2.gain(1, 1);
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
  overdrive_calculated = bound1(breath.read() * breath_to_overdrive +
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
  wave1.frequencyModulation(lfo_max_range * bound1(lfo1_range + breath_to_lfo1_range * breath.read() + modulation_to_lfo1_range * modulation.read() + expression_to_lfo1_range * expression.read()));
  wave2.frequencyModulation(lfo_max_range * bound1(lfo2_range + breath_to_lfo2_range * breath.read() + modulation_to_lfo2_range * modulation.read() + expression_to_lfo2_range * expression.read()));
  //LFO2
  lfo2.frequency(lfo_max_freq * (lfo2_freq + bound1(breath_to_lfo2_freq * breath.read() + modulation_to_lfo2_freq * modulation.read() + expression_to_lfo2_freq * expression.read())));
  lfo2.amplitude(bound1(lfo2_gain + bound1(breath_to_lfo2_gain * breath.read() + modulation_to_lfo2_gain * modulation.read() + expression_to_lfo2_gain * expression.read())));
  wave3.frequencyModulation(lfo2_range * lfo_max_range) ;
  wave4.frequencyModulation(lfo2_range * lfo_max_range)  ;      
            
  mixer1.gain(0, 1);
  mixer1.gain(1, noise_pink_gain);
  mixer1.gain(2, noise_white_gain); 
                              
  waveshape_mixer1.gain(0, bound1(waveshape1_gain*(overdrive_calculated*waveshape_modulation_multiplier + waveshape_modulation_multiplier_offset)));
  waveshape_mixer1.gain(1, bound1(waveshape2_gain*(overdrive_calculated*waveshape_modulation_multiplier + waveshape_modulation_multiplier_offset)));
  waveshape_mixer1.gain(2, bound1(waveshape3_gain*(overdrive_calculated*waveshape_modulation_multiplier + waveshape_modulation_multiplier_offset)));
  waveshape_mixer1.gain(3, bound1(waveshape4_gain*(overdrive_calculated*waveshape_modulation_multiplier + waveshape_modulation_multiplier_offset)));
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
