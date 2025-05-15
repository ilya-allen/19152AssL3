#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

// Variables for network and default wifi status
const char SSID[] = "T8-Arduino";  
const char PASSWORD[] = "T8-Arduino";

// Create an async web server
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

  // Server.on defines a route handler. It awaits a request and tells your server what to do when a specific url is received
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    // When the request is received, it sends a file. The file sent is the index.html which is the main file. The false means not to store any cache
    request->send(LittleFS, "/index.html", "text/html", false, processor); 
  });
  // Make everyfile easily requestable by LittleFS web server, eg. style and script.
  server.serveStatic("/", LittleFS, "/");
  // Same route handler which this time when it receives a request , not only sends the index.html main file but also turns on the LED
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request) {
    digitalWrite(LEDPIN, HIGH);
    request->send(LittleFS, "/index.html", "text/html", false, processor);
  });

  // Same but turns the lef off  
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request) {
    digitalWrite(LEDPIN, LOW);
    request->send(LittleFS, "/index.html", "text/html", false, processor);
  });

  //turn on the server
  server.begin();

}

void loop() {}
