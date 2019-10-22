#include "Connection.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

Connection::Connection( char *SSID,  char *PASSWORD, char *MQTTSERVER, int MQTTPORT, char *MQTTUSER, char *MQTTPASSWORD) : _wifiClient(), _client(_wifiClient) 
{
    _SSID = SSID;
    _PASSWORD = PASSWORD;
    _MQTTSERVER = MQTTSERVER;
    _MQTTPORT = MQTTPORT;
    _MQTTUSER = MQTTUSER;
    _MQTTPASSWORD = MQTTPASSWORD;
    
     Serial.println("Trying to connect to network.");
    WiFi.begin(_SSID, _PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(300);
    } 
    Serial.print("Connected to: ");
    Serial.println(WiFi.SSID());
    // connectToWifi(_SSID, _PASSWORD);
    connectToBroker(_client, _MQTTSERVER, _MQTTPORT, _MQTTUSER);
}

/* Function to connect to wifi access point.
void Connection::connectToWifi( char *ssid,  char *password) {
    Serial.println("Trying to connect to network.");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(300);
    } 
    Serial.print("Connected to: ");
    Serial.println(WiFi.SSID());
} */

// Function to connect and to a MQTT server.
void Connection::connectToBroker(PubSubClient client, char *mqttServer,  int mqttPort,  char *mqttUser) {
    Serial.println("Connecting to MQTT broker");
    client.setServer(_MQTTSERVER, _MQTTPORT);
   // wifiClient.setCallback(callback); // handles incoming messages for subscribed topics.

    while (!client.connected()) {
        Serial.println("Connecting to MQTT broker.");
        if (client.connect(mqttUser)) {
            Serial.println("connected");
        }
    }
}