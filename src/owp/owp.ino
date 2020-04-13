/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/


/*

The Open Woodwind Project uses the following components:
  Teensy 3.2
  MPR121 (address 0x5A)
  MPR121 (address 0x5B)
  MPX2010GS (going into A0, a few filtering caps installed)
  BNO055
  
  It should be compiled in the Teensy Arduino environment with MIDI + SERIAL board options.

*/

#include <Wire.h>
#include <SPI.h>
#include "Adafruit_MPR121.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#define STATE_NOTE_OFF 0
#define STATE_NOTE_NEW 1
#define STATE_NOTE_ON  2

#define SETTINGS_NOTE_DEBOUNCE_DELAY 20
#define SETTINGS_BREATH_AVERAGING    0.7f
#define SETTINGS_BREATH_GAIN         3.0f
#define SETTINGS_BREATH_THRESHOLD    225
#define SETTINGS_CC_DELAY            0
#define SETTINGS_LEGATO              true
#define SETTINGS_TOUCH_LEVEL         100

#define IMU_RAISE  0
#define IMU_LOWER  1
#define IMU_CENTER 2
#define IMU_CC_POSITIVE false
#define IMU_CC_NEGATIVE true

int state = STATE_NOTE_OFF;

int  note_temp              = 0;                    //Temporary variable used during legato fingering 
int  note_playing           = 0;                    //The MIDI note of the current note being played
int  note_fingered          = 0;                    //The MIDI note of the current note being fingered
bool note_debounce          = false;                //Whether or not we are in debounce wait
long note_debounce_time     = 0;                    //The millis() at time of finger change, start of debounce 
int  note_fingered_debounce = 0;                    //The MIDI note of the current note being fingered during debounce wait
int  note_debounce_delay    = SETTINGS_NOTE_DEBOUNCE_DELAY; //How long to wait in debounce before committing to finer change

int   breath_sent      = 0;                         //The last CC breath message value
int   breath_measured  = 0;                         //Current measured breath
float breath_averaging = SETTINGS_BREATH_AVERAGING; //Percent of new vs old breath
int   breath_threshold = SETTINGS_BREATH_THRESHOLD; //The threshold for breath to trigger a note
long  breath_time      = 0;                         //The millis() at time of threshold breach
int   breath_risetime  = 5;                         //the delay after threshold breach before sampling breath for the first CC message

long  cc_time  = 0;                                 //The millis() at time of last CC send
int   cc_delay = SETTINGS_CC_DELAY;                 //Delay in ms between CC messages

bool  legato = SETTINGS_LEGATO;                     //Legato fingering mode

float deg_y           = 0.0;                        //The angle of the instrument
float deg_y_averaging = 0.5;                        //Smoothing from last loop's poll

float deg_z           = 0.0;                        //The roll of the instrument
float deg_z_averaging = 0.5;                        //Smoothing from last loop's poll

float accel           = 0.0;		            //Accelerometer data
float accel_averaging = 0.5;                        //Smoothing from last loop's poll
float accel_damping   = 1.5;		            //Accelerometer dampening

float imu_deg_init   = 0.0;                         //Placeholder for when we gate our pb buttons, locking in the current instrument angle 
float imu_up_limit   = -40;			    //The up angle for modulation
float imu_down_limit = -60;			    //The down angle for modulation

float imu_roll_deadband = 25;			    //How wide our roll dead band is
float imu_roll_upper_limit = 30;	            //Upper roll limit
float imu_roll_lower_limit = -30;		    //Lower roll limit
boolean imu_roll_active    = false;		    //Is imu roll active

float imu_pb_deg_init   = 0.0;						
float imu_pb_up_limit   = 15;
float imu_pb_down_limit = -15;
float imu_pb_deadband   = 6.0;
bool  imu_pb_active     = false;

Adafruit_MPR121 touchA = Adafruit_MPR121();	     //Actual MPR121 object
Adafruit_MPR121 touchB = Adafruit_MPR121();			
Adafruit_BNO055 bno = Adafruit_BNO055(55);	      //IMU	
sensors_event_t event;				      //IMU event object

bool A[] = {false,false,false,false,false,false,false,false,false,false,false,false}; // These are the arrays for finger positions
bool B[] = {false,false,false,false,false,false,false,false,false,false,false,false};

int CC[128]; 					      //CC array
int pb = 0;					      //pb value

const int ledPin = 13;				      //LED for noteOn (onboard Teensy)


void setup() {
  for(int i = 0; i < 128; i++) {
    CC[i] = 0;
  }
  touchA.begin(0x5A);
  touchB.begin(0x5B);
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  delay(1000);
  bno.setExtCrystalUse(true);
  pinMode(ledPin, OUTPUT);
}
  
void loop() {
  // Update our breath, fingered note, and CC messages
  updateSensors();
      //  // Send CC messages if it is time
      //if(millis() > cc_time + cc_delay) {
        sendCC();
      //  cc_time = millis();
      //}
  
  
  //STATE_NOTE_OFF
  // - Exit to STATE_NOTE_NEW on breath over threshold
  if(state == STATE_NOTE_OFF) {
    if(breath_measured > breath_threshold) {
      breath_time = millis();
      state = STATE_NOTE_NEW;
    }
  }
  
  //STATE_NOTE_NEW
  // - Exit to STATE_NOTE_ON if we make it past the risetime
  // - Exit to STATE_NOTE_OFF if we fall below breath_threshold
  if(state == STATE_NOTE_NEW) {
    if(breath_measured > breath_threshold) {
      if(millis() > breath_time + breath_risetime) {
        sendCC();
        sendNoteOn(note_fingered);
        cc_time = millis();
        digitalWrite(ledPin, HIGH);
        state = STATE_NOTE_ON;
      }
    } else {
      state = STATE_NOTE_OFF;
    }
  }
  
  //STATE_NOTE_ON
  // - Send noteOn/noteOff messages with note changes
  // - Exit to STATE_NOTE_OFF if we fall below breath_threshold
  if(state == STATE_NOTE_ON) {
    if(breath_measured > breath_threshold) {
      // Send CC messages if it is time
      if(millis() > cc_time + cc_delay) {
        sendCC();
        cc_time = millis();
      }
      if(note_fingered != note_playing) {
        if(legato) {
          note_temp = note_playing;
          if(imu_pb_active) {
            imu_pb_deg_init = deg_y;
            usbSendPitchBend(0, 1);
          }
          sendNoteOn(note_fingered);
          sendNoteOff(note_temp);
        } else {
          sendNoteOff(note_playing);
          sendNoteOn(note_fingered);
        }
      }
    } else {
      sendNoteOff(note_playing);
      digitalWrite(ledPin, LOW);
      state = STATE_NOTE_OFF;
    }
  }
  
  while (usbMIDI.read()) {
    // ignore incoming messages
  }
}

void updateSensors() {
  updateBreath();
  updateNote();
  updateCC();
}

void updateBreath() {
  float value = SETTINGS_BREATH_GAIN * analogRead(A0);
  if(value>1023) value = 1023;
  breath_measured = value; //breath_averaging * value + (1.0f - breath_averaging) * breath_measured;
}

void updateNote() {
  note_fingered_debounce = 60 + parseNote(); //Update from capacitive touch board
  if(note_fingered_debounce != note_fingered) {
    if(note_debounce) {
      if(millis() > note_debounce_time + note_debounce_delay) {
        note_fingered = note_fingered_debounce;
        note_debounce = false;
      }
    } else {
      note_debounce_time = millis();
      note_debounce = true;
    }
  }
}

int parseNote() {
	// Mapping as follows: 
	// A[0] = Left Hand Index
	// A[1] = Left Hand Middle
	// A[2] = Left Hand Ring
	// A[3] = Left Hand Pinky 1 (sharp)
	// A[4] = Left Hand Pinky 2 (flat)
	// A[5] = Right Hand Index
	// A[6] = Right Hand Middle
	// A[7] = Right Hand Ring
	// A[8] = Right Hand Pinky 1 (Sharp)
	// A[9] = Right Hand Pinky 2 (Flat)
	// A[10]= Right Hand Pinky 3 (Double Flat)
	// B[0] = Bottom Octave (Left thumb bottom)
	// B[1] = Middle Octave (Left thumb mid)
	// B[2] = Top Octave    (Left thumb top)
	// B[3] = PB gate 
	// B[4] = PB gate
	// B[5] = PB Gate
	//
  for (uint8_t i=0; i<12; i++) {
    A[i] = touchA.filteredData(i) < SETTINGS_TOUCH_LEVEL;
    B[i] = touchB.filteredData(i) < SETTINGS_TOUCH_LEVEL;
  }

  //Determine Register
  bool rh = !A[0] & A[1] & !A[2] & A[5];
  bool rl = !A[5] & A[6] &  A[7] & A[10];
  bool rm = !rh & !rl;

  int note = 13;

  if(rm) {
    if( A[0] & !A[1]) note -= 2;
    if(!A[0] &  A[1]) note -= 1;
    if( A[0] &  A[1]) note -= 4;
    if(A[2]) note -= 2;
    if(A[5]) note -= 2;
    if(A[6]) note -= 1;
    if(A[7]) note -= 2;
  }
  if(rh) {
    note = 17;
    if(A[6]) note -= 1;
    if(!A[5] & A[6]) note += 2;
    if(A[7]) note -= 2;
  }
  if(rl) {
     note = 3;
     if(A[0] & !A[1]) note -= 2;
     if(!A[0] & A[1]) note -= 1;
     if(A[0] & A[1]) note -= 4;
     if(A[2]) note -= 2;
     if(A[5]) note -= 2;
  }
  if(A[3]) note += 1;
  if(A[4]) note -= 1;
  if(A[8]) note += 1;
  if(A[9]) note -= 1;
  if(A[10]) note -= 2;

  //Alt Bb
  if(A[0] & !A[1] & !A[2] & A[5]) note += 1;

  //octaves
  if( B[0] &!B[1])                 note -= 24;  // bottom left
  if( B[0] & B[1])                 note -= 12;  // bottom left mid left bridged
  if(!B[0] & B[1] & !B[2] & !B[4]) note = note; // mid left
  if( B[1] & B[2])                 note += 12;  // mid left top left bridged
  if(!B[1] & B[2])                 note += 24;  // top left

  if(B[3] || B[4] || B[5]) { //If our pitch bend gates are active
    if(!imu_pb_active) {
      imu_pb_active = true;
      imu_pb_deg_init = deg_y;
    }
  }
  
  if(!(B[3] || B[4] || B[5])) {
    imu_pb_active = false;
  }
  
  return note;
}

void sendNoteOn(int note) {
  note_playing = note;
  usbMIDI.sendNoteOn(note, 127, 1);
}

void sendNoteOff(int note) {
  usbMIDI.sendNoteOff(note, 0, 1);
}

void sendCC() {
    sendCC_breath();
    sendCC_pitchbend();
    sendCC_modulation();
}

void sendCC_breath() {
  int b = 0;
  if(state == STATE_NOTE_ON) {
    if(breath_measured < SETTINGS_BREATH_THRESHOLD) breath_measured = SETTINGS_BREATH_THRESHOLD;
    b = map(breath_measured,SETTINGS_BREATH_THRESHOLD,1023,0,127);
  }
  usbSendControlChange(2, b, 1); //Breath
  breath_sent = b;
}

void sendCC_pitchbend() {
  //Pitch bend is pretty messy.... so stay with me here. A lot of mapping, and limits.	
  //In updateCC() we poll our IMU data.
	
  float aa = accel; //aa is now a working copy of the accel value
  float c = 0;      //c is the value that will be send out (the pb value itself)
  
  if(aa > 10) aa = 10; //We limit the raw accel value to +/- 10 for easy mapping, and reasonable limits
  if(aa < -10) aa = -10;
  
  float a = mapf(aa, -10*accel_damping, 10*accel_damping, -8192, 8192); // map it to pb limits, including our dampening values from settings.

  float u = deg_z; //this is again a working copy from the IMU poll, this is the roll value
  float g = 0;     //g is a placeholder for if we are using a CCW pitchbend up
  
  if(u < imu_roll_lower_limit) u = imu_roll_lower_limit; //put the raw deg_z into out limits
  if(u > imu_roll_upper_limit) u = imu_roll_upper_limit;
  
  if(u > imu_roll_deadband/2) { //If we are outside of our rolldeadband we can send some values
    
	//I currently have it sending expression data instead of pitchbend up, when CCW is beyond the deadband.
	
	//CCW Pitchbend Up
    // g = (int)mapf(u, imu_roll_deadband/2, imu_roll_upper_limit, 0, 8192);
    
     
     //CCW Expression
     usbSendControlChange(11, mapf(u, imu_roll_deadband/2, imu_roll_upper_limit, 0, 127), 1);
     
  } else { 
    //still within the deadband, so ensure we are sending expression value of 0
    //CCW Expression
    
    usbSendControlChange(11, 0, 1);
  }
  
  //if we are outside the deadband, map it to pitchbend up/down. This allows for accel shakes inside the deadband to self center, but longer angle changes do full pitch bends.
  if(u < -(imu_roll_deadband/2)) g = (int)mapf(u, -imu_roll_deadband/2, imu_roll_lower_limit, 0, -8192);
  
  
  //If we have our pb gates active
  if(imu_pb_active) {
      float d= deg_y;
      float b = 0;
      
      if(d < imu_pb_deg_init + imu_pb_down_limit) d = imu_pb_deg_init + imu_pb_down_limit;
      if(d > imu_pb_deg_init + imu_pb_up_limit)   d = imu_pb_deg_init + imu_pb_up_limit;
    
      if(d > (imu_pb_deg_init + imu_pb_deadband / 2)) {
         b = mapf(d, imu_pb_deg_init + (imu_pb_deadband / 2), imu_pb_deg_init + imu_pb_up_limit, 0, 8192);
      }
      
      if(d < (imu_pb_deg_init + imu_pb_deadband / 2)) {
         b = mapf(d, imu_pb_deg_init + imu_pb_down_limit,imu_pb_deg_init - (imu_pb_deadband / 2), -8192, 0);
      }
      if((d > (imu_pb_deg_init - imu_pb_deadband / 2)) & (d < (imu_pb_deg_init + imu_pb_deadband / 2))) b = 0;

      c = b - a + g; //cc value = bend angle - accelerometer + roll values
      
      if(c >  8192) c = 8192;
      if(c < -8192) c = -8192;
      usbSendPitchBend((int)c, 1);
      
    } else {
      c = g; //If we're note pb gates active, just use roll values
      if(c >  8192) c = 8192;
      if(c < -8192) c = -8192;
      usbSendPitchBend((int)g, 1);
    }
}

void sendCC_modulation() {
    float d= deg_y;
    if(d < imu_down_limit) d = imu_down_limit;
    if(d > imu_up_limit)   d = imu_up_limit;
    
    usbSendControlChange(1, (int)mapf(d, imu_down_limit, imu_up_limit, 0, 127), 1); //deg

}

void updateCC() {
  //Get instrument Angle in x and y axis
  bno.getEvent(&event);
  deg_y = deg_y_averaging*deg_y + (1.0-deg_y_averaging)*(event.orientation.y);
  deg_z = deg_z_averaging*deg_z + (1.0-deg_z_averaging)*(event.orientation.z);

  //Get instrument acceleration in z axis
  accel = accel_averaging*accel + (1.0-accel_averaging)*(bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL).z());
}

float mapf(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void usbSendControlChange(int cc, int value, int channel) {
  if(CC[cc] != value) {
    usbMIDI.sendControlChange(cc, value, channel);
    CC[cc] = value;
  }
}

void usbSendPitchBend(int value, int channel) {
  if(pb != value) {
    usbMIDI.sendPitchBend(value, channel);
    pb = value;
  }
}
