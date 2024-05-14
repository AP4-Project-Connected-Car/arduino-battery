#include <Wire.h>

#define I2C_SLAVE_ADDRESS 12
#define PAYLOAD_SIZE 2

int sensorPin = "A0";
int sensorValue;
int maxResolutionBits = 10; // Bits number Depends of analogRead resolution
float maxVoltage = 15;
float minVoltage = 0;
float voltage;

void setup()
{
    Serial.begin(9600);

    Wire.begin(I2C_SLAVE_ADDRESS);
    Wire.onRequest(requestEvents);

    pinMode(sensorPin, INPUT);
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void loop()
{
    sensorValue = analogRead(sensorPin);
    voltage = mapfloat(sensorValue, 0, pow(2, maxResolutionBits) - 1, minVoltage, maxVoltage);
    delay(500);
}

void requestEvents()
{
    String to_send;
    to_send = String("{\"data\": ");
    to_send += voltage; // Fill data with value (6 char max)
    to_send += String("}");
    Serial.println(to_send);
    Wire.write(to_send.c_str());
}