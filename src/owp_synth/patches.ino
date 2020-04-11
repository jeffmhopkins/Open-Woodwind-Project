/*
 * The Open Woodwind Project - OWP_Synth for Woodwind Controllers by Jeff Hopkins
 * 
 * Handles saving and loading the patch files from the SD card.
 * 
 */
typedef struct Patch {
  float wave1_shape, wave2_shape, wave3_shape, wave4_shape;
  float wave1_pulse_width, wave2_pulse_width, wave3_pulse_width, wave4_pulse_width;
  float wave1_detune_multiplier, wave2_detune_multiplier, wave3_detune_multiplier, wave4_detune_multiplier;
  float wave1_gain,  wave2_gain,  wave3_gain,  wave4_gain;
  float master_volume, reverb_size;
  float noise_pink_gain, noise_white_gain;
  float filter_min_frequency, filter_q;
  float breath_to_pulse_width, breath_to_filter_cutoff, breath_to_filter_resonance, breath_to_overdrive;
  float modulation_to_pulse_width, modulation_to_filter_cutoff, modulation_to_filter_resonance, modulation_to_overdrive;
  float expression_to_pulse_width, expression_to_filter_cutoff, expression_to_filter_resonance, expression_to_portamento, expression_to_overdrive;
  float note_offset, default_tune;
  float effects_oscillators, effects_flange, effects_chorus, effects_delay, effects_delay_ms;
  float portamento_min;
  float wav_gain;
  float lfo1_gain, lfo1_freq, lfo1_range;
  float breath_to_lfo1_gain, modulation_to_lfo1_gain, expression_to_lfo1_gain;
  float breath_to_lfo1_freq, modulation_to_lfo1_freq, expression_to_lfo1_freq;
  float lfo2_gain, lfo2_freq, lfo2_range;
  float breath_to_lfo2_gain, modulation_to_lfo2_gain, expression_to_lfo2_gain;
  float breath_to_lfo2_freq, modulation_to_lfo2_freq, expression_to_lfo2_freq;
  float waveshape1_gain, waveshape2_gain, waveshape3_gain, waveshape4_gain;
  float waveshape_modulation_multiplier, waveshape_modulation_multiplier_offset;
};

File  dataFile;

void configureSD() {
  SPI.setMOSI(11); SPI.setSCK(13);
  if (!(SD.begin(10))) {
      Serial.println("Unable to access the SD card");
  }
}

void savePatchSD(int i) {
  Patch p =      {wave1_shape, wave2_shape, wave3_shape, wave4_shape,
                  wave1_pulse_width, wave2_pulse_width, wave3_pulse_width, wave4_pulse_width,
                  wave1_detune_multiplier,wave2_detune_multiplier,wave3_detune_multiplier,wave4_detune_multiplier,
                  wave1_gain,  wave2_gain,  wave3_gain,  wave4_gain,
                  master_volume, reverb_size,
                  noise_pink_gain, noise_white_gain,
                  filter_min_frequency, filter_q,
                  breath_to_pulse_width, breath_to_filter_cutoff, breath_to_filter_resonance, breath_to_overdrive,
                  modulation_to_pulse_width, modulation_to_filter_cutoff, modulation_to_filter_resonance, modulation_to_overdrive,
                  expression_to_pulse_width, expression_to_filter_cutoff, expression_to_filter_resonance, expression_to_portamento, expression_to_overdrive,
                  note_offset, default_tune,
                  effects_oscillators, effects_flange, effects_chorus, effects_delay, effects_delay_ms,
                  portamento_min,
                  wav_gain,
                  lfo1_gain, lfo1_freq, lfo1_range,
                  breath_to_lfo1_gain, modulation_to_lfo1_gain, expression_to_lfo1_gain,
                  breath_to_lfo1_freq, modulation_to_lfo1_freq, expression_to_lfo1_freq,
                  lfo2_gain, lfo2_freq, lfo2_range,
                  breath_to_lfo2_gain, modulation_to_lfo2_gain, expression_to_lfo2_gain,
                  breath_to_lfo2_freq, modulation_to_lfo2_freq, expression_to_lfo2_freq,
                  waveshape1_gain, waveshape2_gain, waveshape3_gain, waveshape4_gain,
                  waveshape_modulation_multiplier, waveshape_modulation_multiplier_offset};
  if (SD.exists(String(String(i, DEC) +".PAT").c_str())) {
    SD.remove(String(String(i, DEC) +".PAT").c_str());
  }
  dataFile = SD.open(String(String(i, DEC) +".PAT").c_str(), FILE_WRITE);
  if(!dataFile) {
    Serial.println("Could not create file");
    wavplayer.play("err.wav");
  } else {
    Serial.print("size: ");
    Serial.print(sizeof(Patch));
    Serial.println();
    dataFile.write((byte*)&p, sizeof(Patch));
    Serial.write((byte*)&p, sizeof(Patch));
    dataFile.close();
  }
}

void loadPatchSD(int i) {
  Patch patch;
  dataFile = SD.open(String(String(i, DEC) +".PAT").c_str());
  if(!dataFile) {
    Serial.println("Could not load file");
    wavplayer.play("err.wav");
  } else {
    int bytes = dataFile.read(&patch, sizeof(Patch));
    Serial.print("Loaded:");Serial.println(bytes, DEC);
    dataFile.close();
    wave1.begin(patch.wave1_shape); 
    wave2.begin(patch.wave2_shape);
    wave3.begin(patch.wave3_shape);
    wave4.begin(patch.wave4_shape);
    wave1_pulse_width = patch.wave1_pulse_width;
    wave2_pulse_width = patch.wave2_pulse_width;
    wave3_pulse_width = patch.wave3_pulse_width;
    wave4_pulse_width = patch.wave4_pulse_width;
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
    lfo1_gain = patch.lfo1_gain;
    lfo1_freq = patch.lfo1_freq;
    lfo1_range = patch.lfo1_range;
    breath_to_lfo1_gain = patch.breath_to_lfo1_gain;
    modulation_to_lfo1_gain = patch.modulation_to_lfo1_gain;
    expression_to_lfo1_gain = patch.expression_to_lfo1_gain;
    breath_to_lfo1_freq = patch.breath_to_lfo1_freq;
    modulation_to_lfo1_freq = patch.modulation_to_lfo1_freq;
    expression_to_lfo1_freq = patch.expression_to_lfo1_freq;
    lfo2_gain = patch.lfo2_gain;
    lfo2_freq = patch.lfo2_freq;
    lfo2_range = patch.lfo2_range;
    breath_to_lfo2_gain = patch.breath_to_lfo2_gain;
    modulation_to_lfo2_gain = patch.modulation_to_lfo2_gain;
    expression_to_lfo2_gain = patch.expression_to_lfo2_gain;
    breath_to_lfo2_freq = patch.breath_to_lfo2_freq;
    modulation_to_lfo2_freq = patch.modulation_to_lfo2_freq;
    expression_to_lfo2_freq = patch.expression_to_lfo2_freq;
    waveshape1_gain = patch.waveshape1_gain;
    waveshape2_gain = patch.waveshape2_gain;
    waveshape3_gain = patch.waveshape3_gain;
    waveshape4_gain = patch.waveshape4_gain;
    waveshape_modulation_multiplier = patch.waveshape_modulation_multiplier;
    waveshape_modulation_multiplier_offset = patch.waveshape_modulation_multiplier_offset;

    updateOSC();
  }
}

void updateOSC() {
  sendcc(CC_WAVE1_SHAPE, wave1_shape);
  sendcc(CC_WAVE2_SHAPE, wave2_shape);
  sendcc(CC_WAVE3_SHAPE, wave3_shape);
  sendcc(CC_WAVE4_SHAPE, wave4_shape);
  sendcc(CC_WAVE1_PULSE_WIDTH, wave1_pulse_width);
  sendcc(CC_WAVE2_PULSE_WIDTH, wave2_pulse_width);
  sendcc(CC_WAVE3_PULSE_WIDTH, wave3_pulse_width);
  sendcc(CC_WAVE4_PULSE_WIDTH, wave4_pulse_width);
  sendcc(CC_WAVE1_DETUNE_MULTIPLIER, wave1_detune_multiplier);
  sendcc(CC_WAVE2_DETUNE_MULTIPLIER, wave2_detune_multiplier);
  sendcc(CC_WAVE3_DETUNE_MULTIPLIER, wave3_detune_multiplier);
  sendcc(CC_WAVE4_DETUNE_MULTIPLIER, wave4_detune_multiplier);
  sendcc(CC_WAVE1_GAIN, wave1_gain);
  sendcc(CC_WAVE2_GAIN, wave2_gain);
  sendcc(CC_WAVE3_GAIN, wave3_gain);
  sendcc(CC_WAVE4_GAIN, wave4_gain);
  sendcc(CC_MASTER_VOLUME, master_volume);
  sendcc(CC_REVERB_ROOM_SIZE, reverb_size);
  sendcc(CC_NOISE_PINK_GAIN, noise_pink_gain);
  sendcc(CC_NOISE_WHITE_GAIN, noise_white_gain);
  sendcc(CC_FILTER_FREQUENCY_OFFSET, filter_min_frequency);
  sendcc(CC_FILTER_RESONANCE_OFFSET, filter_q);
  sendcc(CC_BREATH_TO_PULSE_WIDTH, breath_to_pulse_width);
  sendcc(CC_BREATH_TO_FILTER_CUTOFF, breath_to_filter_cutoff);
  sendcc(CC_BREATH_TO_FILTER_RESONANCE, breath_to_filter_resonance);
  sendcc(CC_BREATH_TO_OVERDRIVE, breath_to_overdrive);
  sendcc(CC_MODULATION_TO_PULSE_WIDTH, modulation_to_pulse_width);
  sendcc(CC_MODULATION_TO_FILTER_CUTOFF, modulation_to_filter_cutoff);
  sendcc(CC_MODULATION_TO_FILTER_RESONANCE, modulation_to_filter_resonance);
  sendcc(CC_MODULATION_TO_OVERDRIVE, modulation_to_overdrive);
  sendcc(CC_EXPRESSION_TO_PULSE_WIDTH, expression_to_pulse_width);
  sendcc(CC_EXPRESSION_TO_FILTER_CUTOFF, expression_to_filter_cutoff);
  sendcc(CC_EXPRESSION_TO_FILTER_RESONANCE, expression_to_filter_resonance);
  sendcc(CC_EXPRESSION_TO_PORTAMENTO, expression_to_portamento);
  sendcc(CC_EXPRESSION_TO_OVERDRIVE, expression_to_overdrive);
  sendcc(CC_NOTE_OFFSET, note_offset);
//  sendcc(CC_DEFAULT_TUNE, default_tune);
  sendcc(CC_EFFECTS_MIXER_CLEAN, effects_oscillators);
  sendcc(CC_EFFECTS_MIXER_FLANGE, effects_flange);
  sendcc(CC_EFFECTS_MIXER_CHORUS, effects_chorus);
  sendcc(CC_EFFECTS_MIXER_DELAY, effects_delay);
  sendcc(CC_EFFECTS_MIXER_DELAY_MS, effects_delay_ms);
  sendcc(CC_PORTAMENTO_MIN, portamento_min);
  sendcc(CC_WAV_PLAYER_GAIN, wav_gain);
  sendcc(CC_LFO1_AMOUNT, lfo1_gain);
  sendcc(CC_LFO1_FREQUENCY, lfo1_freq);
  sendcc(CC_LFO1_RANGE, lfo1_range);
  sendcc(CC_BREATH_TO_LFO1_GAIN, breath_to_lfo1_gain);
  sendcc(CC_MODULATION_TO_LFO1_GAIN, modulation_to_lfo1_gain);
  sendcc(CC_EXPRESSION_TO_LFO1_GAIN, expression_to_lfo1_gain);
  sendcc(CC_BREATH_TO_LFO1_FREQ, breath_to_lfo1_freq);
  sendcc(CC_MODULATION_TO_LFO1_FREQ, modulation_to_lfo1_freq);
  sendcc(CC_EXPRESSION_TO_LFO1_FREQ, expression_to_lfo1_freq);
  sendcc(CC_LFO2_AMOUNT, lfo2_gain);
  sendcc(CC_LFO2_FREQUENCY, lfo2_freq);
  sendcc(CC_LFO2_RANGE, lfo2_range);
  sendcc(CC_BREATH_TO_LFO2_GAIN, breath_to_lfo2_gain);
  sendcc(CC_MODULATION_TO_LFO2_GAIN, modulation_to_lfo2_gain);
  sendcc(CC_EXPRESSION_TO_LFO2_GAIN, expression_to_lfo2_gain);
  sendcc(CC_BREATH_TO_LFO2_FREQ, breath_to_lfo2_freq);
  sendcc(CC_MODULATION_TO_LFO2_FREQ, modulation_to_lfo2_freq);
  sendcc(CC_EXPRESSION_TO_LFO2_FREQ, expression_to_lfo2_freq);
  sendcc(CC_WAVESHAPE1_GAIN, waveshape1_gain);
  sendcc(CC_WAVESHAPE2_GAIN, waveshape2_gain);
  sendcc(CC_WAVESHAPE3_GAIN, waveshape3_gain);
  sendcc(CC_WAVESHAPE4_GAIN, waveshape4_gain);
  sendcc(CC_WAVESHAPE_MODULATION_MULTIPLIER, waveshape_modulation_multiplier);
  sendcc(CC_WAVESHAPE_MODULATION_MULTIPLIER_OFFSET, waveshape_modulation_multiplier_offset);
}

void sendcc(int cc, float value) {
  usbMIDI.sendControlChange(cc, (int)(value*127.0), 0);
}
