
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "SOCIETY";    // Enter SSID here
const char* password = "vssutrobotix";  //Enter Password here

WiFiServer server1(8080);
int s1, s2;
void setup() {

  Serial.begin (9600);

  Serial.println("Creating: ");
  Serial.println(ssid);

  WiFi.softAP(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println( (WiFi.localIP()));

}

void loop() {
  // put your main code here, to run repeatedly:
    while (server1.available())
    {
      s1 = server1.readStringUntil('*').toInt();
      s2 = server1.readStringUntil('*').toInt();
      if (s2 != 0)
        Serial.println(s2);
    }
}
