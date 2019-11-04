#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#ifndef CONNECTION_H
#define CONNECTION_H

class Connection {
    private:
        // Client credentials
        const char *_SSID; 
        const char *_PASSWORD;

        // MQTT credentials
        char *_MQTTSERVER;
        int _MQTTPORT;
        char *_MQTTUSER;
        char *_MQTTPASSWORD;

        WiFiClient _wifiClient;
        PubSubClient _client;

    public:
        Connection(const char *SSID, const char *PASSWORD, char *MQTTSERVER, int MQTTPORT, char *MQTTUSER, char *MQTTPASSWORD);
        void connectToWifi();
       // void obtainLocalIpAddress();
        void connectToBroker(PubSubClient client, char *mqttServer,  int mqttPort,  char *mqttUser);
};
#endif