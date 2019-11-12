#include "Connection.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

Connection::Connection(const char *SSID, const char *PASSWORD, char *MQTTSERVER, int MQTTPORT, char *MQTTUSER, char *MQTTPASSWORD, WiFiClient wifiClient, PubSubClient pubClient)
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
    Serial.print("Trying to connect to network:");
    Serial.println(_SSID);
    WiFi.begin(_SSID, _PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print('.');
        delay(300);
    }
    Serial.print("Connected to: ");
    Serial.println(WiFi.SSID());
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    connectToBroker();
    Serial.println("Trying to connect to network.");
}

/* Function to connect to a MQTT server.
 *  
 */
void Connection::connectToBroker()
{
    Serial.println("Connecting to MQTT broker");
    _pubClient.setServer(_MQTTSERVER, _MQTTPORT);

    while (!_pubClient.connected())
    {
        Serial.println("Connecting to MQTT broker.");
        if (_pubClient.connect(_MQTTUSER))
        {
            Serial.println("connected");
        }
        else
        {
            Serial.println("Could not connect");
        }
    }
}
