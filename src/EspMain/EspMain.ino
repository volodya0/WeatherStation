#include "Config.h"
#include <LiquidCrystal_I2C.h>
#include "WifiConnector.h"
#include "SerialMessageTransfer.h"
#include "WeatherDataRecord.h"
#include "WeatherDataPool.h"

void setup()
{
    Serial.begin(SERIAL_COMMUNICATION_PORT);
}

int i = 1;
void loop()
{
    Serial.println("************* Iteration " + String(i++) + "***********************");

    Serial.println("RecordsCount " + String(WeatherDataPool::GetRecordsCount()));

    SerialMessageTransfer::CheckNewMessages(Serial.readString());

    if (SerialMessageTransfer::GetNewMessagesCount() > 0)
    {
        Serial.println("MessagesCount: " + String(SerialMessageTransfer::GetNewMessagesCount()));
        SerialMessageTransfer::PrintMessagesStack();
        String lastMessage = SerialMessageTransfer::GetLastMessage(true);
        Serial.println("Last message: " + lastMessage);

        WeatherDataRecord receivedRecord;
        if (receivedRecord.fromJSON(lastMessage))
        {
            Serial.println("Valid record: " + receivedRecord.toJSON());

            WeatherDataPool::AddRecord(receivedRecord);
            WeatherDataPool::PrintAllRecords();

            Serial.println("Last record timestamp parsed: " + TimestampToDateString(receivedRecord.Timestamp) + " " + TimestampToTimeString(receivedRecord.Timestamp));
        }
        else
        {
            Serial.println("Invalid record: " + receivedRecord.toJSON());
        }
    }

    delay(5000);
}

String TimestampToDateString(unsigned long timestamp)
{
    unsigned long days = timestamp / 86400; // 86400 seconds in a day

    // Extract year
    unsigned int year = 1970;
    while (days >= 365)
    {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        {
            if (days >= 366)
                days -= 366;
            else
                break;
        }
        else
        {
            days -= 365;
        }
        year++;
    }

    // Extract month and day
    unsigned int daysPerMonth[] = {31, 28 + ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    unsigned int month = 0;
    while (days >= daysPerMonth[month])
    {
        days -= daysPerMonth[month];
        month++;
    }

    // Extract day of the month
    unsigned int day = days + 1;

    // Format date string
    return String(day) + "/" + String(month + 1) + "/" + String(year);
}

String TimestampToTimeString(unsigned long timestamp)
{
    unsigned int seconds = timestamp % 60;
    unsigned int minutes = (timestamp / 60) % 60;
    unsigned int hours = (timestamp / 3600) % 24;

    // Format time string
    return String(hours) + ":" + String(minutes) + ":" + String(seconds);
}
