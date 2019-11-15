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
        const char *_MQTTSERVER;
        int _MQTTPORT;
        const char *_MQTTUSER;
        const char *_MQTTPASSWORD;
        WiFiClient* _wifiClient;
        PubSubClient* _pubClient;

    public:
        Connection(const char *SSID, const char *PASSWORD, const char *MQTTSERVER, int MQTTPORT, const char *MQTTUSER, const char *MQTTPASSWORD, WiFiClient *wifiClient, PubSubClient *pubClient);
        void connectToWifi();
        void connectToBroker();
};
#endif
