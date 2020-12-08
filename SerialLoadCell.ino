/*
  Read the input of two load-cells and print them with the current motor-direction and the time in milliseconds
*/

// These constants won't change. They're used to give names to the pins used:
const int analogInPin[2] = {A1, A3};  // Analog input pin that the potentiometer is attached to
//const int digitalInPin = 2; // Digital input to read current Motor-Direction (HIGH == Down, LOW == Up)
const unsigned int frame_ms = 1;  // Determining the Samplerate

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
  inValue = digitalRead(digitalInPin);

  // print the results to the Serial Monitor:
  Serial.print(sensorValue[0]);
  Serial.print(";");
  Serial.print(sensorValue[1]);
  Serial.print(";");
  Serial.print(inValue);
  Serial.print(";");
  Serial.println(millis()&0xfff, HEX);
}
