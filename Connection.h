#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#ifndef CONNECTION_H
#define CONNECTION_H

class Connection {
    private:
        // Client credentials
        char const *_ssid; 
        char const *_password;

        // MQTT credentials
        char const *_mqttServer;
        int _mqttPort;
        char const *_mqttUser;
        char const *_mqttPassword;
        WiFiClient* _wifiClient;
        PubSubClient* _pubClient;

    public:
        Connection(char const *ssid, char const *password, char const *mqttServer, int mqttPort, char const *mqttUser, char const *mqttPassword, WiFiClient *wifiClient, PubSubClient *pubClient);
        void connectToWifi();
        bool connectToBroker();
};
#endif
