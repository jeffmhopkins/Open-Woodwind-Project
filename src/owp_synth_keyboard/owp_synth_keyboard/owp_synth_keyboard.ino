#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformDc     waveform_frequency_mixer_offset_dc; //xy=148,290.25390911102295
AudioSynthWaveformDc     waveform_shape_mixer_offset_dc; //xy=157.75390625,324.7539176940918
AudioSynthWaveformDc     modulation_wheel_dc;            //xy=170.50392150878906,183.75389194488525
AudioSynthWaveformDc     expression_dc; //xy=191.5039176940918,255.7538890838623
AudioSynthWaveformDc     filter_cutoff_offset_dc; //xy=199.00390625,362.253963470459
AudioSynthWaveformDc     breath_dc; //xy=204.50392150878906,221.75389957427979
AudioSynthWaveformDc     glide_frequency_dc; //xy=305.0048828125,782.5048828125
AudioSynthWaveformDc     pitchbend_dc; //xy=313.7548828125,748.7548923492432
AudioMixer4              dummy_mixer; //xy=498.75489044189453,780.0048942565918
AudioSynthWaveformDc     waveform_frequency_vca_dc; //xy=577.00390625,57.00394248962402
AudioSynthWaveformDc     waveform_shape_vca_dc; //xy=580.7539672851562,174.5039186477661
AudioMixer4              shape_mixer; //xy=619.0039291381836,230.0039095878601
AudioMixer4              frequency_mixer;         //xy=620.0039291381836,109.00392580032349
AudioEffectMultiply      multiply2; //xy=775.003963470459,193.00393629074097
AudioEffectMultiply      multiply1;      //xy=780.0040245056152,102.0039324760437
AudioSynthWaveformModulated waveformMod1;   //xy=1002.0039558410645,86.00396203994751
AudioSynthWaveformModulated waveformMod2; //xy=1006.0000152587891,161.00392866134644
AudioSynthWaveformModulated waveformMod7; //xy=1004.9999828338623,515.003933429718
AudioSynthWaveformModulated waveformMod8; //xy=1004.9999256134033,583.0040106773376
AudioSynthWaveformModulated waveformMod3; //xy=1007.0001106262207,231.00389337539673
AudioSynthWaveformModulated waveformMod4; //xy=1008.0000019073486,306.00400257110596
AudioSynthWaveformModulated waveformMod6; //xy=1007.9999675750732,446.0039258003235
AudioSynthWaveformModulated waveformMod5; //xy=1009.0039348602295,377.0039496421814
AudioMixer4              cutoff_mixer; //xy=1109.7539520263672,825.2539939880371
AudioEffectEnvelope      envelope1; //xy=1160.6299209594727,85.00488233566284
AudioEffectEnvelope      envelope3; //xy=1163.1299209594727,230.00488471984863
AudioEffectEnvelope      envelope2; //xy=1164.3799209594727,160.00488376617432
AudioEffectEnvelope      envelope8; //xy=1165.6299209594727,582.5048894882202
AudioEffectEnvelope      envelope6; //xy=1166.8799209594727,445.0048875808716
AudioEffectEnvelope      envelope5; //xy=1169.3799209594727,377.50488662719727
AudioEffectEnvelope      envelope7; //xy=1169.3799209594727,515.004889011383
AudioEffectEnvelope      envelope4; //xy=1170.6299209594727,307.50488567352295
AudioMixer4              envelope_mixer1;         //xy=1367.5041961669922,196.0039520263672
AudioMixer4              envelope_mixer2;         //xy=1376.2540435791016,480.0039348602295
AudioMixer4              envelope_mixer3; //xy=1569.0039901733398,213.50397300720215
AudioFilterStateVariable filter;        //xy=1722.504062652588,302.0039358139038
AudioMixer4              filter_mixer; //xy=1873.0041542053223,304.25390625
AudioEffectChorus        chorus;        //xy=2038.7551727294922,332.5048861503601
AudioEffectFlange        flange;        //xy=2041.2551498413086,376.25488662719727
AudioMixer4              delay_mixer; //xy=2041.2550354003906,450.0048885345459
AudioEffectDelay         delay1;         //xy=2207.5049324035645,480.00488662719727
AudioMixer4              effects_mixer; //xy=2235.0051460266113,318.75488662719727
AudioAmplifier           delay_attenuator3; //xy=2365.9424324035645,495.0048885345459
AudioAmplifier           delay_attenuator2; //xy=2368.4424324035645,462.5048875808716
AudioAmplifier           delay_attenuator1;           //xy=2372.5049324035645,430.0048875808716
AudioEffectFreeverbStereo reverb;     //xy=2431.5039596557617,375.753942489624
AudioMixer4              left; //xy=2596.503963470459,277.00391960144043
AudioMixer4              right; //xy=2598.253993988037,344.0039482116699
AudioOutputI2S           out;           //xy=2727.753974914551,311.75394344329834
AudioConnection          patchCord1(waveform_frequency_mixer_offset_dc, 0, frequency_mixer, 3);
AudioConnection          patchCord2(waveform_shape_mixer_offset_dc, 0, shape_mixer, 3);
AudioConnection          patchCord3(modulation_wheel_dc, 0, frequency_mixer, 0);
AudioConnection          patchCord4(modulation_wheel_dc, 0, shape_mixer, 0);
AudioConnection          patchCord5(modulation_wheel_dc, 0, cutoff_mixer, 0);
AudioConnection          patchCord6(expression_dc, 0, frequency_mixer, 2);
AudioConnection          patchCord7(expression_dc, 0, shape_mixer, 2);
AudioConnection          patchCord8(expression_dc, 0, cutoff_mixer, 2);
AudioConnection          patchCord9(filter_cutoff_offset_dc, 0, cutoff_mixer, 3);
AudioConnection          patchCord10(breath_dc, 0, frequency_mixer, 1);
AudioConnection          patchCord11(breath_dc, 0, shape_mixer, 1);
AudioConnection          patchCord12(breath_dc, 0, cutoff_mixer, 1);
AudioConnection          patchCord13(glide_frequency_dc, 0, dummy_mixer, 1);
AudioConnection          patchCord14(pitchbend_dc, 0, dummy_mixer, 0);
AudioConnection          patchCord15(waveform_frequency_vca_dc, 0, multiply1, 0);
AudioConnection          patchCord16(waveform_shape_vca_dc, 0, multiply2, 0);
AudioConnection          patchCord17(shape_mixer, 0, multiply2, 1);
AudioConnection          patchCord18(frequency_mixer, 0, multiply1, 1);
AudioConnection          patchCord19(multiply2, 0, waveformMod1, 1);
AudioConnection          patchCord20(multiply2, 0, waveformMod2, 1);
AudioConnection          patchCord21(multiply2, 0, waveformMod3, 1);
AudioConnection          patchCord22(multiply2, 0, waveformMod4, 1);
AudioConnection          patchCord23(multiply2, 0, waveformMod5, 1);
AudioConnection          patchCord24(multiply2, 0, waveformMod6, 1);
AudioConnection          patchCord25(multiply2, 0, waveformMod7, 0);
AudioConnection          patchCord26(multiply2, 0, waveformMod7, 1);
AudioConnection          patchCord27(multiply2, 0, waveformMod8, 1);
AudioConnection          patchCord28(multiply1, 0, waveformMod1, 0);
AudioConnection          patchCord29(multiply1, 0, waveformMod2, 0);
AudioConnection          patchCord30(multiply1, 0, waveformMod3, 0);
AudioConnection          patchCord31(multiply1, 0, waveformMod4, 0);
AudioConnection          patchCord32(multiply1, 0, waveformMod5, 0);
AudioConnection          patchCord33(multiply1, 0, waveformMod6, 0);
AudioConnection          patchCord34(multiply1, 0, waveformMod7, 0);
AudioConnection          patchCord35(multiply1, 0, waveformMod8, 0);
AudioConnection          patchCord36(waveformMod1, envelope1);
AudioConnection          patchCord37(waveformMod2, envelope2);
AudioConnection          patchCord38(waveformMod7, envelope7);
AudioConnection          patchCord39(waveformMod8, envelope8);
AudioConnection          patchCord40(waveformMod3, envelope3);
AudioConnection          patchCord41(waveformMod4, envelope4);
AudioConnection          patchCord42(waveformMod6, envelope6);
AudioConnection          patchCord43(waveformMod5, envelope5);
AudioConnection          patchCord44(cutoff_mixer, 0, filter, 1);
AudioConnection          patchCord45(envelope1, 0, envelope_mixer1, 0);
AudioConnection          patchCord46(envelope3, 0, envelope_mixer1, 2);
AudioConnection          patchCord47(envelope2, 0, envelope_mixer1, 1);
AudioConnection          patchCord48(envelope8, 0, envelope_mixer2, 3);
AudioConnection          patchCord49(envelope6, 0, envelope_mixer2, 1);
AudioConnection          patchCord50(envelope5, 0, envelope_mixer2, 0);
AudioConnection          patchCord51(envelope7, 0, envelope_mixer2, 2);
AudioConnection          patchCord52(envelope4, 0, envelope_mixer1, 3);
AudioConnection          patchCord53(envelope_mixer1, 0, envelope_mixer3, 0);
AudioConnection          patchCord54(envelope_mixer2, 0, envelope_mixer3, 1);
AudioConnection          patchCord55(envelope_mixer3, 0, filter, 0);
AudioConnection          patchCord56(filter, 0, filter_mixer, 0);
AudioConnection          patchCord57(filter, 1, filter_mixer, 1);
AudioConnection          patchCord58(filter, 2, filter_mixer, 2);
AudioConnection          patchCord59(filter_mixer, 0, effects_mixer, 0);
AudioConnection          patchCord60(filter_mixer, 0, delay_mixer, 0);
AudioConnection          patchCord61(filter_mixer, chorus);
AudioConnection          patchCord62(filter_mixer, flange);
AudioConnection          patchCord63(chorus, 0, effects_mixer, 1);
AudioConnection          patchCord64(flange, 0, effects_mixer, 2);
AudioConnection          patchCord65(delay_mixer, delay1);
AudioConnection          patchCord66(delay_mixer, 0, effects_mixer, 3);
AudioConnection          patchCord67(delay1, 0, delay_attenuator1, 0);
AudioConnection          patchCord68(delay1, 1, delay_attenuator2, 0);
AudioConnection          patchCord69(delay1, 3, delay_attenuator3, 0);
AudioConnection          patchCord70(effects_mixer, reverb);
AudioConnection          patchCord71(effects_mixer, 0, left, 0);
AudioConnection          patchCord72(effects_mixer, 0, right, 0);
AudioConnection          patchCord73(delay_attenuator3, 0, delay_mixer, 3);
AudioConnection          patchCord74(delay_attenuator2, 0, delay_mixer, 2);
AudioConnection          patchCord75(delay_attenuator1, 0, delay_mixer, 1);
AudioConnection          patchCord76(reverb, 0, left, 1);
AudioConnection          patchCord77(reverb, 1, right, 1);
AudioConnection          patchCord78(left, 0, out, 0);
AudioConnection          patchCord79(right, 0, out, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=2854.5040321350098,313.50390434265137
// GUItool: end automatically generated code

float master_volume  = 0.8;
float reverb_wet     = 0.2;
float reverb_size    = 0.85;
float reverb_damping = 0.999;

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

float filter_frequency      = 1000;
float filter_resonance      = 0.707;
float filter_octave_control = 7;

float envelope_delay          = 0.0;
float envelope_attack         = 5.5;
float envelope_hold           = 2.5;
float envelope_decay          = 35;
float envelope_sustain        = 1.0;
float envelope_release        = 50;
float envelope_release_noteOn = 7;

int waveform_shape = WAVEFORM_SAWTOOTH;

bool noteOn1 = false;
bool noteOn2 = false;
bool noteOn3 = false;
bool noteOn4 = false;
bool noteOn5 = false;
bool noteOn6 = false;
bool noteOn7 = false;
bool noteOn8 = false;

int note1 = -1;
int note2 = -1;
int note3 = -1;
int note4 = -1;
int note5 = -1;
int note6 = -1;
int note7 = -1;
int note8 = -1;

int note_offset = 24; //octave offset


void setup() {
  Serial.begin(115200);
  sgtl5000_1.enable();
  sgtl5000_1.volume(master_volume);
  AudioMemory(1500);
  sgtl5000_1.audioPostProcessorEnable();

  left.gain(0, 1.0 - reverb_wet); //Dry
  left.gain(1, reverb_wet); //Reverb
  right.gain(0, 1.0 - reverb_wet); //Dry
  right.gain(1, reverb_wet); //Reverb

  reverb.roomsize(reverb_size); 
  reverb.damping(reverb_damping);

  effects_mixer.gain(0, 1.0);//Dry
  effects_mixer.gain(1, 0);  //Chorus
  effects_mixer.gain(2, 0);  //Flange
  effects_mixer.gain(3, 0);  //Delay

  chorus.begin(chorus_delayline,CHORUS_DELAY_LENGTH,n_chorus);
  flange.begin(delayline,FLANGE_DELAY_LENGTH,s_idx,s_depth,s_freq);

  filter_mixer.gain(0, 1.0);//Low pass Filter
  filter_mixer.gain(1, 0);  //Band pass
  filter_mixer.gain(2, 0);  //High pass

  filter.frequency(filter_frequency);
  filter.resonance(filter_resonance);
  filter.octaveControl(filter_octave_control);

  envelope_mixer1.gain(0, 0.25);
  envelope_mixer1.gain(1, 0.25);
  envelope_mixer1.gain(2, 0.25);
  envelope_mixer1.gain(3, 0.25);
  envelope_mixer2.gain(0, 0.25);
  envelope_mixer2.gain(1, 0.25);
  envelope_mixer2.gain(2, 0.25);
  envelope_mixer2.gain(3, 0.25);
  envelope_mixer3.gain(0, 0.5);//From envelope_mixer1
  envelope_mixer3.gain(1, 0.5);//From envelope_mixer2

  envelope1.delay(envelope_delay);
  envelope2.delay(envelope_delay);
  envelope3.delay(envelope_delay);
  envelope4.delay(envelope_delay);
  envelope5.delay(envelope_delay);
  envelope6.delay(envelope_delay);
  envelope7.delay(envelope_delay);
  envelope8.delay(envelope_delay);

  envelope1.attack(envelope_attack);
  envelope2.attack(envelope_attack);
  envelope3.attack(envelope_attack);
  envelope4.attack(envelope_attack);
  envelope5.attack(envelope_attack);
  envelope6.attack(envelope_attack);
  envelope7.attack(envelope_attack);
  envelope8.attack(envelope_attack);

  envelope1.decay(envelope_decay);
  envelope2.decay(envelope_decay);
  envelope3.decay(envelope_decay);
  envelope4.decay(envelope_decay);
  envelope5.decay(envelope_decay);
  envelope6.decay(envelope_decay);
  envelope7.decay(envelope_decay);
  envelope8.decay(envelope_decay);


  envelope1.sustain(envelope_sustain);
  envelope2.sustain(envelope_sustain);
  envelope3.sustain(envelope_sustain);
  envelope4.sustain(envelope_sustain);
  envelope5.sustain(envelope_sustain);
  envelope6.sustain(envelope_sustain);
  envelope7.sustain(envelope_sustain);
  envelope8.sustain(envelope_sustain);

  envelope1.release(envelope_release);
  envelope2.release(envelope_release);
  envelope3.release(envelope_release);
  envelope4.release(envelope_release);
  envelope5.release(envelope_release);
  envelope6.release(envelope_release);
  envelope7.release(envelope_release);
  envelope8.release(envelope_release);

  envelope1.releaseNoteOn(envelope_release_noteOn);
  envelope2.releaseNoteOn(envelope_release_noteOn);
  envelope3.releaseNoteOn(envelope_release_noteOn);
  envelope4.releaseNoteOn(envelope_release_noteOn);
  envelope5.releaseNoteOn(envelope_release_noteOn);
  envelope6.releaseNoteOn(envelope_release_noteOn);
  envelope7.releaseNoteOn(envelope_release_noteOn);
  envelope8.releaseNoteOn(envelope_release_noteOn);

  waveformMod1.begin(1.0, 440, waveform_shape); waveformMod1.frequencyModulation(7);
  waveformMod2.begin(1.0, 440, waveform_shape); waveformMod2.frequencyModulation(7);
  waveformMod3.begin(1.0, 440, waveform_shape); waveformMod3.frequencyModulation(7);
  waveformMod4.begin(1.0, 440, waveform_shape); waveformMod4.frequencyModulation(7);
  waveformMod5.begin(1.0, 440, waveform_shape); waveformMod5.frequencyModulation(7);
  waveformMod6.begin(1.0, 440, waveform_shape); waveformMod6.frequencyModulation(7);
  waveformMod7.begin(1.0, 440, waveform_shape); waveformMod7.frequencyModulation(7);
  waveformMod8.begin(1.0, 440, waveform_shape); waveformMod8.frequencyModulation(7);

  frequency_mixer.gain(0,0); //Modulation wheel
  frequency_mixer.gain(1,0); //Breath
  frequency_mixer.gain(2,0); //Expression
  frequency_mixer.gain(3,1); //DC Offset
  waveform_frequency_vca_dc.amplitude(1.0);          //Allows frequency_mixer through to waveforms
  waveform_frequency_mixer_offset_dc.amplitude(0.0); //Sets the DC offset for frequency modulation to waveforms

  shape_mixer.gain(0,0); //Modulation Wheel
  shape_mixer.gain(1,0); //Breath
  shape_mixer.gain(2,0); //Expression
  shape_mixer.gain(3,1); //DC Offset
  waveform_shape_vca_dc.amplitude(1.0);          //Allows shape-mixer through to waveforms
  waveform_shape_mixer_offset_dc.amplitude(0.0); //Sets the DC offset for shape modulation

  modulation_wheel_dc.amplitude(0);
  breath_dc.amplitude(0);
  expression_dc.amplitude(0);
  pitchbend_dc.amplitude(0);
  glide_frequency_dc.amplitude(0);
  filter_cutoff_offset_dc.amplitude(0);
  
  usbMIDI.setHandleNoteOff(myNoteOff);
  usbMIDI.setHandleNoteOn(myNoteOn);
  usbMIDI.setHandleControlChange(myControlChange);
  usbMIDI.setHandleProgramChange(myProgramChange);
}

void loop() {
  usbMIDI.read();
}

void myNoteOn(byte channel, byte note, byte velocity) {
  if(!noteOn1) {
    note1 = (int)note;
    waveformMod1.frequency(pow(2.0, ((float)(24.0 + note + note_offset) / 12.0)));
    waveformMod1.amplitude((float)velocity/127.0);
    envelope1.noteOn();
    noteOn1 = true;
  } else if(!noteOn2) {
    note2 = (int)note;
    waveformMod2.frequency(pow(2.0, ((float)(24.0 + note + note_offset) / 12.0)));
    waveformMod2.amplitude((float)velocity/127.0);
    envelope2.noteOn();
    noteOn2 = true;
  } else if(!noteOn3) {
    note3 = (int)note;
    waveformMod3.frequency(pow(2.0, ((float)(24.0 + note + note_offset) / 12.0)));
    waveformMod3.amplitude((float)velocity/127.0);
    envelope3.noteOn();
    noteOn3 = true;
  } else if(!noteOn4) {
    note4 = (int)note;
    waveformMod4.frequency(pow(2.0, ((float)(24.0 + note + note_offset) / 12.0)));
    waveformMod4.amplitude((float)velocity/127.0);
    envelope4.noteOn();
    noteOn4 = true;
  } else if(!noteOn5) {
    note5 = (int)note;
    waveformMod5.frequency(pow(2.0, ((float)(24.0 + note + note_offset) / 12.0)));
    waveformMod5.amplitude((float)velocity/127.0);
    envelope5.noteOn();
    noteOn5 = true;
  } else if(!noteOn6) {
    note6 = (int)note;
    waveformMod6.frequency(pow(2.0, ((float)(24.0 + note + note_offset) / 12.0)));
    waveformMod6.amplitude((float)velocity/127.0);
    envelope6.noteOn();
    noteOn6 = true;
  } else if(!noteOn7) {
    note7 = (int)note;
    waveformMod7.frequency(pow(2.0, ((float)(24.0 + note + note_offset) / 12.0)));
    waveformMod7.amplitude((float)velocity/127.0);
    envelope7.noteOn();
    noteOn7 = true;
  } else if(!noteOn8) {
    note8 = (int)note;
    waveformMod8.frequency(pow(2.0, ((float)(24.0 + note + note_offset) / 12.0)));
    waveformMod8.amplitude((float)velocity/127.0);
    envelope8.noteOn();
    noteOn8 = true;
  } 
  
}

void myNoteOff(byte channel, byte note, byte velocity) {
    if(noteOn1 & (note1 == (int) note)) {
      envelope1.noteOff();
      note1 = -1;
      noteOn1 = false;
    } else if(noteOn2 & (note2 == (int) note)) {
      envelope2.noteOff();
      note2 = -1;
      noteOn2 = false;
    } else if(noteOn3 & (note3 == (int) note)) {
      envelope3.noteOff();
      note3 = -1;
      noteOn3 = false;
    } else if(noteOn4 & (note4 == (int) note)) {
      envelope4.noteOff();
      note4 = -1;
      noteOn4 = false;
    } else if(noteOn5 & (note5 == (int) note)) {
      envelope5.noteOff();
      note5 = -1;
      noteOn5 = false;
    } else if(noteOn6 & (note6 == (int) note)) {
      envelope6.noteOff();
      note6 = -1;
      noteOn6 = false;
    } else if(noteOn7 & (note7 == (int) note)) {
      envelope7.noteOff();
      note7 = -1;
      noteOn7 = false;
    } else if(noteOn8 & (note8 == (int) note)) {
      envelope8.noteOff();
      note8 = -1;
      noteOn8 = false;
    }  
}
void myControlChange(byte channel, byte control, byte value) {
  switch(control) {
    case 1:
      filter.frequency(   ((float)value / 127.0) * 10000.0   );
      break;
  }
  
}

void myProgramChange(byte channel, byte program) {
  
}
