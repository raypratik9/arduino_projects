

#include <PS4USB.h>
#include <Servo.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>
Servo servo_left,servo_right;
USB Usb;
PS4USB PS4(&Usb);

bool printAngle, printTouch;
uint8_t oldL2Value, oldR2Value;
#define m4 5
#define m1 2
#define m2 3
#define m3 4
#define d1 23
#define d2 25
#define d3 27
#define d4 29 



void setup() {
  Serial.begin(115200);
  servo_left.attach(6);
 servo_right.attach(13);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // Halt
  }
  Serial.print(F("\r\nPS4 USB Library Started")); 

    
  // put your setup code here, to run once:
  
  
  pinMode(m1,OUTPUT);
  pinMode(m2,OUTPUT);
  pinMode(m3,OUTPUT);
  pinMode(d1,OUTPUT);
  pinMode(d2,OUTPUT);
  pinMode(d3,OUTPUT);

}
float s1,s2,s3,s4,x,y,w,sf;
int d_1,d_2,d_3,d_4;
void loop() {
   Usb.Task();
  // put your main code here, to run repeatedly:
if(PS4.connected())
{
 if (PS4.getAnalogHat(LeftHatX) > 137 || PS4.getAnalogHat(LeftHatX) < 117 || PS4.getAnalogHat(LeftHatY) > 137 || PS4.getAnalogHat(LeftHatY) < 117 || PS4.getAnalogHat(RightHatX) > 137 || PS4.getAnalogHat(RightHatX) < 117 || PS4.getAnalogHat(RightHatY) > 137 || PS4.getAnalogHat(RightHatY) < 117) {
     

x=PS4.getAnalogHat(LeftHatX);
y=PS4.getAnalogHat(LeftHatY);
w=PS4.getAnalogHat(RightHatX);
x=map(x,0,255,255,-255);
y=map(y,0,255,-255,255);
w=map(w,0,255,-255,255);

float sf=1;
s1=sf*(-0.35*x+0.35*y+0.25*w);
s2=sf*(-0.35*x-0.35*y+0.25*w);
s3=sf*(0.35*x-0.35*y+0.25*w);
s4=sf*(0.1768*x+0.35*y+0.25*w);

d_1=(s1>0?1:0);
d_2=(s2>0?1:0);
d_3=(s3>0?1:0);
d_4=(s4>0?1:0);
digitalWrite(d1,d_1);
digitalWrite(d2,d_2);
digitalWrite(d3,d_3);
digitalWrite(d4,d_4);

analogWrite(m1,abs(s1));
analogWrite(m2,abs(s2));
analogWrite(m3,abs(s3));
analogWrite(m4,abs(s4));

}
else
{
analogWrite(m1,0);
analogWrite(m2,0);
analogWrite(m3,0);
analogWrite(m4,0);
  
}
if (PS4.getButtonClick(UP))
{
  servo_left.write(0);
 servo_right.write(180);
}
if (PS4.getButtonClick(DOWN))
{
  servo_left.writeMicroseconds(90);
 servo_right.writeMicroseconds(90);
}

}
}
