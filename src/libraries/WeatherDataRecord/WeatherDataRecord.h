#ifndef WEATHER_DATA_RECORD_H
#define WEATHER_DATA_RECORD_H

#include <Arduino.h>

struct WeatherData
{
    float Temperature;
    float TemperatureDht;
    float Humidity;
};

class WeatherDataRecord
{
public:
    WeatherData Data;
    unsigned long Timestamp;

    WeatherDataRecord();
    WeatherDataRecord(const String &jsonString);
    WeatherDataRecord(unsigned long timestamp, WeatherData data);

    String toJSON() const;
    bool fromJSON(const String &jsonString);
    String toCompressed() const;
    bool fromCompressed(const String &binaryString);
};

#endif // WEATHER_DATA_RECORD_H
