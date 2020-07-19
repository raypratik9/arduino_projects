void setup()
{
  pinMode(3,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);

for(int i=0;i<256;i++)
{
   analogWrite(3,i); 
analogWrite(9,i); 
analogWrite(10,i); 
analogWrite(11,i); 
delay(100);
}
}
void loop()
{
   analogWrite(3,100); 
analogWrite(9,100); 
analogWrite(10,100); 
analogWrite(11,100); 
}
