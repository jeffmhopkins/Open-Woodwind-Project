#include <EEPROM.h>

#define PATCH_EEPROM_ADDRESS_START 0

struct Patch {
  float wave1_shape, wave2_shape, wave3_shape, wave4_shape;
  float wave1_pulse_width, wave2_pulse_width, wave3_pulse_width, wave4_pulse_width;
  float wave1_detune_multiplier, wave2_detune_multiplier, wave3_detune_multiplier, wave4_detune_multiplier;
  float wave1_gain,  wave2_gain,  wave3_gain,  wave4_gain;
  float master_volume, reverb_size;
  float distortion_mix, noise_pink_gain, noise_white_gain;
  float filter_min_frequency, filter_q;
  float breath_to_pulse_width, breath_to_filter_cutoff, breath_to_filter_resonance, breath_to_overdrive;
  float modulation_to_pulse_width, modulation_to_filter_cutoff, modulation_to_filter_resonance, modulation_to_overdrive;
  float expression_to_pulse_width, expression_to_filter_cutoff, expression_to_filter_resonance, expression_to_portamento, expression_to_overdrive;
  float note_offset, default_tune;
  float effects_oscillators, effects_flange, effects_chorus, effects_delay, effects_delay_ms;
  float portamento_min;
  float wav_gain;
};

void configureSD() {
  SPI.setMOSI(11); SPI.setSCK(13);
  if (!(SD.begin(10))) {
      Serial.println("Unable to access the SD card");
  }
}

void loadPatch(int i) {
  Patch patch;
  EEPROM.get(PATCH_EEPROM_ADDRESS_START + sizeof(patch) * i, patch);
  Serial.println(patch.wave1_shape);
  wave1.begin(patch.wave1_shape);
  wave2.begin(patch.wave2_shape);
  wave3.begin(patch.wave3_shape);
  wave4.begin(patch.wave4_shape);
  wave1.pulseWidth(patch.wave1_pulse_width);
  wave2.pulseWidth(patch.wave2_pulse_width);
  wave3.pulseWidth(patch.wave3_pulse_width);
  wave4.pulseWidth(patch.wave4_pulse_width);
  wave1_detune_multiplier = patch.wave1_detune_multiplier;
  wave2_detune_multiplier = patch.wave2_detune_multiplier;
  wave3_detune_multiplier = patch.wave3_detune_multiplier;
  wave4_detune_multiplier = patch.wave4_detune_multiplier;
  waveselect.gain(0, patch.wave1_gain); wave1_gain = patch.wave1_gain;
  waveselect.gain(1, patch.wave2_gain); wave2_gain = patch.wave2_gain;
  waveselect.gain(2, patch.wave3_gain); wave3_gain = patch.wave3_gain;
  waveselect.gain(3, patch.wave4_gain); wave4_gain = patch.wave4_gain;
  master_volume = patch.master_volume;
  reverb_size   = patch.reverb_size;
  distortion_mix = patch.distortion_mix;
  noise_pink_gain = patch.noise_pink_gain;
  noise_white_gain = patch.noise_white_gain;
  filter_min_frequency = patch.filter_min_frequency;
  filter_q = patch.filter_q;
  breath_to_pulse_width  = patch.breath_to_pulse_width;
  breath_to_filter_cutoff = patch.breath_to_filter_cutoff;
  breath_to_filter_resonance = patch.breath_to_filter_resonance;
  breath_to_overdrive = patch.breath_to_overdrive;
  modulation_to_pulse_width = patch.modulation_to_pulse_width;
  modulation_to_filter_cutoff = patch.modulation_to_filter_cutoff;
  modulation_to_filter_resonance = patch.modulation_to_filter_resonance;
  modulation_to_overdrive = patch.modulation_to_overdrive;
  expression_to_pulse_width = patch.expression_to_pulse_width;
  expression_to_filter_cutoff = patch.expression_to_filter_cutoff;
  expression_to_filter_resonance = patch.expression_to_filter_resonance;
  expression_to_portamento = patch.expression_to_portamento;
  expression_to_overdrive = patch.expression_to_overdrive;
  note_offset = patch.note_offset;
  default_tune = patch.default_tune;
  effects_oscillators = patch.effects_oscillators;
  effects_flange = patch.effects_flange;
  effects_chorus = patch.effects_chorus;
  effects_delay = patch.effects_delay;
  effects_delay_ms = patch.effects_delay_ms;
  portamento_min = patch.portamento_min;
  wav_gain = patch.wav_gain;
}

void savePatch(int i) {
  Patch patch =  {wave1_shape, wave2_shape, wave3_shape, wave4_shape,
                  wave1_pulse_width, wave2_pulse_width, wave3_pulse_width, wave4_pulse_width,
                  wave1_detune_multiplier,wave2_detune_multiplier,wave3_detune_multiplier,wave4_detune_multiplier,
                  wave1_gain,  wave2_gain,  wave3_gain,  wave4_gain,
                  master_volume, reverb_size,
                  distortion_mix, noise_pink_gain, noise_white_gain,
                  filter_min_frequency, filter_q,
                  breath_to_pulse_width, breath_to_filter_cutoff, breath_to_filter_resonance, breath_to_overdrive,
                  modulation_to_pulse_width, modulation_to_filter_cutoff, modulation_to_filter_resonance, modulation_to_overdrive,
                  expression_to_pulse_width, expression_to_filter_cutoff, expression_to_filter_resonance, expression_to_portamento, expression_to_overdrive,
                  note_offset, default_tune,
                  effects_oscillators, effects_flange, effects_chorus, effects_delay, effects_delay_ms,
                  portamento_min,
                  wav_gain};
  EEPROM.put(PATCH_EEPROM_ADDRESS_START + sizeof(Patch) * i, patch);
}
