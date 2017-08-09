#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,20,4);  // set the LCD address to 0x3F for a 20 chars and 4 line display

void setup()
{
  lcd.init();                      // initialize the lcd   
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("| | |-- |  |  --- |");  
  lcd.setCursor(0,1);
  lcd.print("|-| |-  |  |  | | |");
  lcd.setCursor(0,2);
  lcd.print("| | |-- |_ |_ --- o");
}

void loop()
{
}
