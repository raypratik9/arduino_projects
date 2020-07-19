#include <Wire.h>
#include <MPU6050.h>

#define period 20000

MPU6050 mpu;

int count=0;
char okFlag=0;

byte degree[8] = {
  0b00000,
  0b00110,
  0b01111,
  0b00110,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

void setup() 
{
  Serial.begin(9600);
  Serial.println("Initialize MPU6050");
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  count=0;

  mpu.calibrateGyro();
  mpu.setThreshold(3);
  
}

void loop()
{
    long st=millis();
    Serial.println("Temperature");
    /*while(millis()<st)
    {
      tempShow();
    }
    delay(2000);
    st=millis();
    Serial.println("Gyro");
    while(millis()<st+period)
    {
      gyroShow();
      delay(3000);
    }
    delay(2000);
    st=millis();
    Serial.println("Accelerometer");
    */while(millis()<st+period)
    {
      accelShow();
    delay(3000);
    }
}

void tempShow()
{
    float temp = mpu.readTemperature();
    Serial.print(" Temp = ");
    Serial.print(temp);
    Serial.println(" *C");
    delay(400);
}

void gyroShow()
{
  Vector rawGyro = mpu.readRawGyro();
  Vector normGyro = mpu.readNormalizeGyro();
  Serial.print(" Xnorm = ");
  Serial.print(normGyro.XAxis);
  Serial.print(" Ynorm = ");
  Serial.print(normGyro.YAxis);
  Serial.print(" Znorm = ");
  Serial.println(normGyro.ZAxis);
  delay(200);
}

void accelShow()
{
  Vector rawAccel = mpu.readRawAccel();
  Vector normAccel = mpu.readNormalizeAccel();
  Serial.print(" Xnorm = ");
  Serial.print(normAccel.XAxis);
  Serial.print(" Ynorm = ");
  Serial.print(normAccel.YAxis);
  Serial.print(" Znorm = ");
  Serial.println(normAccel.ZAxis);
  delay(200);
}
