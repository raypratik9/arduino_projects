#include <Wire.h>
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(0b1101000);
  Wire.write(0x6B);
  Wire.write(0b00000000);
  Wire.endTransmission();
  Wire.beginTransmission(0b1101000);
  Wire.write(0x1B);
  Wire.write(0x00000000);
  Wire.endTransmission();
  Wire.beginTransmission(0b1101000);
  Wire.write(0x1C);
  Wire.write(0b00000000);
  Wire.endTransmission();
  Serial.println("Calibrating Accelerometer......");
  for (calx = 1; calx <= 2000; calx++)
  {
    recordAccelRegisters();
    accel_x_cal += accelX;
    accel_y_cal += accelY;
    accel_z_cal += accelZ;
  }
  Serial.println("Calibrating Gyroscope......");
  for (caly = 1; caly <= 2000; caly++)
  {
    recordGyroRegisters();
    gyro_x_cal += gyroX;
    gyro_y_cal += gyroY;
    gyro_z_cal += gyroZ;
  }
  Serial.println("Calibration Done..!!!");
  gyro_x_cal /= 2000;
  gyro_y_cal /= 2000;
  gyro_z_cal /= 2000;

  gyro_x_cal /= 2000;
  gyro_y_cal /= 2000;
  gyro_z_cal /= 2000;
}

void loop() {
  // put your main code here, to run repeatedly:
recordAccelRegisters();
recordGyroRegisters(); 
  
  accelX = (accelX / 16384.0);
  accelY = (accelY / 16384.0);
  accelZ = (accelZ / 16384.0);

  gyroX = gyroX / 131.0;
  gyroY = gyroY / 131.0;
  gyroZ = gyroZ / 131.0;
  
  Serial.print(" accelX=");
  Serial.print(accelX);
  Serial.print(" accelY=");
  Serial.print(accelY);
  Serial.print(" accelZ=");
  Serial.print(accelZ);
  Serial.println();
}
void recordAccelRegisters() {
  Wire.beginTransmission(0b1101000);
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(0b1101000, 6);
  while (Wire.available() < 6);
  accelX = Wire.read() << 8 | Wire.read();
  if (calx == 2000)accelX -= accel_x_cal;
  accelY = Wire.read() << 8 | Wire.read();
  if (calx == 2000)accelY -= accel_y_cal;
  accelZ = Wire.read() << 8 | Wire.read();
  if (calx == 2000)accelZ -= accel_z_cal;

}

void recordGyroRegisters() {
  Wire.beginTransmission(0b1101000);
  Wire.write(0x43);
  Wire.endTransmission();
  Wire.requestFrom(0b1101000, 6);
  while (Wire.available() < 6);
  gyroX = Wire.read() << 8 | Wire.read();
  if (caly == 2000)gyroX -= gyro_x_cal;
  gyroY = Wire.read() << 8 | Wire.read();
  if (caly == 2000)gyroY -= gyro_y_cal;
  gyroZ = Wire.read() << 8 | Wire.read();
  if (caly == 2000)gyroZ -= gyro_z_cal;

}
