#include <ESP8266WiFi.h>
#define m1 D1
#define m2 D2
#define m3 D3
#define d1 
#define d2 
#define d3 
int s1,s2,s3;
const char* ssid = "pratik";    // Enter SSID here
const char* password = "87654321";  //Enter Password here
int x,y,z;
const char* server = "192.168.43.12";
WiFiClient server1;
void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  Serial.println(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
}
void loop() {
   if (! server1.connect(server,1000))
    Serial.println("Failed to connect to server");
  while(1)
  {
    while(server1.available()){
      x = server1.readStringUntil(',').toInt();
      y = server1.readStringUntil(',').toInt();
      z = server1.readStringUntil('*').toInt();
    Serial.println(x);
    Serial.println(y);
    Serial.println(z);
    Serial.println();
    yield();
  }
 }
  int d_1 = (s1 > 0 ? 1 : 0);
  int d_2 = (s2 > 0 ? 1 : 0);
  int d_3 = (s3 > 0 ? 1 : 0);
  digitalWrite(d1, d_1);
  digitalWrite(d2, d_2);
  digitalWrite(d3, d_3);

  analogWrite(m1, abs(s1));
  analogWrite(m2, abs(s2));
  analogWrite(m3, abs(s3));

}
