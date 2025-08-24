// All Defined Libraries
// Work done on tinkercad
#include <SPI.h>
#include <Wire.h>
#include <WiFi.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <ICM_20948.h>
#include <Adafruit_ST7789.h>
#include <Adafruit_AHTX0.h>


//Includes the document storing HTML variables
#include "arduinoHTML.h"


// Sensors Pins
const byte BUZZERPIN = A4;
const byte SENSORPIN = A5;

// Variables for network and default wifi status
const char SSID[] = "T8-Arduino";  
const char PASSWORD[] = "T8-Arduino";

//HAN Notes - What is this object used for?
WiFiServer server(80);


//set the time
unsigned long timeTriggered;

// ---- Variables ----
sensors_event_t humidity, tempAHT;
float tempBMP, pressure, altitude;

//Declare ICM and Extra Libraries.
ICM_20948_I2C myICM;
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
Adafruit_AHTX0 aht;
Adafruit_BMP280 bmp;


/**
  * HAN Notes - give a brief overview of this method
  */
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

/**
  * HAN Notes - give a brief overview of this method
  */
void setup() {
  Serial.begin(115200);
  initWifi();

  
  while (!Serial)
  {
    delay(100);
  }

  // turn on backlite
  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);

  // turn on the TFT / I2C power supply
  pinMode(TFT_I2C_POWER, OUTPUT);
  digitalWrite(TFT_I2C_POWER, HIGH);
  delay(10);

  // initialize TFT
  tft.init(135, 240); // Init ST7789 240x135
  tft.setRotation(3);
  tft.fillScreen(ST77XX_RED); //will blank any previous text on screen
  pinMode(BUZZERPIN, OUTPUT);
  pinMode(SENSORPIN, INPUT);

  //initialize BMP280 and AHT sensors
  if (!bmp.begin()) {
    Serial.println("Could not find BMP280? Check wiring");
    while (1)
      ; // stop if sensor not found
  } else {
    Serial.println("BMP280 found");
    bmp.setSampling(Adafruit_BMP280::MODE_FORCED); //take measurements only when requested
  }


  if (!aht.begin())
  {
    Serial.println("Could not find AHT? Check wiring");
    while (1)
      ; 
  }
  Serial.println("AHT10 or AHT20 found");
  //HAN Notes - what does this code do?
  server.begin();
}

/**
  * HAN Notes - give a brief overview of this method
  */
void loop() {

  //check if anyones connects to the ESP32
  WiFiClient client = server.available();
  if(client) {
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

            // Now printing basic to check values
            client.println("<!DOCTYPE html><html><head><title>ESP32 Sensor Dashboard</title></head><body>");
            client.println("<h1>ESP32 Sensor Dashboard</h1>");

            // AHT-Readings
            sensors_event_t humidity, tempAHT;
            aht.getEvent(&humidity, &tempAHT);
            client.print("<p><b>AHT20 Temp:</b> ");
            client.print(tempAHT.temperature, 1);
            client.println(" °C</p>");

            // --- BMP280 readings ---
            float tempBMP   = bmp.readTemperature();
            float pressure  = bmp.readPressure() / 100.0F;
            float altitude  = bmp.readAltitude(1013.25);

            client.print("<p><b>BMP280 Temp:</b> ");
            client.print(tempBMP, 1);
            client.println(" °C</p>");

            client.print("<p><b>Pressure:</b> ");
            client.print(pressure, 1);
            client.println(" hPa</p>");


            client.println("</body></html>");
            break;  // break out after serving page
            
          } else {
            // Clear variable if first new line
            currentLine = "";
          }
        } else if(c != '\r') {
          currentLine += c; // add to end of currentline
        }
      } // End of client.available()
    } // End of while loop
    // close connection with esp32 and as client is not connected
    client.stop();
    Serial.println("client disconnected");
  }

}


