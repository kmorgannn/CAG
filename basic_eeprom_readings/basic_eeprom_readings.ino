#include <EEPROM.h>

int SOIL_SENSOR_INPUT_PIN = 0;
int TEMPERATURE_INPUT_PIN = 1;
int LIGHT_INPUT_PIN = 2;
int BAUD = 9600;
int DELAY = 100;
int EIGHT_BITS = 255;
int j=0;
int soil;
int temp;
int light;
int EEsize=1024;

void setup(){  
  Serial.begin(BAUD); 
}

void loop()
{
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
      delay(1000*10);
}
