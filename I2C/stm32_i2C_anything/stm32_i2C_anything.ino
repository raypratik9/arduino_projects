
#include <Wire.h>
#include <I2C_Anything.h>

const byte SLAVE_ADDRESS = 42;
union Buffer
{
  int ticks[3];     //first coordinate for x and next for y.
  byte section[4];
} coordinate;  

void setup()
{
  Wire.begin ();
  Serial.begin(9600);

}  // end of setup


void loop()
{
    Wire.requestFrom(42, 12);    // request 2 bytes from slave device #8

  while (Wire.available()) 
  { // slave may send less than requested
//    for (int i = 0; i < 2; i++)
    I2C_readAnything (coordinate.ticks[0]);// receive a byte as character
//    for (int i = 0; i < 2; i++)
    I2C_readAnything (coordinate.ticks[1]);
    I2C_readAnything (coordinate.ticks[2]);
    Serial.print(coordinate.ticks[0]); 
    Serial.print("      ");
      Serial.print(coordinate.ticks[1]);      // print the character
  Serial.print("      ");
   Serial.print(coordinate.ticks[2]); 
  Serial.println();
  }
}  // end of loop
