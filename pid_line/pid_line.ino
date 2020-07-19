#define kp 4
#define ki 0
#define kd 0
#define lm 9
#define rm 11
#define setpoint 0
#define rpm 150
int error,value,p,i,d,pverror,pid;
void pid_cal();
int pwm_left,pwm_right;
void pwm_value();
int s1=A0;
int s2=A1;
int s3=A2;
int s4=A3;
int s5=A4;
int s6=A5;
int s7=2;
int s8=3;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(A0,INPUT);
pinMode(A1,INPUT);
pinMode(A2,INPUT);
pinMode(A3,INPUT);
pinMode(A4,INPUT);
pinMode(A5,INPUT);
pinMode(2,INPUT);
pinMode(3,INPUT);
pinMode(10,OUTPUT);
pinMode(11,OUTPUT);
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
s1=digitalRead(s1);
s2=digitalRead(s2);
s3=digitalRead(s3);
s4=digitalRead(s4);
s5=digitalRead(s5);
s6=digitalRead(s6);
s7=digitalRead(s7);
s8=digitalRead(s8);
value=(-4)*s1+(-3)*s2+(-2)*s3+(-1)*s4+(1)*s5+(2)*s6+(3)*s7+(4)*s8;
pid_cal();
pwm_value();
show_data();
}
void pid_cal()
{
  error=value-setpoint;
  p=kp*error;
  i+=ki*error;
  d=kd*(error-pverror);
  pid=p+i+d;
  pverror=error;
}
void pwm_value()
{
  pwm_left=rpm+pid;
  pwm_right=rpm-pid;
  analogWrite(lm,pwm_left);
  analogWrite(rm,pwm_right);
}
void show_data()
{
  Serial.print(s1);
  Serial.print(s2);
  Serial.print(s3);
  Serial.print(s4);
  Serial.print(s5);
  Serial.print(s6);
  Serial.print(s7);
  Serial.println(s8);
  Serial.print(pid);
  Serial.print(error);
  Serial.println(pverror);
}
