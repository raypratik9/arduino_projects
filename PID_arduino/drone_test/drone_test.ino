#include <Servo.h>

Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;
void setup() {
  Serial.begin(9600);
  motor1.attach(3);
   motor2.attach(5);
   motor3.attach(6);
   motor4.attach(9);
   motor3.writeMicroseconds(2000);
   delay(3000);
   motor3.writeMicroseconds(1000);
   delay(3000);
   }
 


void loop() {
 
motor1.writeMicroseconds(1200);
motor2.writeMicroseconds(1200);
motor3.writeMicroseconds(1500);
motor4.writeMicroseconds(1200);
   }
 
