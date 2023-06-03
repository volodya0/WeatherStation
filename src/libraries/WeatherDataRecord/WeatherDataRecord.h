#ifndef WEATHER_DATA_RECORD_H
#define WEATHER_DATA_RECORD_H

#include <Arduino.h>

class WeatherDataRecord
{
public:
    float Temperature;
    float Humidity;
    long Timestamp;

    WeatherDataRecord(const String &jsonString);
    WeatherDataRecord(float temperature, float humidity, long timestamp);

    String toJSON() const;
    void fromJSON(const String &jsonString);
};

#endif // WEATHER_DATA_RECORD_H
