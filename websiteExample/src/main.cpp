#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

// Variables for network and default wifi status
const char SSID[] = "T8-Arduino";  
const char PASSWORD[] = "T8-Arduino";

AsyncWebServer server(80);

const byte LEDPIN = LED_BUILTIN;

String ledState;

//Initialize LittleFS
void initLittleFS() {
  if(!LittleFS.begin(true)) {
    Serial.println("An Error has occured while mounting LittleFS");
  } else {
    Serial.println("LittleFS amounted successfully");
  }

}

void initWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  Serial.print("Connecting to wifi...");

  while(WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }

  Serial.print("Use this IP in your browser");
  Serial.println(WiFi.localIP());

}

String processor(const String &VAR) {
  if(VAR == "STATE") {
    if(digitalRead(LEDPIN)) {
      ledState = "ON";
    } else {
      ledState = "OFF";
    }
    return ledState;
  }
  return String();
}

void setup() {
  Serial.begin(115200);
  while(!Serial) {
    delay(100);
  }
  initWifi();
  initLittleFS();
  pinMode(LEDPIN, OUTPUT);
}