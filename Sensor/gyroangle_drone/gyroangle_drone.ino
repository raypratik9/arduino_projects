#include <Wire.h>

#include <Servo.h>

Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;
float rad_to_deg = 180/3.141592654;

float kp=3.22;  //difference=109rpm
float kd=1.90;  //171
long accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ;
int x,y;
long gyroX, gyroY, gyroZ;
float rotX, rotY, rotZ;
void setupMPU();
void recordAccelRegisters();
 void recordGyroRegisters();
 //void printData();
 void pidcalX();
 void pidcalY();
#define output 1600
void setup() {
  pinMode(6,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  Serial.begin(9600);
  Wire.begin();
  setupMPU();
  motor1.attach(6);
  motor2.attach(9);
  motor3.attach(10);
  motor4.attach(11);
  delay(100);
  for(int i=2000;i>999;i--)
  {
  motor3.writeMicroseconds(i);
  motor1.writeMicroseconds(i);
  motor2.writeMicroseconds(i);
  motor4.writeMicroseconds(i);
  delay(10);
 }
}


void loop() {
  recordAccelRegisters();
  recordGyroRegisters();
 // printData();
   pidcalX();
   pidcalY();
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
 gForceX= (atan((accelX / 16384.0)/sqrt(pow((accelX / 16384.0),2) + pow((accelZ / 16384.0),2)))*rad_to_deg)*2;
     /*---Y---*/
     gForceY = (atan(-1*(accelY / 16384.0)/sqrt(pow((accelY / 16384.0),2) + pow((accelZ / 16384.0),2)))*rad_to_deg)*2;
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

/*void printData() {
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
}*/
void motor()
{
  if(gForceX<0&&gForceX<0)
  {
      motor1.writeMicroseconds(output);
      motor2.writeMicroseconds(output+y);
      motor3.writeMicroseconds(output-x);
      motor4.writeMicroseconds(output-y);
       Serial.print("motor1=");
      Serial.println(output);
       Serial.print("motor2=");
      Serial.println(output);
       Serial.print("motor3=");
      Serial.println(output-x);
       Serial.print("motor4=");
      Serial.println(output-y);
  }
  if(gForceX<0&&gForceY>0)
  {
      motor1.writeMicroseconds(output);
     motor2.writeMicroseconds(output+y);
      motor3.writeMicroseconds(output-x);
      motor4.writeMicroseconds(output-y);
       Serial.print("motor1=");
      Serial.println(output);
       Serial.print("motor2=");
      Serial.println(output+y);
       Serial.print("motor3=");
      Serial.println(output-x);
       Serial.print("motor4=");
      Serial.println(output);
     
  }
  if(gForceX>0&&gForceY<0)
  {
      motor1.writeMicroseconds(output+x);
     motor2.writeMicroseconds(output+y);
      motor3.writeMicroseconds(output);
     motor4.writeMicroseconds(output-y);
       Serial.print("motor1=");
      Serial.println(output+x);
       Serial.print("motor2=");
      Serial.println(output);
       Serial.print("motor3=");
      Serial.println(output);
       Serial.print("motor4=");
      Serial.println(output-y);
  
  }
  if(gForceX>0&&gForceY>0)
  {
      motor1.writeMicroseconds(output+x);
      motor2.writeMicroseconds(output+y);
      motor3.writeMicroseconds(output);
      motor4.writeMicroseconds(output-y);
      Serial.print("motor1=");
      Serial.println(output+x);
       Serial.print("motor2=");
      Serial.println(output+y);
       Serial.print("motor3=");
      Serial.println(output);
       Serial.print("motor4=");
      Serial.println(output);
     
  }
}
void pidcalX()
{
  if(gForceX<34&&gForceX>-34)
x=kp*gForceX;
else
x=kd*gForceX;
//Serial.println(x);
//delay(500);
}
void pidcalY()
{
  if(gForceY<34&&gForceY>-34)
y=kp*gForceY;
else
y=kd*gForceY;
//Serial.println(y); 
//delay(500);
}
