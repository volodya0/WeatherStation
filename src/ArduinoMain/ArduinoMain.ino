#include <Arduino.h>
#include "WeatherDataRecord.h"
#include "SerialMessageTransfer.h"
#include "Temperature.h"
#include "Time.h"

const uint8_t DHT11_PIN = 2;
const uint8_t TMP_PIN = A0;
const uint8_t RTC_CLC_PIN = 6;
const uint8_t CLC_DAT_PIN = 7;
const uint8_t CLC_RST_PIN = 8;

Time time(RTC_CLC_PIN, CLC_DAT_PIN, CLC_RST_PIN);
Temperature temperature(DHT11_PIN, TMP_PIN);

void setup()
{
    Serial.begin(9600);

    Serial.println(SerialMessageTransfer::WrapMessage("Hello boss"));
    Serial.println(SerialMessageTransfer::WrapMessage("Hello boss 2"));
    Serial.println(SerialMessageTransfer::WrapMessage("Hi"));
}

int i = 0;
void loop()
{
    //  Serial.println("Current Serial: " + Serial.readString());
    if (SerialMessageTransfer::CheckNewMessages(Serial.readString()))
    {
        SerialMessageTransfer::PrintMessagesStack();
    }
    else
    {
        Serial.println("No new messages" + String(i++));
    }

    if (SerialMessageTransfer::GetNewMessagesCount() > 0)
    {
        Serial.println("LastMessage: " + SerialMessageTransfer::GetLastMessage());
    }

    delay(5000);
}
