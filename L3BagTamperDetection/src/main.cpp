// Below are all the necessary libraries for the code to access and utilise external methods.
// Without outside libraries, we are stuck to the default methods, most of which aren't capabale of accessing the ESP32's demands
#include <SPI.h>
#include <Wire.h>
#include <WiFi.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <ICM_20948.h>
#include <Adafruit_ST7789.h>
#include <Adafruit_AHTX0.h>


//Includes the document storing HTML variables, a shortcut and utilising external code outside of this page
#include "arduinoHTML.h"

// Variables for network and default wifi status
const char SSID[] = "T8-Arduino";  
const char PASSWORD[] = "T8-Arduino";

// This object is intialising a web server that listens for incoming connections on port 80
WiFiServer server(80);

// Variables for sensor values
sensors_event_t humidity, tempAHT;
float tempBMP, pressure, altitude;

// Declare ICM and extra libraries .
ICM_20948_I2C myICM;
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
Adafruit_AHTX0 aht;
Adafruit_BMP280 bmp;


// creating a function which can be called later in the code.
// inside, wifi methods are accessed from the WiFi library and used to initialise the wifi connection between the esp and computer
// messages are also printed into the serial monitor so that the IP can be accessed.
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

// Void setup is called once and that is when the code is initially SETUP.
// Everything inside void setup will only be called once unless inside any loops within the setup.
void setup() {

  // Checking whether or not the serial monitor is active.
  Serial.begin(115200);
  while (!Serial)
  {
    delay(100);
  }

  // After making sure the serial monitor works, the wifi setup function is called.
  initWifi();

  

  // This bit turns on the backlight of the ESP32 Board. Without the light you will be unable to see which pixels are working and which aren't
  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);

  // Turns on the TFT / I2C power supply
  pinMode(TFT_I2C_POWER, OUTPUT);
  digitalWrite(TFT_I2C_POWER, HIGH);
  delay(10);

  // Initialize the TFT
  tft.init(135, 240); // Init ST7789 240x135
  tft.setRotation(3);
  tft.fillScreen(ST77XX_RED); //will blank any previous text on screen

  // Initializes BMP280 and AHT sensors
  if (!bmp.begin()) {
    Serial.println("Could not find BMP280? Check wiring");
    while (1); // stop if sensor not found
  } else {
    Serial.println("BMP280 found");
    bmp.setSampling(Adafruit_BMP280::MODE_FORCED); //take measurements only when requested
  }

  // In case the aht sensors do not begin, warn the user otherwise print that it is found.
  if (!aht.begin()) {
    Serial.println("Could not find AHT? Check wiring");
    while (1); 
  }
  Serial.println("AHT10 or AHT20 found");

  // The WiFi server that was initiallised previously is called to start processing 
  server.begin();
}



// Everything inside this function is constantly forever looped. Everything inside this void Loop is constantly declared through a stack and once the stack is completet it will go back to the top to start again
void loop() {

  // Check if anyones connects to the ESP32
  WiFiClient client = server.available();
  if(client) {
    Serial.println("new client");
    // Variable to hold any incoming data from the browser/client
    String currentLine = "";

    // While the user is connected to the webest, this loop is constantly calling whats inside.
    while(client.connected()) {
      if(client.available()) {
        // Debug check
        char c = client.read();
        Serial.write(c);

        /////
        // if browser sent a newline character
        if(c == '\n') {

          // If the current line is blank
          // end of line
          if(currentLine.length() == 0) {
            // http code for a webpage after some initial setup
            client.println("HTTP/1.1 200 OK");  
            client.println("Content-Type: text/html");
            client.println("Connection: close"); // the connection will be closed after completion of the response
            client.println("Refresh: 5");        // refresh the page automatically every 5 sec
            client.println();

            // The basic html ui code which displays websiute title and headings for the upcoming values
            client.println("<!DOCTYPE html><html><head><title>ESP32 Sensor Dashboard</title></head><body>");
            client.println("<h1 style='text-align: center; font-size: 15px;'>ESP32 Sensor Dashboard</h1>");

            // AHT-Readings which will be displayed as HTML values
            sensors_event_t humidity, tempAHT;
            aht.getEvent(&humidity, &tempAHT);
            client.print("<p><b>AHT20 Temp:</b> ");
            client.print(tempAHT.temperature, 1);
            client.println(" °C</p>");

            // BMP280 Values of both temperature and pressure
            float tempBMP   = bmp.readTemperature();
            float pressure  = bmp.readPressure() / 100.0F;

            // front end values of the BMP280 readings which will be displayed as HTML values
            client.print("<p><b>BMP280 Temp:</b> ");
            client.print(tempBMP, 1);
            client.println(" °C</p>");

            client.print("<p><b>Pressure:</b> ");
            client.print(pressure, 1);
            client.println(" hPa</p>");

            // closing the html front-end
            client.println("</body></html>");
            break; 
            
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


