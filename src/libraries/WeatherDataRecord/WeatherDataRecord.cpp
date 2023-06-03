#include <Arduino.h>
#include "WeatherDataRecord.h"

WeatherDataRecord::WeatherDataRecord(const String &jsonString)
{
    this->fromJSON(jsonString);
}

WeatherDataRecord::WeatherDataRecord(float temperature, float humidity, long timestamp)
    : Temperature(temperature), Humidity(humidity),
      Timestamp(timestamp) {}

String WeatherDataRecord::toJSON() const
{
    String json = "{";
    json += "\"temperature\":" + String(Temperature) + ",";
    json += "\"humidity\":" + String(Humidity) + ",";
    json += "\"timestamp\":" + String(Timestamp);
    json += "}";
    return json;
}

void WeatherDataRecord::fromJSON(const String &jsonString)
{
    String json = jsonString;
    json.trim();
    if (json.length() < 2 || json.charAt(0) != '{' || json.charAt(json.length() - 1) != '}')
    {
        Serial.println("Invalid JSON format");
        return;
    }

    json = json.substring(1, json.length() - 1);
    while (json.length() > 0)
    {
        int colonIndex = json.indexOf(':');
        if (colonIndex == -1)
        {
            Serial.println("Invalid JSON format");
            return;
        }

        String key = json.substring(0, colonIndex);
        key.trim();

        json = json.substring(colonIndex + 1);
        json.trim();

        int commaIndex = json.indexOf(',');
        if (commaIndex == -1)
        {
            commaIndex = json.length();
        }

        String value = json.substring(0, commaIndex);
        value.trim();

        json = json.substring(commaIndex + 1);
        json.trim();

        if (key == "\"temperature\"")
        {
            Temperature = value.toFloat();
        }
        else if (key == "\"humidity\"")
        {
            Humidity = value.toFloat();
        }
        else if (key == "\"timestamp\"")
        {
            Timestamp = value.toInt();
        }
    }
}