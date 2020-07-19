#include<Servo.h> 
Servo servo_yaw,servo_roll,servo_pitch,servo_throttle;              
int b=1;
void setup() {
  // put your setup code here, to run once:
 servo_yaw.attach(PA8);
 servo_throttle.attach(PA9);
 servo_roll.attach(PA10);
 servo_pitch.attach(PB6);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  while(b)
  {
    for(int a=0;a<1000;a++)
{
 servo_throttle.writeMicroseconds(980);
 servo_yaw.writeMicroseconds(980);
 servo_roll.writeMicroseconds(1500);
 servo_pitch.writeMicroseconds(1500);
 delay(30);
 b=0;
}
  }
for(int a=0;a<50;a++)
{
  servo_throttle.writeMicroseconds(980);
servo_yaw.writeMicroseconds(1500);
 servo_roll.writeMicroseconds(1500);
 servo_pitch.writeMicroseconds(1500);
}
for(int a=0;a<2000;a++)
{
  servo_throttle.writeMicroseconds(1200);
servo_yaw.writeMicroseconds(1500);
 servo_roll.writeMicroseconds(1500);
 servo_pitch.writeMicroseconds(1500);
}
}
