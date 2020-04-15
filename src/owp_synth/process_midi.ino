/*
 * The Open Woodwind Project - OWP_Synth for Woodwind Controllers by Jeff Hopkins
 * 
 * =============================================================================================================================================
 * 
 * This is where all the CC updates happen. Most of the time we just set a variable and the main audio loop
 * handles updating the specific audio objects.
 * 
 * The exception is that we set our modulation, breath, and expression to DC smoothers with ramp rates.
 * 
 * =============================================================================================================================================
 * 
 * The process for adding new CC modulations:
 *       -Add a define in patches.ino                                             EX: #define CC_EXPRESSION_TO_WAVE3_WAVE4_GAIN 112
 *       -Update patches.ino to add the CC to the END of the patch struct:        EX: float breath_to_wave3_wave4_gain, modulation_to_wave3_wave4_gain, expression_to_wave4_wave4_gain;
 *       -Update patches.ino to add the CC to createPatch():                      EX: breath_to_wave3_wave4_gain, modulation_to_wave3_wave4_gain, expression_to_wave4_wave4_gain};
 *       -Update patches.ino to add the CC to initialize_patch():                 EX: expression_to_wave4_wave4_gain = patch.expression_to_wave4_wave4_gain;
 *       -Update patches.ino to add the CC to updateOSC():                        EX: sendcc(CC_EXPRESSION_TO_WAVE3_WAVE4_GAIN, expression_to_wave4_wave4_gain);
 *       -Update process_midi.ino to add the CC to procesMIDI():                  EX: case CC_EXPRESSION_TO_WAVE3_WAVE4_GAIN:expression_to_wave4_wave4_gain = data2f;break;
 *       -Update loop() to modify the value:                                      EX: wave3_wave4_gain_modulation_mixer.gain(2, expression_to_wave4_wave4_gain);
 *       
 *       NOTE: if needed, make sure the value is modified in setup() as well      EX: wave3_wave4_gain_modulation_mixer.gain(2, 0.0);
 *       
 * =============================================================================================================================================
 *       
 *  TODO1: maybe define a CC handler class that has the following?
 *    int CC;
 *    int value;
 *    void setup();
 *    void loop();
 *    float save();
 *    void load(float);
 *    void sendToOSC();
 *    void processMIDI();
 *    
 *    This would make creating custom modulations a little easier, however the process avove is not that arduous
 */

void processMIDI(void) {
  byte type, data1, data2;
  type = usbMIDI.getType();       // which MIDI message, 128-255
  data1 = usbMIDI.getData1();     // first data byte of message, 0-127
  data2 = usbMIDI.getData2();     // second data byte of message, 0-127
  float data2f = data2/127.0;

  switch (type) {
    case usbMIDI.NoteOff: // 0x80
      if(note == data1) { //if this noteOff message matches are currently playing note
        breath.amplitude(0.0, breath_ramp_rate_note_off);
        noteon = false;
      }
      break;
      
    case usbMIDI.NoteOn: // 0x90
    AudioNoInterrupts();
      if(noteon) {
        if((pitchbend_value < -8155) | (pitchbend_value > 8155)) {
          pitchbend.amplitude(0.0);
          glide_frequency.amplitude((pow(2.0, ((float)(24+data1+note_offset+tuning_value)/12.0))/wave_freq));
        } else {
          glide_frequency.amplitude((pow(2.0, ((float)(24+data1+note_offset+tuning_value)/12.0))/wave_freq), portamento_min_multiplier * portamento_max + expression.read() * (portamento_max - portamento_min_multiplier * portamento_max) * expression_to_portamento);
        }
      } else {
        glide_frequency.amplitude((pow(2.0, ((float)(24+data1+note_offset+tuning_value)/12.0))/wave_freq));
      }
      note = data1;
      noteon = true;
      if(lfo_reset_phase_on_new_note!=0.0) {//No phase change at 0 (can be set to 127 for start of sample)
        lfo1.phase(lfo_reset_phase_on_new_note*360);
        lfo2.phase(lfo_reset_phase_on_new_note*360);
      }
      AudioInterrupts();
      break;

    case usbMIDI.ControlChange: // 0xB0
      switch(data1) {
        case CC_MODULATION_WHEEL:
          modulation.amplitude(data2f, modulation_ramp_rate);sendcc(CC_MODULATION_WHEEL, data2*127.0);
          break;
        case CC_BREATH:
          if(noteon) {breath.amplitude(lin_to_log(data2, 127, breath_gamma)/127.0, breath_ramp_rate);sendcc(CC_BREATH, data2*127.0);}
          break;
        case CC_EXPRESSION:
          expression.amplitude(data2f, expression_ramp_rate);sendcc(CC_EXPRESSION, data2*127.0);
          break;
        case CC_BREATH_TO_PULSE_WIDTH:
          breath_to_pulse_width = data2f;
          break;
        case CC_BREATH_TO_FILTER_CUTOFF:
          breath_to_filter_cutoff = data2f;
          break;
        case CC_BREATH_TO_FILTER_RESONANCE: 
          breath_to_filter_resonance = data2f;
          break;
        case CC_BREATH_TO_OVERDRIVE: 
          breath_to_overdrive = data2f;
          break;
        case CC_MODULATION_TO_PULSE_WIDTH: 
          modulation_to_pulse_width = data2f;
          break;
        case CC_MODULATION_TO_FILTER_CUTOFF: 
          modulation_to_filter_cutoff = data2f;
          break;
        case CC_MODULATION_TO_FILTER_RESONANCE:
          modulation_to_filter_resonance = data2f;
          break; 
        case CC_MODULATION_TO_OVERDRIVE: 
          modulation_to_overdrive = data2f;
          break;
        case CC_EXPRESSION_TO_PULSE_WIDTH: 
          expression_to_pulse_width = data2f;
          break;
        case CC_EXPRESSION_TO_FILTER_CUTOFF: 
          expression_to_filter_cutoff = data2f;
          break;
        case CC_EXPRESSION_TO_FILTER_RESONANCE: 
          expression_to_filter_resonance = data2f;
          break;
        case CC_EXPRESSION_TO_PORTAMENTO:
          expression_to_portamento = data2f;
          break; 
        case CC_EXPRESSION_TO_OVERDRIVE: 
          expression_to_overdrive = data2f;
          break;
        case CC_PORTAMENTO_MIN_MULTIPLIER:
          portamento_min_multiplier = data2f;
          break; 
        case CC_WAV_PLAYER: 
          if(data2==0) {
            wavplayer.stop();
          } else {
            if(wavplayer.isPlaying()) {
                wavplayer.stop();
            }
            wavplayer.play(String(String(data2, DEC) +".WAV").c_str());
          }
          break;
        case CC_WAV_PLAYER_GAIN: 
          wav_gain = data2f;
          break;
        case CC_LOAD_PATCH:
          loadPatchSD(data2);
          break; 
        case CC_SAVE_PATCH: 
          savePatchSD(data2);
          savePatchEEPROM();
          break;
        case CC_WAVE1_SHAPE: 
          if(data2 < 32) {
            wave1.begin(WAVEFORM_SINE);
            wave1_shape = WAVEFORM_SINE;
          } else if(data2 < 64) {
            wave1.begin(WAVEFORM_SAWTOOTH);
            wave1_shape = WAVEFORM_SAWTOOTH;
          } else if(data2 < 96) {
            wave1.begin(WAVEFORM_PULSE);
            wave1_shape = WAVEFORM_PULSE;
          } else {
            wave1.begin(WAVEFORM_TRIANGLE_VARIABLE);
            wave1_shape = WAVEFORM_TRIANGLE_VARIABLE;
          }
          break;
        case CC_WAVE2_SHAPE: 
            if(data2 < 32) {
            wave2.begin(WAVEFORM_SINE);
            wave2_shape = WAVEFORM_SINE;
          } else if(data2 < 64) {
            wave2.begin(WAVEFORM_SAWTOOTH);
            wave2_shape = WAVEFORM_SAWTOOTH;
          } else if(data2 < 96) {
            wave2.begin(WAVEFORM_PULSE);
            wave2_shape = WAVEFORM_PULSE;
          } else {
            wave2.begin(WAVEFORM_TRIANGLE_VARIABLE);
            wave2_shape = WAVEFORM_TRIANGLE_VARIABLE;
          }
          break;
        case CC_WAVE3_SHAPE: 
           if(data2 < 32) {
            wave3.begin(WAVEFORM_SINE);
            wave3_shape = WAVEFORM_SINE;
          } else if(data2 < 64) {
            wave3.begin(WAVEFORM_SAWTOOTH);
            wave3_shape = WAVEFORM_SAWTOOTH;
          } else if(data2 < 96) {
            wave3.begin(WAVEFORM_PULSE);
            wave3_shape = WAVEFORM_PULSE;
          } else {
            wave3.begin(WAVEFORM_TRIANGLE_VARIABLE);
            wave3_shape = WAVEFORM_TRIANGLE_VARIABLE;
          }
          break;
        case CC_WAVE4_SHAPE: 
          if(data2 < 32) {
            wave4.begin(WAVEFORM_SINE);
            wave4_shape = WAVEFORM_SINE;
          } else if(data2 < 64) {
            wave4.begin(WAVEFORM_SAWTOOTH);
            wave4_shape = WAVEFORM_SAWTOOTH;
          } else if(data2 < 96) {
            wave4.begin(WAVEFORM_PULSE);
            wave4_shape = WAVEFORM_PULSE;
          } else {
            wave4.begin(WAVEFORM_TRIANGLE_VARIABLE);
            wave4_shape = WAVEFORM_TRIANGLE_VARIABLE;
          }
          break;
        case CC_WAVE1_GAIN: 
          wave1_gain = (data2f);
          break;
        case CC_WAVE2_GAIN:
          wave2_gain = (data2f);
          break; 
        case CC_WAVE3_GAIN: 
          wave3_gain = (data2f);
          break;
        case CC_WAVE4_GAIN: 
          wave4_gain = (data2f);
          break;
        case CC_WAVE1_DETUNE_MULTIPLIER:
          wave1_detune_multiplier = data2f*0.75+0.25;
          break; 
        case CC_WAVE2_DETUNE_MULTIPLIER:
          wave2_detune_multiplier = data2f*0.75+0.25;
          break; 
        case CC_WAVE3_DETUNE_MULTIPLIER:
          wave3_detune_multiplier = data2f*0.75+0.25;
          break; 
        case CC_WAVE4_DETUNE_MULTIPLIER:
          wave4_detune_multiplier = data2f*0.75+0.25;
          break; 
        case CC_WAVE1_PULSE_WIDTH:
          wave1_pulse_width = (data2f);
          break; 
        case CC_WAVE2_PULSE_WIDTH: 
          wave2_pulse_width = (data2f);
          break;
        case CC_WAVE3_PULSE_WIDTH: 
          wave3_pulse_width = (data2f);
          break;
        case CC_WAVE4_PULSE_WIDTH:
          wave4_pulse_width = (data2f);
          break; 
        case CC_FILTER_RESONANCE_OFFSET:
          filter_q = data2f*3;
          break; 
        case CC_NOTE_OFFSET: 
          note_offset=(int)(data2-64);
          break;
        case CC_FINE_TUNING: 
          default_tune=(data2f/2+0.75);
          break;
        case CC_MASTER_VOLUME: 
          master_volume = data2f;
          break;
        case CC_FILTER_FREQUENCY_OFFSET:
          //filter_min_frequency = data2f*5000.0;
          filter_min_frequency = data2f;
          break; 
        case CC_NOISE_PINK_GAIN: 
          noise_pink_gain = data2f;
          break;
        case CC_NOISE_WHITE_GAIN: 
          noise_white_gain = data2f;
          break;
        case CC_EFFECTS_MIXER_CLEAN:
          effects_oscillators = data2f;
          break; 
        case CC_EFFECTS_MIXER_FLANGE:
          effects_flange = data2f;
          break; 
        case CC_EFFECTS_MIXER_CHORUS: 
          effects_chorus = data2f;
          break;
        case CC_EFFECTS_MIXER_DELAY: 
          effects_delay = data2f;
          break;
        case CC_REVERB_ROOM_SIZE: 
          reverb_size = data2f;
          break;
        case CC_EFFECTS_MIXER_DELAY_MS:  
          effects_delay_ms = data2f * 250;
          delay1.delay(0, effects_delay_ms);
          delay1.delay(1, effects_delay_ms*2);
          delay1.delay(2, effects_delay_ms*3);
          delay1.delay(3, effects_delay_ms*4);  
          break;     
        case CC_LFO1_FREQUENCY:
          lfo1_freq = data2f;
          break;
        case CC_LFO1_AMOUNT:
          lfo1_gain = data2f;
          break;
        case CC_LFO1_RANGE:
          lfo1_range = data2f;
          break;
        case CC_BREATH_TO_LFO1_GAIN:
          breath_to_lfo1_gain = data2f;
          break;
        case CC_MODULATION_TO_LFO1_GAIN:
          modulation_to_lfo1_gain = data2f;
          break;
        case CC_EXPRESSION_TO_LFO1_GAIN:
          expression_to_lfo1_gain = data2f;
          break;
        case CC_BREATH_TO_LFO1_FREQ:
          breath_to_lfo1_freq = data2f;
          break;
        case CC_MODULATION_TO_LFO1_FREQ:
          modulation_to_lfo1_freq = data2f;
          break;
        case CC_EXPRESSION_TO_LFO1_FREQ:
          expression_to_lfo1_freq = data2f;
          break;
        case CC_BREATH_TO_LFO1_RANGE:
          breath_to_lfo1_range = data2f;
          break;
        case CC_MODULATION_TO_LFO1_RANGE:
          modulation_to_lfo1_range = data2f;
          break;
        case CC_EXPRESSION_TO_LFO1_RANGE:
          expression_to_lfo1_range = data2f;
          break;
        case CC_LFO2_FREQUENCY:
          lfo2_freq = data2f;
          break;
        case CC_LFO2_AMOUNT:
          lfo2_gain = data2f;
          break;
        case CC_LFO2_RANGE:
          lfo2_range = data2f;
          break;
        case CC_BREATH_TO_LFO2_GAIN:
          breath_to_lfo2_gain = data2f;
          break;
        case CC_MODULATION_TO_LFO2_GAIN:
          modulation_to_lfo2_gain = data2f;
          break;
        case CC_EXPRESSION_TO_LFO2_GAIN:
          expression_to_lfo2_gain = data2f;
          break;
        case CC_BREATH_TO_LFO2_FREQ:
          breath_to_lfo2_freq = data2f;
          break;
        case CC_MODULATION_TO_LFO2_FREQ:
          modulation_to_lfo2_freq = data2f;
          break;
        case CC_EXPRESSION_TO_LFO2_FREQ:
          expression_to_lfo2_freq = data2f;
          break;
        case CC_BREATH_TO_LFO2_RANGE:
          breath_to_lfo2_range = data2f;
          break;
        case CC_MODULATION_TO_LFO2_RANGE:
          modulation_to_lfo2_range = data2f;
          break;
        case CC_EXPRESSION_TO_LFO2_RANGE:
          expression_to_lfo2_range = data2f;
          break;
        case CC_WAVESHAPE1_GAIN:
          waveshape1_gain = data2f;
          break;
        case CC_WAVESHAPE2_GAIN:
          waveshape2_gain = data2f;
          break;
        case CC_WAVESHAPE3_GAIN:
          waveshape3_gain = data2f;
          break;
        case CC_WAVESHAPE4_GAIN:
          waveshape4_gain = data2f;
          break;
        case CC_WAVESHAPE_MODULATION_MULTIPLIER:
          waveshape_modulation_multiplier = data2f;
          break;
        case CC_WAVESHAPE_MODULATION_MULTIPLIER_OFFSET:
          waveshape_modulation_multiplier_offset = data2f;
          break;
        case CC_WAVESHAPE_CLEAN_GAIN:
          waveshape_clean_gain = data2f;
          break;
        case CC_LFO1_DESTINATION_FREQUENCY:
          lfo1_destination_frequency = data2f;
          break;
        case CC_LFO1_DESTINATION_GAIN:
          lfo1_destination_gain = data2f;
          break;
        case CC_LFO1_DESTINATION_FILTER:
          lfo1_destination_filter = data2f;
          break;
        case CC_LFO2_DESTINATION_FREQUENCY:
          lfo2_destination_frequency  = data2f;
          break;
        case CC_LFO2_DESTINATION_GAIN:
          lfo2_destination_gain = data2f;
          break;
        case CC_LFO2_DESTINATION_FILTER:
          lfo2_destination_filter = data2f;
          break;
        case CC_LFO_RESET_PHASE_ON_NEW_NOTE:
          lfo_reset_phase_on_new_note = data2f;
          break;
        case CC_BREATH_TO_WAVE3_WAVE4_GAIN:
          breath_to_wave3_wave4_gain = data2f;
          break;
        case CC_MODULATION_TO_WAVE3_WAVE4_GAIN:
          modulation_to_wave3_wave4_gain = data2f;
          break;
        case CC_EXPRESSION_TO_WAVE3_WAVE4_GAIN:
          expression_to_wave4_wave4_gain = data2f;
          break;
        case CC_WAVE3_WAVE4_GAIN_MODULATION_OFFSET:
          wave3_wave4_gain_modulation_offset = data2f;
          break;
        case CC_VCA_GATE_BYPASS:
          vca_gate_bypass = data2f;
          break;
        case CC_FILTER_BYPASS:
          filter_bypass = data2f;
          break;
        case CC_FILTER_TYPE:
          filter_type = data2f;
          break;
      }
      break;


    case usbMIDI.PitchBend: // 0xE0
      pitchbend.amplitude((data1+data2*128.0-8192.0)/8192.0, pitchbend_ramp_rate);
      pitchbend_value = data1+data2*128.0-8192.0;
      break;

    default:
      break;
  }
}
