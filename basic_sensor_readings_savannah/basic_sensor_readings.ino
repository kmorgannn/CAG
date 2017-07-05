int PH_INPUT_PIN = 0;
int DO_INPUT_PIN = 1;
int BAUD = 9600;
int DELAY = 500;

void setup()
{
  Serial.begin(BAUD); 
  pinMode(PH_INPUT_PIN, INPUT);
  pinMode(DO_INPUT_PIN, INPUT);
}

void loop()
{
  Serial.println(
    ""
    + String(analogRead(PH_INPUT_PIN)) + " "
    + String(analogRead(DO_INPUT_PIN)) + " "
    );

  delay(DELAY); 
}
