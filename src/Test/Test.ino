#include <Arduino.h>
#include "WeatherDataRecord.h"

void setup()
{
    Serial.begin(9600);

    // Create a WeatherDataRecord object
    WeatherDataRecord dataRecord(1722732400, 25.5, 23.7, 60.2);
    Serial.println("Timestamp: " + String(dataRecord.Timestamp));
    Serial.println("Temperature: " + String(dataRecord.Temperature));
    Serial.println("TemperatureDht: " + String(dataRecord.TemperatureDht));
    Serial.println("Humidity: " + String(dataRecord.Humidity));

    // Convert to JSON
    String json = dataRecord.toJSON();
    Serial.println("JSON: " + json);

    // Convert to binary
    String binary = dataRecord.toCompressed();
    Serial.println("Binary: " + binary);

    // Create a new WeatherDataRecord object from JSON
    WeatherDataRecord jsonRecord;
    if (jsonRecord.fromJSON(json))
    {
        Serial.println("JSON -> Timestamp: " + String(jsonRecord.Timestamp));
        Serial.println("JSON -> Temperature: " + String(jsonRecord.Temperature));
        Serial.println("JSON -> TemperatureDht: " + String(jsonRecord.TemperatureDht));
        Serial.println("JSON -> Humidity: " + String(jsonRecord.Humidity));
    }

    // Create a new WeatherDataRecord object from binary
    WeatherDataRecord binaryRecord;
    if (binaryRecord.fromCompressed(binary))
    {
        Serial.println("Binary -> Timestamp: " + String(binaryRecord.Timestamp));
        Serial.println("Binary -> Temperature: " + String(binaryRecord.Temperature));
        Serial.println("Binary -> TemperatureDht: " + String(binaryRecord.TemperatureDht));
        Serial.println("Binary -> Humidity: " + String(binaryRecord.Humidity));
    }
}

void loop()
{
    // Do nothing in the loop
}
