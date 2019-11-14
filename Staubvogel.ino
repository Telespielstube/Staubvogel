#include "DHT.h"
#include "SdsDustSensor.h"
#include "MeasuringStation.h"
#include "Connection.h"

const int DHT_PIN = 13;
const int DHT_TYPE = DHT11; // DHT 11
const int DUST_RX_PIN = D1; // fine dust sensor
const int DUST_TX_PIN = D2; // fine dust sensor

const char *SSID = "Telespielstube_2.0";
const char *PASSWORD = "8757420130565695";

char *MQTTSERVER = "localhost";
int MQTTPORT = 1883;
char *MQTTUSER = "Marta";
char *MQTTPASSWORD = "12345";
const char *topicTemp = "/home/backyard/temperature";
const char *topicHum = "/home/backyard/humidity";
const char *topicDust = "/home/backyard/fineDust";
String dustSensorMessage;

WiFiClient wifiClient;
PubSubClient pubClient;
Station station(DHT_PIN, DHT_TYPE, DUST_RX_PIN, DUST_TX_PIN);
Connection connection(SSID, PASSWORD, MQTTSERVER, MQTTPORT, MQTTUSER, MQTTPASSWORD, wifiClient, pubClient);
float humidity = 0.0;
float temperature = 0.0;

void setup()
{
  delay(2000);
  Serial.begin(9600);
  connection.connectToWifi();
  connection.connectToBroker();
}

void loop()
{
  delay(10000);

  humidity = station.readHumidity();
  temperature = station.readTemperature();
  station.sensorFailure(&humidity, &temperature);
  PmResult pm = station.readPm();
  dustSensorMessage = buildDustMessage(pm);
  pubClient.publish(topicTemp, String(temperature).c_str());
  pubClient.publish(topicHum, String(humidity).c_str());
  pubClient.publish(topicDust, dustSensorMessage.c_str());
  serialOutput(pm);
}

// Concatenates all measured values to one String.
String buildDustMessage(PmResult pm)
{
  String pm10 = String(pm.pm25);
  String pm25 = String(pm.pm10);
  String tempMsg = pm10 + ',' + pm25;
  return tempMsg;
}

// Prints all values to the serial monitor. Just for debugging.
void serialOutput(PmResult pm) 
{
  Serial.print("Humidity: ");
  Serial.print(humidity, 1);
  Serial.print("% Temperature: ");
  Serial.print(temperature, 1);
  Serial.println(F("C "));

  if (pm.isOk())
  {
    Serial.print("PM2.5 = ");
    Serial.print(pm.pm25);
    Serial.print(", PM10 = ");
    Serial.println(pm.pm10);
  }
  else
  {
    Serial.println("PM not measuring.");
  }
}
