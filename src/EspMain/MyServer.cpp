#include <WiFi.h>
#include <WebServer.h>
#include <Arduino.h>
#include "MyServer.h"
#include "WeatherDataPool.h"
#include "WeatherDataRecord.h"

WebServer MyServer::server(80);

void MyServer::InitEndpoints()
{
    server.on("/", handleRoot);
    server.on("/getcurrentdata", handleGetCurrentData);
    server.on("/getallrecords", handleGetAllRecords);

    server.begin();
}

void MyServer::CheckAndHandleRequests()
{
    server.handleClient();
}

void MyServer::handleRoot()
{
    server.sendHeader("Content-Type", "text/plain");
    server.send(200, "text/plain", "OK");
}

void MyServer::handleGetCurrentData()
{
    WeatherDataRecord lastRecord = WeatherDataPool::GetLastRecord();
    String response = lastRecord.toJSON();

    server.sendHeader("Content-Type", "text/plain");
    server.send(200, "text/plain", response);
}

void MyServer::handleGetAllRecords()
{
    std::vector<WeatherDataRecord> allRecords = WeatherDataPool::GetAllRecords();

    // Convert all records to JSON array
    String jsonArray = "[";
    for (size_t i = 0; i < allRecords.size(); ++i)
    {
        String recordJson = allRecords[i].toJSON();
        jsonArray += recordJson;

        // Add comma between records (except for the last one)
        if (i != allRecords.size() - 1)
        {
            jsonArray += ",";
        }
    }
    jsonArray += "]";

    // Set the response content type
    server.sendHeader("Content-Type", "application/json");

    // Send the response
    server.send(200, "application/json", jsonArray);
}