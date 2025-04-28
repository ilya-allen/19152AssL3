#include <Arduino.h>

const byte SENSORPIN = 2;
const byte LEDPIN = 13;
const byte BTNPIN = 3;

int detectionValue = 500;
boolean disabled = false;

// put function declarations here:

void setup() {
  //pinModes
  pinMode(SENSORPIN, INPUT);
  pinMode(LEDPIN, OUTPUT);

  //serial stuff
  Serial.begin(115200);
  while(!Serial) {
    delay(100);
  }
  Serial.println("setup is done");

}

void loop() {
  if(digitalRead(BTNPIN) == HIGH) {
    disabled = !disabled;
  }
  if(analogRead(SENSORPIN) > detectionValue && disabled == false) {
    //call method
    flashLED(1000, 5);
    Serial.println("Smells Bad");
  } else {
    Serial.println("Smells ok");
  }
}

// put function definitions here:
int flashLED(int delayTime, int numTimes) {
  for(int i = 0; i < numTimes; i++) {
    digitalWrite(LEDPIN, HIGH);
    delay(delayTime);
    digitalWrite(LEDPIN, LOW);
    delay(delayTime);
  }
}