int a,b,c,d,e,f,g,h;
void setup() {
 pinMode(A0,INPUT);
 pinMode(A1,INPUT);
 pinMode(A2,INPUT);
 pinMode(A3,INPUT);
 pinMode(A4,INPUT);
 pinMode(A5,INPUT);
 pinMode(2,INPUT);
 pinMode(3,INPUT);
 pinMode(5,OUTPUT);
 pinMode(6,OUTPUT);
 pinMode(9,OUTPUT);
 pinMode(10,OUTPUT);


}
void forward()
     {
      analogWrite(5,85);
      analogWrite(9,85);
     }
void right(){
      analogWrite(5, 120);
      analogWrite(9,0);
 }
void left()
{
      analogWrite(9,120);
      analogWrite(5,0);
 }
 void sright()
 {
  analogWrite(5, 105);
      analogWrite(9,0);
 }
 void sleft()
 {
   analogWrite(9,105);
      analogWrite(5,0);
 }
void asru(){ 
     analogWrite(5, 0);
    digitalWrite(6, LOW);
    digitalWrite(9, LOW);
      analogWrite(10, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
 a=digitalRead(3);
    b=digitalRead(2);
      c=digitalRead(A5);
        d=digitalRead(A4);
          e=digitalRead(A3);
            f=digitalRead(A2);
              g=digitalRead(A1);
                h=digitalRead(A0);
 
 
 if(a==1&&b==1&&c==1&&d==0&&e==0&&f==1&&g==1&&h==1)
 forward();
 else if(a==0&&b==0&&c==0&&d==1&&e==1&&f==0&&g==0&&h==0)
 forward();
 else if(a==1&&b==1&&c==1&&d==0&&e==0&&f==0&&g==0&&h==0)
 {
  right();
  delay(100);
 }
 else if(a==0&&b==0&&c==0&&d==0&&e==0&&f==1&&g==1&&h==1)
 {
  left();  
  delay(100);
 }
 else if(a==1&&b==1&&c==0&&d==0&&e==0&&f==1&&g==1&&h==1)
 forward();
 else if(a==1&&b==1&&c==1&&d==0&&e==0&&f==0&&g==1&&h==1)
 forward();
 else if(a==0&&b==0&&c==0&&d==0&&e==0&&f==0&&g==0&&h==0)
 forward();
 else if(a==0||b==0||c==0)
 left();
 else if(f==0||g==0||h==0)
 right();
}
