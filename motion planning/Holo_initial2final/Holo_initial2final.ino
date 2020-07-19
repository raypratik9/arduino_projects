//programme for holonomic bot follow shortest path with avoiding some point
volatile int encX, encY;

int x, y, w;

void func_want(int d_x, int d_y);

//final coordinate
int p = 20;  //(20,20)

int arr[4][2] = {{0, 0}, {p, p}};

int s1 = 23, s2 = 25, s3 = 27, s4 = 29;
int s_1, s_2, s_3, s_4;
int d_1, d_2, d_3, d_4;
int d1 = 2, d2 = 3, d3 = 4, d4 = 5; 

//volatile long encoderValueX = 0;
//volatile long encoderValueY = 0;
volatile int d_x;
volatile int d_y;

//ISR function for X nd Y axis
//void updateEncoderX();
//void updateEncoderY();

void setup()
{
  // Setup Serial Monitor
  Serial.begin(9600);

  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);

  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(s4, OUTPUT);

  // Attach interrupt for both x nd y axis encoder
  attachInterrupt(digitalPinToInterrupt(18), updateEncoderX, RISING);
  attachInterrupt(digitalPinToInterrupt(19), updateEncoderY, RISING);
}

void loop()
{
  for (int i = 1; i < 4; i++)
  {
    while (encX != arr[i][1] && encY != arr[i][2])
    {
      int d_x = arr[i][1] - encX; 
      int d_y = arr[i][2] - encY; 
      int angle = atan(d_y / d_x) * 57;  //angle between x axis and line joining to final coordinate and x axis
      d_x = map((90 - angle), -90, 90, -255, 255);
      d_y = map(angle, -90, 90, 255, -255);
      func_want(d_x, d_y);
    }
  }
}
//ISR function for x axis encoder
//void updateEncoderX()
//{
//  if (digitalRead(18) == digitalRead(20)) //18&20 are x axis encoder pin
//    encoderValueX--;
//  else
//    encoderValueX++;
//  if (encoderValueX / ENC_COUNT_REV >= 100)
//  {
//    encX++;                              //x coordinate increment
//    encoderValueX = 0;
//  }
//  if (encoderValueX / ENC_COUNT_REV <= -100)
//  {
//    encX--;
//    encoderValueX = 0;
//  }

//}
////ISR function for y axis encoder
//void updateEncoderY()
//{
//  if (digitalRead(19) == digitalRead(21)) //19&21 are x axis encoder pin
//    encoderValueY--;
//  else
//    encoderValueY++;
//  if (encoderValueY / ENC_COUNT_REV >= 100)
//  {
//    encY++;                               //y coordinate increment
//    encoderValueY = 0;
//  }
//  if (encoderValueY / ENC_COUNT_REV <= -100)
//  {
//    encY--;
//    encoderValueY = 0;
//  }
//}
void func_want(int x, int y)
{
  int sf = 1;
  s_1 = sf * (0.1768 * x + 0.1768 * y + 0.25 * w);
  s_2 = sf * (0.1768 * x + 0.1768 * y + 0.25 * w);
  s_3 = sf * (-0.1768 * x - 0.1768 * y + 0.25 * w);
  s_4 = sf * (-0.1768 * x - 0.1768 * y + 0.25 * w);

  d_1 = (s_1 > 0 ? 1 : 0);
  d_2 = (s_2 > 0 ? 1 : 0);
  d_3 = (s_3 > 0 ? 1 : 0);
  d_4 = (s_4 > 0 ? 1 : 0);

  //digital output for 4 motor
  digitalWrite(d1, d_1);
  digitalWrite(d2, d_2);
  digitalWrite(d3, d_3);
  digitalWrite(d4, d_4);

  //analog output speed for 4 motor
  analogWrite(s1, s_1);
  analogWrite(s2, s_2);
  analogWrite(s3, s_3);
  analogWrite(s4, s_4);
}
