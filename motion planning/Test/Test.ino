void setup() {
 pinMode(D0,OUTPUT);
 pinMode(D1,OUTPUT);
 pinMode(D2,OUTPUT);
 pinMode(D3,OUTPUT);
 pinMode(D4,OUTPUT);
 pinMode(D5,OUTPUT);
 

}

void loop() {

 digitalWrite(D3,1);
 analogWrite(D0,100);
 delay(2000);
 digitalWrite(D3,0);
 analogWrite(D0,100);
 delay(2000);
 digitalWrite(D4,1);
 analogWrite(D1,100);
 delay(2000);
 digitalWrite(D4,0);
 analogWrite(D1,100);
 delay(2000);
 digitalWrite(D5,1);
 analogWrite(D2,100);
 delay(2000);
 digitalWrite(D5,0);
 analogWrite(D2,100);
 delay(2000);
 
}
