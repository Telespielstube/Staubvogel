#include "TempSensor.h"


TempSensor::TempSensor(const int SENSORPIN, const it SENSORTYPE) {
    this->SENSORPIN = SENSORPIN;
    this->SENSORTYPE = SENSORTYPE;
    init();
}