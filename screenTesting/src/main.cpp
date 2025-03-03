#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

Adafruit_ST7789 tftScreen = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

/*
Colours From the Library
ST77XX_BLACK
ST77XX_WHITE
ST77XX_RED
ST77XX_GREEN
ST77XX_BLUE
ST77XX_CYAN
ST77XX_MAGENTA
ST77XX_YELLOW
ST77XX_ORANGE
*/

void setup(void)  {
  pinMode(TFT_BACKLITE, OUTPUT);
  pinMode(TFT_12C_POWER, OUTPUT);

  Serial.begin(115200);
  Serial.println("tft screen example code");

  digitalWrite(TFT_BACKLITE, HIGH);
  digitalWrite(TFT_12C_POWER, HIGH);

  delay(10);

  tftScreen.init(135, 240);
  tftScreen.settotation(3);
  tftScreen.fillScreen(ST77XX_BLACK);
  Serial.print("screen height is ");
  Serial.println(tftScreen.height());
  Serial.print("scrren width is ");
  Serial.println(tftScreen.width());

  Serial.println("screen should be ready to go");
}

void loop() {

}