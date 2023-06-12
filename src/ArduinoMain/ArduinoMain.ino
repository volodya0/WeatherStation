#include <Arduino.h>
#include "Config.h"
#include "SerialMessageTransfer.h"
#include "WeatherSensorsReader.h"
#include "RtcReader.h"
#include "WeatherDataRecord.h"
#include "Timestamp.h"

const uint8_t HW_PIN = A0;
const uint8_t TMP_PIN = A1;
const uint8_t PTR_PIN = A2;

const uint8_t DHT11_PIN = 4;
const uint8_t RTC_CLC_PIN = 6;
const uint8_t CLC_DAT_PIN = 7;
const uint8_t CLC_RST_PIN = 8;

RtcReader rtcReader(RTC_CLC_PIN, CLC_DAT_PIN, CLC_RST_PIN);
WeatherSensorsReader weatherSensorsReader(DHT11_PIN, TMP_PIN, HW_PIN, PTR_PIN);

void setup()
{
    Serial.begin(SERIAL_COMMUNICATION_PORT);
    // rtcReader.SetTime(0, 45, 12, 0, 12, 6, 2023);
}

long delayMs = 20 * 1000;
void loop()
{
    Timestamp timestamp = rtcReader.GetCurrentTimeStamp();
    WeatherData weatherData = weatherSensorsReader.ReadWholeData();

    WeatherDataRecord record(timestamp.getTimestampFromComponents(), weatherData);

    String json = record.toJSON();
    String message = SerialMessageTransfer::WrapMessage(json);

    Serial.println(message);

    delay(delayMs);
}
