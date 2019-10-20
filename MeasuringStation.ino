#include "MeasuringStation.h"
#include "DHT.h"
#include "SdsDustSensor.h"

Station::Station(int dhtPin, int dhtType, int DUST_RX_PIN, int DUST_TX_PIN) : _dht(dhtPin, dhtType), _sds(DUST_RX_PIN, DUST_TX_PIN)
{
    _dhtPin = dhtPin;
    _dhtType = dhtType;
    _DUST_RX_PIN = DUST_RX_PIN;
    _DUST_TX_PIN = DUST_TX_PIN;   
    _dht.begin();
    _sds.begin();
}

float Station::readHumidity() {
    return _dht.readHumidity();
}

float Station::readTemperature() {
    return _dht.readTemperature();
}

void Station::sensorFailure(float humidity, float temperature) {
    if (isnan(humidity) || isnan(temperature) ) {
        Serial.println(F("Failed to read from DHT sensor!"));
    }
    return;
}

PmResult Station::readPm() {
    return _sds.readPm();
} 