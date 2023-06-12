#include <Arduino.h>
#include "Temperature.h"
#include "DHT.h"
#include "WeatherDataRecord.h"

#define DHTTYPE DHT11 // DHT 11

Temperature::Temperature(uint8_t dht_pin, uint8_t tmp_pin, uint8_t hw_pin, uint8_t ptr_pin) : dht(DHT(dht_pin, DHTTYPE))
{
    pinMode(dht_pin, INPUT);
    pinMode(tmp_pin, INPUT);
    pinMode(hw_pin, INPUT);
    pinMode(ptr_pin, INPUT);

    this->tmp_pin = tmp_pin;
    this->hw_pin = hw_pin;
    this->ptr_pin = ptr_pin;

    dht.begin();
}

float Temperature::GetTemp()
{
    float temp = analogRead(tmp_pin);                 // 0 - 1023
    float result = (temp / 1023.0) * 5.0 * 1000 / 10; // Converting to celsius

    return result;
}

float Temperature::GetDhtTempC()
{
    // Read temperature as Celsius
    float result = dht.readTemperature();
    return result;
}

float Temperature::GetDhtTempF()
{
    // Read temperature as Fahrenheit
    float result = dht.readTemperature(true);
    return result;
}

float Temperature::GetHumidity()
{
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
    float result = dht.readHumidity();
    return result;
}

int Temperature::GetPrecipitation()
{
    int value = analogRead(hw_pin);
    return 1024 - value;
}

int Temperature::GetBrightness()
{
    int value = analogRead(ptr_pin);
    return value;
}

WeatherData Temperature::GetData()
{
    WeatherData data;

    data.Temperature = GetTemp();
    data.TemperatureDht = GetDhtTempC();
    data.Humidity = GetHumidity();
    data.Precipitation = GetPrecipitation();
    data.Brightness = GetBrightness();

    return data;
}

String Temperature::GetLogString()
{
    WeatherData data = GetData();

    return "Temp: " + String(data.Temperature) + "\tDhtTempC: " + String(data.TemperatureDht) +
           "\tHumidity: " + String(data.Humidity);
}
