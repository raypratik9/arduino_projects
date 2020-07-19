#include <Servo.h>

Servo ail;    //side
Servo ele;   //forward
Servo throttle;
Servo rudo;    //yaw
void setup() {
  Serial.begin(9600);
  ail.attach(3);
   ele.attach(5);
  throttle.attach(6);
   rudo.attach(9); 
 
}
void loop() {
   ail.writeMicroseconds(1200);
  ele.writeMicroseconds(1200);
  throttle.writeMicroseconds(1200);
  rudo.writeMicroseconds(1200);

}
 
