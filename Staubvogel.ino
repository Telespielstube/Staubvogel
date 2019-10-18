

// Defines are preprocessor. That allows to give names to constant values before the programm is compiled. 
// !!Constants do not use the small memory space on the chip 
#define DHT_PIN 2   
#define DHT_TYPE DHT11   // DHT 11
const int DUST_TX_PIN = D1;
const int DUST_RX_PIN = D2;
/*
DHT dht(DHT_PIN, DHT_TYPE);
SdsDustSensor sds(DUST_RX_PIN, DUST_TX_PIN);
*/

MeasuringStation measure(DHT_PIN, DHT_TYPE, DUST_TX_PIN, DUST_RX_PIN);

void setup() {
  sds.begin();
  Serial.begin(9600);
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
  PmResult pm = sds.readPm();
  Serial.println(pm.toString());
  Serial.print("Humidity: ");
  Serial.print(humidity, 1);
  Serial.print("% Temperature: ");
  Serial.print(temperature, 1);
  Serial.println(F("C "));

  delay(2000);
}