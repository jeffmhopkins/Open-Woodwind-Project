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
#define CC_BREATH_TO_WAVE3_WAVE4_GAIN     110
#define CC_MODULATION_TO_WAVE3_WAVE4_GAIN 111
#define CC_EXPRESSION_TO_WAVE3_WAVE4_GAIN 112

extern const float driven_waveform1[257];
extern const float driven_waveform2[257];
extern const float driven_waveform3[257];
extern const float wave_shape_tube_12at7[513];
extern const float wave_shape_tube_6v6[513];
extern const float wave_shape_tube_12au7[513];
extern const float wave_shape_tube_kt88[513];
extern const float wave_shape_tube_12ax7_1025[1025];

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformDc     breath;         //xy=789.584228515625,1003.5000333786011
AudioSynthWaveformDc     modulation;     //xy=791.5006713867188,1037.5835056304932
AudioSynthWaveformDc     expression;     //xy=792.8340072631836,1084.4722480773926
AudioSynthWaveformDc     glide_frequency; //xy=1022.3341293334961,1217.4171905517578
AudioSynthWaveformDc     pitchbend;      //xy=1043.7786979675293,1187.4169292449951
AudioMixer4              dc_smoothing1; //xy=1213.111717224121,1218.8613891601562
AudioSynthWaveformSine   lfo2;           //xy=1293.13920211792,730.6390647888184
AudioSynthWaveformSine   lfo1;           //xy=1307.2223892211914,394.1112117767334
AudioMixer4              wave3_wave4_gain_modulation_mixer; //xy=1340.1668701171875,815.2779159545898
AudioAmplifier           lfo2_destination_filter_amp; //xy=1619.9725036621094,1181.3333530426025
AudioAmplifier           lfo1_destination_filter_amp; //xy=1620.7501678466797,1142.1111145019531
AudioSynthWaveformDc     wave4_gain_dc;  //xy=1631.2780303955078,840.222225189209
AudioSynthWaveformDc     wave3_gain_dc;  //xy=1634.4448318481445,765.7223167419434
AudioSynthWaveformDc     filter_frequency; //xy=1665.7776260375977,1107.8890781402588
AudioAmplifier           lfo1_destination_gain_amp; //xy=1848.000099182129,362.0000305175781
AudioAmplifier           lfo2_destination_gain_amp; //xy=1850.8613891601562,734.0277872085571
AudioEffectMultiply      wave3_gain_multiply;      //xy=1864.1669235229492,801.9167346954346
AudioAmplifier           lfo1_destination_frequency_amp; //xy=1867.000099182129,397.0000305175781
AudioEffectMultiply      wave4_gain_multiply;      //xy=1867.1668701171875,839.4444465637207
AudioAmplifier           lfo2_destination_frequency_amp; //xy=1870.194808959961,694.8890609741211
AudioSynthWaveformDc     wave1_gain_dc;  //xy=1872.000099182129,278.0000305175781
AudioSynthWaveformDc     wave2_gain_dc;  //xy=1874.000099182129,321.0000305175781
AudioMixer4              filter_frequency_lfo_mixer; //xy=1894.7776260375977,1147.8890781402588
AudioSynthWaveformDc     wave4_width;    //xy=1960.416862487793,631.7779607772827
AudioSynthWaveformDc     wave2_width;    //xy=1961.0001983642578,534.6667757034302
AudioSynthWaveformDc     wave1_width;    //xy=1962.000099182129,489.0000305175781
AudioSynthWaveformDc     wave3_width;    //xy=1965.3335037231445,587.3334436416626
AudioMixer4              lfo1_wave2_multiplier_mixer; //xy=2201.000099182129,366.0000305175781
AudioSynthWaveformModulated wave2;          //xy=2202.000099182129,532.0000305175781
AudioMixer4              lfo1_wave1_multiplier_mixer; //xy=2203.000099182129,297.0000305175781
AudioSynthWaveformModulated wave1;          //xy=2203.000099182129,485.0000305175781
AudioSynthWaveformModulated wave4;          //xy=2203.722225189209,617.1390113830566
AudioSynthWaveformModulated wave3;          //xy=2208.000099182129,576.0000305175781
AudioMixer4              lfo2_wave4_multiplier_mixer; //xy=2229.000114440918,816.0000228881836
AudioMixer4              lfo2_wave3_multiplier_mixer; //xy=2231.944580078125,740.7777976989746
AudioEffectMultiply      wave2_lfo1_multiply; //xy=2515.000099182129,523.0000305175781
AudioEffectMultiply      wave4_lfo2_multiply; //xy=2517.000099182129,610.0000305175781
AudioEffectMultiply      wave1_lfo1_multiply; //xy=2519.000099182129,486.0000305175781
AudioEffectMultiply      wave3_lfo2_multiply; //xy=2520.000099182129,570.0000305175781
AudioSynthNoiseWhite     noise_white;    //xy=2785.000099182129,633.0000305175781
AudioSynthNoisePink      noise_pink;     //xy=2786.000099182129,591.0000305175781
AudioMixer4              waveselect;     //xy=2805.000099182129,523.0000305175781
AudioMixer4              wave_noise_mixer;         //xy=2983.000160217285,575.0000648498535
AudioSynthNoiseWhite     noise_white2;   //xy=3207.000160217285,599.0000677108765
AudioEffectWaveshaper    waveshape1;     //xy=3211.000160217285,640.0000677108765
AudioEffectWaveshaper    waveshape2;     //xy=3211.000160217285,671.0000677108765
AudioEffectWaveshaper    waveshape3;     //xy=3214.000160217285,703.0000677108765
AudioEffectWaveshaper    waveshape4;     //xy=3216.000160217285,743.0000677108765
AudioEffectDigitalCombine combine1;       //xy=3355.0001678466797,606.0001487731934
AudioMixer4              waveshape_mixer1; //xy=3539.000175476074,638.000150680542
AudioMixer4              waveshape_mixer2; //xy=3730.000503540039,578.0000648498535
AudioEffectMultiply      vca;      //xy=3903.7778930664062,782.6667633056641
AudioFilterStateVariable filter1;        //xy=4036.000476837158,839.4446029663086
AudioEffectDelay         delay1;         //xy=4176.000434875488,746.8889236450195
AudioEffectChorus        chorus1;        //xy=4206.333839416504,635.1111660003662
AudioEffectFlange        flange1;        //xy=4208.333812713623,592.4444961547852
AudioMixer4              delay_mixer1;   //xy=4327.000434875488,720.8889236450195
AudioMixer4              effect_mixer;   //xy=4450.333831787109,478.88891220092773
AudioPlaySdWav           wavplayer;      //xy=4548.000434875488,601.8889236450195
AudioEffectFreeverbStereo reverb;         //xy=4603.000434875488,542.8889236450195
AudioMixer4              left;           //xy=4841.000434875488,492.88892364501953
AudioMixer4              right;          //xy=4841.000434875488,583.8889236450195
AudioOutputI2S           audio_output;   //xy=4999.000434875488,535.8889236450195
AudioConnection          patchCord1(breath, 0, vca, 1);
AudioConnection          patchCord2(breath, 0, wave3_wave4_gain_modulation_mixer, 0);
AudioConnection          patchCord3(modulation, 0, wave3_wave4_gain_modulation_mixer, 1);
AudioConnection          patchCord4(expression, 0, wave3_wave4_gain_modulation_mixer, 2);
AudioConnection          patchCord5(glide_frequency, 0, dc_smoothing1, 1);
AudioConnection          patchCord6(pitchbend, 0, dc_smoothing1, 0);
AudioConnection          patchCord7(lfo2, lfo2_destination_gain_amp);
AudioConnection          patchCord8(lfo2, lfo2_destination_frequency_amp);
AudioConnection          patchCord9(lfo2, lfo2_destination_filter_amp);
AudioConnection          patchCord10(lfo1, lfo1_destination_frequency_amp);
AudioConnection          patchCord11(lfo1, lfo1_destination_gain_amp);
AudioConnection          patchCord12(lfo1, lfo1_destination_filter_amp);
AudioConnection          patchCord13(wave3_wave4_gain_modulation_mixer, 0, wave3_gain_multiply, 1);
AudioConnection          patchCord14(wave3_wave4_gain_modulation_mixer, 0, wave4_gain_multiply, 1);
AudioConnection          patchCord15(lfo2_destination_filter_amp, 0, filter_frequency_lfo_mixer, 2);
AudioConnection          patchCord16(lfo1_destination_filter_amp, 0, filter_frequency_lfo_mixer, 1);
AudioConnection          patchCord17(wave4_gain_dc, 0, wave4_gain_multiply, 0);
AudioConnection          patchCord18(wave3_gain_dc, 0, wave3_gain_multiply, 0);
AudioConnection          patchCord19(filter_frequency, 0, filter_frequency_lfo_mixer, 0);
AudioConnection          patchCord20(lfo1_destination_gain_amp, 0, lfo1_wave1_multiplier_mixer, 1);
AudioConnection          patchCord21(lfo1_destination_gain_amp, 0, lfo1_wave2_multiplier_mixer, 1);
AudioConnection          patchCord22(lfo2_destination_gain_amp, 0, lfo2_wave3_multiplier_mixer, 1);
AudioConnection          patchCord23(lfo2_destination_gain_amp, 0, lfo2_wave4_multiplier_mixer, 1);
AudioConnection          patchCord24(wave3_gain_multiply, 0, lfo2_wave3_multiplier_mixer, 0);
AudioConnection          patchCord25(lfo1_destination_frequency_amp, 0, wave1, 0);
AudioConnection          patchCord26(lfo1_destination_frequency_amp, 0, wave2, 0);
AudioConnection          patchCord27(wave4_gain_multiply, 0, lfo2_wave4_multiplier_mixer, 0);
AudioConnection          patchCord28(lfo2_destination_frequency_amp, 0, wave3, 0);
AudioConnection          patchCord29(lfo2_destination_frequency_amp, 0, wave4, 0);
AudioConnection          patchCord30(wave1_gain_dc, 0, lfo1_wave1_multiplier_mixer, 0);
AudioConnection          patchCord31(wave2_gain_dc, 0, lfo1_wave2_multiplier_mixer, 0);
AudioConnection          patchCord32(filter_frequency_lfo_mixer, 0, filter1, 1);
AudioConnection          patchCord33(wave4_width, 0, wave4, 1);
AudioConnection          patchCord34(wave2_width, 0, wave2, 1);
AudioConnection          patchCord35(wave1_width, 0, wave1, 1);
AudioConnection          patchCord36(wave3_width, 0, wave3, 1);
AudioConnection          patchCord37(lfo1_wave2_multiplier_mixer, 0, wave2_lfo1_multiply, 0);
AudioConnection          patchCord38(wave2, 0, wave2_lfo1_multiply, 1);
AudioConnection          patchCord39(lfo1_wave1_multiplier_mixer, 0, wave1_lfo1_multiply, 0);
AudioConnection          patchCord40(wave1, 0, wave1_lfo1_multiply, 1);
AudioConnection          patchCord41(wave4, 0, wave4_lfo2_multiply, 1);
AudioConnection          patchCord42(wave3, 0, wave3_lfo2_multiply, 1);
AudioConnection          patchCord43(lfo2_wave4_multiplier_mixer, 0, wave4_lfo2_multiply, 0);
AudioConnection          patchCord44(lfo2_wave3_multiplier_mixer, 0, wave3_lfo2_multiply, 0);
AudioConnection          patchCord45(wave2_lfo1_multiply, 0, waveselect, 1);
AudioConnection          patchCord46(wave4_lfo2_multiply, 0, waveselect, 3);
AudioConnection          patchCord47(wave1_lfo1_multiply, 0, waveselect, 0);
AudioConnection          patchCord48(wave3_lfo2_multiply, 0, waveselect, 2);
AudioConnection          patchCord49(noise_white, 0, wave_noise_mixer, 2);
AudioConnection          patchCord50(noise_pink, 0, wave_noise_mixer, 1);
AudioConnection          patchCord51(waveselect, 0, wave_noise_mixer, 0);
AudioConnection          patchCord52(wave_noise_mixer, waveshape1);
AudioConnection          patchCord53(wave_noise_mixer, waveshape2);
AudioConnection          patchCord54(wave_noise_mixer, 0, waveshape_mixer2, 0);
AudioConnection          patchCord55(wave_noise_mixer, waveshape3);
AudioConnection          patchCord56(wave_noise_mixer, waveshape4);
AudioConnection          patchCord57(noise_white2, 0, combine1, 0);
AudioConnection          patchCord58(waveshape1, 0, combine1, 1);
AudioConnection          patchCord59(waveshape2, 0, waveshape_mixer1, 1);
AudioConnection          patchCord60(waveshape3, 0, waveshape_mixer1, 2);
AudioConnection          patchCord61(waveshape4, 0, waveshape_mixer1, 3);
AudioConnection          patchCord62(combine1, 0, waveshape_mixer1, 0);
AudioConnection          patchCord63(waveshape_mixer1, 0, waveshape_mixer2, 1);
AudioConnection          patchCord64(waveshape_mixer2, 0, vca, 0);
AudioConnection          patchCord65(vca, 0, filter1, 0);
AudioConnection          patchCord66(filter1, 0, effect_mixer, 0);
AudioConnection          patchCord67(filter1, 0, flange1, 0);
AudioConnection          patchCord68(filter1, 0, chorus1, 0);
AudioConnection          patchCord69(filter1, 0, delay1, 0);
AudioConnection          patchCord70(delay1, 0, delay_mixer1, 0);
AudioConnection          patchCord71(delay1, 1, delay_mixer1, 1);
AudioConnection          patchCord72(delay1, 2, delay_mixer1, 2);
AudioConnection          patchCord73(delay1, 3, delay_mixer1, 3);
AudioConnection          patchCord74(chorus1, 0, effect_mixer, 2);
AudioConnection          patchCord75(flange1, 0, effect_mixer, 1);
AudioConnection          patchCord76(delay_mixer1, 0, effect_mixer, 3);
AudioConnection          patchCord77(effect_mixer, reverb);
AudioConnection          patchCord78(effect_mixer, 0, left, 0);
AudioConnection          patchCord79(effect_mixer, 0, right, 0);
AudioConnection          patchCord80(wavplayer, 0, left, 2);
AudioConnection          patchCord81(wavplayer, 1, right, 2);
AudioConnection          patchCord82(reverb, 0, left, 1);
AudioConnection          patchCord83(reverb, 1, right, 1);
AudioConnection          patchCord84(left, 0, audio_output, 0);
AudioConnection          patchCord85(right, 0, audio_output, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=3238.000099182129,296.0000305175781
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
float breath_to_wave3_wave4_gain     = 0.0;
float modulation_to_wave3_wave4_gain = 0.0;
float expression_to_wave4_wave4_gain = 0.0;

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
  wave3_wave4_gain_modulation_mixer.gain(0, 1.0);//Breath
  wave3_wave4_gain_modulation_mixer.gain(1, 0.0);//Modulation
  wave3_wave4_gain_modulation_mixer.gain(2, 0.0);//Expression
  wave3_wave4_gain_modulation_mixer.gain(3, 0.0);
  filter1.frequency(filter_min_frequency);
  filter1.resonance(0.707);
  filter1.octaveControl(14);
  combine1.setCombineMode(AudioEffectDigitalCombine::OR);
  noise_white2.amplitude(1.0);
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
  wave_noise_mixer.gain(0, 1);//waveforms
  wave_noise_mixer.gain(1, noise_pink_gain);//pink noise
  wave_noise_mixer.gain(2, noise_white_gain);//white noise
  wave_noise_mixer.gain(3, 0);//nc
  waveshape_mixer1.gain(0, waveshape1_gain);
        waveshape1.shape((float *)wave_shape_tube_6v6, 513);
  waveshape_mixer1.gain(1, waveshape2_gain);      
        waveshape2.shape((float *)wave_shape_tube_6v6, 513);
  waveshape_mixer1.gain(2, waveshape3_gain);
        waveshape3.shape((float *)wave_shape_tube_6v6, 513);
  waveshape_mixer1.gain(3, waveshape4_gain);
        waveshape4.shape((float *)wave_shape_tube_12ax7_1025, 1025);
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
  wave3_wave4_gain_modulation_mixer.gain(0, breath_to_wave3_wave4_gain);//Breath
  wave3_wave4_gain_modulation_mixer.gain(1, modulation_to_wave3_wave4_gain);//Modulation
  wave3_wave4_gain_modulation_mixer.gain(2, expression_to_wave4_wave4_gain);//Expression
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
  filter_frequency.amplitude(bound1(filter_min_frequency + bound1(breath_to_filter_cutoff * breath.read() + 
                                    modulation_to_filter_cutoff * modulation.read() +
                                    expression_to_filter_cutoff * expression.read())), filter_frequency_ramp_rate);   
  filter1.resonance(2*bound1(filter_q + breath_to_filter_resonance * breath.read() +
                                      modulation_to_filter_resonance * modulation.read() +
                                      expression_to_filter_resonance * expression.read()));
  lfo1.frequency(lfo_max_freq * (lfo1_freq + bound1(breath_to_lfo1_freq * breath.read() + modulation_to_lfo1_freq * modulation.read() + expression_to_lfo1_freq * expression.read())));
  lfo1.amplitude(bound1(lfo1_gain + bound1(breath_to_lfo1_gain * breath.read() + modulation_to_lfo1_gain * modulation.read() + expression_to_lfo1_gain * expression.read())));
  wave1.frequencyModulation(lfo_max_range * bound1(lfo1_range + breath_to_lfo1_range * breath.read() + modulation_to_lfo1_range * modulation.read() + expression_to_lfo1_range * expression.read()));
  wave2.frequencyModulation(lfo_max_range * bound1(lfo2_range + breath_to_lfo2_range * breath.read() + modulation_to_lfo2_range * modulation.read() + expression_to_lfo2_range * expression.read()));
  lfo2.frequency(lfo_max_freq * (lfo2_freq + bound1(breath_to_lfo2_freq * breath.read() + modulation_to_lfo2_freq * modulation.read() + expression_to_lfo2_freq * expression.read())));
  lfo2.amplitude(bound1(lfo2_gain + bound1(breath_to_lfo2_gain * breath.read() + modulation_to_lfo2_gain * modulation.read() + expression_to_lfo2_gain * expression.read())));
  wave3.frequencyModulation(lfo2_range * lfo_max_range);
  wave4.frequencyModulation(lfo2_range * lfo_max_range); 
  wave_noise_mixer.gain(0, 1);
  wave_noise_mixer.gain(1, noise_pink_gain);
  wave_noise_mixer.gain(2, noise_white_gain);       
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
