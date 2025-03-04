#include <Adafruit_GFX.h>

const byte BTNPIN = 2;
const byte LEDPIN = 13;

int ledState = HIGH;
int buttonState;
int lastButtonState = LOW;

unsigned long debounceDelay = 50;
unsigned long lastDebounceTime = 0;


void setup() {
  pinMode(BTNPIN, INPUT);
  pinMode(LEDPIN, OUTPUT);

  analogWrite(LEDPIN, ledState)
}

void loop() {
  int reading = digitalRead(BTNPIN);
  if(reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if((millis() - lastDebounceTime) > debounceDelay) {
    if(reading != buttonState) {
      buttonState = reading;
      if(buttonState == HIGH) {
        ledState = !ledState;
      }
    }    
  }
  digitalWrite(LEDPIN, ledState);
  lastButtonState = reading;
    
}
