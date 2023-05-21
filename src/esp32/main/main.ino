#include <WiFi.h>
#include <HTTPClient.h>
#include "WifiConnector.h"

String testUrl = "https://catfact.ninja/fact";

void setup()
{
    Serial.begin(115200);
    delay(10);

    WifiConnector::Connect();
}

void loop()
{
    WifiConnector::EnsureConnection();

    HTTPClient http;
    http.begin(testUrl.c_str());

    int httpResponseCode = http.GET();
    Serial.print("http.GET()");
    delay(2000);

    if (httpResponseCode > 0)
    {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
    }
    else
    {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    http.end();
}
