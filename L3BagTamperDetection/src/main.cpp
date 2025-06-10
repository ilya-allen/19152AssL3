#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>

// Sensors Pins
const byte LEDPIN = LED_BUILTIN;
const byte SENSORPIN = A5;