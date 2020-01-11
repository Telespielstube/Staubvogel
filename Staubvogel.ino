#include "DHT.h"
#include "SdsDustSensor.h"
#include "Station.h"
#include "Connection.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Sensor pins
int const dhtPin = 13;
int const dhtType = DHT11; // DHT 11
int const dustRxPin = D1; // fine dust sensor
int const dustTxPin = D2; // fine dust sensor

//Wifi credentials
char const *ssid = "iPhone";
char const *password = "mqttProject";

// MQTT credentials
char const *mqttServer = "broker.hivemq.com";
int mqttPort = 1883;
char const *mqttUser = "telespielstube";
char const *mqttPassword = "12345";

// MQTT topics
char const *topicTemp = "/home/backyard/dht11";
char const *topicDust = "/home/backyard/sds11";

WiFiClient wifiClient;
PubSubClient pubClient(wifiClient);
Station station(dhtPin, dhtType, dustRxPin, dustTxPin);
Connection connection(ssid, password, mqttServer, mqttPort, mqttUser, mqttPassword, &wifiClient, &pubClient);
float humidity;
float temperature;

void setup() {
  Serial.begin(115200);
  connection.connectToWifi();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connection.connectToWifi();
  } else if (!pubClient.connected()) {
    if (connection.connectToBroker()) {
      return;
    }
  }
  pubClient.loop();
  delay(12000);
  humidity = station.readHumidity();
  temperature = station.readTemperature();
  PmResult pm = station.readPm();

  // Validates fine dust data values and publishes them if valid
  if (station.sdsValid(&pm)) {
    String dustSensorMessage = station.buildDustMessage(pm);
    if (!pubClient.publish(topicDust, dustSensorMessage.c_str(), true)) {
      Serial.println("Error publishing fine dust data.");
    }
  } else {
    Serial.println("Invalid fine dust data received. Not publishing.");
  }
  if (station.dhtValid(&humidity, &temperature)) {
    String tempSensorMessage = station.buildTempMessage(temperature, humidity);
    if (!pubClient.publish(topicTemp, tempSensorMessage.c_str(), true)) {
      Serial.println("Error publishing dht11 data.");
    }
  } else {
    Serial.println("Invalid temperature data received. Not publishing.");
  }
}
