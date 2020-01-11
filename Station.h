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
        /** Constructor for Station object.
         *  
         *  @param dhtPin     pin numver the dht data pin is connected to.
         *  @param dhtType    model name of the temperature sensor.
         *  @param dustRxPin  pin number the dust senor rx pin is connected to.
         *  @param dustTxPin  pin number the dust senor tx pin is connected to.
         */
        Station(int dhtPin, int dhtType, int dustRxPin, int dustTxPin);
        
        /** Read humidity as percent.
         */
        float readHumidity();
        
        /** Read temperature as Celsius.
         */
        float readTemperature();
        
        /** checks if values are valid measurements.
         *
         * @param *humidity     read humidity value.
         * @param *temperature  read temperature value;
         */
        bool dhtValid(float *humidity, float *temperature);
        
        /** Checks if dust measurement is valid;
         *  
         *  @param *pm  holds values for pm10 and pm25.
         */
        bool sdsValid(PmResult *pm);
        
        /** Reads the particulate pollution. 
         */
        PmResult readPm();
        
        /** Casts float values to a String object.
         */
        String buildDustMessage(PmResult pm);
        
        /** Casts float values to a String object.
         */
        String buildTempMessage(float temperature, float humidity);
};

#endif
