#include <Arduino.h>
#include "WeatherDataRecord.h"

WeatherDataRecord::WeatherDataRecord()
{
}

WeatherDataRecord::WeatherDataRecord(const String &jsonString)
{
    this->fromJSON(jsonString);
}

WeatherDataRecord::WeatherDataRecord(unsigned long timestamp, float temperature, float temperatureDht, float humidity)
    : Timestamp(timestamp), Temperature(temperature), TemperatureDht(temperatureDht), Humidity(humidity)
{
}

String WeatherDataRecord::toJSON() const
{
    String json = "{";
    json += "\"timestamp\":" + String(Timestamp) + ",";
    json += "\"temperature\":" + String(Temperature) + ",";
    json += "\"temperatureDht\":" + String(TemperatureDht) + ",";
    json += "\"humidity\":" + String(Humidity);
    json += "}";
    return json;
}

bool WeatherDataRecord::fromJSON(const String &jsonString)
{
    String json = jsonString;
    json.trim();
    if (json.length() < 2 || json.charAt(0) != '{' || json.charAt(json.length() - 1) != '}')
    {
        Serial.println("WeatherDataRecord::fromJSON() -> Invalid JSON format");
        return false;
    }

    json = json.substring(1, json.length() - 1);
    while (json.length() > 0)
    {
        int colonIndex = json.indexOf(':');
        if (colonIndex == -1)
        {
            Serial.println("WeatherDataRecord::fromJSON() -> Invalid JSON format");
            return false;
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

        if (key == "\"timestamp\"")
        {
            Timestamp = value.toInt();
        }
        else if (key == "\"temperature\"")
        {
            Temperature = value.toFloat();
        }
        else if (key == "\"temperatureDht\"")
        {
            TemperatureDht = value.toFloat();
        }
        else if (key == "\"humidity\"")
        {
            Humidity = value.toFloat();
        }
    }

    return true;
}

String WeatherDataRecord::toCompressed() const
{
    // byte buffer[sizeof(Timestamp) + sizeof(Temperature) + sizeof(TemperatureDht) + sizeof(Humidity)];

    // memcpy(buffer, &Timestamp, sizeof(Timestamp));
    // memcpy(buffer + sizeof(Timestamp), &Temperature, sizeof(Temperature));
    // memcpy(buffer + sizeof(Timestamp) + sizeof(Temperature), &TemperatureDht, sizeof(TemperatureDht));
    // memcpy(buffer + sizeof(Timestamp) + sizeof(Temperature) + sizeof(TemperatureDht), &Humidity, sizeof(Humidity));

    // String rawBinary = "";
    // for (unsigned int i = 0; i < sizeof(buffer); i++)
    // {
    //     rawBinary += (char)buffer[i];
    // }

    return toJSON();
}

bool WeatherDataRecord::fromCompressed(const String &compressed)
{
    // Check if the compressed string has the expected length
    // if (compressed.length() != sizeof(Timestamp) + sizeof(Temperature) + sizeof(TemperatureDht) + sizeof(Humidity))
    // {
    //     Serial.println("WeatherDataRecord::fromCompressed() -> Invalid binary data");
    //     return false;
    // }

    // memcpy(&Timestamp, compressed.c_str(), sizeof(Timestamp));
    // memcpy(&Temperature, compressed.c_str() + sizeof(Timestamp), sizeof(Temperature));
    // memcpy(&TemperatureDht, compressed.c_str() + sizeof(Timestamp) + sizeof(Temperature), sizeof(TemperatureDht));
    // memcpy(&Humidity, compressed.c_str() + sizeof(Timestamp) + sizeof(Temperature) + sizeof(TemperatureDht), sizeof(Humidity));

    return fromJSON(compressed);
}
