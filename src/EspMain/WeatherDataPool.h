#ifndef WEATHER_DATA_POOL_H
#define WEATHER_DATA_POOL_H

#include <Arduino.h>
#include <vector>
#include "WeatherDataRecord.h"

class WeatherDataPool
{
public:
    static void AddRecord(const WeatherDataRecord &record);
    static size_t GetRecordsCount();
    static WeatherDataRecord GetRecordByIndex(size_t index);
    static WeatherDataRecord GetLastRecord();
    static std::vector<WeatherDataRecord> GetLastRecords(size_t count);
    static std::vector<WeatherDataRecord> GetAllRecords();
    static void PrintAllRecords();

private:
    static const size_t MAX_RECORDS = 10000;
    static std::vector<String> recordsBinaries; // Store compressed records as bytes
};

#endif // WEATHER_DATA_POOL_H
