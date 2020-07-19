

// Encoder output to Arduino Interrupt pin

// Pulse count from both X and Y axis Encoder
volatile int encoderValueX = 0;
volatile int encoderValueY = 0;

void setup()
{
  // Setup Serial Monitor
  Serial.begin(9600);

  // Set encoder as input with internal pullup
  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
//
//  pinMode(A11, INPUT_PULLUP);
//  pinMode(A14, INPUT_PULLUP);

  // Attach interrupt
  attachInterrupt(digitalPinToInterrupt(2), updateEncoderX, RISING);
//  attachInterrupt(3, updateEncoderY, RISING);
}

void loop()
{
  Serial.print("X= ");
  Serial.println(encoderValueX );
//  Serial.print("  Y ");
//  Serial.print(encoderValueY);
//  Serial.println();
}

//void updateEncoderY()
//{
//  //Serial.print(digitalRead(A11));
//  if (digitalRead(2) == digitalRead(4))
//    encoderValueY++;
//  else
//    encoderValueY--;
//
//
//}
void updateEncoderX()
{
  if (digitalRead(4) == digitalRead(2))
    encoderValueX++;
  else
    encoderValueX--;
}
