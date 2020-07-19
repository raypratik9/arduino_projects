#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>
#define joyx A0
#define joyy A1
RF24 radio(7,8);  //csn,ce
const uint8_t pipe = 0xE8E8F0F0E1LL;
uint8_t joystick[2];

void setup() {
  // put your setup code here, to run once:
  pinMode(5,INPUT);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  radio.begin();
radio.openWritingPipe(pipe);
radio.setPALevel(RF24_PA_MIN);
radio.stopListening();  
}


void loop() {
  // put your main code here, to run repeatedly:
joystick[0]=digitalRead(A0);
joystick[1]=digitalRead(A1);
radio.write(&joystick[0],sizeof(joystick[0]));
radio.write(&joystick[1],sizeof(joystick[1]));
}
