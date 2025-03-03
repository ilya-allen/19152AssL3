
#include <ESP32Servo.h>

const byte SERVOPIN = 18;

Servo exampleServo;
String name = "Il'ya Allen";
int servoPos = 0;

void setup() {
  exampleServo.setPeriodHertz(50);
  exampleServo.attach(SERVOPIN, 500, 2400);

  Serial.begin(115200);
  Serial.println("Srl Monitor Example");

  Serial.print("What is your name?");
  if (Serial.available() > 0){
    name = Serial.readStringUntil('\n');
  }
  Serial.print("Meet your Padre:");
  Serial.println(name);
}

void loop(){
  Serial.println("where should the servo move? pick 0 - 180");
  if(Serial.available() > 0){
    servoPos = Serial.parseInt();
  }
  exampleServo.write(servoPos);
  Serial.print("servo moving to ");
  Serial.println(servoPos);
  delay(500); 
}