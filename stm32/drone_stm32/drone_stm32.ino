#include<Servo.h>
Servo servo_yaw, servo_roll, servo_pitch, servo_throttle;
int b = 1;
void Arm();
void DisArm();
void Ready_to_fly();
void Motor_testing();

void Arm()
{
  for (int a = 0; a < 1000; a++)
  {
    servo_throttle.writeMicroseconds(980);
    servo_yaw.writeMicroseconds(980);
    servo_roll.writeMicroseconds(1500);
    servo_pitch.writeMicroseconds(1500);
    delay(30);
    b = 0;
  }
}
void DisArm()
{
  for (int a = 0; a < 1000; a++)
  {
    servo_throttle.writeMicroseconds(980);
    servo_yaw.writeMicroseconds(2000);
    servo_roll.writeMicroseconds(1500);
    servo_pitch.writeMicroseconds(1500);
    delay(10);
  }
}
void Ready_to_fly()
{
  servo_throttle.writeMicroseconds(980);
  servo_yaw.writeMicroseconds(1500);
  servo_roll.writeMicroseconds(1500);
  servo_pitch.writeMicroseconds(1500);
}
void Motor_testing()
{
  servo_throttle.writeMicroseconds(1100);
  servo_yaw.writeMicroseconds(1500);
  servo_roll.writeMicroseconds(1500);
  servo_pitch.writeMicroseconds(1500);

}
void motor_calibrate()
{
  for (int c = 0; c < 7; c++)
  {
    Motor_testing();
    Ready_to_fly();
    delay(400);
  }
}
  void setup() {
    // put your setup code here, to run once:
    servo_yaw.attach(PA8);
    servo_throttle.attach(PA9);
    servo_roll.attach(PA10);
    servo_pitch.attach(PB6);
  }

  void loop() {
    // put your main code here, to run repeatedly:
   while(b)
   Arm();
   Ready_to_fly();
   Motor_testing();
  }
