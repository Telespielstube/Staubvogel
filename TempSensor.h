#include <ARduino.h>
#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H

class TempSensor {
    private:
        const int SENSORPIN;
        const int SENSORTYPE;

    public:
        TempSensor(const int SENSORPIN, const int SENSORTYPE);
        void init()
        float readTemperature();
        float readHumidity();

};

#endif