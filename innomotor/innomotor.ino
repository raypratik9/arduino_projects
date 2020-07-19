int S1,S2,S3,S4,S5,S6;
void setup() {
  // put 2our setup code here, to run once:
pinMode(2,INPUT);
pinMode(4,INPUT);
pinMode(7,INPUT);
pinMode(8,INPUT);
pinMode(12,INPUT);
pinMode(13,INPUT);
pinMode(3,OUTPUT);
pinMode(13,OUTPUT);
pinMode(13,OUTPUT);
Serial.begin(9600);
pinMode(9,OUTPUT);
}

void forwardvoid loop() {
  // put your main code here, to run repeatedly:
S1=digitalRead(2);
S2=digitalRead(4);
S3=digitalRead(7);
S4=digitalRead(8);
S5=digitalRead(12);
S6=digitalRead(13);

Serial.print(S1);
Serial.print(S2);
Serial.print(S3);
Serial.print(S4);
Serial.print(S5);
Serial.println(S6);
delay(400);
}
