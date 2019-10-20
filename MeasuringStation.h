#include <Arduino.h>
#include "DHT.h"
#include "SdsDustSensor.h"

#ifndef MEASURINGSTATION_H
#define MEASURINGSTATION_H

class Station {
    private:
        int _dhtPin;
        int _dhtType;
        int _DUST_RX_PIN;
        int _DUST_TX_PIN;
        DHT _dht;
        SdsDustSensor _sds;

    public:
        Station(int dhtPin, int dhtType, int DUST_RX_PIN, int DUST_TX_PIN);
        float readHumidity();
        float readTemperature();
        void sensorFailure(float humidity, float temperature);
        PmResult readPm();
};

#endif