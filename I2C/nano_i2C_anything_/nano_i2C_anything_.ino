
#include <Wire.h>
#include <I2C_Anything.h>

const byte MY_ADDRESS = 42;

long encX = 410;
long encY = 511;
long encZ=-16;
void setup()
{

 Wire.begin (MY_ADDRESS);
 Serial.begin (9600);
  Wire.onRequest(requestEvent);

}  // end of setup

void loop()
{

}  // end of loop

void requestEvent (int howMany)
{
  
  I2C_writeAnything (encX);
  I2C_writeAnything (encY);
  I2C_writeAnything (encZ);
} 
