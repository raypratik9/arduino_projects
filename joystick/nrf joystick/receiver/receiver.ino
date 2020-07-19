#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>
#define motorl 5
#define motorr 6
RF24 radio(7,8);  //csn,ce
const uint8_t pipe = 0xE8E8F0F0E1LL;
uint8_t joystick[2];
void setup() {
  // put your setup code here, to run once:
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
Serial.begin(9600);
radio.begin();
radio.openReadingPipe(1,pipe);
radio.setPALevel(RF24_PA_MIN);
radio.startListening();  
}


void loop() 
{
  // put your main code here, to run repeatedly:

radio.startListening();  
  if(radio.available()>0)
  {
   radio.read(&joystick[0],sizeof(joystick[0]));
   radio.read(&joystick[1],sizeof(joystick[1]));
    Serial.println(joystick[0]);
    Serial.println(joystick[1]);
}
}
