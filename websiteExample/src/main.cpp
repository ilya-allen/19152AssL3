#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <Arduino_JSON.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>

#include "arduino_secrets.h"

// Variables for network and default wifi status
const char SSID[] = "T8-Arduino";  
const char PASSWORD[] = "T8-Arduino";

AsyncEventSource events("/events");
JSONVar readings;

unsigned long lastTime = 0;
unsigned long timerDelay = 30000;
Adafruit_BMP280 bmp;

// Create an async web server
AsyncWebServer server(80);

const byte LEDPIN = LED_BUILTIN;
const byte SENSORPIN = A5;

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

void initBMP() {
  if(!bmp.begin()) {
    Serial.println("Couldn't find the BMP80 Sensor, Check Wiring!");
    while(1)
      ;
  }
}

String getSensorReadings() {
  // 100.0F means taking the pressure reading and divide into a floating point so you don't have 25.5 become 25
  readings["pressure"] = String(bmp.readPressure()/100.0F);

  String jsonString = JSON.stringify(readings);
  return jsonString;
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
 // initLittleFS();
  initBMP();
  pinMode(LEDPIN, OUTPUT);
  pinMode(SENSORPIN, INPUT);

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

  //Request for last sensor readings
  server.on("/readings", HTTP_GET, [](AsyncWebServerRequest *request){
    String json = getSensorReadings();
    request->send(200, "application/json", json);
    json = String();
  }); 
  events.onConnect([](AsyncEventSourceClient * client) {
    if(client->lastId()) {
      Serial.printf("Client Reconnected! Last message ID that it got is: %u\n", client->lastId());
    }
    //send event with message hello id current millis
    client->send("Hello!", NULL, millis(), 10000);
  });
  server.addHandler(&events);

  //turn on the server
  server.begin();

}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    // Variable to hold any incoming data from the browser/client
    String currentLine = "";

    // while they are connected
    while(client.connected()) {
      if(client.available()) {
        // another var to hold any incoming
        char c = client.read();
        Serial.write(c);

        /////
        // if browser sent a newline character
        if(c == '\n') {

          // If the current line is blank
          // end of line
          if(currentLine.length() == 0) {
            // http code for a webpage after some initial
            client.println("HTTP/1.1 200 OK");  
            client.println("Content-Type: text/html");
            client.println("Connection: close"); // the connection will be closed after completion of the response
            client.println("Refresh: 5");        // refresh the page automatically every 5 sec
            client.println();
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("<style>html{font-family: Arial;}</style>");
            client.println("<h1>Sensor stuff</h1>");

            // output the value of an analog input pin
            int sensorReading = analogRead(SENSORPIN);
            client.print("RAW Sensor value is ");
            client.print(sensorReading);

            //Output different text depending on LED colour
            byte LEDReading = digitalRead(LEDPIN);
            if(LEDReading == HIGH) {
              client.print("Red LED is on <br><br>");
            } else {
              client.print("Red LED is off <br><br>"); 
            }

            // When clicking either an H or L

            client.print("Click <a href=\"/H\">here</a> turn the LED on<br>");
            client.print("Click <a href=\"/H\">here</a> turn the LED off<br>");

            client.println("</html>");
            break;
          } else {
            // Clear variable if first new line
            currentLine = "";
          }
        } else if(c != '\r') {
          currentLine += c; // add to end of currentline
        }

        // Check for H or L at the end of the address bar
        if(currentLine.endsWith("GET /H")) {
          digitalWrite(LEDPIN, HIGH); // GET /H turns led on
        }
        if(currentLine.endsWith("GET /L")) {
          digitalWrite(LEDPIN, LOW); // GET /L turns led off
        }
      } // End of client.available()
    } // End of while loop
    // close connection with esp32 and as client is not connected
    client.stop();
    Serial.println("client disconnected");
  }
  if((millis() - lastTime) > timerDelay) {
    // Send events to the client with the sensor readings every 30 seconds
    events.send("ping", NULL, millis());
    events.send(getSensorReadings().c_str(), "new_reading", millis());
    lastTime = millis();
  }
}
