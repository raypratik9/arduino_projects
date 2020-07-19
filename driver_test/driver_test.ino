#define pwm_2 8
#define pwm_1 7
#define dir_2 3
#define dir_1 6
void setup() {
pinMode(pwm_2, OUTPUT);
pinMode(pwm_1, OUTPUT);
pinMode(dir_1, OUTPUT);
pinMode(dir_2, OUTPUT);
Serial.begin(9600);
//Serial.println(&quot;DIR&quot;);
}
void loop() {
digitalWrite(pwm_1,HIGH);
digitalWrite(pwm_2,HIGH);
analogWrite(dir_1,200);
analogWrite(dir_2,200);
delay(100);
analogWrite(dir_1,50);
analogWrite(dir_2,50);
delay(100);
}
