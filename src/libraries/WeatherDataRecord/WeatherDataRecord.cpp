#include <Arduino.h>
#include "WeatherDataRecord.h"

WeatherDataRecord::WeatherDataRecord()
{
}

WeatherDataRecord::WeatherDataRecord(const String &jsonString)
{
    this->fromJSON(jsonString);
}

WeatherDataRecord::WeatherDataRecord(unsigned long timestamp, WeatherData data)
    : Timestamp(timestamp), Data(data)
{
}

String WeatherDataRecord::toJSON() const
{
    // The max number of digits in an unsigned long is 20, with an extra space for the null terminator
    char buffer[21];
    char *p = buffer + 20;       // Pointer to the end of the buffer
    *p = '\0';                   // Null terminate the string
    unsigned long n = Timestamp; // The number to convert

    do
    {
        *--p = '0' + n % 10; // Convert the last digit of n to a char and store it
        n /= 10;             // Remove the last digit from n
    } while (n);

    String json = "{";
    json += "\"timestamp\":" + String(p) + ",";
    json += "\"temperature\":" + String(Data.Temperature) + ",";
    json += "\"temperatureDht\":" + String(Data.TemperatureDht) + ",";
    json += "\"humidity\":" + String(Data.Humidity);
    json += "\"precipitation\":" + String(Data.Precipitation);
    json += "\"brightness\":" + String(Data.Brightness);
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
            const char *p = value.begin(); // The string to convert
            unsigned long n = 0;

            while (*p >= '0' && *p <= '9')
            {
                n = 10 * n + (*p++ - '0');
            }

            Timestamp = n;
        }
        else if (key == "\"temperature\"")
        {
            Data.Temperature = value.toFloat();
        }
        else if (key == "\"temperatureDht\"")
        {
            Data.TemperatureDht = value.toFloat();
        }
        else if (key == "\"humidity\"")
        {
            Data.Humidity = value.toFloat();
        }
        else if (key == "\"precipitation\"")
        {
            Data.Precipitation = value.toInt();
        }
        else if (key == "\"brightness\"")
        {
            Data.Brightness = value.toInt();
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
