#include <EEPROM.h>

int BUTTON = 12;
int SOIL_SENSOR_INPUT_PIN = 0;
int TEMPERATURE_INPUT_PIN = 1;
int LIGHT_INPUT_PIN = 2;
int BAUD = 9600;
int DELAY = 100; //1/10 second
int WRITE_DELAY = 1000*30; //30 minutes
int BUTTON_BOUNCE = 1000*10; //10 seconds
int TEN_BITS = 1023;
int EEsize = 1024; // size in bytes of your board's 

unsigned char soil;
unsigned char temp;
unsigned char light;
int i = 0;
int ms=0;
int button_time=BUTTON_BOUNCE;


unsigned char ten_bits_to_char(int bits) {
  int new_bits = map(bits, 0, 1024, 0, 256);
  return (unsigned char)new_bits;
}
unsigned char bit_to_char(int bitt) {
  return (unsigned char)bitt;
}

void setup()
{
  Serial.begin(BAUD); 
  pinMode(SOIL_SENSOR_INPUT_PIN, INPUT);
  pinMode(TEMPERATURE_INPUT_PIN, INPUT);
  pinMode(LIGHT_INPUT_PIN, INPUT);
  pinMode(BUTTON, INPUT);
}

void loop()
{
  // if we push the button, dump data over the serial port
  if ((digitalRead(BUTTON) == HIGH) && (button_time > BUTTON_BOUNCE)) {
      button_time = 0;
      for (int j = 0; j < (EEsize/3)*3-2; j += 3) {
        soil = EEPROM.read(j);
        temp = EEPROM.read(j+1);
        light = EEPROM.read(j+2);
        Serial.println(
          ""
          + String((int)soil) + " "
          + String((int)temp) + " "
          + String((int)light) + " "
        ); 
        delay(10);
      }
  }
  if (!(ms%WRITE_DELAY)) {
      soil = ten_bits_to_char(analogRead(SOIL_SENSOR_INPUT_PIN));
      temp = ten_bits_to_char(analogRead(TEMPERATURE_INPUT_PIN));
      light = bit_to_char(digitalRead(LIGHT_INPUT_PIN));
      EEPROM.write(i, soil);
      EEPROM.write(i+1, temp);
      EEPROM.write(i+2, light);
      i = (i+3)%((EEsize/3)*3);
  }
  button_time += DELAY;
  delay(DELAY); 
}
