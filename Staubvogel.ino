#include <DHT.h>
#include "SdsDustSensor.h"

#define DHT_PIN 2   
#define DHT_TYPE DHT11   // DHT 11
const int DUST_RX_PIN = D1;
const int DUST_TX_PIN = D2;


DHT dht(DHT_PIN, DHT_TYPE);
SdsDustSensor sds(DUST_RX_PIN, DUST_TX_PIN);

void setup() {
  Serial.begin(9600);
  sds.begin();
  dht.begin();
  
}

void sensorFailure(float humidity, float temperature) {
    if (isnan(humidity) || isnan(temperature) ) {
      Serial.println(F("Failed to read from DHT sensor!"));
    return;
    }
}

void loop() {
  delay(2000);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  sensorFailure(humidity, temperature);
  PmResult pm = sds.readPm();
  if (pm.isOk()) {
    Serial.print("PM2.5 = ");
    Serial.print(pm.pm25);
    Serial.print(", PM10 = ");
    Serial.println(pm.pm10);
  }
  Serial.print("Humidity: ");
  Serial.print(humidity, 1);
  Serial.print("% Temperature: ");
  Serial.print(temperature, 1);
  Serial.println(F("C "));
}
