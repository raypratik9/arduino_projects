#include <Wire.h>
long accelX, accelY, accelZ;
long gyroX, gyroY, gyroZ;

int16_t gForceX, gForceY, gForceZ;
int16_t rotX, rotY, rotZ;

void printData();
void recordAccelRegisters();
void recordGyroRegisters();
void processGyroData();
void recordAccelRegisters();

void recordAccelRegisters()
{
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(0x68, 6);
  gForceX = Wire.read() << 8 | Wire.read();
  gForceY = Wire.read() << 8 | Wire.read();
  gForceZ = Wire.read() << 8 | Wire.read();
 // processAccelData();
}

void recordGyroRegisters()
{
  Wire.beginTransmission(0x68);
  Wire.write(0x43);
  Wire.endTransmission();
  Wire.requestFrom(0x68, 6);
  rotX = Wire.read() << 8 | Wire.read();
  rotY = Wire.read() << 8 | Wire.read();
  rotZ = Wire.read() << 8 | Wire.read();
  //processGyroData();
}

void processGyroData() {
  gyroX = (rotX / 131.0);
  gyroY = (rotY / 131.0);
  gyroZ = (rotZ / 131.0);
}

void processAccelData() {
  accelX = (gForceX / 16384.0);
  accelY = (gForceY / 16384.0);
  accelZ = (gForceZ / 16384.0);
//  accelX=map(accelX,-1,1,-90,90);
//  accelY=map(accelY,-1,1,-90,90);
//  accelZ=map(accelZ,-1,1,-90,90); 
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.setClock(400000);
  Wire.begin();
  delay(250);

  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();
}

void loop() {
  // put your main code here, to run repeatedly:
  recordGyroRegisters();
  recordAccelRegisters();
  printData();
}
void printData() {
  Serial.print("Gyro data     ");
  Serial.print("   X=");
  Serial.print(gyroX);
  Serial.print(" Y=");
  Serial.print(gyroY);
  Serial.print(" Z=");
  Serial.println(gyroZ);
  Serial.print("Accel data      ");
  Serial.print(" X=");
  Serial.print(accelX);
  Serial.print(" Y=");
  Serial.print(accelY);
  Serial.print(" Z=");
  Serial.println(accelZ);
  Serial.println();
  
}
