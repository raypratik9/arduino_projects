#include <Servo.h>

Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;
#include <Wire.h>
long accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ;
int x,y;
long gyroX, gyroY, gyroZ;
float rotX, rotY, rotZ;
void setupMPU();
void recordAccelRegisters();
 void recordGyroRegisters();
 void printData();
 void pidcalX();
 void pidcalY();
 const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 5; // Echo Pin of Ultrasonic Sensor
int cm=0;
long int cumError=0;
int output=0;
int lastError=0;
unsigned long elapsedTime=0; 
unsigned long currentTime=0;
unsigned long previousTime=0;
void setup() {
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  Serial.begin(9600);
  Wire.begin();
  setupMPU();
  motor1.attach(9);
  motor2.attach(10);
  motor3.attach(11);
  motor4.attach(6);
  delay(100);
  for(int i=2000;i>999;i--)
  {
  motor3.writeMicroseconds(i);
  motor1.writeMicroseconds(i);
  motor2.writeMicroseconds(i);
  motor4.writeMicroseconds(i);
  delay(10);
 }
 Serial.println("calibration is completed");
}


void loop() {
  Serial.println("loop is starting");
  recordAccelRegisters();
  recordGyroRegisters();
  //printData();
  long duration, inches;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   cm=duration/29/2;
   delay(100);
   Serial.println(cm);
   calX();
   calY();
   motor();
}

void setupMPU(){
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
}

void recordAccelRegisters() {
  Wire.beginTransmission(0b1101000); 
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); 
  while(Wire.available() < 6);
  accelX = Wire.read()<<8|Wire.read(); 
  accelY = Wire.read()<<8|Wire.read(); 
  accelZ = Wire.read()<<8|Wire.read(); 
  processAccelData();
}

void processAccelData(){
  gForceX = (accelX / 16384.0)*1000;
  gForceY = (accelY / 16384.0)*1000; 
  gForceZ = (accelZ / 16384.0)*1000;
}

void recordGyroRegisters() {
  Wire.beginTransmission(0b1101000);
  Wire.write(0x43); 
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6);
  while(Wire.available() < 6);
  gyroX = Wire.read()<<8|Wire.read(); 
  gyroY = Wire.read()<<8|Wire.read(); 
  gyroZ = Wire.read()<<8|Wire.read(); 
  processGyroData();
}

void processGyroData() {
  rotX = (gyroX / 131.0)*1000;
  rotY = (gyroY / 131.0)*1000; 
  rotZ = (gyroZ / 131.0)*1000;
}

void printData() {
  Serial.print("Gyro (deg)");
  Serial.print(" X=");
  Serial.print(rotX);
  Serial.print(" Y=");
  Serial.print(rotY);
  Serial.print(" Z=");
  Serial.print(rotZ);
  Serial.print(" Accel (g)");
  Serial.print(" X=");
  Serial.print(gForceX);
  Serial.print(" Y=");
  Serial.print(gForceY);
  Serial.print(" Z=");
  Serial.println(gForceZ);
  delay(2000);
}
void motor()
{
  if(gForceX<0&&gForceX>-700&&gForceY<0&&gForceY>-700)
  {
      motor1.writeMicroseconds(output-x);
      motor2.writeMicroseconds(output);
      motor3.writeMicroseconds(output);
      motor4.writeMicroseconds(output-y);
  }
  if(gForceX<0&&gForceY>0&&gForceX>-700&&gForceY<700)
  {
      motor1.writeMicroseconds(output-x);
      motor2.writeMicroseconds(output-y);
      motor3.writeMicroseconds(output);
      motor4.writeMicroseconds(output);
  }
  if(gForceX>0&&gForceY<0&&gForceX<700&&gForceY>-700)
  {
      motor1.writeMicroseconds(output);
      motor2.writeMicroseconds(output);
      motor3.writeMicroseconds(output-x);
      motor4.writeMicroseconds(output-y);
  }
  if(gForceX>0&&gForceY>0&&gForceX<700&&gForceY<700)
  {
      motor1.writeMicroseconds(output);
      motor2.writeMicroseconds(output-y);
      motor3.writeMicroseconds(output-x);
      motor4.writeMicroseconds(output);
  }
if(gForceX<-700&&gForceX>-1100&&gForceY<-700&&gForceY>-1100)
  {
      motor1.writeMicroseconds(output-x);
      motor2.writeMicroseconds(output+y);
      motor3.writeMicroseconds(output+x);
      motor4.writeMicroseconds(output-y);
  }
  if(gForceX<-700&&gForceY>700&&gForceX>-1100&&gForceY<1100)
  {
      motor1.writeMicroseconds(output-x);
      motor2.writeMicroseconds(output-y);
      motor3.writeMicroseconds(output+x);
      motor4.writeMicroseconds(output+y);
  }
  if(gForceX>700&&gForceY<-700&&gForceX<1100&&gForceY>-1100)
  {
      motor1.writeMicroseconds(output+x);
      motor2.writeMicroseconds(output+y);
      motor3.writeMicroseconds(output-x);
      motor4.writeMicroseconds(output-y);
  }
  if(gForceX>700&&gForceY>700&&gForceX<1100&&gForceY<1100)
  {
      motor1.writeMicroseconds(output+x);
      motor2.writeMicroseconds(output-y);
      motor3.writeMicroseconds(output-x);
      motor4.writeMicroseconds(output+y);
  }
  Serial.println("motor is working");
}
void calX()
{
  Serial.println("calculating x value");
  if(gForceX<0)
  x=map(gForceX,0,-1100,0,-180);
  if(gForceX>0)
  x=map(gForceX,0,1100,1000,2000);
}
void calY()
{
  Serial.println("calculating Y value");
if(gForceY<0)
  y=map(gForceY,0,-1100,0,-180);
  if(gForceY>0)
  y=map(gForceY,0,1100,0,180);  
}
void pidDistance()
 {
  Serial.println("calculating distance value");
  int kp=1,ki=0,kd=1;
currentTime = millis();
 elapsedTime = (currentTime - previousTime)/100;
int error =300-cm;
 cumError+= error * elapsedTime;
int rateError = (error - lastError)/elapsedTime;
 output=kp*error+ki*cumError+kd*rateError;
lastError = error;
previousTime = currentTime;
if(output>=0&&output<=300)
output=map(output,0,300,1000,2000);
else
output=0;
 }
/*Serial.print("currentTime=");
Serial.println(currentTime);
Serial.print("elapsedTime=");
Serial.println(elapsedTime);
Serial.print("previousTime"); 
Serial.println(previousTime);
 Serial.print("error=");
Serial.println(error);
 Serial.print("cumError=");
Serial.println(cumError);
Serial.print("rateError=");
Serial.println(rateError);
Serial.print("output=");
Serial.println(output);
}*/
