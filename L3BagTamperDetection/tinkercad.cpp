// C++ code
// Code written by Il'ya Allen

// Constant (non changing) Variables
const byte HEATBULB = 3;
const byte TEMPSENSOR = A0; 
const byte PRESSENSOR = A1;

// Changing Variables, all number based
unsigned long lastCallbackTime = 0;
int chosenDelay = -1;
int chosenTemp = -1;


// Function that calls upon user preferences, when the user
// starts up the program, the user will be asked for their
// preffered tempereature and delay between checks to save power.
void userPref(int &chosenTemp) {
  // Prints questions into the serial for the user to read.
  Serial.println("Choose Your Preffered Temperature: ");
  while(chosenTemp < 0 || chosenTemp > 60) {
  	while(Serial.available() == 0) {
      
  	}
    chosenTemp = Serial.parseFloat();
    // Wait for correct user input before continuing with next tasks
    if(chosenTemp < 0 || chosenTemp > 60) {
      Serial.println("You have inputed an invalid temperature range. Please stay above 0 degrees and below 60 degrees");
    } else if (chosenTemp > 0 && chosenTemp < 3) {
      Serial.println("You have inputed a boundary temperature. The program will work fine but there are possibilites of slight errors.");
    }
    
  }
  // Read user input
  Serial.print("Your Chosen Temp: ");
  Serial.println(chosenTemp);
  
  // Same as aboved but with changed text and variable names
  Serial.println("Now Choose Your Preffered delay between temperature checks in minutes (shorter time between checks can result in more power usage): ");
  while(chosenDelay < 0 || chosenDelay >  15 * 60) {
  	while(Serial.available() == 0) {
      
  	}
    chosenDelay = Serial.parseFloat() * 60;
    // Wait for correct user input before continuing with next tasks
    if(chosenDelay < 0) {
      Serial.println("You have inputed an invalid delay in mintes. Please stay above 0 minutes and below 15 mintues");
    } else if (chosenDelay > 0 && chosenDelay < 3 * 60) {
      Serial.println("You have inputed a boundary delay. The program will work fine but there are possibilites of slight errors.");
    }
    
  }
  Serial.print("Your Chosen Delay: ");
  Serial.print(chosenDelay / 60);
  Serial.println(" Minutes");
}


// This function is called constantly after however many seconds
// the user determined at the start of the program. 
void tempCheck(byte val) {
  // If statements determining whether to increase or decrease heat
  if(val >= chosenTemp + 1) {
    digitalWrite(HEATBULB, LOW);
  } else if (val <= chosenTemp - 1) {
  	digitalWrite(HEATBULB, HIGH);
  }	else {
  	digitalWrite(HEATBULB, LOW);
  }
}

// Setup calls all functions and completes all tasks that need 
// doing before void loop is reached.
void setup() {
  Serial.begin(9600);
  Serial.parseInt();
  pinMode(HEATBULB, OUTPUT);
  pinMode(TEMPSENSOR, INPUT);
  pinMode(PRESSENSOR, INPUT);
  userPref(chosenTemp);
}


// Main looping block of code. These functions are called
// constantly and non-stop.
void loop() {
  unsigned long currentMillis = millis();
  byte sensorVal = map(((analogRead(TEMPSENSOR) - 20) * 3.04), 0, 1023, -40, 125); // Changes the values into easily outputted options
  //
  if(currentMillis - lastCallbackTime >= chosenDelay * 1000) {
    lastCallbackTime = millis();
  	tempCheck(sensorVal);
  }
  
  
}
