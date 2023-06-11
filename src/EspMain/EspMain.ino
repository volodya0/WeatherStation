#include "Config.h"
#include <LiquidCrystal_I2C.h>
#include "WifiConnector.h"
#include "SerialMessageTransfer.h"
#include "WeatherDataRecord.h"
#include "WeatherDataPool.h"
#include "Timestamp.h"

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

            Timestamp timestamp(receivedRecord.Timestamp);
            Serial.println("Last record timestamp parsed: " + timestamp.getTimeString() + " " + timestamp.getDateString());
        }
        else
        {
            Serial.println("Invalid record: " + receivedRecord.toJSON());
        }
    }

    delay(5000);
}
