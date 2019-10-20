#include "MeasuringStation.h"
#include "DHT.h"
#include "SdsDustSensor.h"

#define DHT_PIN 2   
#define DHT_TYPE DHT11   // DHT 11
const int DUST_RX_PIN = D1;  // fine dust sensor
const int DUST_TX_PIN = D2;  // fine dust sensor

Station station(DHT_PIN, DHT_TYPE, DUST_RX_PIN, DUST_TX_PIN);

void setup() {
  Serial.begin(9600);
}

void loop() {
    delay(2000);
    
    float humidity = station.readHumidity();
    float temperature = station.readTemperature();
    station.sensorFailure(humidity, temperature);
    PmResult pm = station.readPm();
    Serial.print("Humidity: ");
    Serial.print(humidity, 1);
    Serial.print("% Temperature: ");
    Serial.print(temperature, 1);
    Serial.println(F("C ")); 
  
    if (pm.isOk()) {
        Serial.print("PM2.5 = ");
              Serial.print(pm.pm25);
    Serial.print(", PM10 = ");
    Serial.println(pm.pm10);
  }
}
