
int Time;
float dis; 

void setup() {
  // put your setup code here, to run once:
pinMode(3,INPUT);      //echo pin
pinMode(4,OUTPUT);    //trig pin
pinMode(5,OUTPUT);   //red led
pinMode(6,OUTPUT);  //yellow led
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(4,HIGH);
  delayMicroseconds(10);
  digitalWrite(4,LOW);
  delayMicroseconds(10);
   
  Time=pulseIn(3,HIGH);
  dis=(Time/2)/29;
  if(dis<10)
  {
  digitalWrite(5,HIGH);  
  delay(200);
  digitalWrite(5,LOW);  
  delay(200);
  }
  if((dis>10)&&(dis<25))
  {
    for(int i=0;i<3;i++)
    {
  digitalWrite(5,HIGH);  
  delay(100);
  digitalWrite(5,LOW);
  }}
  
  if((dis>25)&&(dis<40))       
  {    for(int i=0;i<2;i++)
    {
  digitalWrite(5,HIGH);  
  delay(200);
  digitalWrite(5,LOW);  
  delay(200);
  digitalWrite(6,HIGH);  
  delay(200);
  digitalWrite(6,LOW);
  }}
}
