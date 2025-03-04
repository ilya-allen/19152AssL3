#include <Adafruit_NeoPixel.h>

const byte RLEDPIN = LED_BUILTIN;
Adafruit_NeoPixel pixels(1, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

void setup() {
    // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(RLEDPIN, OUTPUT);
  pixels.begin();
  pixels.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("red led on");
  digitalWrite(RLEDPIN, HIGH);

  delay(2000);

  Serial.println("red led off");
  digitalWrite(RLEDPIN, LOW);

  delay(2000);

  pixels.setPixelColor(0, pixels.Color(235, 52, 216));

  Serial.println("show new color on neopixel");
  pixels.show();

  delay(200);

  Serial.println("blank neopixel");
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}