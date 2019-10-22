#include "DHT.h"
#include "SdsDustSensor.h"
#include "MeasuringStation.h"
#include "Connection.h"

const int DHT_PIN = 13;   
const int DHT_TYPE = DHT11;   // DHT 11
const int DUST_RX_PIN = D1;  // fine dust sensor
const int DUST_TX_PIN = D2;  // fine dust sensor

char *SSID = "Telespielstube_2.0"; 
char *PASSWORD = "8757420130565695";

char *MQTTSERVER = "localhost";
int MQTTPORT = 1883;
char *MQTTUSER = "Marta";
char *MQTTPASSWORD = "12345";

Station station(DHT_PIN, DHT_TYPE, DUST_RX_PIN, DUST_TX_PIN);
Connection connection(SSID, PASSWORD, MQTTSERVER, MQTTPORT, MQTTUSER, MQTTPASSWORD);
//Publish publish(); 
//Subscribe subscribe();

void setup() {
  Serial.begin(9600);
  connection.connectToWifi();
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
    } else {
      Serial.println("PM not measuring.");
    }
}
