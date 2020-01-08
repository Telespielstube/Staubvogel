#include "Station.h"
#include "DHT.h"
#include "SdsDustSensor.h"

Station::Station(int dhtPin, int dhtType, int dustRxPin, int dustTxPin) : _dht(dhtPin, dhtType), _sds(dustRxPin, dustTxPin) {
    _dhtPin = dhtPin;
    _dhtType = dhtType;
    _dustRxPin = dustRxPin;
    _dustTxPin = dustTxPin;   
    _dht.begin();
    _sds.begin();
}

inline float Station::readHumidity()  {
    return _dht.readHumidity();
}

inline float Station::readTemperature()  {
    return _dht.readTemperature();
}

bool Station::dhtValid(float *humidity, float *temperature) {
  return !isnan(*humidity) && !isnan(*temperature);
}

bool Station::sdsValid(PmResult *pm) {
  return pm->pm10 >= 0.0 && pm->pm25 >= 0.0;
}

inline PmResult Station::readPm()  {
    return _sds.readPm();
} 

// Concatenates SDS11 values to one String. 
inline String Station::buildDustMessage(PmResult pm) {
  return String(pm.pm25) + ',' + String(pm.pm10);
}

// Concatenates DHT11 values to one String. 
inline String Station::buildTempMessage(float temperature, float humidity) {
  return String(temperature) + ',' + String(humidity);
}
