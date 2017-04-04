#include <EEPROM.h>

int BUTTON = 12;
int PH_SENSOR_INPUT_PIN = 0;
int O2_INPUT_PIN = 1;
int BAUD = 9600;
int DELAY = 100; //1/10 second
int WRITE_DELAY = 1000; //30 minutes
int BUTTON_BOUNCE = 1000*10; //10 seconds
int TEN_BITS = 1023;
int EEsize = 1024; // size in bytes of your board's 

unsigned char ph;
unsigned char o2;
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
  pinMode(PH_SENSOR_INPUT_PIN, INPUT);
  pinMode(O2_INPUT_PIN, INPUT);
  pinMode(BUTTON, INPUT);
}

void loop()
{
  // if we push the button, dump data over the serial port
  if ((digitalRead(BUTTON) == HIGH) && (button_time > BUTTON_BOUNCE)) {
      button_time = 0;
      for (int j = 0; j < (EEsize/2)*2-1; j += 2) {
        ph = EEPROM.read(j);
        o2 = EEPROM.read(j+1);
        Serial.println(
          ""
          + String((int)ph) + " "
          + String((int)o2) + " "
        ); 
        delay(10);
      }
  }
  if (!(ms%WRITE_DELAY)) {
      ph = ten_bits_to_char(analogRead(PH_SENSOR_INPUT_PIN));
      o2 = ten_bits_to_char(analogRead(O2_INPUT_PIN));
      EEPROM.write(i, ph);
      EEPROM.write(i+1, o2);
      i = (i+2)%((EEsize/2)*2);
  }
  button_time += DELAY;
  delay(DELAY); 
}
