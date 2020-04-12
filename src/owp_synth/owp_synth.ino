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
 * See https://github.com/jeffmhopkins/Open-Woodwind-Project/tree/master/src/osc_configuration_for_linux_touchosc
 * 
 * I run an osc2midi and midi2osc bridge on a linux box for the mapping. 
 * https://github.com/jeffmhopkins/Open-Woodwind-Project/tree/master/src/osc_configuration_for_linux_touchosc
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
#define CC_WAVESHAPE_MODULATION_MULTIPLIER        100
#define CC_WAVESHAPE_MODULATION_MULTIPLIER_OFFSET 101
#define CC_WAVESHAPE_CLEAN_GAIN                   102
#define CC_LFO1_DESTINATION_FREQUENCY     103
#define CC_LFO1_DESTINATION_GAIN          104
#define CC_LFO1_DESTINATION_FILTER        105
#define CC_LFO2_DESTINATION_FREQUENCY     106
#define CC_LFO2_DESTINATION_GAIN          107
#define CC_LFO2_DESTINATION_FILTER        108
#define CC_LFO_RESET_PHASE_ON_NEW_NOTE    109


extern float driven_waveform1[257];
extern float driven_waveform2[257];
extern float driven_waveform3[257];

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSine   lfo2;           //xy=64.00391006469727,448.9999942779541
AudioSynthWaveformSine   lfo1;           //xy=77.00386810302734,98.00000953674316
AudioAmplifier           lfo2_destination_frequency_amp; //xy=281.00390625,485.00390625
AudioAmplifier           lfo1_destination_frequency_amp;           //xy=287.0039291381836,143.00390529632568
AudioAmplifier           lfo2_destination_filter_amp; //xy=289.00390625,520.00390625
AudioAmplifier           lfo2_destination_gain_amp;  //xy=291.00390625,449.00390625
AudioAmplifier           lfo1_destination_gain_amp; //xy=295.00390625,105.00390625
AudioAmplifier           lfo1_destination_filter_amp; //xy=301.00391387939453,187.0039119720459
AudioSynthWaveformDc     glide_frequency; //xy=300.00393295288086,840.0000286102295
AudioSynthWaveformDc     wave1_gain_dc;            //xy=319.00389862060547,21.9999942779541
AudioSynthWaveformDc     wave2_gain_dc; //xy=321.00390625,64.00390625
AudioSynthWaveformDc     expression;     //xy=320.00393295288086,761.0000286102295
AudioSynthWaveformDc     wave4_gain_dc; //xy=321.00390625,594.0038967132568
AudioSynthWaveformDc     modulation;     //xy=321.00393295288086,680.0000286102295
AudioSynthWaveformDc     wave1_width;    //xy=323.0039176940918,249.99999052286148
AudioSynthWaveformDc     wave3_gain_dc; //xy=322.00391387939453,557.0038976669312
AudioSynthWaveformDc     pitchbend;      //xy=323.00393295288086,800.0000286102295
AudioSynthWaveformDc     wave3_width;    //xy=325.0039119720459,356.99999782443047
AudioSynthWaveformDc     wave4_width;    //xy=325.0039119720459,388.99999782443047
AudioSynthWaveformDc     wave2_width;    //xy=326.0039119720459,288.99999782443047
AudioSynthWaveformDc     breath;         //xy=327.00393295288086,721.0000286102295
AudioMixer4              dc_smoothing2;  //xy=495.00393295288086,847.0000286102295
AudioMixer4              dc_smoothing1;  //xy=499.00393295288086,734.0000286102295
AudioSynthWaveformModulated wave2;          //xy=527.0039119720459,287.99999782443047
AudioSynthWaveformModulated wave1;          //xy=528.0039119720459,240.99999782443047
AudioSynthWaveformModulated wave4;          //xy=529.0039119720459,377.99999782443047
AudioSynthWaveformModulated wave3;          //xy=533.0039119720459,331.99999782443047
AudioMixer4              lfo1_wave2_multiplier_mixer;         //xy=580.0039024353027,115.00390815734863
AudioMixer4              lfo1_wave1_multiplier_mixer;         //xy=584.00390625,34.00390625
AudioMixer4              lfo2_wave3_multiplier_mixer; //xy=591.00390625,455.00390625
AudioMixer4              lfo2_wave4_multiplier_mixer; //xy=591.0038909912109,540.003927230835
AudioEffectMultiply      wave2_lfo1_multiply;      //xy=840.0039520263672,278.00390911102295
AudioEffectMultiply      wave4_lfo2_multiply; //xy=842.00390625,365.00390625
AudioEffectMultiply      wave1_lfo1_multiply;      //xy=844.0039520263672,241.00393199920654
AudioEffectMultiply      wave3_lfo2_multiply; //xy=845.00390625,325.00390625
AudioSynthNoisePink      noise_pink;     //xy=1111.0038585662842,346.0000095665455
AudioSynthNoiseWhite     noise_white;    //xy=1118.0038585662842,388.0000095665455
AudioMixer4              waveselect;     //xy=1130.003900527954,278.00002643465996
AudioMixer4              mixer1;         //xy=1282.0038585662842,339.0000095665455
AudioEffectWaveshaper    waveshape1;     //xy=1471.0038585662842,398.0000095665455
AudioEffectWaveshaper    waveshape2;     //xy=1471.0038585662842,429.0000095665455
AudioEffectWaveshaper    waveshape4;     //xy=1472.0038585662842,493.0000095665455
AudioEffectWaveshaper    waveshape3;     //xy=1474.0038585662842,461.0000095665455
AudioSynthWaveformDc     filter_frequency; //xy=1649.0039596557617,516.0000429153442
AudioMixer4              waveshape_mixer1; //xy=1656.0038585662842,440.0000095665455
AudioMixer4              waveshape_mixer2; //xy=1741.0038986206055,299.00001335144043
AudioAmplifier           amp1;           //xy=1914.0039520263672,288.00002098083496
AudioMixer4              filter_frequency_lfo_mixer;         //xy=1970.00390625,423.00393295288086
AudioFilterStateVariable filter1;        //xy=2059.0038986206055,299.00390434265137
AudioEffectDelay         delay1;         //xy=2249.004020690918,470.99999618530273
AudioEffectChorus        chorus1;        //xy=2362.004020690918,388.99999618530273
AudioEffectFlange        flange1;        //xy=2364.004020690918,344.99999618530273
AudioMixer4              delay_mixer1;   //xy=2400.004020690918,444.99999618530273
AudioMixer4              effect_mixer;   //xy=2548.004020690918,338.99999618530273
AudioPlaySdWav           wavplayer;      //xy=2625.004020690918,419.99999618530273
AudioEffectFreeverbStereo reverb;         //xy=2730.004020690918,284.99999618530273
AudioMixer4              left;           //xy=2924.004020690918,360.99999618530273
AudioMixer4              right;          //xy=2928.004020690918,433.99999618530273
AudioOutputI2S           audio_output;   //xy=3072.004020690918,389.99999618530273
AudioConnection          patchCord1(lfo2, lfo2_destination_gain_amp);
AudioConnection          patchCord2(lfo2, lfo2_destination_frequency_amp);
AudioConnection          patchCord3(lfo2, lfo2_destination_filter_amp);
AudioConnection          patchCord4(lfo1, lfo1_destination_frequency_amp);
AudioConnection          patchCord5(lfo1, lfo1_destination_gain_amp);
AudioConnection          patchCord6(lfo1, lfo1_destination_filter_amp);
AudioConnection          patchCord7(lfo2_destination_frequency_amp, 0, wave3, 0);
AudioConnection          patchCord8(lfo2_destination_frequency_amp, 0, wave4, 0);
AudioConnection          patchCord9(lfo1_destination_frequency_amp, 0, wave1, 0);
AudioConnection          patchCord10(lfo1_destination_frequency_amp, 0, wave2, 0);
AudioConnection          patchCord11(lfo2_destination_filter_amp, 0, filter_frequency_lfo_mixer, 2);
AudioConnection          patchCord12(lfo2_destination_gain_amp, 0, lfo2_wave3_multiplier_mixer, 1);
AudioConnection          patchCord13(lfo2_destination_gain_amp, 0, lfo2_wave4_multiplier_mixer, 1);
AudioConnection          patchCord14(lfo1_destination_gain_amp, 0, lfo1_wave1_multiplier_mixer, 1);
AudioConnection          patchCord15(lfo1_destination_gain_amp, 0, lfo1_wave2_multiplier_mixer, 1);
AudioConnection          patchCord16(lfo1_destination_filter_amp, 0, filter_frequency_lfo_mixer, 1);
AudioConnection          patchCord17(glide_frequency, 0, dc_smoothing2, 1);
AudioConnection          patchCord18(wave1_gain_dc, 0, lfo1_wave1_multiplier_mixer, 0);
AudioConnection          patchCord19(wave2_gain_dc, 0, lfo1_wave2_multiplier_mixer, 0);
AudioConnection          patchCord20(expression, 0, dc_smoothing1, 2);
AudioConnection          patchCord21(wave4_gain_dc, 0, lfo2_wave4_multiplier_mixer, 0);
AudioConnection          patchCord22(modulation, 0, dc_smoothing1, 0);
AudioConnection          patchCord23(wave1_width, 0, wave1, 1);
AudioConnection          patchCord24(wave3_gain_dc, 0, lfo2_wave3_multiplier_mixer, 0);
AudioConnection          patchCord25(pitchbend, 0, dc_smoothing2, 0);
AudioConnection          patchCord26(wave3_width, 0, wave3, 1);
AudioConnection          patchCord27(wave4_width, 0, wave4, 1);
AudioConnection          patchCord28(wave2_width, 0, wave2, 1);
AudioConnection          patchCord29(breath, 0, dc_smoothing1, 1);
AudioConnection          patchCord30(wave2, 0, wave2_lfo1_multiply, 1);
AudioConnection          patchCord31(wave1, 0, wave1_lfo1_multiply, 1);
AudioConnection          patchCord32(wave4, 0, wave4_lfo2_multiply, 1);
AudioConnection          patchCord33(wave3, 0, wave3_lfo2_multiply, 1);
AudioConnection          patchCord34(lfo1_wave2_multiplier_mixer, 0, wave2_lfo1_multiply, 0);
AudioConnection          patchCord35(lfo1_wave1_multiplier_mixer, 0, wave1_lfo1_multiply, 0);
AudioConnection          patchCord36(lfo2_wave3_multiplier_mixer, 0, wave3_lfo2_multiply, 0);
AudioConnection          patchCord37(lfo2_wave4_multiplier_mixer, 0, wave4_lfo2_multiply, 0);
AudioConnection          patchCord38(wave2_lfo1_multiply, 0, waveselect, 1);
AudioConnection          patchCord39(wave4_lfo2_multiply, 0, waveselect, 3);
AudioConnection          patchCord40(wave1_lfo1_multiply, 0, waveselect, 0);
AudioConnection          patchCord41(wave3_lfo2_multiply, 0, waveselect, 2);
AudioConnection          patchCord42(noise_pink, 0, mixer1, 1);
AudioConnection          patchCord43(noise_white, 0, mixer1, 2);
AudioConnection          patchCord44(waveselect, 0, mixer1, 0);
AudioConnection          patchCord45(mixer1, waveshape1);
AudioConnection          patchCord46(mixer1, waveshape2);
AudioConnection          patchCord47(mixer1, 0, waveshape_mixer2, 0);
AudioConnection          patchCord48(mixer1, waveshape3);
AudioConnection          patchCord49(mixer1, waveshape4);
AudioConnection          patchCord50(waveshape1, 0, waveshape_mixer1, 0);
AudioConnection          patchCord51(waveshape2, 0, waveshape_mixer1, 1);
AudioConnection          patchCord52(waveshape4, 0, waveshape_mixer1, 3);
AudioConnection          patchCord53(waveshape3, 0, waveshape_mixer1, 2);
AudioConnection          patchCord54(filter_frequency, 0, filter_frequency_lfo_mixer, 0);
AudioConnection          patchCord55(waveshape_mixer1, 0, waveshape_mixer2, 1);
AudioConnection          patchCord56(waveshape_mixer2, amp1);
AudioConnection          patchCord57(amp1, 0, filter1, 0);
AudioConnection          patchCord58(filter_frequency_lfo_mixer, 0, filter1, 1);
AudioConnection          patchCord59(filter1, 0, effect_mixer, 0);
AudioConnection          patchCord60(filter1, 0, flange1, 0);
AudioConnection          patchCord61(filter1, 0, chorus1, 0);
AudioConnection          patchCord62(filter1, 0, delay1, 0);
AudioConnection          patchCord63(delay1, 0, delay_mixer1, 0);
AudioConnection          patchCord64(delay1, 1, delay_mixer1, 1);
AudioConnection          patchCord65(delay1, 2, delay_mixer1, 2);
AudioConnection          patchCord66(delay1, 3, delay_mixer1, 3);
AudioConnection          patchCord67(chorus1, 0, effect_mixer, 2);
AudioConnection          patchCord68(flange1, 0, effect_mixer, 1);
AudioConnection          patchCord69(delay_mixer1, 0, effect_mixer, 3);
AudioConnection          patchCord70(effect_mixer, reverb);
AudioConnection          patchCord71(effect_mixer, 0, left, 0);
AudioConnection          patchCord72(effect_mixer, 0, right, 0);
AudioConnection          patchCord73(wavplayer, 0, left, 2);
AudioConnection          patchCord74(wavplayer, 1, right, 2);
AudioConnection          patchCord75(reverb, 0, left, 1);
AudioConnection          patchCord76(reverb, 1, right, 1);
AudioConnection          patchCord77(left, 0, audio_output, 0);
AudioConnection          patchCord78(right, 0, audio_output, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1563.0039443969727,51.00000476837158
// GUItool: end automatically generated code





//Global Variables - Settings (You can change these to set startup conditions)
float lfo_reset_phase_on_new_note    = 1.0; //float makes the cc easier
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
float filter_max_frequency           = 25000;
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
float waveshape_clean_gain           = 0.0;
float lfo1_destination_gain          = 0.0;
float lfo1_destination_frequency     = 0.0;
float lfo1_destination_filter        = 0.0;
float lfo2_destination_gain          = 0.0; 
float lfo2_destination_frequency     = 0.0;
float lfo2_destination_filter        = 0.0;

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

  //New Filter Test
  filter1.frequency(filter_min_frequency);
  filter1.resonance(0.707);
  filter1.octaveControl(7);
  
  amp1.gain(0.0);
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
  wave1.amplitude(1.0);
  wave2.amplitude(1.0);
  wave3.amplitude(1.0);
  wave4.amplitude(1.0);
  lfo1_destination_gain_amp.gain(0.0);
  lfo1_destination_frequency_amp.gain(0.0);
  lfo1_destination_filter_amp.gain(0.0);
  lfo2_destination_gain_amp.gain(0.0);
  lfo2_destination_frequency_amp.gain(0.0);
  lfo2_destination_filter_amp.gain(0.0);
  
  wave1_gain_dc.amplitude(1.0);
  wave2_gain_dc.amplitude(1.0);
  wave3_gain_dc.amplitude(1.0);
  wave4_gain_dc.amplitude(1.0);
  lfo1_wave1_multiplier_mixer.gain(0,1.0);
  lfo1_wave1_multiplier_mixer.gain(1,1.0);
  lfo1_wave2_multiplier_mixer.gain(0,1.0);
  lfo1_wave2_multiplier_mixer.gain(1,1.0);
  lfo2_wave3_multiplier_mixer.gain(0,1.0);
  lfo2_wave3_multiplier_mixer.gain(1,1.0);
  lfo2_wave4_multiplier_mixer.gain(0,1.0);
  lfo2_wave4_multiplier_mixer.gain(1,1.0);
  filter_frequency_lfo_mixer.gain(0,1.0);
  filter_frequency_lfo_mixer.gain(1,1.0);
  filter_frequency_lfo_mixer.gain(2,1.0);
  
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
        waveshape1.shape(driven_waveform1, 257);
  waveshape_mixer1.gain(1, waveshape2_gain);      
        waveshape2.shape(driven_waveform2, 257);
  waveshape_mixer1.gain(2, waveshape3_gain);
        waveshape3.shape(driven_waveform3, 257);
  waveshape_mixer1.gain(3, waveshape4_gain);
        waveshape4.shape(driven_waveform3, 257);
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
  
  loadPatchSD(1);
  
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
  wave1.amplitude(wave1_gain);
  wave2.amplitude(wave2_gain);
  wave3.amplitude(wave3_gain);
  wave4.amplitude(wave4_gain);
  amp1.gain(breath.read());
  lfo1_destination_gain_amp.gain(lfo1_destination_gain);
  lfo1_destination_frequency_amp.gain(lfo1_destination_frequency);
  lfo1_destination_filter_amp.gain(lfo1_destination_filter);
  lfo2_destination_gain_amp.gain(lfo2_destination_gain);
  lfo2_destination_frequency_amp.gain(lfo2_destination_frequency);
  lfo2_destination_filter_amp.gain(lfo2_destination_filter);
  waveselect.gain(0, wave1_gain);
  waveselect.gain(1, wave2_gain);
  waveselect.gain(2, wave3_gain);
  waveselect.gain(3, wave4_gain);
  wave1_width.amplitude(wave1_pulse_width + pulsewidth_calculated);
  wave2_width.amplitude(wave2_pulse_width + pulsewidth_calculated);
  wave3_width.amplitude(wave3_pulse_width + pulsewidth_calculated);
  wave4_width.amplitude(wave4_pulse_width + pulsewidth_calculated);
  wave1.frequency(glide_frequency.read() * pitchbend_multiplier * wave1_detune_multiplier * wave_freq * default_tune);
  wave2.frequency(glide_frequency.read() * pitchbend_multiplier * wave2_detune_multiplier * wave_freq * default_tune);
  wave3.frequency(glide_frequency.read() * pitchbend_multiplier * wave3_detune_multiplier * wave_freq * default_tune);
  wave4.frequency(glide_frequency.read() * pitchbend_multiplier * wave4_detune_multiplier * wave_freq * default_tune);
  noise_pink.amplitude(breath.read());
  noise_white.amplitude(breath.read());
 filter_frequency.amplitude(filter_min_frequency, filter_frequency_ramp_rate);               
 
 filter_frequency.amplitude(bound1(filter_min_frequency + bound1(breath_to_filter_cutoff * breath.read() + 
                                    modulation_to_filter_cutoff * modulation.read() +
                                    expression_to_filter_cutoff * expression.read())), filter_frequency_ramp_rate);   
  filter1.resonance(2*bound1(filter_q + breath_to_filter_resonance * breath.read() +
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
  
  waveshape_mixer2.gain(0, waveshape_clean_gain);
  
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
