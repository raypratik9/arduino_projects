#include<Wire.h>                             //Library for I2C Communication functions

byte x =0;
void setup() 

{
  Serial.begin(9600);                        //Begins Serial Communication at 9600 baud rate
  Wire.begin(8);                             // join i2c bus with its slave Address as 8 at pin (A4,A5)
  Wire.onReceive(receiveEvent);              //Function call when Slave Arduino receives value from master STM32
  Wire.onRequest(requestEvent);              //Function call when Master STM32 request value from Slave Arduino
}

void loop() 
{
  delay(100);
}

void receiveEvent (int howMany)              //This Function is called when Slave Arduino receives value from master STM32
{
  byte a = Wire.read();                      //Used to read value received from master STM32 and store in variable a
  
}

void requestEvent()                            //This Function is called when Master STM32 wants value from slave Arduino
{
  x=1;
  Wire.write(x);                             // sends one byte of x value to master STM32
  
}
