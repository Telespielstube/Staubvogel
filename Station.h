#include <Arduino.h>
#include "DHT.h"
#include "SdsDustSensor.h"

#ifndef STATION_H
#define STATION_H

class Station {
    private:
        int _dhtPin;
        int _dhtType;
        int _dustRxPin;
        int _dustTxPin;
        DHT _dht;
        SdsDustSensor _sds;

    public:
        Station(int dhtPin, int dhtType, int dustRxPin, int dustTxPin);
        float readHumidity();
        float readTemperature();
        bool dhtValid(float *humidity, float *temperature);
        bool sdsValid(PmResult *pm);
        PmResult readPm();
        String buildDustMessage(PmResult pm);
        String buildTempMessage(float temperature, float humidity);
};

#endif
