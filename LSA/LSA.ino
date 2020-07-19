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
void forward();
void left();
void right();
void forward()
{
  digitalWrite(ldir, HIGH);
  digitalWrite(rdir, LOW);
  analogWrite(lm, rpm);
  analogWrite(rm, rpm);
}

void left()
{
  digitalWrite(ldir, HIGH);
  digitalWrite(rdir, LOW);
  analogWrite(lm, 0);
  analogWrite(rm, rpm);
}

void right()
{
  digitalWrite(ldir, HIGH);
  digitalWrite(rdir, LOW);
  analogWrite(lm, rpm);
  analogWrite(rm, 0);
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
    left();
  }

  if (value > 45)
  {
    right();
  }
  if (value > 25 && value < 45)
  {
    if (value < 35)
    {
      pwm_left = rpm;
      pwm_right = rpm + pid;
      digitalWrite(ldir, HIGH);
      digitalWrite(rdir, LOW);
      analogWrite(lm, pwm_left);
      analogWrite(rm, pwm_right);
    }
    if (value > 35)
    {
      pwm_left = rpm + pid;
      pwm_right = rpm ;
      digitalWrite(ldir, HIGH);
      digitalWrite(rdir, LOW);
      analogWrite(lm, pwm_left);
      analogWrite(rm, pwm_right);
    }
  }
}



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

}
