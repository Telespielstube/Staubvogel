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
const char *topic = "/home/AirQuality";
String message;

WiFiClient wifiClient;
PubSubClient pubClient;
Station station(DHT_PIN, DHT_TYPE, DUST_RX_PIN, DUST_TX_PIN);
Connection connection(SSID, PASSWORD, MQTTSERVER, MQTTPORT, MQTTUSER, MQTTPASSWORD, wifiClient, pubClient);
float humidity;
float temperature;

void setup()
{
  delay(2000);
  Serial.begin(9600);
  connection.connectToWifi();
  connection.connectToBroker();
}

void loop()
{
  delay(8000);

  humidity = station.readHumidity();
  temperature = station.readTemperature();
  station.sensorFailure(&humidity, &temperature);
  PmResult pm = station.readPm();
  message = buildMessage(pm);
  pubClient.publish(topic, message.c_str());
  
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

String buildMessage(PmResult pm)
{
  String partOne = String(humidity); 
  String partTwo = String(temperature);
  String partThree = String(pm.pm25);
  String partFour = String(pm.pm10);
  String tempMsg = partOne + partTwo + partThree + partFour;
  return tempMsg;
}
