#include "Connection.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

Connection::Connection(const char *SSID, const char *PASSWORD, const char *MQTTSERVER, int MQTTPORT, const char *MQTTUSER, const char *MQTTPASSWORD, WiFiClient* wifiClient, PubSubClient* pubClient)
{
  _SSID = SSID;
  _PASSWORD = PASSWORD;
  _MQTTSERVER = MQTTSERVER;
  _MQTTPORT = MQTTPORT;
  _MQTTUSER = MQTTUSER;
  _MQTTPASSWORD = MQTTPASSWORD;
  _wifiClient = wifiClient;
  _pubClient = pubClient;
}

// Function to connect to wifi access point.
void Connection::connectToWifi()
{
  Serial.println("Trying to connect to network:" + String(_SSID));
  randomSeed(micros()); 
  WiFi.begin(_SSID, _PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(300);
  }
  Serial.println("\nConnected to: " + WiFi.SSID());
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  delay(3000);
}

/* Function to connect to a MQTT server.

*/
void Connection::connectToBroker()
{
  
  if (_pubClient->connected())
  {
    return;
  }
  
  _pubClient->setServer(_MQTTSERVER, _MQTTPORT);
  Serial.println("Connecting to MQTT broker");
  while (!_pubClient->connected())
  {
    String clientId = "Staubfaenger";
    clientId += String(random(0xffff), HEX);
    if (_pubClient->connect(clientId.c_str(), MQTTUSER, MQTTPASSWORD))
    {
      Serial.println(clientId + " is connected");
    } else
    {
      Serial.println("Could not connect. " + _pubClient->state());
    }
  }
}
