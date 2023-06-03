#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "WifiConnector.h"
#include "config.h"

bool WifiConnector::IsConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

void WifiConnector::EnsureConnection()
{
    if (WifiConnector::IsConnected() == false)
    {
        WifiConnector::Connect();
    }
}

void WifiConnector::Connect()
{
    Serial.println();
    Serial.print("[WiFi] Connecting to '");
    Serial.print(ssid);
    Serial.print("' with password '");
    Serial.print(password);
    Serial.print("'");
    Serial.println();

    WiFi.begin(ssid, password);

    int tryDelay = 300;
    int numberOfTries = 30;

    while (true)
    {
        switch (WiFi.status())
        {
        case WL_NO_SSID_AVAIL:
            Serial.println("[WiFi] SSID not found");
            break;
        case WL_CONNECT_FAILED:
            Serial.print("[WiFi] Failed - WiFi not connected! Reason: ");
            return;
            break;
        case WL_CONNECTION_LOST:
            Serial.println("[WiFi] Connection was lost");
            break;
        case WL_SCAN_COMPLETED:
            Serial.println("[WiFi] Scan is completed");
            break;
        case WL_DISCONNECTED:
            Serial.println("[WiFi] WiFi is disconnected");
            break;
        case WL_CONNECTED:
            Serial.println("[WiFi] WiFi is connected!");
            Serial.print("[WiFi] IP address: ");
            Serial.println(WiFi.localIP());
            return;
            break;
        default:
            Serial.print("[WiFi] WiFi Status: ");
            Serial.println(WiFi.status());
            break;
        }
        delay(tryDelay);

        if (numberOfTries <= 0)
        {
            Serial.print("[WiFi] Failed to connect to WiFi!");
            WiFi.disconnect();
            return;
        }
        else
        {
            numberOfTries--;
        }
    }
}
