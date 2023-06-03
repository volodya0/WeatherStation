#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <Arduino.h>
#include "DHT.h"

class Temperature
{
public:
    Temperature(uint8_t dht_pin, uint8_t tmp_pin);
    float GetTemp();
    float GetDhtTempC();
    float GetDhtTempF();
    float GetHumidity();
    String GetLogString();

private:
    uint8_t tmp_pin;
    DHT dht;
};

#endif