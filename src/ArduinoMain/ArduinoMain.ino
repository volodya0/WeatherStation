#include <Arduino.h>
#include "WeatherDataRecord.h"
#include "Temperature.h"
#include "Time.h"

uint8_t DHT11_PIN = 2;
uint8_t TMP_PIN = A0;
uint8_t RTC_CLC_PIN = 6;
uint8_t CLC_DAT_PIN = 7;
uint8_t CLC_RST_PIN = 8;

Time time(RTC_CLC_PIN, CLC_DAT_PIN, CLC_RST_PIN);
Temperature temperature(DHT11_PIN, TMP_PIN);

void setup()
{
    Serial.begin(9600);
}

int i = 0;
void loop()
{

    long a = 42342342323;
    Serial.println("hello from 9600 from arduino" + String(i++));
    Serial.println("Time: " + time.GetLogString());
    Serial.println("Temperature:  " + temperature.GetLogString());

    WeatherDataRecord record(temperature.GetTemp(), temperature.GetHumidity(), 43234233);
    String recordJ = record.toJSON();

    Serial.println("JSON :  " + recordJ);

    WeatherDataRecord parsedRecord(recordJ);
    Serial.println("from JSON :  " + String(parsedRecord.Temperature));
    Serial.println("from JSON :  " + String(parsedRecord.Humidity));
    Serial.println("from JSON :  " + String(parsedRecord.Timestamp));

    delay(1500);
}
