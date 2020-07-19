#define kp 3.5
#define ki 0
#define kd 2.5
#define lm 9
#define ldir 8
#define rm 11
#define rdir 10
#define setpoint 35
#define rpm 120
int error, p, i, d, pverror, pid;
float value;
void pid_cal();
int pwm_left, pwm_right;
void pwm_value();
void setup()
{
  Serial.begin(115200);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(A0, INPUT);
}

void loop()
{
  pid_cal();
  pwm_value();
  show_data();
}
void pid_cal()
{
  float v = (analogRead(A0) / 921.00);
  //Serial.println(analogRead(A0));
  //Serial.println(v);
  value = v * 70;
  error = value - setpoint;
  p = kp * error;
  i += ki * error;
  d = kd * (error - pverror);
  pid = p + i + d;
  pverror = error;
}
void pwm_value()
{
  if (value < 25)
  {
l1:
    digitalWrite(ldir, HIGH);
    digitalWrite(rdir, LOW);
    analogWrite(lm, 0);
    analogWrite(rm, 255);
    pid_cal();
    if (value < 25)
      goto l1;
  }

  if (value > 45)
  {
    /*digitalWrite(ldir,HIGH);
      digitalWrite(rdir,LOW);
      analogWrite(lm,255);
      analogWrite(rm,0);
      delay(30);*/
l2:
    digitalWrite(ldir, HIGH);
    digitalWrite(rdir, LOW);
    analogWrite(lm, 255);
    analogWrite(rm, 0);
    pid_cal();
    if (value > 45)
      goto l2;
  }
  if (value > 25 && value < 45)
  {
    pwm_left = rpm + pid;
    pwm_right = rpm - pid;
    digitalWrite(ldir, HIGH);
    digitalWrite(rdir, LOW);
    analogWrite(lm, pwm_left);
    analogWrite(rm, pwm_right);
  }
}
void show_data()
{
  //Serial.println(value);
  Serial.println("pwm_left");
  Serial.println(pwm_left);
  Serial.println(pwm_right);
  //Serial.print(pid);
  //Serial.print(error);
  //Serial.println(pverror);
}
