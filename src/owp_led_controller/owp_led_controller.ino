// This project controlls 6 MOSFETS that PWM two RGB light strips.
// - One knob controls decay of all channels
// - Six CV inputs
// - Six CV outputs

//Using an Arduino Micro
//Input and Output Pin Definitions
int pin_input_decay = A0; // 0-5V, if inputting from 12V eurorack, make sure to scale it to 5V 25mA max
int pin_input_cv1   = A1; // A-Red
int pin_input_cv2   = A2; // A-Green
int pin_input_cv3   = A3; // A-Blue
int pin_input_cv4   = A4; // B-Red
int pin_input_cv5   = A5; // B-Blue
int pin_input_cv6   = A6; // B-Green
int pin_output_pwm1 = 3;  //PWM Only on these pins on the Micro: 3, 5, 6, 9, 10, 11 and 13
int pin_output_pwm2 = 4;
int pin_output_pwm3 = 6;
int pin_output_pwm4 = 9;
int pin_output_pwm5 = 10;
int pin_output_pwm6 = 11;

//Internal variables
int   cv1_raw = 0;
int   cv2_raw = 0;
int   cv3_raw = 0;
int   cv4_raw = 0;
int   cv5_raw = 0;
int   cv6_raw = 0;
float cv1_with_decay = 0;
float cv2_with_decay = 0;
float cv3_with_decay = 0;
float cv4_with_decay = 0;
float cv5_with_decay = 0;
float cv6_with_decay = 0;
int   decay_raw = 0;
float decay_per_loop = 0;

//Settings
float decay_max = 1;
float decay_min = 0.001;


void setup() {
  pinMode(pin_input_decay, INPUT);
  pinMode(pin_input_cv1,   INPUT);
  pinMode(pin_input_cv2,   INPUT);
  pinMode(pin_input_cv3,   INPUT);
  pinMode(pin_input_cv4,   INPUT);
  pinMode(pin_input_cv5,   INPUT);
  pinMode(pin_input_cv6,   INPUT);
  
  pinMode(pin_output_pwm1, OUTPUT);
  pinMode(pin_output_pwm2, OUTPUT);
  pinMode(pin_output_pwm3, OUTPUT);
  pinMode(pin_output_pwm4, OUTPUT);
  pinMode(pin_output_pwm5, OUTPUT);
  pinMode(pin_output_pwm6, OUTPUT);

  analogWrite(pin_output_pwm1, 0);
  analogWrite(pin_output_pwm2, 0);
  analogWrite(pin_output_pwm3, 0);
  analogWrite(pin_output_pwm4, 0);
  analogWrite(pin_output_pwm5, 0);
  analogWrite(pin_output_pwm6, 0);
}

void loop() {
  readInputs();
  writeOutputs();
}

void readInputs() {
  //Read pin values
  decay_raw = analogRead(pin_input_decay); //0-1023   
  cv1_raw = analogRead(pin_input_cv1);
  cv2_raw = analogRead(pin_input_cv2);
  cv3_raw = analogRead(pin_input_cv3);
  cv4_raw = analogRead(pin_input_cv4);
  cv5_raw = analogRead(pin_input_cv5);
  cv6_raw = analogRead(pin_input_cv6);

  //Update Decay
  decay_per_loop = mapFloat(decay_raw, 0, 1023, decay_min, decay_max);

  //Update each CV (better ways to write this, but this is easy and the speed doesn't matter)
  if(cv1_raw > cv1_with_decay) {cv1_with_decay = cv1_raw;} else {cv1_with_decay -= decay_per_loop;}
  if(cv2_raw > cv2_with_decay) {cv2_with_decay = cv2_raw;} else {cv2_with_decay -= decay_per_loop;}
  if(cv3_raw > cv3_with_decay) {cv3_with_decay = cv3_raw;} else {cv3_with_decay -= decay_per_loop;}
  if(cv4_raw > cv4_with_decay) {cv4_with_decay = cv4_raw;} else {cv4_with_decay -= decay_per_loop;}
  if(cv5_raw > cv5_with_decay) {cv5_with_decay = cv5_raw;} else {cv5_with_decay -= decay_per_loop;}
  if(cv6_raw > cv6_with_decay) {cv6_with_decay = cv6_raw;} else {cv6_with_decay -= decay_per_loop;}

}

void writeOutputs() {
  analogWrite(pin_output_pwm1, (int()cv1_with_decay/4.0)); //output is 0-255, so divide by four
  analogWrite(pin_output_pwm2, (int)(cv2_with_decay/4.0));
  analogWrite(pin_output_pwm3, (int)(cv3_with_decay/4.0));
  analogWrite(pin_output_pwm4, (int)(cv4_with_decay/4.0));
  analogWrite(pin_output_pwm5, (int)(cv5_with_decay/4.0));
  analogWrite(pin_output_pwm6, (int)(cv6_with_decay/4.0));
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
