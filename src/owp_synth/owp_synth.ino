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
AudioSynthWaveformDc     breath;         //xy=1907.7539367675781,990.9999866485596
AudioSynthWaveformDc     modulation;     //xy=1909.7539367675781,1024.9999866485596
AudioSynthWaveformDc     expression;     //xy=1910.7539367675781,1071.9999866485596
AudioSynthWaveformDc     wave2_wave3_wave4_gain_modulation_offset_dc; //xy=2011.7539367675781,1115.9999866485596
AudioSynthWaveformDc     glide_frequency4; //xy=2131.753936767578,1328.9999866485596
AudioSynthWaveformDc     glide_frequency2; //xy=2135.753936767578,1243.9999866485596
AudioSynthWaveformDc     glide_frequency3; //xy=2135.753936767578,1283.9999866485596
AudioSynthWaveformDc     glide_frequency; //xy=2140.753936767578,1204.9999866485596
AudioSynthWaveformDc     pitchbend;      //xy=2161.753936767578,1174.9999866485596
AudioMixer4              dc_smoothing1;  //xy=2364.753936767578,1203.9999866485596
AudioMixer4              dc_smoothing2;  //xy=2364.753936767578,1283.9999866485596
AudioMixer4              wave2_wave3_wave4_gain_modulation_mixer; //xy=2381.753936767578,798.0000343322754
AudioSynthWaveformSine   lfo2;           //xy=2411.753936767578,717.9999866485596
AudioSynthWaveformSine   lfo1;           //xy=2425.753936767578,381.99998664855957
AudioSynthWaveformDc     wave2_gain_dc;  //xy=2580.7539978027344,295.9999990463257
AudioAmplifier           lfo2_destination_filter_amp; //xy=2737.753936767578,1168.9999866485596
AudioAmplifier           lfo1_destination_filter_amp; //xy=2738.753936767578,1129.9999866485596
AudioSynthWaveformDc     wave4_gain_dc;  //xy=2749.753936767578,827.9999866485596
AudioSynthWaveformDc     wave3_gain_dc;  //xy=2752.753936767578,752.9999866485596
AudioEffectMultiply      wave2_gain_multiply;      //xy=2782.753875732422,316.00392055511475
AudioSynthWaveformDc     filter_frequency; //xy=2783.753936767578,1094.9999866485596
AudioAmplifier           lfo1_destination_gain_amp; //xy=2966.753936767578,349.99998664855957
AudioAmplifier           lfo2_destination_gain_amp; //xy=2968.753936767578,721.9999866485596
AudioEffectMultiply      wave3_gain_multiply; //xy=2982.753936767578,788.9999866485596
AudioAmplifier           lfo1_destination_frequency_amp; //xy=2985.753936767578,384.99998664855957
AudioEffectMultiply      wave4_gain_multiply; //xy=2985.753936767578,826.9999866485596
AudioAmplifier           lfo2_destination_frequency_amp; //xy=2988.753936767578,681.9999866485596
AudioSynthWaveformDc     wave1_gain_dc;  //xy=2990.753936767578,265.99998664855957
AudioMixer4              filter_frequency_lfo_mixer; //xy=3012.753936767578,1134.9999866485596
AudioSynthWaveformDc     wave4_width;    //xy=3078.753936767578,618.9999866485596
AudioSynthWaveformDc     wave2_width;    //xy=3079.753936767578,521.9999866485596
AudioSynthWaveformDc     wave1_width;    //xy=3080.753936767578,476.99998664855957
AudioSynthWaveformDc     wave3_width;    //xy=3083.753936767578,574.9999866485596
AudioMixer4              lfo1_wave2_multiplier_mixer; //xy=3319.753936767578,353.99998664855957
AudioSynthWaveformModulated wave2;          //xy=3320.753936767578,519.9999866485596
AudioMixer4              lfo1_wave1_multiplier_mixer; //xy=3321.753936767578,284.99998664855957
AudioSynthWaveformModulated wave1;          //xy=3321.753936767578,472.99998664855957
AudioSynthWaveformModulated wave4;          //xy=3321.753936767578,604.9999866485596
AudioSynthWaveformModulated wave3;          //xy=3326.753936767578,563.9999866485596
AudioMixer4              lfo2_wave4_multiplier_mixer; //xy=3347.753936767578,803.9999866485596
AudioMixer4              lfo2_wave3_multiplier_mixer; //xy=3349.753936767578,727.9999866485596
AudioEffectMultiply      wave2_lfo1_multiply; //xy=3633.753936767578,510.99998664855957
AudioEffectMultiply      wave4_lfo2_multiply; //xy=3635.753936767578,597.9999866485596
AudioEffectMultiply      wave1_lfo1_multiply; //xy=3637.753936767578,473.99998664855957
AudioEffectMultiply      wave3_lfo2_multiply; //xy=3638.753936767578,557.9999866485596
AudioSynthNoiseWhite     noise_white;    //xy=3903.753936767578,620.9999866485596
AudioSynthNoisePink      noise_pink;     //xy=3904.753936767578,578.9999866485596
AudioMixer4              waveselect;     //xy=3923.753936767578,510.99998664855957
AudioMixer4              wave_noise_mixer; //xy=4101.753936767578,562.9999866485596
AudioEffectWaveshaper    waveshape4;     //xy=4282.753936767578,718.9999866485596
AudioEffectWaveshaper    waveshape1;     //xy=4283.753936767578,595.9999866485596
AudioEffectWaveshaper    waveshape2;     //xy=4283.753936767578,632.9999866485596
AudioEffectWaveshaper    waveshape3;     //xy=4286.753936767578,676.9999866485596
AudioEffectWaveshaper    waveshape5;     //xy=4286.753936767578,760.9999866485596
AudioEffectWaveshaper    waveshape6;     //xy=4288.753936767578,798.9999866485596
AudioMixer4              waveshape_mixer1; //xy=4657.753936767578,625.9999866485596
AudioInputI2S            audio_in;       //xy=4693.753936767578,404.99998664855957
AudioMixer4              waveshape_mixer2; //xy=4882.753936767578,583.9999866485596
AudioEffectMultiply      vca;            //xy=4999.753936767578,690.9999866485596
AudioFilterStateVariable filter1;        //xy=5086.753936767578,813.9999866485596
AudioMixer4              vca_bypass_mixer; //xy=5138.753936767578,601.9999866485596
AudioEffectDelay         delay1;         //xy=5356.753936767578,925.9999866485596
AudioMixer4              filter_bypass_mixer; //xy=5377.753936767578,618.9999866485596
AudioEffectChorus        chorus1;        //xy=5450.753936767578,812.9999866485596
AudioEffectFlange        flange1;        //xy=5459.753936767578,771.9999866485596
AudioMixer4              delay_mixer1;   //xy=5507.753936767578,899.9999866485596
AudioMixer4              effect_mixer;   //xy=5630.753936767578,657.9999866485596
AudioPlaySdWav           wavplayer;      //xy=5728.753936767578,780.9999866485596
AudioEffectFreeverbStereo reverb;         //xy=5783.753936767578,721.9999866485596
AudioMixer4              left;           //xy=6021.753936767578,671.9999866485596
AudioMixer4              right;          //xy=6021.753936767578,762.9999866485596
AudioOutputI2S           audio_output;   //xy=6179.753936767578,714.9999866485596
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
AudioConnection          patchCord21(lfo2_destination_filter_amp, 0, filter_frequency_lfo_mixer, 2);
AudioConnection          patchCord22(lfo1_destination_filter_amp, 0, filter_frequency_lfo_mixer, 1);
AudioConnection          patchCord23(wave4_gain_dc, 0, wave4_gain_multiply, 0);
AudioConnection          patchCord24(wave3_gain_dc, 0, wave3_gain_multiply, 0);
AudioConnection          patchCord25(wave2_gain_multiply, 0, lfo1_wave2_multiplier_mixer, 0);
AudioConnection          patchCord26(filter_frequency, 0, filter_frequency_lfo_mixer, 0);
AudioConnection          patchCord27(lfo1_destination_gain_amp, 0, lfo1_wave1_multiplier_mixer, 1);
AudioConnection          patchCord28(lfo1_destination_gain_amp, 0, lfo1_wave2_multiplier_mixer, 1);
AudioConnection          patchCord29(lfo2_destination_gain_amp, 0, lfo2_wave3_multiplier_mixer, 1);
AudioConnection          patchCord30(lfo2_destination_gain_amp, 0, lfo2_wave4_multiplier_mixer, 1);
AudioConnection          patchCord31(wave3_gain_multiply, 0, lfo2_wave3_multiplier_mixer, 0);
AudioConnection          patchCord32(lfo1_destination_frequency_amp, 0, wave1, 0);
AudioConnection          patchCord33(lfo1_destination_frequency_amp, 0, wave2, 0);
AudioConnection          patchCord34(wave4_gain_multiply, 0, lfo2_wave4_multiplier_mixer, 0);
AudioConnection          patchCord35(lfo2_destination_frequency_amp, 0, wave3, 0);
AudioConnection          patchCord36(lfo2_destination_frequency_amp, 0, wave4, 0);
AudioConnection          patchCord37(wave1_gain_dc, 0, lfo1_wave1_multiplier_mixer, 0);
AudioConnection          patchCord38(filter_frequency_lfo_mixer, 0, filter1, 1);
AudioConnection          patchCord39(wave4_width, 0, wave4, 1);
AudioConnection          patchCord40(wave2_width, 0, wave2, 1);
AudioConnection          patchCord41(wave1_width, 0, wave1, 1);
AudioConnection          patchCord42(wave3_width, 0, wave3, 1);
AudioConnection          patchCord43(lfo1_wave2_multiplier_mixer, 0, wave2_lfo1_multiply, 0);
AudioConnection          patchCord44(wave2, 0, wave2_lfo1_multiply, 1);
AudioConnection          patchCord45(lfo1_wave1_multiplier_mixer, 0, wave1_lfo1_multiply, 0);
AudioConnection          patchCord46(wave1, 0, wave1_lfo1_multiply, 1);
AudioConnection          patchCord47(wave4, 0, wave4_lfo2_multiply, 1);
AudioConnection          patchCord48(wave3, 0, wave3_lfo2_multiply, 1);
AudioConnection          patchCord49(lfo2_wave4_multiplier_mixer, 0, wave4_lfo2_multiply, 0);
AudioConnection          patchCord50(lfo2_wave3_multiplier_mixer, 0, wave3_lfo2_multiply, 0);
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
AudioControlSGTL5000     sgtl5000_1;     //xy=4356.753936767578,283.99998664855957
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
float breath_gamma               = 1.85;
int   breath_ramp_rate           = 8;
int   breath_ramp_rate_note_off  = 16;
int   expression_ramp_rate       = 30; 
int   modulation_ramp_rate       = 30;
int   pitch_ramp_rate            = 10;
float reverb_wet                 = 0.15;

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
float filter_q                       = .707;
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
