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
        char const *_willTopic;
        int _willQoS;
        int _willRetain;
        char const *_willMessage;
        WiFiClient* _wifiClient;
        PubSubClient* _pubClient;

    public:
        /** Constructor for Connection object.
         *  
         *  @param *ssid        name of the wifi network (service set identifier)
         *  @param *password    password for wifi network.
         *  @param *mqttServer  ip address for MQTT broker. 
         *  @param *mqttPort    port number broker listens tn.
         *  @param *mqttUser    user name needed for authorization to access topic
         *  @param *mqttPasword user password needed for authorization to access topic
         *  @param *willTopic   specifies the last will topic.
         *  @param willQos      sets the quality of service level for this message.
         *  @param willRetain   sets the retained flag for this message.
         *  @param *willMessage  contains the last will message for the clients.
         *  @param *wifiClient  wifi object.
         *  @param *pubClient   publisher object. 
         */
        Connection(char const *ssid, char const *password, char const *mqttServer, int mqttPort, char const *mqttUser, char const *mqttPassword, char const *willTopic, int willQoS, int willRetain, char const *willMessage, WiFiClient *wifiClient, PubSubClient *pubClient);
        /** Connects client to wifi network.
         */
        void connectToWifi();
        /** Connects client to mqtt broker.
         */
        bool connectToBroker();
};
#endif
