#include "Connection.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

Connection::Connection(char const *ssid, char const *password, char const *mqttServer, int mqttPort, char const *mqttUser, char const *mqttPassword, char const *willTopic, int willQoS, int willRetain, char const *willMessage, WiFiClient *wifiClient, PubSubClient *pubClient) {
  _ssid = ssid;
  _password = password;
  _mqttServer = mqttServer;
  _mqttPort = mqttPort;
  _mqttUser = mqttUser;
  _mqttPassword = mqttPassword;
  _willTopic = willTopic;
  _willQoS = willQoS;
  _willRetain = willRetain;
  _willMessage = willMessage;
  _wifiClient = wifiClient;
  _pubClient = pubClient;
}

// Function to connect to wifi access point.
void Connection::connectToWifi() {
  Serial.println("Trying to connect to network:" + String(_ssid));
  randomSeed(micros()); 
  WiFi.begin(_ssid, _password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(300);
  }
  Serial.println("\nConnected to: " + WiFi.SSID());
  Serial.print("IP address: " + WiFi.localIP());
  delay(3000);
}

/* Function to connect to a MQTT server.
*/
bool Connection::connectToBroker(){ 
  if (_pubClient->connected()) {
    return true;
  }
  _pubClient->setServer(_mqttServer, _mqttPort);
  Serial.println("Connecting to MQTT broker");
  while (!_pubClient->connected()) {
    String clientId = "Staubfaenger";
    clientId += String(random(0xffff), HEX);
    if (_pubClient->connect(clientId.c_str(), _mqttUser, _mqttPassword, willTopic, willQoS, willRetain, willMessage)) {
      Serial.println(clientId + " is connected");
      return true;
    } else {
      Serial.println("Could not connect. " + _pubClient->state());
      delay(3000);
    }
  }
  return false;
}
