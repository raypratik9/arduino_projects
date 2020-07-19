#define m1 2
#define m2 3
#define m3 4
#define m4 5
#define d1 23
#define d2 25
#define d3 27
#define d4 29
int d_1,d_2,d_3,d_4;
#include <PS4USB.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
PS4USB PS4(&Usb);

bool printAngle, printTouch;
uint8_t oldL2Value, oldR2Value;
void setup()
{
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // Halt
  }
  Serial.print(F("\r\nPS4 USB Library Started"));
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

}

void loop()
{
  double sf, s1, s2, s3, s4;

  if (PS4.getAnalogHat(LeftHatX) > 137 || PS4.getAnalogHat(LeftHatX) < 117 || PS4.getAnalogHat(LeftHatY) > 137 || PS4.getAnalogHat(LeftHatY) < 117 || PS4.getAnalogHat(RightHatX) > 137 || PS4.getAnalogHat(RightHatX) < 117 || PS4.getAnalogHat(RightHatY) > 137 || PS4.getAnalogHat(RightHatY) < 117)

  x = map(PS4.getAnalogHat(LeftHatX), 0, 255, -255, 255);
  y = map(PS4.getAnalogHat(LeftHatY), 0, 255, -255, 255);
  w = map(PS4.getAnalogHat(RightHatX), 0, 255, -255, 255);
  sf = 1;
  s1 = sf * (0.1768 * x + 0.1768 * y + 0.25 * w);
  s2 = sf * (0.1768 * x + 0.1768 * y + 0.25 * w);
  s3 = sf * (-0.1768 * x - 0.1768 * y + 0.25 * w);
  s4 = sf * (-0.1768 * x - 0.1768 * y + 0.25 * w);
  d_1=(s1>0?1:0);
  d_1=(s1>0?1:0);
  d_1=(s1>0?1:0);
  d_1=(s1>0?1:0);
  if (PS4.getButtonClick(TRIANGLE)) 
  {
    sf = sf + 0.1;
  }
  if (PS4.getButtonClick(CROSS))
  {
    sf = sf - 0.1;
  }

}
