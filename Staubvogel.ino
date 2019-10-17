#include "DHT.h"

// Defines are preprocessor. That allows to give names to constant values before the programm is compiled. 
// !!Constants do not use the small memory space on the chip 
#define DHT_PIN 2   
#define DHT_TYPE DHT11   // DHT 11

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht.begin();
}


void sensorFailure(float humidity, float temperature) {
    if (isnan(humidity) || isnan(temperature) ) {
      Serial.println(F("Failed to read from DHT sensor!"));
    return;
    }
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  sensorFailure(humidity, temperature);

  Serial.print("Humidity: ");
  Serial.print(humidity, 1);
  Serial.print("%  Temperature: ");
  Serial.print(temperature, 1);
  Serial.print(F("°C "));

  delay(2000);
}