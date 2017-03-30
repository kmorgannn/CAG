#include <EEPROM.h>

int TEMPERATURE_INPUT_PIN = 0;
int BAUD = 9600;
int DELAY = 10; //30 minutes
int TEN_BITS = 1023;
int EEsize = 1024; // size in bytes of your board's 

unsigned char temp;
int i = 0;

unsigned char ten_bits_to_char(int bits) {
  int new_bits = map(bits, 0, 1024, 0, 256);
  return (unsigned char)new_bits;
}

void setup()
{
  pinMode(TEMPERATURE_INPUT_PIN, INPUT);
}

void loop()
{
  temp = ten_bits_to_char(analogRead(TEMPERATURE_INPUT_PIN));
  EEPROM.write(i, temp);
  i = (i+1)%(EEsize);
  delay(DELAY); 
}
