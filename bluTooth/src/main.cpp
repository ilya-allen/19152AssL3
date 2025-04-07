#include <Arduino.h>
#include <ArduinoBLE.h>
/**
 * BLE Connection Life Cycle:
 * Advertising: The peripheral device broadcasts its presence.
 * Scanning: The central device searches for advertising devices.
 * Connection Request: The central device initiates a connection request.
 * Connection Established: The peripheral device accepts the connection.
 * Data Exchange: The central and peripheral devices exchange data.
 * Disconnection: The connection is terminated
 * 
 * Peripheral device is the ESP32
 * Central device is the phone etc
 * another way of saying this is the ESP is a server and your phone is the client
 * 
 * https://reference.arduino.cc/reference/en/libraries/arduinoble/
 * 
 * I use nRF Connect App on my phone to play with these settings
**/

// Bluetooth setup
