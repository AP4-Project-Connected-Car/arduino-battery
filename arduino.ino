#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

int sensorValue;
int maxVoltage = 5;
int minVoltage = 0;

void setup()
{
  Serial.begin(9600);
  lcd.init();
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void loop()
{
  sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  float x = mapfloat(sensorValue, 0, 1023, minVoltage, maxVoltage);
  lcd.setCursor(0, 0);
  lcd.print(" Volt : ");
  lcd.print(x*0.914);
  Serial.println(x*0.914);
  delay(2000);
}
