#ifndef WEATHER_DATA_RECORD_H
#define WEATHER_DATA_RECORD_H

#include <Arduino.h>

class WeatherDataRecord
{
public:
    float Temperature;
    float TemperatureDht;
    float Humidity;
    long Timestamp;

    WeatherDataRecord();
    WeatherDataRecord(const String &jsonString);
    WeatherDataRecord(unsigned long timestamp, float temperature, float temperatureDht, float humidity);

    String toJSON() const;
    bool fromJSON(const String &jsonString);
    String toCompressed() const;
    bool fromCompressed(const String &binaryString);
};

#endif // WEATHER_DATA_RECORD_H
