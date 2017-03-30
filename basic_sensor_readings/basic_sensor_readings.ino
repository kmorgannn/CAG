int TEMPERATURE_INPUT_PIN = 0;
int BAUD = 9600;
int DELAY = 100;
int TEN_BITS = 1023;

void setup()
{
  Serial.begin(BAUD); 
  pinMode(TEMPERATURE_INPUT_PIN, INPUT);
}

void loop()
{
  Serial.println(
    ""
    + String(TEN_BITS - analogRead(TEMPERATURE_INPUT_PIN)) + " "
    );

  delay(DELAY); 
}
