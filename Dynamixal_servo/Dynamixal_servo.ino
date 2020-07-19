#include <DynamixelSerial.h>

void setup(){
   Dynamixel.begin(1000000,2);  // Inicialize the servo at 1Mbps and Pin Control 2
}

void loop(){
    Dynamixel.move(8,800);
    delay(2000);
    Dynamixel.move(8,500);
    delay(2000);
}
