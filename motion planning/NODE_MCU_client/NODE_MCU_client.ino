
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "Sourav";    // Enter SSID here
const char* password = "123456789";  //Enter Password here
const char* server = "10.26.62.212";

WiFiClient server1;
int s1, s2;
void setup() {

  Serial.begin (9600);
  
  Serial.println("Creating: ");
  Serial.println(ssid);
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

}

void loop() {
  // put your main code here, to run repeatedly:
  if (! server1.connect(server, 8080))
    Serial.println("Failed to connect to server");
  while (1)
  {
    while (server1.available())
    {
      s1 = server1.readStringUntil('*').toInt();
      s2 = server1.readStringUntil('*').toInt();
      Serial.println(s1);
      Serial.println(s2);
    }
  }
}
