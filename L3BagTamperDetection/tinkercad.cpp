// C++ code
const byte HEATBULB = 3;
const byte TEMPSENSOR = A0; 
const byte PRESSENSOR = A1;
const byte DEFAULTTEMP = 35;

unsigned long lastCallbackTime = 0;
int chosenDelay;
byte chosenTemp = DEFAULTTEMP;


void setup()
{
  Serial.begin(9600);
  pinMode(HEATBULB, OUTPUT);
  pinMode(TEMPSENSOR, INPUT);
  pinMode(PRESSENSOR, INPUT);
}

void loop()
{
  int sensorVal = analogRead(PRESSENSOR);
  Serial.println(sensorVal);

  
}
