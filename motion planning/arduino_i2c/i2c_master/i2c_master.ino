
#include <Wire.h>
#include <I2C_Anything.h>

const byte SLAVE_ADDRESS = 42;

void setup()
{
  Wire.begin ();
}  // end of setup

void loop()
{
    float fnum=300;
    int foo = 3;
    Wire.beginTransmission (SLAVE_ADDRESS);
    I2C_writeAnything (fnum);
    I2C_writeAnything (foo++);
    Wire.endTransmission ();

    delay (200);

}  // end of loop
