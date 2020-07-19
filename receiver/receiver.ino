#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>
#define motorl 5
#define motorr 6
RF24 radio(7,8);  //csn,ce
const uint8_t pipe = 0xE8E8F0F0E1LL;
unsigned int joystick;
void setup() {
  // put your setup code here, to run once:
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
Serial.begin(9600);
radio.begin();
radio.openReadingPipe(0,pipe);
radio.setPALevel(RF24_PA_MIN);
radio.startListening();  
}


void loop() 
{ 
  // put your main code here, to run repeatedly:
  if(radio.available())
  {
   joystick=radio.read(&joystick,sizeof(joystick));
  Serial.print(joystick);
  }
}
