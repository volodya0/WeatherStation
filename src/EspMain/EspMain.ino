#include "Config.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "WifiConnector.h"
#include "MyServer.h"
#include "SerialMessageTransfer.h"
#include "WeatherDataRecord.h"
#include "WeatherDataPool.h"
#include "Timestamp.h"

void setup()
{
    Serial.begin(SERIAL_COMMUNICATION_PORT);

    WifiConnector::Connect();

    MyServer::InitEndpoints();
}

int i = 1;
void loop()
{
    SerialMessageTransfer::CheckNewMessages(Serial.readString());

    if (SerialMessageTransfer::GetNewMessagesCount() > 0)
    {
        String lastMessage = SerialMessageTransfer::GetLastMessage(true);

        WeatherDataRecord receivedRecord;
        if (receivedRecord.fromJSON(lastMessage))
        {
            WeatherDataPool::AddRecord(receivedRecord);
        }
    }

    delay(10);

    WifiConnector::EnsureConnection();
    MyServer::CheckAndHandleRequests();

    delay(1000);
}
