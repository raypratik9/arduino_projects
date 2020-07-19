

/*
  Example sketch for the PS4 USB library - developed by Kristian Lauszus
  For more information visit my blog: http://blog.tkjelectronics.dk/ or
  send me an e-mail:  kristianl@tkjelectronics.com
*/

#include <PS4USB.h>

volatile float sf = 1;
// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
PS4USB PS4(&Usb);

bool printAngle, printTouch;
uint8_t oldL2Value, oldR2Value;

#define m1 2
#define m2 3
#define m3 4
#define m4 5
#define d1 23
#define d2 25
#define d3 27
#define d4 29



void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // Halt
  }
  Serial.print(F("\r\nPS4 USB Library Started"));
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);

}
float s1, s2, s3, s4, x, y, w;
int s_1, s_2, s_3, s_4;
int d_1, d_2, d_3, d_4;
void loop() {
  Usb.Task();
  // put your main code here, to run repeatedly:
  if (PS4.connected())
  {
    
    Serial.print("connected  ");
    if (PS4.getAnalogHat(LeftHatX) > 137 || PS4.getAnalogHat(LeftHatX) < 117 || PS4.getAnalogHat(LeftHatY) > 137 || PS4.getAnalogHat(LeftHatY) < 117 || PS4.getAnalogHat(RightHatX) > 137 || PS4.getAnalogHat(RightHatX) < 117 || PS4.getAnalogHat(RightHatY) > 137 || PS4.getAnalogHat(RightHatY) < 117)
    {
      Serial.print("........");

      x = PS4.getAnalogHat(LeftHatX);
      //      y = PS4.getAnalogHat(LeftHatY);
      y = PS4.getAnalogHat(RightHatY);
      w = 0;
      x = map(x, 0, 255, -255, 255);
      y = map(y, 0, 255, 255, -255);
      //      w = map(w, 0, 255, -255, 255);

      if (x > -15 && x < 15)
        x = 0;
      if (y > -15 && y < 15)
        y = 0;
      if (w > -15 && w < 15)
        w = 0;
      s_1 = sf * (-0.35 * x + 0.35 * y + 0.25 * 0);
      s_2 = sf * (-0.35 * x - 0.35 * y + 0.25 * 0);
      s_3 = sf * (0.35 * x - 0.35 * y + 0.25 * 0);
      s_4 = sf * (0.35 * x + 0.35 * y + 0.25 * 0);

      d_1 = (s_1 > 0 ? 1 : 0);
      d_2 = (s_2 > 0 ? 1 : 0);
      d_3 = (s_3 > 0 ? 1 : 0);
      d_4 = (s_4 > 0 ? 1 : 0);

      digitalWrite(d1, d_1);
      digitalWrite(d2, d_2);
      digitalWrite(d3, d_3);
      digitalWrite(d4, d_4);

      analogWrite(m1, abs(s_1));
      analogWrite(m2, abs(s_2));
      analogWrite(m3, abs(s_3));
      analogWrite(m4, abs(s_4));

      Serial.print("x=");
      Serial.print(x);
      Serial.print("y=");
      Serial.print(y);
      Serial.print("w=");
      Serial.print(w);
      Serial.print("  s1=");
      Serial.print(s_1);
      Serial.print("  s2=");
      Serial.print(s_2);
      Serial.print("  s3=");
      Serial.print(s_3);
      Serial.print("  s4=");
      Serial.print(s_4);
    }
    else
    {
      analogWrite(m1, 0);
      analogWrite(m2, 0);
      analogWrite(m3, 0);
      analogWrite(m3, 0);

    }
    if (PS4.getButtonClick(UP))
      sf = sf + 0.5;
    if (PS4.getButtonClick(DOWN))
    {
      if (sf > 0.5)
        sf = sf - 0.5;
    }

  }
  else
  {
    analogWrite(m1, 0);
    analogWrite(m2, 0);
    analogWrite(m3, 0);
    analogWrite(m3, 0);
  }
  Serial.println();
}
