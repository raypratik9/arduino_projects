

#include <Wire.h>
#include <Adafruit_BMP280.h>
#include<SoftWire.h>
int b=1;
float distance,pressure;
Adafruit_BMP280 bmp; // I2C
void setup() {
    
  Serial.begin(9600);
  Serial.println(F("BMP280 test"));
Wire.begin(); 
 
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void loop() {
    while(b)
    {
      b=0;
      pressure=bmp.readPressure();
    }
    distance=(bmp.readPressure()-pressure)*-6.66;
    float pressure1=(bmp.readPressure()-pressure)*-1;
    Serial.print("Pressure = ");
    Serial.print(pressure1);
    Serial.println(" Pa");
    Serial.println();
}
