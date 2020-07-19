#include <Wire.h>
#include <Servo.h>
void recordAccelRegisters();
void recordGyroRegisters();
Servo right_prop;
Servo left_prop;
Servo right_prop2;
Servo left_prop2;
/*MPU-6050 gives you 16 bits data so you have to create some 16int constants
 * to store the data for accelerations and gyro*/
#define A 0.962
#define dt 0.020

int calx,caly;
int16_t Acc_rawX, Acc_rawY, Acc_rawZ,Gyr_rawX, Gyr_rawY, Gyr_rawZ;
 double accel_x_cal,accel_y_cal,accel_z_cal;
double accelX, accelY, accelZ;

float rollangle,pitchangle;
float roll,pitch,yaw;

double gyroX, gyroY, gyroZ;
double gyro_x_cal,gyro_y_cal,gyro_z_cal;


float Acceleration_angle[2];
float Gyro_angle[2];
float Total_angle[2];




float elapsedTime, time, timePrev;
float rad_to_deg = 180/3.141592654;

float PID, pwmLeft, pwmRight, error, previous_error;
float PID2, pwmLeft2, pwmRight2, error2, previous_error2;
float pid_p=0;
float pid_i=0;
float pid_d=0;
float pid_p2=0;
float pid_i2=0;
float pid_d2=0;
/////////////////PID CONSTANTS/////////////////
double kp=3.55;//3.55
double ki=0.005;//0.003
double kd=2.05;//2.05
///////////////////////////////////////////////

double throttle=1200; //initial value of throttle to the motors
float desired_angle = 0; //This is the angle in which we whant the
                         //balance to stay steady


void setup() {
  Wire.begin(); //begin the wire comunication
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
    Serial.println("Calibrating Accelerometer......");
  for(int calx=1;calx<=2000;calx++)
  {
     recordAccelRegisters();
     accel_x_cal += accelX;                      
     accel_y_cal += accelY;      
     accel_z_cal += accelZ;
  }
  Serial.println("Calibrating Gyroscope......");
  for(int caly=1;caly<=2000;caly++)
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

  Serial.begin(9600);
  right_prop.attach(6); //attatch the right motor to pin 3
  left_prop.attach(10);  //attatch the left motor to pin 5
right_prop2.attach(9); //attatch the right motor to pin 3
  left_prop2.attach(11);
  time = millis(); //Start counting time in milliseconds
 
for(int i=2000;i>999;i--)
  {
  right_prop.writeMicroseconds(i);
  right_prop2.writeMicroseconds(i);
  left_prop.writeMicroseconds(i);
  left_prop2.writeMicroseconds(i);
  delay(10);
 }
}//end of setup void

void loop() {

/////////////////////////////I M U/////////////////////////////////////
    timePrev = time;  // the previous time is stored before the actual time read
    time = millis();  // actual time read
    elapsedTime = (time - timePrev) / 1000; 
     Wire.beginTransmission(0x68);
     Wire.write(0x3B); //Ask for the 0x3B register- correspond to AcX
     Wire.endTransmission(false);
     Wire.requestFrom(0x68,6,true); 
    
     Acc_rawX=Wire.read()<<8|Wire.read(); //each value needs two registres
     Acc_rawY=Wire.read()<<8|Wire.read();
     Acc_rawZ=Wire.read()<<8|Wire.read();

 
   
     Acceleration_angle[0] = atan((Acc_rawY/16384.0)/sqrt(pow((Acc_rawX/16384.0),2) + pow((Acc_rawZ/16384.0),2)))*rad_to_deg;
     /*---Y---*/
     Acceleration_angle[1] = atan(-1*(Acc_rawX/16384.0)/sqrt(pow((Acc_rawY/16384.0),2) + pow((Acc_rawZ/16384.0),2)))*rad_to_deg;
 

   Wire.beginTransmission(0x68);
   Wire.write(0x43); //Gyro data first adress
   Wire.endTransmission(false);
   Wire.requestFrom(0x68,4,true); //Just 4 registers
   
   Gyr_rawX=Wire.read()<<8|Wire.read(); //Once again we shif and sum
   Gyr_rawY=Wire.read()<<8|Wire.read();
 
   /*Now in order to obtain the gyro data in degrees/seconda we have to divide first
   the raw value by 131 because that's the value that the datasheet gives us*/

   /*---X---*/
   Gyro_angle[0] = Gyr_rawX/131.0; 
   /*---Y---*/
   Gyro_angle[1] = Gyr_rawY/131.0;

   /*---X axis angle---*/
   Total_angle[0] = 0.98 *(Total_angle[0] + Gyro_angle[0]*elapsedTime) + 0.02*Acceleration_angle[0];
   /*---Y axis angle---*/
   Total_angle[1] = 0.98 *(Total_angle[1] + Gyro_angle[1]*elapsedTime) + 0.02*Acceleration_angle[1];
error = Total_angle[1] - desired_angle;

pid_p = kp*error;

if(-3 <error <3)
{
  pid_i = pid_i+(ki*error);  
}

pid_d = kd*((error - previous_error)/elapsedTime);

/*The final PID values is the sum of each of this 3 parts*/
PID = pid_p + pid_i + pid_d;
if(PID < -1000)
{
  PID=-1000;
}
if(PID > 1000)
{
  PID=1000;
}
pwmLeft = throttle + PID;
pwmRight = throttle - PID;
//Right
if(pwmRight < 1000)
{
  pwmRight= 1000;
}
if(pwmRight > 2000)
{
  pwmRight=2000;
}
//Left
if(pwmLeft < 1000)
{
  pwmLeft= 1000;
}
if(pwmLeft > 2000)
{
  pwmLeft=2000;
}
previous_error = error; //Remember to store the previous error.

error2 = Total_angle[0] - desired_angle;

pid_p2 = kp*error2;

if(-3 <error2 <3)
{
  pid_i2 = pid_i2+(ki*error2);  
}
pid_d2 = kd*((error2-previous_error2)/elapsedTime);

/*The final PID values is the sum of each of this 3 parts*/
PID2 = pid_p2 + pid_i2 + pid_d2;

if(PID2 < -1000)
{
  PID2=-1000;
}
if(PID2 > 1000)
{
  PID2=1000;
}
pwmLeft2 = throttle + PID2;
pwmRight2 = throttle - PID2;
//Right
if(pwmRight2 < 1000)
{
  pwmRight2= 1000;
}
if(pwmRight2 > 2000)
{
  pwmRight2=2000;
}
//Left
if(pwmLeft2 < 1000)
{
  pwmLeft2= 1000;
}
if(pwmLeft2 > 2000)
{
  pwmLeft2=2000;
}
Serial.print("error2");
Serial.println(error2);
Serial.print("error");
Serial.println(error);
Serial.print("elapsedTime");
Serial.println(elapsedTime);
Serial.print("pid=");
Serial.println(PID);
Serial.print("pid2=");
Serial.println(PID2);

/*Serial.print("pwmLeft");
Serial.println(pwmLeft);
Serial.print("pwmLeft2");
Serial.println(pwmLeft2);
Serial.print("pwmRight");
Serial.println(pwmRight);
Serial.print("pwmRight2");
Serial.println(pwmRight2);
*/
left_prop2.writeMicroseconds(pwmLeft2);
right_prop2.writeMicroseconds(pwmRight2);
left_prop.writeMicroseconds(pwmLeft);
right_prop.writeMicroseconds(pwmRight);
previous_error2 = error2; //Remember to store the previous error.

}
void recordAccelRegisters() {
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x3B); //Starting register for Accel Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); //Request Accel Registers (3B - 40)
  while(Wire.available() < 6);
  accelX = Wire.read()<<8|Wire.read(); 
  if(calx == 2000)accelX -= accel_x_cal; 
  accelY = Wire.read()<<8|Wire.read(); 
  if(calx == 2000)accelY -= accel_y_cal; 
  accelZ = Wire.read()<<8|Wire.read(); 
  if(calx == 2000)accelZ -= accel_z_cal; 
  
}


void recordGyroRegisters() {
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x43); //Starting register for Gyro Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); //Request Gyro Registers (43 - 48)
  while(Wire.available() < 6);
  gyroX = Wire.read()<<8|Wire.read();
  if(caly == 2000)gyroX -= gyro_x_cal; 
  gyroY = Wire.read()<<8|Wire.read(); 
  if(caly == 2000)gyroY -= gyro_y_cal; 
  gyroZ = Wire.read()<<8|Wire.read();
  if(caly == 2000)gyroZ -= gyro_z_cal; 
  
}
