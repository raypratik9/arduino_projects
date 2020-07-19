#include <SPI.h>                  /* to handle the communication interface with the modem*/
#include <nRF24L01.h>             /* to handle this particular modem driver*/
#include <RF24.h>                 /* the library which helps us to control the radio modem*/
RF24 radio(7,8);                    /* Creating instance 'radio'  ( CE , CSN )   CE -> D7 | CSN -> D8 */                              
const byte Address[6] = " 00009 " ;     /* Address to which data to be transmitted*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  radio.begin();                /* Activate the modem*/
  radio.openWritingPipe(Address); /* Sets the address of transmitter to which program will send the data */
}
void loop() {
  Serial.print("Transmitting Data : ");
  radio.stopListening ();          /* Setting modem in transmission mode*/
  char value = "hi";    /*Reading analog value at pin A0 and storing in varible 'value'*/
  radio.write(&value, sizeof(value));            /* Sending data over NRF 24L01*/
  Serial.print("Transmitting Data : ");
  Serial.println(value);                           /* Printing POT value on serial monitor*/
}
