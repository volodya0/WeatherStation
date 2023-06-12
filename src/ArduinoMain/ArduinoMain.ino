#include <Arduino.h>
#include "WeatherDataRecord.h"
#include "SerialMessageTransfer.h"
#include "Temperature.h"
#include "Timestamp.h"
#include "Time.h"
#include "Config.h"

const uint8_t HW_PIN = A0;
const uint8_t TMP_PIN = A1;
const uint8_t PTR_PIN = A2;

const uint8_t DHT11_PIN = 4;
const uint8_t RTC_CLC_PIN = 6;
const uint8_t CLC_DAT_PIN = 7;
const uint8_t CLC_RST_PIN = 8;

Time time(RTC_CLC_PIN, CLC_DAT_PIN, CLC_RST_PIN);
Temperature temperature(DHT11_PIN, TMP_PIN, HW_PIN, PTR_PIN);

void setup()
{
    Serial.begin(SERIAL_COMMUNICATION_PORT);
    // time.SetTime(0, 27, 21, 6, 11, 5, 2023);
}

int i = 0;
void loop()
{
    Timestamp timestamp = time.GetCurrentTimeStamp();

    WeatherDataRecord record(timestamp.getTimestampFromComponents(), temperature.GetData());

    String json = record.toJSON();

    String message = SerialMessageTransfer::WrapMessage(json);

    Serial.println(message);

    delay(5000);
}
