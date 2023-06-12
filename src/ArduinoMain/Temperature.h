#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <Arduino.h>
#include "WeatherDataRecord.h"
#include "DHT.h"

class Temperature
{
public:
    Temperature(uint8_t dht_pin, uint8_t tmp_pin, uint8_t hw_pin, uint8_t ptr_pin);
    float GetTemp();
    float GetDhtTempC();
    float GetDhtTempF();
    float GetHumidity();
    int GetPrecipitation();
    int GetBrightness();
    String GetLogString();
    WeatherData GetData();

private:
    uint8_t tmp_pin;
    uint8_t hw_pin;
    uint8_t ptr_pin;
    DHT dht;
};

#endif