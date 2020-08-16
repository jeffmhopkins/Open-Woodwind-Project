/*
 * The Open Woodwind Project - OWP_Synth for Woodwind Controllers by Jeff Hopkins
 * 
 * =============================================================================================================================================
 * 
 * The OWP_Synth is a MIDI synthesizer that runs on a Teensy 4.0 + Audio Shield Rev.D, specially designed for working with the OWP controller.
 * It will eventually also run the controller software on top of the synth, but for now it's standalone.
 * 
 * It's meant to be controlled via the OSC interface on an iPad, and uses an SD card from the Audio Shield to store patches and backing tracks.
 * 
 * Some features:
 *     -Four Oscillators
 *     -Two LFOs
 *     -Six cascaded and mixed overdrive waveform shapers
 *     -LOTS of modulation settings
 *     -Flange, String Chorus, Delay and Reverb effects
 *     
 * =============================================================================================================================================
 * 
 * https://github.com/jeffmhopkins/Open-Woodwind-Project
 * https://hackaday.io/project/2992-the-open-woodwind-project
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
 * 
 * =============================================================================================================================================
 * 
 * Basic layout for this project:
 *     owp_synth.ino       -   Main file for the project. 
 *     driven_waveform.ino - Stores the waveform shaper structs
 *     name.c              - creates the USB name of the synth
 *     patches.ino         - handles creatings, loading and saving patch files to the SD card
 *     process_midi        - processes the MIDI messegages coming in for CC based synth settings
 * 
 * =============================================================================================================================================
 * 
 * TODO LIST:
 *   1. Rebumber the CC channels. This would be nice to group similar things together. It'd require remapping in patches.ino, and then updating
 *      the OSC interface to reflect
 *      
 *      This includes remapping portamento amount, volume, reverb etc to standard numbers.
 *      
 *   3. Go through and standardize the CC #define names to the global variable names. They are 95% identintical, but hey should be 100%.
 *   
 *   4. Add another Chorus effect that doesn't have the string quality? Modify number of voices and time block allowance
 *   
 *   5. Branch and merge OWP and OWP_Synth into OWP_Controller_Synth
 *   
 *   https://roboticsbackend.com/arduino-object-oriented-programming-oop/
 * 
 */
#if !defined(ARDUINO_TEENSY40)
  #error "Please Select Teensy 4.0 Board Type"
#endif
 
#if !defined(USB_MIDI) && !defined(USB_MIDI_SERIAL)
  #error "USB MIDI not enabled. Please set USB type to 'Serial + MIDI'."
#endif

#define DEBUG_TO_SERIAL true

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformDc     breath;         //xy=337.00390625,952.9999990463257
AudioSynthWaveformDc     modulation;     //xy=339.00390625,986.9999990463257
AudioSynthWaveformDc     expression;     //xy=340.00390625,1033.9999990463257
AudioSynthWaveformDc     wave2_wave3_wave4_gain_modulation_offset_dc; //xy=441.00390625,1077.9999990463257
AudioSynthWaveformDc     glide_frequency4; //xy=561.00390625,1290.9999990463257
AudioSynthWaveformDc     glide_frequency2; //xy=565.00390625,1205.9999990463257
AudioSynthWaveformDc     glide_frequency3; //xy=565.00390625,1245.9999990463257
AudioSynthWaveformDc     glide_frequency; //xy=570.00390625,1166.9999990463257
AudioSynthWaveformDc     pitchbend;      //xy=591.00390625,1136.9999990463257
AudioMixer4              dc_smoothing1;  //xy=794.00390625,1165.9999990463257
AudioMixer4              dc_smoothing2;  //xy=794.00390625,1245.9999990463257
AudioMixer4              wave2_wave3_wave4_gain_modulation_mixer; //xy=811.00390625,760.9999990463257
AudioSynthWaveformSine   lfo2;           //xy=841.00390625,679.9999990463257
AudioSynthWaveformSine   lfo1;           //xy=855.00390625,343.9999990463257
AudioSynthWaveformDc     wave2_gain_dc;  //xy=1115.7181701660156,512.2858009338379
AudioSynthWaveformDc     wave3_gain_dc;  //xy=1116.2897491455078,552.1428890228271
AudioSynthWaveformDc     wave4_gain_dc;  //xy=1117.5754203796387,597.1428575515747
AudioAmplifier           lfo2_destination_filter_amp; //xy=1167.00390625,1130.9999990463257
AudioAmplifier           lfo1_destination_filter_amp; //xy=1168.00390625,1091.9999990463257
AudioSynthWaveformDc     filter_frequency; //xy=1213.00390625,1056.9999990463257
AudioAmplifier           lfo1_destination_gain_amp; //xy=1396.00390625,311.9999990463257
AudioEffectMultiply      wave3_gain_multiply; //xy=1400.5753479003906,773.8571138381958
AudioEffectMultiply      wave4_gain_multiply; //xy=1400.7181396484375,813.2857217788696
AudioAmplifier           lfo1_destination_frequency_amp; //xy=1415.00390625,346.9999990463257
AudioEffectMultiply      wave2_gain_multiply; //xy=1416.2895278930664,733.2857627868652
AudioSynthWaveformDc     wave1_gain_dc;  //xy=1420.00390625,227.99999904632568
AudioMixer4              filter_frequency_lfo_mixer; //xy=1442.00390625,1096.9999990463257
AudioAmplifier           lfo2_destination_gain_amp; //xy=1445.1467742919922,671.1427955627441
AudioAmplifier           lfo2_destination_frequency_amp; //xy=1493.7183227539062,621.1428537368774
AudioSynthWaveformDc     wave4_width;    //xy=1508.00390625,580.9999990463257
AudioSynthWaveformDc     wave2_width;    //xy=1509.00390625,483.9999990463257
AudioSynthWaveformDc     wave1_width;    //xy=1510.00390625,438.9999990463257
AudioSynthWaveformDc     wave3_width;    //xy=1513.00390625,536.9999990463257
AudioSynthWaveformModulated wave2;          //xy=1750.00390625,481.9999990463257
AudioMixer4              lfo1_wave1_multiplier_mixer; //xy=1751.00390625,246.99999904632568
AudioSynthWaveformModulated wave1;          //xy=1751.00390625,434.9999990463257
AudioSynthWaveformModulated wave4;          //xy=1751.00390625,566.9999990463257
AudioSynthWaveformModulated wave3;          //xy=1756.00390625,525.9999990463257
AudioMixer4              lfo2_wave3_multiplier_mixer; //xy=1761.8612823486328,854.2857341766357
AudioMixer4              lfo1_wave2_multiplier_mixer; //xy=1764.7182006835938,757.4285774230957
AudioMixer4              lfo2_wave4_multiplier_mixer; //xy=1781.2897491455078,938.857141494751
AudioEffectMultiply      wave2_lfo1_multiply; //xy=2063.00390625,472.9999990463257
AudioEffectMultiply      wave4_lfo2_multiply; //xy=2065.00390625,559.9999990463257
AudioEffectMultiply      wave1_lfo1_multiply; //xy=2067.00390625,435.9999990463257
AudioEffectMultiply      wave3_lfo2_multiply; //xy=2068.00390625,519.9999990463257
AudioSynthNoiseWhite     noise_white;    //xy=2333.00390625,582.9999990463257
AudioSynthNoisePink      noise_pink;     //xy=2334.00390625,540.9999990463257
AudioMixer4              waveselect;     //xy=2353.00390625,472.9999990463257
AudioMixer4              wave_noise_mixer; //xy=2531.00390625,524.9999990463257
AudioEffectWaveshaper    waveshape4;     //xy=2712.00390625,680.9999990463257
AudioEffectWaveshaper    waveshape1;     //xy=2713.00390625,557.9999990463257
AudioEffectWaveshaper    waveshape2;     //xy=2713.00390625,594.9999990463257
AudioEffectWaveshaper    waveshape3;     //xy=2716.00390625,638.9999990463257
AudioEffectWaveshaper    waveshape5;     //xy=2716.00390625,722.9999990463257
AudioEffectWaveshaper    waveshape6;     //xy=2718.00390625,760.9999990463257
AudioMixer4              waveshape_mixer1; //xy=3087.00390625,587.9999990463257
AudioInputI2S            audio_in;       //xy=3123.00390625,366.9999990463257
AudioMixer4              waveshape_mixer2; //xy=3312.00390625,545.9999990463257
AudioEffectMultiply      vca;            //xy=3429.00390625,652.9999990463257
AudioFilterStateVariable filter1;        //xy=3516.00390625,775.9999990463257
AudioMixer4              vca_bypass_mixer; //xy=3568.00390625,563.9999990463257
AudioEffectDelay         delay1;         //xy=3786.00390625,887.9999990463257
AudioMixer4              filter_bypass_mixer; //xy=3807.00390625,580.9999990463257
AudioEffectChorus        chorus1;        //xy=3880.00390625,774.9999990463257
AudioEffectFlange        flange1;        //xy=3889.00390625,733.9999990463257
AudioMixer4              delay_mixer1;   //xy=3937.00390625,861.9999990463257
AudioMixer4              effect_mixer;   //xy=4060.00390625,619.9999990463257
AudioPlaySdWav           wavplayer;      //xy=4158.00390625,742.9999990463257
AudioEffectFreeverbStereo reverb;         //xy=4213.00390625,683.9999990463257
AudioMixer4              left;           //xy=4451.00390625,633.9999990463257
AudioMixer4              right;          //xy=4451.00390625,724.9999990463257
AudioOutputI2S           audio_output;   //xy=4609.00390625,676.9999990463257
AudioConnection          patchCord1(breath, 0, vca, 1);
AudioConnection          patchCord2(breath, 0, wave2_wave3_wave4_gain_modulation_mixer, 0);
AudioConnection          patchCord3(modulation, 0, wave2_wave3_wave4_gain_modulation_mixer, 1);
AudioConnection          patchCord4(expression, 0, wave2_wave3_wave4_gain_modulation_mixer, 2);
AudioConnection          patchCord5(wave2_wave3_wave4_gain_modulation_offset_dc, 0, wave2_wave3_wave4_gain_modulation_mixer, 3);
AudioConnection          patchCord6(glide_frequency4, 0, dc_smoothing2, 3);
AudioConnection          patchCord7(glide_frequency2, 0, dc_smoothing2, 1);
AudioConnection          patchCord8(glide_frequency3, 0, dc_smoothing2, 2);
AudioConnection          patchCord9(glide_frequency, 0, dc_smoothing2, 0);
AudioConnection          patchCord10(pitchbend, 0, dc_smoothing1, 0);
AudioConnection          patchCord11(wave2_wave3_wave4_gain_modulation_mixer, 0, wave3_gain_multiply, 1);
AudioConnection          patchCord12(wave2_wave3_wave4_gain_modulation_mixer, 0, wave4_gain_multiply, 1);
AudioConnection          patchCord13(wave2_wave3_wave4_gain_modulation_mixer, 0, wave2_gain_multiply, 1);
AudioConnection          patchCord14(lfo2, lfo2_destination_gain_amp);
AudioConnection          patchCord15(lfo2, lfo2_destination_frequency_amp);
AudioConnection          patchCord16(lfo2, lfo2_destination_filter_amp);
AudioConnection          patchCord17(lfo1, lfo1_destination_frequency_amp);
AudioConnection          patchCord18(lfo1, lfo1_destination_gain_amp);
AudioConnection          patchCord19(lfo1, lfo1_destination_filter_amp);
AudioConnection          patchCord20(wave2_gain_dc, 0, wave2_gain_multiply, 0);
AudioConnection          patchCord21(wave3_gain_dc, 0, wave3_gain_multiply, 0);
AudioConnection          patchCord22(wave4_gain_dc, 0, wave4_gain_multiply, 0);
AudioConnection          patchCord23(lfo2_destination_filter_amp, 0, filter_frequency_lfo_mixer, 2);
AudioConnection          patchCord24(lfo1_destination_filter_amp, 0, filter_frequency_lfo_mixer, 1);
AudioConnection          patchCord25(filter_frequency, 0, filter_frequency_lfo_mixer, 0);
AudioConnection          patchCord26(lfo1_destination_gain_amp, 0, lfo1_wave1_multiplier_mixer, 1);
AudioConnection          patchCord27(wave3_gain_multiply, 0, lfo2_wave3_multiplier_mixer, 0);
AudioConnection          patchCord28(wave4_gain_multiply, 0, lfo2_wave4_multiplier_mixer, 0);
AudioConnection          patchCord29(lfo1_destination_frequency_amp, 0, wave1, 0);
AudioConnection          patchCord30(wave2_gain_multiply, 0, lfo1_wave2_multiplier_mixer, 0);
AudioConnection          patchCord31(wave1_gain_dc, 0, lfo1_wave1_multiplier_mixer, 0);
AudioConnection          patchCord32(filter_frequency_lfo_mixer, 0, filter1, 1);
AudioConnection          patchCord33(lfo2_destination_gain_amp, 0, lfo2_wave3_multiplier_mixer, 1);
AudioConnection          patchCord34(lfo2_destination_gain_amp, 0, lfo2_wave4_multiplier_mixer, 1);
AudioConnection          patchCord35(lfo2_destination_gain_amp, 0, lfo1_wave2_multiplier_mixer, 1);
AudioConnection          patchCord36(lfo2_destination_frequency_amp, 0, wave3, 0);
AudioConnection          patchCord37(lfo2_destination_frequency_amp, 0, wave4, 0);
AudioConnection          patchCord38(lfo2_destination_frequency_amp, 0, wave2, 0);
AudioConnection          patchCord39(wave4_width, 0, wave4, 1);
AudioConnection          patchCord40(wave2_width, 0, wave2, 1);
AudioConnection          patchCord41(wave1_width, 0, wave1, 1);
AudioConnection          patchCord42(wave3_width, 0, wave3, 1);
AudioConnection          patchCord43(wave2, 0, wave2_lfo1_multiply, 1);
AudioConnection          patchCord44(lfo1_wave1_multiplier_mixer, 0, wave1_lfo1_multiply, 0);
AudioConnection          patchCord45(wave1, 0, wave1_lfo1_multiply, 1);
AudioConnection          patchCord46(wave4, 0, wave4_lfo2_multiply, 1);
AudioConnection          patchCord47(wave3, 0, wave3_lfo2_multiply, 1);
AudioConnection          patchCord48(lfo2_wave3_multiplier_mixer, 0, wave3_lfo2_multiply, 0);
AudioConnection          patchCord49(lfo1_wave2_multiplier_mixer, 0, wave2_lfo1_multiply, 0);
AudioConnection          patchCord50(lfo2_wave4_multiplier_mixer, 0, wave4_lfo2_multiply, 0);
AudioConnection          patchCord51(wave2_lfo1_multiply, 0, waveselect, 1);
AudioConnection          patchCord52(wave4_lfo2_multiply, 0, waveselect, 3);
AudioConnection          patchCord53(wave1_lfo1_multiply, 0, waveselect, 0);
AudioConnection          patchCord54(wave3_lfo2_multiply, 0, waveselect, 2);
AudioConnection          patchCord55(noise_white, 0, wave_noise_mixer, 2);
AudioConnection          patchCord56(noise_pink, 0, wave_noise_mixer, 1);
AudioConnection          patchCord57(waveselect, 0, wave_noise_mixer, 0);
AudioConnection          patchCord58(wave_noise_mixer, 0, waveshape_mixer2, 0);
AudioConnection          patchCord59(wave_noise_mixer, waveshape1);
AudioConnection          patchCord60(waveshape4, 0, waveshape_mixer1, 2);
AudioConnection          patchCord61(waveshape4, waveshape5);
AudioConnection          patchCord62(waveshape1, waveshape2);
AudioConnection          patchCord63(waveshape1, 0, waveshape_mixer1, 0);
AudioConnection          patchCord64(waveshape2, 0, waveshape_mixer1, 1);
AudioConnection          patchCord65(waveshape2, waveshape3);
AudioConnection          patchCord66(waveshape3, waveshape4);
AudioConnection          patchCord67(waveshape5, waveshape6);
AudioConnection          patchCord68(waveshape6, 0, waveshape_mixer1, 3);
AudioConnection          patchCord69(waveshape_mixer1, 0, waveshape_mixer2, 1);
AudioConnection          patchCord70(audio_in, 0, waveshape_mixer2, 2);
AudioConnection          patchCord71(audio_in, 0, left, 3);
AudioConnection          patchCord72(audio_in, 1, right, 3);
AudioConnection          patchCord73(audio_in, 1, waveshape_mixer2, 3);
AudioConnection          patchCord74(waveshape_mixer2, 0, vca, 0);
AudioConnection          patchCord75(waveshape_mixer2, 0, vca_bypass_mixer, 0);
AudioConnection          patchCord76(vca, 0, vca_bypass_mixer, 1);
AudioConnection          patchCord77(filter1, 0, filter_bypass_mixer, 1);
AudioConnection          patchCord78(filter1, 1, filter_bypass_mixer, 2);
AudioConnection          patchCord79(filter1, 2, filter_bypass_mixer, 3);
AudioConnection          patchCord80(vca_bypass_mixer, 0, filter1, 0);
AudioConnection          patchCord81(vca_bypass_mixer, 0, filter_bypass_mixer, 0);
AudioConnection          patchCord82(delay1, 0, delay_mixer1, 0);
AudioConnection          patchCord83(delay1, 1, delay_mixer1, 1);
AudioConnection          patchCord84(delay1, 2, delay_mixer1, 2);
AudioConnection          patchCord85(delay1, 3, delay_mixer1, 3);
AudioConnection          patchCord86(filter_bypass_mixer, 0, effect_mixer, 0);
AudioConnection          patchCord87(filter_bypass_mixer, flange1);
AudioConnection          patchCord88(filter_bypass_mixer, chorus1);
AudioConnection          patchCord89(filter_bypass_mixer, delay1);
AudioConnection          patchCord90(chorus1, 0, effect_mixer, 2);
AudioConnection          patchCord91(flange1, 0, effect_mixer, 1);
AudioConnection          patchCord92(delay_mixer1, 0, effect_mixer, 3);
AudioConnection          patchCord93(effect_mixer, reverb);
AudioConnection          patchCord94(effect_mixer, 0, left, 0);
AudioConnection          patchCord95(effect_mixer, 0, right, 0);
AudioConnection          patchCord96(wavplayer, 0, left, 2);
AudioConnection          patchCord97(wavplayer, 1, right, 2);
AudioConnection          patchCord98(reverb, 0, left, 1);
AudioConnection          patchCord99(reverb, 1, right, 1);
AudioConnection          patchCord100(left, 0, audio_output, 0);
AudioConnection          patchCord101(right, 0, audio_output, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=2786.00390625,245.99999904632568
// GUItool: end automatically generated code




//located in driven_waveform.ino
extern const float driven_waveform1[257];
extern const float driven_waveform2[257];
extern const float driven_waveform3[257];
extern const float wave_shape_tube_12at7[513];
extern const float wave_shape_tube_6v6[513];
extern const float wave_shape_tube_12au7[513];
extern const float wave_shape_tube_kt88[513];
extern const float wave_shape_tube_12ax7_1025[1025];

//Global Variables
int   note;
int   note2, note3, note4; //for keyboard mode       
bool  noteon;
bool  noteon2, noteon3, noteon4;
int   velocity1, velocity2, velocity3, velocity4;
int   current_keyboard_voice = 0;
float portamento;
float pitchbend_multiplier;
float pulsewidth_calculated;
float overdrive_calculated;
float filter_frequency_calculated;
float filter_resonance_calculated;
int   pitchbend_value;
float wave2_wave3_wave4_gain_modulation_offset;

//Global Variables that aren't overwritten by CC values such as ramp rates
bool  keyboard_mode              = false;
int   pitchbend_range            = 2;   
bool  pitchbend_reset_on_noteon  = true;  
int   pitchbend_ramp_rate        = 10;
int   portamento_max             = 500.0;
int   lfo_max_range              = 3;
int   lfo_max_freq               = 60;
float filter_passes              = 0;   
float filter_min_frequency       = 10;
int   filter_frequency_ramp_rate = 10;
float reverb_damping             = 0.999;
float tuning_value               = 0.377;   //This fixes a little bit of note_offset to true A440 tuning, tuned with a notefreq object to wave1
float wave_freq                  = 5000; //We use a float for our glide frequency, this is the frequency we multiply it by. Lower values make a more accurate pitchbend/glide refresh
int   breath_ramp_rate           = 8;
int   breath_ramp_rate_note_off  = 16;
int   expression_ramp_rate       = 30; 
int   modulation_ramp_rate       = 30;
int   pitch_ramp_rate            = 10;

//Global Variables - Settings (You can change these to set startup conditions, though most will be overwritten when we load the patch from loadPatchSD(1) in setup()
float lfo_reset_phase_on_new_note    = 1.0;
float note_offset                    = 16.0;   
float default_tune                   = 1.0;
float portamento_min_multiplier      = 0.1;//makes 10% of portamento_max   
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
float filter_max_frequency           = 25000;
float filter_q                       = 0.707;
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
float breath_to_wave2_wave3_wave4_gain     = 0.0;
float modulation_to_wave2_wave3_wave4_gain = 0.0;
float expression_to_wave2_wave3_wave4_gain = 0.0;
float vca_gate_bypass                = 0.0;
float filter_bypass                  = 0.0;
float filter_type                    = 0.0;
float audio_in_pre                   = 1.0;
float audio_in_post                  = 0.0;
float eq_1                           = 0.0;
float eq_2                           = 0.0;
float eq_3                           = 0.0;
float eq_4                           = 0.0;
float eq_5                           = 0.0;
float reverb_wet                     = 0.15;
float breath_gamma                   = 1.85;

//Flange specific
#define FLANGE_DELAY_LENGTH (6*AUDIO_BLOCK_SAMPLES)
short   delayline[FLANGE_DELAY_LENGTH];
int     s_idx   = FLANGE_DELAY_LENGTH/4;
int     s_depth = FLANGE_DELAY_LENGTH/4;
double  s_freq  = .5;

//Chorus specific
#define CHORUS_DELAY_LENGTH (16*AUDIO_BLOCK_SAMPLES)
short   chorus_delayline[CHORUS_DELAY_LENGTH];
int     n_chorus = 4;

unsigned long last_time = millis();

void setup() {
  Serial.begin(115200);
  configureSD();
  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.volume(master_volume);
  AudioMemory(400);
  sgtl5000_1.audioPostProcessorEnable();
  //sgtl5000_1.surroundSoundEnable();
  //sgtl5000_1.surroundSound(7, 3);
  sgtl5000_1.adcHighPassFilterDisable();
  sgtl5000_1.eqSelect(3);//5-band eq
  sgtl5000_1.eqBands(eq_1, eq_2, eq_3, eq_4, eq_5);
  AudioNoInterrupts();
  //notefreq1.begin(.15);
  wave2_wave3_wave4_gain_modulation_offset_dc.amplitude(wave2_wave3_wave4_gain_modulation_offset);
  wave2_wave3_wave4_gain_modulation_mixer.gain(0, 1.0);//Breath
  wave2_wave3_wave4_gain_modulation_mixer.gain(1, 0.0);//Modulation
  wave2_wave3_wave4_gain_modulation_mixer.gain(2, 0.0);//Expression
  wave2_wave3_wave4_gain_modulation_mixer.gain(3, 1.0);//DC offset
  filter1.frequency(filter_min_frequency);
  filter1.resonance(0.707);
  filter1.octaveControl(14);
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
  left.gain(0, 1.0 - reverb_wet);
  left.gain(1, reverb_wet);
  left.gain(2, 1);
  left.gain(3, audio_in_post);//AudioInL
  right.gain(0, 1.0 - reverb_wet);
  right.gain(1, reverb_wet);
  right.gain(2, 1);
  right.gain(3, audio_in_post);//AudioInR
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
        waveshape5.shape((float *)wave_shape_tube_12ax7_1025, 1025);
        waveshape6.shape((float *)driven_waveform3, 257);
  waveshape_mixer2.gain(0,1);//Dry
  waveshape_mixer2.gain(1,1);//Overdrive
  waveshape_mixer2.gain(2,audio_in_pre);//AudioInL
  waveshape_mixer2.gain(3,audio_in_pre);//AudioInR
  vca_bypass_mixer.gain(0,0);//Bypass
  vca_bypass_mixer.gain(1,1);//Breath VCA
  filter_bypass_mixer.gain(0,0);//No Filter
  filter_bypass_mixer.gain(1,1);//Low Pass
  filter_bypass_mixer.gain(2,0);//Band Pass
  filter_bypass_mixer.gain(3,0);//High Pass
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
  //loadPatchEEPROM(); //Loads the last saved patch.
  loadPatchSD(1);
  AudioInterrupts();
}

void loop() {
  //Do some math before we start turning off the audio interrupts, cleans up some stuff visually below too
  pitchbend_multiplier        = pow(2.0, (pitchbend_range * (pitchbend.read())/12.0));
  pulsewidth_calculated       = bound1(breath.read()* breath_to_pulse_width + 
                                         modulation.read() * modulation_to_pulse_width + 
                                         expression.read() * expression_to_pulse_width);
  overdrive_calculated        = bound1(breath.read() * breath_to_overdrive +
                                         modulation.read() * modulation_to_overdrive +
                                         expression.read() * expression_to_overdrive);
  filter_frequency_calculated = bound1(filter_min_frequency + bound1(breath_to_filter_cutoff * breath.read() + 
                                         modulation_to_filter_cutoff * modulation.read() +
                                         expression_to_filter_cutoff * expression.read()));
  filter_resonance_calculated = 2*bound1(filter_q + breath_to_filter_resonance * breath.read() +
                                         modulation_to_filter_resonance * modulation.read() +
                                         expression_to_filter_resonance * expression.read());
  AudioNoInterrupts();
  if(keyboard_mode) {//This allows us to play the keyboard on the synth with four voices, emulating some nice organ sounds
    if(noteon)  {wave1.amplitude(velocity1/127.0);} else {wave1.amplitude(0);}
    if(noteon2) {wave2.amplitude(velocity2/127.0);} else {wave2.amplitude(0);}
    if(noteon3) {wave3.amplitude(velocity3/127.0);} else {wave3.amplitude(0);}
    if(noteon4) {wave4.amplitude(velocity4/127.0);} else {wave4.amplitude(0);}
  } else {
    wave1.amplitude(wave1_gain);
    wave2.amplitude(wave2_gain);
    wave3.amplitude(wave3_gain);
    wave4.amplitude(wave4_gain);
  }
  
  wave2_wave3_wave4_gain_modulation_offset_dc.amplitude(wave2_wave3_wave4_gain_modulation_offset);
  wave2_wave3_wave4_gain_modulation_mixer.gain(0, breath_to_wave2_wave3_wave4_gain);    //Breath
  wave2_wave3_wave4_gain_modulation_mixer.gain(1, modulation_to_wave2_wave3_wave4_gain);//Modulation
  wave2_wave3_wave4_gain_modulation_mixer.gain(2, expression_to_wave2_wave3_wave4_gain);//Expression
  wave2_wave3_wave4_gain_modulation_mixer.gain(3, 1);                             //DC Offset
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
  if(keyboard_mode) {
    wave1.frequency(glide_frequency.read() * pitchbend_multiplier * wave1_detune_multiplier * wave_freq * default_tune);
    wave2.frequency(glide_frequency2.read() * pitchbend_multiplier * wave2_detune_multiplier * wave_freq * default_tune);
    wave3.frequency(glide_frequency3.read() * pitchbend_multiplier * wave3_detune_multiplier * wave_freq * default_tune);
    wave4.frequency(glide_frequency4.read() * pitchbend_multiplier * wave4_detune_multiplier * wave_freq * default_tune);
  } else {
    wave1.frequency(glide_frequency.read() * pitchbend_multiplier * wave1_detune_multiplier * wave_freq * default_tune);
    wave2.frequency(glide_frequency.read() * pitchbend_multiplier * wave2_detune_multiplier * wave_freq * default_tune);
    wave3.frequency(glide_frequency.read() * pitchbend_multiplier * wave3_detune_multiplier * wave_freq * default_tune);
    wave4.frequency(glide_frequency.read() * pitchbend_multiplier * wave4_detune_multiplier * wave_freq * default_tune);
  }
  noise_pink.amplitude(breath.read());
  noise_white.amplitude(breath.read());              
  filter_frequency.amplitude(filter_frequency_calculated);   
  filter1.resonance(filter_resonance_calculated);
  lfo1.frequency(lfo_max_freq * (lfo1_freq + bound1(breath_to_lfo1_freq * breath.read() + modulation_to_lfo1_freq * modulation.read() + expression_to_lfo1_freq * expression.read())));
  lfo1.amplitude(bound1(lfo1_gain + bound1(breath_to_lfo1_gain * breath.read() + modulation_to_lfo1_gain * modulation.read() + expression_to_lfo1_gain * expression.read())));
  wave1.frequencyModulation(lfo_max_range * bound1(lfo1_range + breath_to_lfo1_range * breath.read() + modulation_to_lfo1_range * modulation.read() + expression_to_lfo1_range * expression.read()));
  wave2.frequencyModulation(lfo_max_range * bound1(lfo1_range + breath_to_lfo1_range * breath.read() + modulation_to_lfo1_range * modulation.read() + expression_to_lfo1_range * expression.read()));
  wave3.frequencyModulation(lfo_max_range * bound1(lfo2_range + breath_to_lfo2_range * breath.read() + modulation_to_lfo2_range * modulation.read() + expression_to_lfo2_range * expression.read()));
  wave4.frequencyModulation(lfo_max_range * bound1(lfo2_range + breath_to_lfo2_range * breath.read() + modulation_to_lfo2_range * modulation.read() + expression_to_lfo2_range * expression.read()));
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
  waveshape_mixer2.gain(2,audio_in_pre);//AudioInL
  waveshape_mixer2.gain(3,audio_in_pre);//AudioInR
  left.gain(3, audio_in_post);//AudioInL
  right.gain(3, audio_in_post);//AudioInR
  effect_mixer.gain(0, effects_oscillators);
  effect_mixer.gain(1, effects_flange);
  effect_mixer.gain(2, effects_chorus);
  effect_mixer.gain(3, effects_delay);
  left.gain(2, wav_gain);
  right.gain(2, wav_gain);
  left.gain(0, 1.0 - reverb_wet);
  left.gain(1, reverb_wet);
  right.gain(0, 1.0 - reverb_wet);
  right.gain(1, reverb_wet);
  sgtl5000_1.volume(master_volume);
  reverb.roomsize(reverb_size);
  vca_bypass_mixer.gain(0, vca_gate_bypass);      //Bypass
  vca_bypass_mixer.gain(1, 1.0 - vca_gate_bypass);//Breath VCA
  filter_bypass_mixer.gain(0, filter_bypass);     //No Filter
  if(filter_type < 0.33) {
    filter_bypass_mixer.gain(1, 1.0);//Low Pass
    filter_bypass_mixer.gain(2, 0);  //Band Pass
    filter_bypass_mixer.gain(3, 0);  //High Pass
  } else if(filter_type < 0.66) {
    filter_bypass_mixer.gain(1, 0);  //Low Pass
    filter_bypass_mixer.gain(2, 1.0);//Band Pass
    filter_bypass_mixer.gain(3, 0);  //High Pass
  }  else {
    filter_bypass_mixer.gain(1, 0);  //Low Pass
    filter_bypass_mixer.gain(2, 0);  //Band Pass
    filter_bypass_mixer.gain(3, 1);  //High Pass
  }
  
  AudioInterrupts();
  if (usbMIDI.read()) {
    processMIDI();
  }
  if(DEBUG_TO_SERIAL) {
    if(millis() - last_time >= 5000) {
      Serial.print("Proc = ");
      Serial.print(AudioProcessorUsage());
      Serial.print(" (");    
      Serial.print(AudioProcessorUsageMax());
      Serial.print("),  Mem = ");
      Serial.print(AudioMemoryUsage());
      Serial.print(" (");    
      Serial.print(AudioMemoryUsageMax());
      Serial.println(")");
      last_time = millis();
    } 
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
