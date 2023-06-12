#ifndef WEATHERSENSORREADER_H
#define WEATHERSENSORREADER_H

#include <Arduino.h>
#include "WeatherDataRecord.h"
#include "DHT.h"

class WeatherSensorsReader
{
public:
    WeatherSensorsReader(uint8_t dht_pin, uint8_t tmp_pin, uint8_t hw_pin, uint8_t ptr_pin);
    float ReadTemp();
    float ReadDhtTempC();
    float ReadDhtTempF();
    float ReadHumidity();
    int ReadPrecipitation();
    int ReadBrightness();
    String GetLogString();
    WeatherData ReadWholeData();

private:
    uint8_t tmp_pin;
    uint8_t hw_pin;
    uint8_t ptr_pin;
    DHT dht;
};

#endif