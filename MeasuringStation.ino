#include "TempSensor.h"

TempSensor::TempSensor(const int SENSORPIN, const int SENSORTYPE) {
    this->SENSORPIN = SENSORPIN;
    this->SENSORTYPE = SENSORTYPE;
    init();
}