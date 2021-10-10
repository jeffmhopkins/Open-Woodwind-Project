// OWP_LED_Controller
// v0.1a - Jeff Hopkins 3/7/2021

// This project controlls 6 MOSFETS that PWM two RGB light strips.
// - One knob controls decay of all channels
// - two CV voltage inputs
// - RGB pots for channel 1 and 2 (6 total)
// - Decay pot 
// - 6 PWM outputs for controlling the mosfets etc

//Using an Arduino Micro
//Input and Output Pin Definitions
int pin_input_cv1        = A0; //14
int pin_input_cv2        = A1; //15
int pin_input_cv1_red    = A2; //16
int pin_input_cv1_blue   = A3; //17
int pin_input_cv1_green  = A4; //18
int pin_input_cv2_red    = A5; //19
int pin_input_cv2_blue   = A6; //4
int pin_input_cv2_green  = A8; //8
int pin_input_decay      = A11;//12
int pin_output_pwm1      = 3;   //PWM Only on these pins on the Micro: 3, 5, 6, 9, 10, 11 and 13
int pin_output_pwm2      = 5;
int pin_output_pwm3      = 6;
int pin_output_pwm4      = 9;
int pin_output_pwm5      = 10;
int pin_output_pwm6      = 11;

//Settings
float   cv_max = 3.3;      //in volts
float   cv_min = 0.1;
float   pulse_max = 255;
float   pulse_min = 0;
float   decay_max = (1024.0/3000.0); //decay from 1024 in decay per ms from 3000 ms


//Internal variables

//Inputs from the Eurorack 3.5mm jacks, dioded to forward only, scaled to 0-5V
int   cv1_raw   = 0;
int   cv2_raw   = 0;

//Pots fed from 5V, wiper to pin
int   cv1_red_raw   = 0;
int   cv1_green_raw = 0;
int   cv1_blue_raw  = 0;
int   cv2_red_raw   = 0;
int   cv2_blue_raw  = 0;
int   cv2_green_raw = 0;
int   decay_raw     = 0;

//CV outputs that take into account the decay
float cv1 = 0;
float cv2 = 0;


//Loop Time
long  last_decay_time = 0;
float loop_decay_amount = 0; //storage variable for loop temp data
float decay_per_ms = 0; //set in the loop


void setup() {
  pinMode(pin_input_cv1,       INPUT);
  pinMode(pin_input_cv2,       INPUT);
  pinMode(pin_input_cv1_red,   INPUT);
  pinMode(pin_input_cv1_blue,  INPUT);
  pinMode(pin_input_cv1_green, INPUT);
  pinMode(pin_input_cv2_red,   INPUT);
  pinMode(pin_input_cv2_blue,  INPUT);
  pinMode(pin_input_cv2_green, INPUT);
  pinMode(pin_input_decay,     INPUT);

  pinMode(pin_output_pwm1, OUTPUT);
  pinMode(pin_output_pwm2, OUTPUT);
  pinMode(pin_output_pwm3, OUTPUT);
  pinMode(pin_output_pwm4, OUTPUT);
  pinMode(pin_output_pwm5, OUTPUT);
  pinMode(pin_output_pwm6, OUTPUT);
  
  last_decay_time = millis();
}

void loop() {
  readInputs();
  writeOutputs();
  
}

void readInputs() {
  //Read pin values
  decay_raw =     analogRead(pin_input_decay);
  
  cv1_raw =       analogRead(pin_input_cv1);
  cv2_raw =       analogRead(pin_input_cv2);
  
  cv1_red_raw =   analogRead(pin_input_cv1_red);
  cv1_blue_raw =  analogRead(pin_input_cv1_blue);
  cv1_green_raw = analogRead(pin_input_cv1_green);
  cv2_red_raw =   analogRead(pin_input_cv2_red);
  cv2_blue_raw =  analogRead(pin_input_cv2_blue);
  cv2_green_raw = analogRead(pin_input_cv2_green);

  //Update our decay first
  decay_per_ms = ((float)decay_raw/1024.0) * decay_max;

  //Calculate our decay max
  loop_decay_amount = (float)decay_per_ms * (float)(millis() - last_decay_time);

  //Reset our timer
  last_decay_time = millis();

  //for each raw, if the value is greater, make it that value
  //  if current value - decay < the raw, just keep it raw 
  if(cv1_raw > cv1) {cv1 = cv1_raw;} else {if((cv1 - loop_decay_amount < cv1_raw)) {cv1 = cv1_raw;} else {cv1 -= loop_decay_amount;}}
  if(cv2_raw > cv2) {cv2 = cv2_raw;} else {if((cv2 - loop_decay_amount < cv2_raw)) {cv2 = cv2_raw;} else {cv2 -= loop_decay_amount;}}
}

void writeOutputs() {
  analogWrite(pin_output_pwm1, (int)mapFloat(cv1*cv1_red_raw,   cv_min*204.8, cv_max*204.8, pulse_min, pulse_max)); 
  analogWrite(pin_output_pwm2, (int)mapFloat(cv1*cv1_blue_raw,  cv_min*204.8, cv_max*204.8, pulse_min, pulse_max)); 
  analogWrite(pin_output_pwm3, (int)mapFloat(cv1*cv1_green_raw, cv_min*204.8, cv_max*204.8, pulse_min, pulse_max)); 
  analogWrite(pin_output_pwm4, (int)mapFloat(cv2*cv2_red_raw,   cv_min*204.8, cv_max*204.8, pulse_min, pulse_max)); 
  analogWrite(pin_output_pwm5, (int)mapFloat(cv2*cv2_blue_raw,  cv_min*204.8, cv_max*204.8, pulse_min, pulse_max)); 
  analogWrite(pin_output_pwm6, (int)mapFloat(cv2*cv2_green_raw, cv_min*204.8, cv_max*204.8, pulse_min, pulse_max)); 
}

float constrainFloat(float in, float minimum, float maximum) {
  if(in <= minimum)
      return minimum;
  if(in >= maximum)
      return maximum;
  return in;
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (constrainFloat(x, in_min, in_max) - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
