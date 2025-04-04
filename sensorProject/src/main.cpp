#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

const byte SENSORPIN = A5;

Adafruit_ST7789 tftScreen = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  pinMode(SENSORPIN, INPUT);

  pinMode(TFT_BACKLITE, OUTPUT);
  pinMode(TFT_I2C_POWER, OUTPUT);

  // turn on backlight by setting it to HIGH
  digitalWrite(TFT_BACKLITE, HIGH);
  // turn on the screen by setting it to HIGH
  digitalWrite(TFT_I2C_POWER, HIGH);
  delay(10);

  //init TFT
  tftScreen.init(135, 240);
  tftScreen.setRotation(3);
  tftScreen.fillScreen(ST77XX_WHITE);

  //SERIAL-SETUP
  Serial.begin(115200);
  while(!Serial) {
    delay(100);
  }
}

void loop() {
  int sensorValue = analogRead(SENSORPIN);

  //display the raw reading on screen
  tftScreen.setCursor(0, 0);
  tftScreen.setTextColor(ST77XX_BLACK);
  tftScreen.setTextSize(1);
  tftScreen.setTextWrap(true);
  tftScreen.print("Sensor reading is");
  tftScreen.println(sensorValue);

  sensorValue = map(sensorValue, 0, 1023, 0, 4);
  switch(sensorValue) {
    case 0:
      tftScreen.println("under 30cm");
      break;
    case 1:
      tftScreen.println("31 to 50cm");
      break;
    case 2:
      tftScreen.println("51 to 70cm");
      break;
    case 3:
      tftScreen.println("71 to 90m");
      break;
    case 4:
      tftScreen.println("over 90cm");
      break;
    default:
      tftScreen.println("Map of sensor vals is not working correctly");
      break;
    
  }
}