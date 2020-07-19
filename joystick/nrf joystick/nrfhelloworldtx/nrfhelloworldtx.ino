#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7,8); // CE, CSN
const byte address[6] = "010001";
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}
void loop() {
  int text=digitalRead(A0);
   Serial.print(text);
    Serial.println("...");
  radio.write(&text, sizeof(text));
  Serial.println(text);
  delay(100);
}
