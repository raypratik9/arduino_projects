
#include <Wire.h>
#include <I2C_Anything.h>

const byte SLAVE_ADDRESS = 42;

 long x;
volatile long y;

void setup()
{
  Wire.begin ();
  Serial.begin(9600);

}  // end of setup


void loop()
{
    Wire.requestFrom(42, 4);    // request 6 bytes from slave device #8

  while (Wire.available()) 
  { // slave may send less than requested
    I2C_readAnything (x);// receive a byte as character
    Serial.print(x);         // print the character
  
  }
   Wire.requestFrom(43, 4);  
   
   while (Wire.available()) 
  { // slave may send less than requested
    I2C_readAnything (y);// receive a byte as character
    Serial.print(y);         // print the character
  
  }
Serial.println();
}  // end of loop
