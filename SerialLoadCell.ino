/*
  Analog input, analog output, serial output

  Reads an analog input pin, maps the result to a range from 0 to 255 and uses
  the result to set the pulse width modulation (PWM) of an output pin.
  Also prints the results to the Serial Monitor.

  The circuit:
  - potentiometer connected to analog pin 0.
    Center pin of the potentiometer goes to the analog pin.
    side pins of the potentiometer go to +5V and ground
  - LED connected from digital pin 9 to ground

  created 29 Dec. 2008
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogInOutSerial

  Arduino Nano Setup (Wire Colors):
  - Black: Ground
  - Red: 5 V
  - Blue: Load-Cell 1
  - Green: Load-Cell 2
*/

// These constants won't change. They're used to give names to the pins used:
const int analogInPin[2] = {A1, A3};  // Analog input pin that the potentiometer is attached to
//const int digitalInPin = 2;
const unsigned int frame_ms = 1;

int sensorValue[2] = {0,0};        // value read from the pot
int inValue = 0;
int overrun_count = 0;
int loop_count = 0;

unsigned int time_next_sample_ms;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(230400);
  pinMode(analogInPin[0], INPUT);
  pinMode(analogInPin[1], INPUT);
  pinMode(2, INPUT);
}

void loop() {
  time_next_sample_ms += frame_ms;
  if((unsigned)(time_next_sample_ms - millis()) > frame_ms){
    time_next_sample_ms = millis();
    overrun_count++;
  }
  loop_count++;
  while((unsigned)(time_next_sample_ms - millis()) < frame_ms)
      ;
       
  // read the analog in value:
  sensorValue[0] = analogRead(analogInPin[0]);
  sensorValue[1] = analogRead(analogInPin[1]);
//  inValue = digitalRead(digitalInPin);
  // map it to the range of the analog out:
  //outputValue = map(sensorValue, 0, 1023, 0, 255);
  // change the analog out value:
  //analogWrite(analogOutPin, outputValue);

  // print the results to the Serial Monitor:
  Serial.print(sensorValue[0]);
  Serial.print(";");
  Serial.print(sensorValue[1]);
  Serial.print(";");
  Serial.print(inValue);
  Serial.print(";");
  Serial.println(millis()&0xfff, HEX);

//  if((loop_count & 0xff) == 0)
//    Serial.println(overrun_count);  
}
