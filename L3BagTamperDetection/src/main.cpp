// All Defined Libraries
// Work done on tinkercad
#include <SPI.h>
#include <WiFi.h>
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

//HAN Notes - What is this object used for?
WiFiServer server(80);

//set the time
unsigned long timeTriggered;

//Declare ICM
ICM_20948_I2C myICM;

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
  initWifi();

  pinMode(BUZZERPIN, OUTPUT);
  pinMode(SENSORPIN, INPUT);
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
            client.println(OPENINGHTML);
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////Needs Checking from Below////////////////////////////////////////////////7
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //HAN Notes - I would move the getAGMT code here and if it detects movement update some readings
            // output the value of an analog input pin
            int sensorReading = analogRead(SENSORPIN);
            client.print("RAW Sensor value is ");
            client.print(sensorReading);

            //Output different text depending on LED colour
            byte BUZZReading = digitalRead(BUZZERPIN);
            if(BUZZReading == HIGH) {
              client.print("Buzzer is on <br><br>");
            } else {
              client.print("Buzzer is off <br><br>"); 
            }

            // When clicking either an H or L
//HAN Notes - what do we want to turn on or off, think about all the controls you may want for this project
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
//HAN Notes - do you think H and L are good references for buzzer on and off? or could you give more descriptive messages
        // Check for H or L at the end of the address bar
        if(currentLine.endsWith("GET /H")) {
          tone(BUZZERPIN, 1000); // Turn Buzzer on with a 1000HZ signal
        }
        if(currentLine.endsWith("GET /L")) {
          noTone(BUZZERPIN); // GET /L turns led off
        }
      } // End of client.available()
    } // End of while loop
    // close connection with esp32 and as client is not connected
    client.stop();
    Serial.println("client disconnected");
  }
  // Obtain ICM's AGMT readings
  myICM.getAGMT();

}


