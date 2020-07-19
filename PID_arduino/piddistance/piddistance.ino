const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor
void pidDistance();
int cm=0;
long int cumError=0;
int output=0;
int lastError=0;
unsigned long elapsedTime=0; 
unsigned long currentTime=0;
unsigned long previousTime=0;
void setup() {
   Serial.begin(9600); // Starting Serial Terminal
}

void loop() {
   long duration, inches;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   cm=duration/29/2;
   delay(100);
   pidDistance();
   Serial.print("cm=");
   Serial.println(cm);
}

void pidDistance()
 {Serial.begin(9600);
  int kp=1,ki=0,kd=1;
//currentTime = millis();
 //elapsedTime = (currentTime - previousTime)/100;


int error =300-cm;
cumError+= error * elapsedTime;
int rateError = (error - lastError)/elapsedTime;
output=kp*error+ki*cumError+kd*rateError;
lastError = error;
previousTime = currentTime;

Serial.print("currentTime=");
Serial.println(currentTime);
Serial.print("elapsedTime=");
Serial.println(elapsedTime);
Serial.print("previousTime");
Serial.println(previousTime);
 Serial.print("error=");
Serial.println(error);
 Serial.print("cumError=");
Serial.println(cumError);
 Serial.print("rateError=");
Serial.println(rateError);
 Serial.print("output=");
Serial.println(output);
}
