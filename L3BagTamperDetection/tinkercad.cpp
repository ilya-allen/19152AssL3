// C++ code
const byte HEATBULB = 3;
const byte TEMPSENSOR = A0; 
const byte PRESSENSOR = A1;
const byte DEFAULTTEMP = 35;

unsigned long lastCallbackTime = 0;
int chosenDelay = 5 * 60;
byte chosenTemp = DEFAULTTEMP;

void userPref(byte &chosenTemp) {
  Serial.print("Default Temp: ");
  Serial.println(chosenTemp);
  Serial.println("Choose Your Preffered Temperature: ");
  // Wait for user input
  while(Serial.available() == 0) {
     
  }
  chosenTemp = Serial.parseInt(); // Read user input
  Serial.print("Your Chosen Temp: ");
  Serial.println(chosenTemp);
  Serial.println("Now Choose Your Preffered delay between temperature checks in minutes (shorter time between checks can result in more power usage): ");
  while(Serial.available() == 0) {
     
  }
  chosenDelay = Serial.parseInt() * 60;
  Serial.print("Your Chosen Delay: ");
  Serial.print(chosenDelay / 60);
  Serial.println(" Minutes");
}

void tempCheck(byte val) {
  if(val >= chosenTemp + 1) {
    digitalWrite(HEATBULB, LOW);
  } else if (val <= chosenTemp + 1) {
  	digitalWrite(HEATBULB, HIGH);
  }	else {
  	digitalWrite(HEATBULB, LOW);
  }
}

void setup() {
  Serial.begin(9600);
  Serial.parseInt();
  pinMode(HEATBULB, OUTPUT);
  pinMode(TEMPSENSOR, INPUT);
  pinMode(PRESSENSOR, INPUT);
  userPref(chosenTemp);
}

void loop() {
  byte sensorVal = analogRead(TEMPSENSOR);
  
  if(millis() - lastCallbackTime >= chosenDelay) {
  	tempCheck(sensorVal);
  }
  
  
}
