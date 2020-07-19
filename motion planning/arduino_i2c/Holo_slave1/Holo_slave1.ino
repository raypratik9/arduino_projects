
#include <Wire.h>
#include <I2C_Anything.h>

const byte MY_ADDRESS = 42;

volatile long encoderValueX = 0;
volatile long encX = 0;

void setup()
{
  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);

 Wire.begin (MY_ADDRESS);
 Serial.begin (9600);
  Wire.onRequest(requestEvent);

  attachInterrupt(digitalPinToInterrupt(4), updateEncoderX, RISING);

}  // end of setup

void loop()
{

}  // end of loop

void requestEvent (int howMany)
{
  
  I2C_writeAnything (encX);
  Serial.print(encoderValueX);

} 

 
void updateEncoderX()
{
  Serial.print("here");
  if (digitalRead(2) == digitalRead(4))
    encoderValueX++;
  else
    encoderValueX--;
  if (encoderValueX >= 100)
  {
    encX++;                              //x coordinate increment
    encoderValueX = 0;
  }
  if (encoderValueX  <= -100)
  {
    encX--;
    encoderValueX = 0;
  }
}
