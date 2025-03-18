

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <WiFi.h>

// Variables for network and default wifi status
const char SSID[] = "T8-Arduino";  
const char PASSWORD[] = "T8-Arduino";



int status = WL_IDLE_STATUS;
// Hexadecimal mac address
byte mac[6];

// tftscreen
Adafruit_ST7789 tftScreen = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);


void setup() {
  //TFT_BACKLITE
  pinMode(TFT_BACKLITE, OUTPUT);
  pinMode(TFT_I2C_POWER, OUTPUT);

  Serial.begin(115200);
  Serial.println("tft screen example code");

  digitalWrite(TFT_BACKLITE, HIGH);
  digitalWrite(TFT_I2C_POWER, HIGH);

  delay(10);

  // init Tft

  tftScreen.init(135, 240);
  tftScreen.setRotation(3);
  tftScreen.fillScreen(ST77XX_RED);

  // serial-setup
  Serial.begin(115200);
  while(!Serial) {
    delay(100);
  }

  // Display MAC Address
  status = WiFi.begin(SSID, PASSWORD);
  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
     
  } 
  
  if(WL_CONNECTED == true) {
    WiFi.macAddress(mac);
    Serial.println("Default MAC address");
    // HEX
    Serial.print(mac[5], HEX);
    Serial.print(":");
    Serial.print(mac[4], HEX);
    Serial.print(":");
    Serial.print(mac[3], HEX);
    Serial.print(":");
    Serial.print(mac[2], HEX);
    Serial.print(":");
    Serial.print(mac[1], HEX);
    Serial.print(":");
    Serial.print(mac[0], HEX);
    Serial.print(":");

    // Display tft
    tftScreen.setCursor(0, 0);
    tftScreen.setTextColor(ST77XX_YELLOW);
    tftScreen.setTextSize(1);
    tftScreen.setTextWrap(true);
    tftScreen.println("Default MAC address");
    Serial.print(mac[5], HEX);
    Serial.print(":");
    Serial.print(mac[4], HEX);
    Serial.print(":");
    Serial.print(mac[3], HEX);
    Serial.print(":");
    Serial.print(mac[2], HEX);
    Serial.print(":");
    Serial.print(mac[1], HEX);
    Serial.print(":");
    Serial.print(mac[0], HEX);
    Serial.print(":");
    
  }

}

void loop() {
  // Blank
}