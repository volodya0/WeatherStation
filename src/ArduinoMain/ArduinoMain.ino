#include <Arduino.h>
#include "WeatherDataRecord.h"
#include "SerialMessageTransfer.h"
#include "Temperature.h"
#include "Time.h"
#include "Config.h"

const uint8_t DHT11_PIN = 2;
const uint8_t TMP_PIN = A0;
const uint8_t RTC_CLC_PIN = 6;
const uint8_t CLC_DAT_PIN = 7;
const uint8_t CLC_RST_PIN = 8;

Time time(RTC_CLC_PIN, CLC_DAT_PIN, CLC_RST_PIN);
Temperature temperature(DHT11_PIN, TMP_PIN);

void setup()
{
    Serial.begin(SERIAL_COMMUNICATION_PORT);
}

int i = 0;
void loop()
{

    delay(5000);

    WeatherDataRecord record(time.GetCurrentTimeStamp(), temperature.GetTemp(), temperature.GetDhtTempC(), temperature.GetHumidity());
    String json = record.toJSON();
    String message = SerialMessageTransfer::WrapMessage(json);
    Serial.println(message);
}
