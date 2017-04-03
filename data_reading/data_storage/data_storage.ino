#include <EEPROM.h>

int SOIL_SENSOR_INPUT_PIN = 0;
int TEMPERATURE_INPUT_PIN = 1;
int LIGHT_INPUT_PIN = 2;
int BAUD = 9600;
int DELAY = 10; //30 minutes
int TEN_BITS = 1023;
int EEsize = 1024; // size in bytes of your board's 

unsigned char soil;
unsigned char temp;
unsigned char light;
int i = 0;

unsigned char ten_bits_to_char(int bits) {
  int new_bits = map(bits, 0, 1024, 0, 256);
  return (unsigned char)new_bits;
}
unsigned char bit_to_char(int bitt) {
  return (unsigned char)bitt;
}

void setup()
{
  pinMode(SOIL_SENSOR_INPUT_PIN, INPUT);
  pinMode(TEMPERATURE_INPUT_PIN, INPUT);
  pinMode(LIGHT_INPUT_PIN, INPUT);
}

void loop()
{
  soil = ten_bits_to_char(analogRead(SOIL_SENSOR_INPUT_PIN));
  temp = ten_bits_to_char(analogRead(TEMPERATURE_INPUT_PIN));
  light = bit_to_char(digitalRead(LIGHT_INPUT_PIN));
  EEPROM.write(i, soil);
  EEPROM.write(i+1, temp);
  EEPROM.write(i+2, light);
  i = (i+3)%((EEsize/3)*3);
  delay(DELAY); 
}
