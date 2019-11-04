#include "Connection.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

Connection::Connection(const char *SSID, const char *PASSWORD, char *MQTTSERVER, int MQTTPORT, char *MQTTUSER, char *MQTTPASSWORD) : _wifiClient(), _client(_wifiClient)
{
    _SSID = SSID;
    _PASSWORD = PASSWORD;
    _MQTTSERVER = MQTTSERVER;
    _MQTTPORT = MQTTPORT;
    _MQTTUSER = MQTTUSER;
    _MQTTPASSWORD = MQTTPASSWORD;
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
    connectToBroker(_client, _MQTTSERVER, _MQTTPORT, _MQTTUSER);
    Serial.println("Trying to connect to network.");
}

/* Function to connect to a MQTT server.
 *  
 */
void Connection::connectToBroker(PubSubClient client, char *mqttServer, int mqttPort, char *mqttUser)
{
    Serial.println("Connecting to MQTT broker");
    client.setServer(_MQTTSERVER, _MQTTPORT);
    // wifiClient.setCallback(callback); // handles incoming messages for subscribed topics.

    while (!client.connected())
    {
        Serial.println("Connecting to MQTT broker.");
        if (client.connect(mqttUser))
        {
            Serial.println("connected");
        }
        else
        {
            Serial.println("Could not connect");
        }
    }
}
