// All Defined Libraries
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <ICM_20948.h>

//Includes the document storing HTML variables
#include "arduinoHTML.h"


// Sensors Pins
const byte BUZZERPIN = A4;
const byte SENSORPIN = A5;

// Variables for network and default wifi status
const char SSID[] = "T8-Arduino";  
const char PASSWORD[] = "T8-Arduino";

//set the time
unsigned long lastTriggered;
AsyncWebServer server(80);

//Declare ICM
ICM_20948_I2C myICM;

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

void setup() {
  initWifi();

  pinMode(BUZZERPIN, OUTPUT);
  pinMode(SENSORPIN, INPUT);
}

void loop() {

  //check if anyones connects to the ESP32
  WiFiClient client = server.available();
  if(client) {
    
  }

  // Obtain ICM's AGMT readings
  myICM.getAGMT();

}