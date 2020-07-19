
#include <Wire.h>
#include <I2C_Anything.h>

const byte MY_ADDRESS = 43;

volatile long encoderValueY= 0;
volatile long encY = 0;

void setup()
{
  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(2), updateEncoderY, RISING);

  Wire.begin (MY_ADDRESS);
  Serial.begin (9600);
  Wire.onRequest(requestEvent);
}  // end of setup

void loop()
{
Serial.println(encY);
}  // end of loop

void requestEvent (int howMany)
{
  
  I2C_writeAnything (encY);
  Serial.println(encY);

} 

 
void updateEncoderY()
{
  if (digitalRead(2) == digitalRead(4))
    encoderValueY++;
  else
    encoderValueY--;
  if (encoderValueY >= 100)
  {
    encY++;                              //y coordinate increment
    encoderValueY = 0;
  }
  if (encoderValueY  <= -100)
  {
    encY--;
    encoderValueY = 0;
  }
}
