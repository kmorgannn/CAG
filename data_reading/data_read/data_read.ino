#include <EEPROM.h>

int SOIL_SENSOR_INPUT_PIN = 0;
int TEMPERATURE_INPUT_PIN = 1;
int LIGHT_INPUT_PIN = 2;
int BAUD = 9600;
int DELAY = 20*1000; //20 seconds
int EEsize = 1024; // size in bytes of your board's 

unsigned char soil;
unsigned char temp;
unsigned char light;
int i = 0;

unsigned char ten_bits_to_char(int bits) {
  int new_bits = map(bits, 0, 1024, 0, 256);
  return (unsigned char)new_bits;
}

void setup()
{
  Serial.begin(BAUD); 
}

void loop()
{
  delay(DELAY);
  for (int i = 0; i < (EEsize/3)*3-2; i += 3) {
    soil = EEPROM.read(i);
    temp = EEPROM.read(i+1);
    light = EEPROM.read(i+2);
    Serial.println(
      ""
      + String((int)soil) + " "
      + String((int)temp) + " "
      + String((int)light) + " "
    ); 
    delay(10);
  }
}
