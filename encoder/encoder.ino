#define ENC_COUNT_REV 100

#define x_enc 2
#define y_enc 3
#define predefine_value 10
int X_enc=0;
int Y_enc=0;

int arr1[100];
int arr2[100];
int n=0;
 int i=0,j=0;
 int x=0,y=0;
 
int speedcontrol = 0;
volatile long xencoderValue = 0;
volatile long yencoderValue = 0;



void setup()
{
    Serial.begin(9600); 
    pinMode(x_enc, INPUT_PULLUP); 
    pinMode(y_enc, INPUT_PULLUP);
    pinMode(4, INPUT); 
    pinMode(5, INPUT);
    digitalWrite(4,HIGH);
    digitalWrite(5,HIGH); 
  attachInterrupt(digitalPinToInterrupt(x_enc), updateXEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(y_enc), updateYEncoder, CHANGE);
}
void loop()
{ 
    X_enc = (float)(xencoderValue / ENC_COUNT_REV);
    Y_enc = (float)(yencoderValue / ENC_COUNT_REV);
    Serial.print("X=");
    Serial.print(X_enc);
    Serial.print("Y=");
    Serial.print(Y_enc);
    Serial.println();
    if(X_enc==100)
    {
      i++;
      j++;
      x++;
      xencoderValue=0;
    }
    if(X_enc==-100)
    {
      i++;
      j++;
      x--;
      xencoderValue=0;
     }
    if(Y_enc==100)
    {
      j++;
      i++;
      y++;
      yencoderValue=0;
    }
    if(Y_enc==-100)
    {
      j++;
      i++;
      y--;
      yencoderValue=0;
    }
    arr1[i]=x;
    arr2[j]=y;
   // Serial.println();
   for(int k=0;k<=i;k++)
   {
     Serial.print(arr1[k]);
     Serial.print(arr2[k]);
   }
   Serial.println();
}
void updateXEncoder()
{
  if(digitalRead(x_enc)==digitalRead(4))
  {
   xencoderValue--;
  }
  else
  {
  xencoderValue++;
  }
}
void updateYEncoder()
{
  if(digitalRead(y_enc)==digitalRead(5))
  {
   yencoderValue--;
  }
  else
  {
  yencoderValue++;
  }
  }
