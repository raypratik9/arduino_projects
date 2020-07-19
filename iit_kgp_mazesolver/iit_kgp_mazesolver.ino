
#define trigPinR 3
#define trigPinL 4
#define trigPinF 5
#define echoPinR 6
#define echoPinL 7
#define echoPinF 8
#define left_motor 9
#define right_motor 10

long durationR, durationF, durationL;
int distanceR, distanceF, distanceL;

//variable for pid
int setpoint = 0, cumError, rateError, lastError, elapsedTime, previousTime, currentTime, error, output;
int kp = 0, ki = 0, kd = 0;

void distance_right()
{
  // Clears the trigPinR
  digitalWrite(trigPinR, LOW);
  delayMicroseconds(2);

  // Sets the trigPinR on HIGH state for 10 micro seconds
  digitalWrite(trigPinR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinR, LOW);

  // Reads the echoPinR, returns the sound wave travel time in microseconds

  durationR = pulseIn(echoPinR, HIGH);

  // Calculating the distance
  distanceR = durationR * 0.034 / 2;
}
void distance_left()
{
  // Clears the trigPinL
  digitalWrite(trigPinL, LOW);
  delayMicroseconds(2);

  // Sets the trigPinL on HIGH state for 10 micro seconds
  digitalWrite(trigPinL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinL, LOW);

  // Reads the echoPinL, returns the sound wave travel time in microseconds

  durationL = pulseIn(echoPinL, HIGH);

  // Calculating the distance
  distanceL = durationL * 0.034 / 2;
}
void distance_forward()
{
  // Clears the trigPinF
  digitalWrite(trigPinF, LOW);
  delayMicroseconds(2);

  // Sets the trigPinF on HIGH state for 10 micro seconds
  digitalWrite(trigPinF, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinF, LOW);

  // Reads the echoPinF, returns the sound wave travel time in microseconds

  durationF = pulseIn(echoPinF, HIGH);

  // Calculating the distance
  distanceF = durationF * 0.034 / 2;
}
void pid()
{
  setpoint = (distanceL + distanceR) / 2;
  error = setpoint;
  currentTime = millis();
  elapsedTime = (currentTime - previousTime) / 100;
  cumError += error * elapsedTime;
  rateError = (error - lastError) / elapsedTime;
  output = kp * error + ki * cumError + kd * rateError;
  lastError = error;
  previousTime = currentTime;
}
void forward()
{
  analogWrite(left_motor, 200);
  analogWrite(right_motor, 200);
}
void left()
{
  analogWrite(left_motor, 0);
  analogWrite(right_motor, 200);
}
void right()
{
  analogWrite(left_motor, 200);
  analogWrite(right_motor, 0);
}
void motion()
{
  if ((distanceL + distanceR) < 10)
  {
    pid();
    int pwm_left=150+output;
    int pwm_right=150-output;
    analogWrite(left_motor, pwm_left);
    analogWrite(right_motor, pwm_right);
  }
  if (distanceF > 15 && distanceL < 7 && distanceR < 7)
    forward();
  if (distanceF > 15 && distanceL < 7 && distanceR > 15)
    forward();
  if (distanceF > 15 && distanceL > 15 && distanceR < 7)
    left();
  if (distanceF > 15 && distanceL > 15 && distanceR > 15)
    left();
  if (distanceF < 7 && distanceL < 7 && distanceR < 7)
    right();
}
void setup() {
  // put your setup code here, to run once:
  pinMode(trigPinR, OUTPUT);
  pinMode(trigPinL, OUTPUT);
  pinMode(trigPinF, OUTPUT);

  pinMode(echoPinR, INPUT);
  pinMode(echoPinL, INPUT);
  pinMode(echoPinF, INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  distance_left();
  distance_right();
  distance_forward();
  motion();
}
