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

void setup()  {
  pinMode(TFT_BACKLITE, OUTPUT);
  pinMode(TFT_I2C_POWER, OUTPUT);

  Serial.begin(115200);
  Serial.println("tft screen example code");

  digitalWrite(TFT_BACKLITE, HIGH);
  digitalWrite(TFT_I2C_POWER, HIGH);

  delay(10);

  tftScreen.init(135, 240);
  tftScreen.setRotation(3);
  tftScreen.fillScreen(ST77XX_BLACK);
  Serial.print("screen height is ");
  Serial.println(tftScreen.height());
  Serial.print("scrren width is ");
  Serial.println(tftScreen.width());

  Serial.println("screen should be ready to go");
}

void loop() {
  tftScreen.fillScreen(ST77XX_BLACK);

  testdrawtext(
    "lorean mebuians nhinbg itesm ness"
    "shtht sahhng mban bual jhjhf",
    ST77XX_WHITE
  );
  Serial.println("lots of text on screen");
  //pause 2 secs
  delay(2000);

  //call the method
  tftScreenPrintTest();
  Serial.println("hello world x3 in different sizes");
  delay(2000);

  tftScreen.invertDisplay(true);
  Serial.println("inverted colours");
  delay(1000);
  tftScreen.invertDisplay(false);
  Serial.println("normal colours");
  delay(1000);
  Serial.println("repeat loop code"); 
}

void testdrawtext(char *text, uint16_t color) {
  //first cycle of loop
  tftScreen.setCursor(0, 0);
  tftScreen.setTextColor(color);
  tftScreen.setTextWrap(true);

  tftScreen.print(text);
}

void tftScreenPrintTest() {
  tftScreen.setTextWrap(false);
  tftScreen.fillScreen(ST77XX_BLACK);
  
  tftScreen.setCursor(0, 30);

  tftScreen.setTextColor(ST77XX_RED);
  tftScreen.setTextSize(1);
  tftScreen.println("hello");

  tftScreen.setTextColor(ST77XX_YELLOW);
  tftScreen.setTextSize(2);
  tftScreen.println("Hello World!");

  tftScreen.setTextColor(ST77XX_GREEN);
  tftScreen.setTextSize(3);
  tftScreen.println("Hello World!");
  
  
  
}