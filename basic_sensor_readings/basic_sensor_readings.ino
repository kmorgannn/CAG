int SOIL_SENSOR_INPUT_PIN = 0;
int TEMPERATURE_INPUT_PIN = 1;
int LIGHT_INPUT_PIN = 2;
int BAUD = 9600;
int DELAY = 100;
int TEN_BITS = 1023;

void setup()
{
  Serial.begin(BAUD); 
  pinMode(SOIL_SENSOR_INPUT_PIN, INPUT);
  pinMode(TEMPERATURE_INPUT_PIN, INPUT);
  pinMode(LIGHT_INPUT_PIN, INPUT);
}

void loop()
{
  Serial.println(
    ""
    + String(TEN_BITS - analogRead(SOIL_SENSOR_INPUT_PIN)) + " "
    + String(TEN_BITS - analogRead(TEMPERATURE_INPUT_PIN)) + " "
    + String(TEN_BITS - analogRead(LIGHT_INPUT_PIN)) + " "
    );

  delay(DELAY); 
}
