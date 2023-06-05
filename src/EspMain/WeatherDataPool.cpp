#include "WeatherDataPool.h"
#include "WeatherDataRecord.h"

std::vector<String> WeatherDataPool::recordsBinaries;

void WeatherDataPool::AddRecord(const WeatherDataRecord &record)
{
    if (recordsBinaries.size() >= MAX_RECORDS)
    {
        recordsBinaries.erase(recordsBinaries.begin());
    }

    String recordBinary = record.toCompressed();

    Serial.println("WeatherDataPool::AddRecord() -> Binary: " + recordBinary);

    recordsBinaries.push_back(recordBinary);
}

size_t WeatherDataPool::GetRecordsCount()
{
    return recordsBinaries.size();
}

WeatherDataRecord WeatherDataPool::GetRecordByIndex(size_t index)
{
    WeatherDataRecord record;

    if (index > recordsBinaries.size())
    {
        Serial.println("WeatherDataPool::GetRecordByIndex() -> No records available");
        return record;
    }

    String recordBinary = recordsBinaries.at(index);
    record.fromCompressed(recordBinary);

    return record;
}

WeatherDataRecord WeatherDataPool::GetLastRecord()
{
    return GetRecordByIndex(recordsBinaries.size() - 1);
}

std::vector<WeatherDataRecord> WeatherDataPool::GetLastRecords(size_t count)
{
    Serial.println("WeatherDataPool::GetLastRecords() -> count: " + String(count));

    size_t c = std::min(count, recordsBinaries.size());
    std::vector<WeatherDataRecord> result{};

    Serial.println("WeatherDataPool::GetLastRecords() -> c: " + String(c));

    for (size_t i = 1; i <= c; i++)
    {
        result.push_back(GetRecordByIndex(recordsBinaries.size() - i));
    }

    return result;
}

std::vector<WeatherDataRecord> WeatherDataPool::GetAllRecords()
{
    return GetLastRecords(recordsBinaries.size());
}

void WeatherDataPool::PrintAllRecords()
{
    std::vector<WeatherDataRecord> allRecords = GetAllRecords();

    Serial.println("=== All records ===");
    Serial.println("TotalCount: " + String(recordsBinaries.size()));

    for (const auto &record : allRecords)
    {
        Serial.print("Timestamp: ");
        Serial.println(record.Timestamp);
        Serial.print("Temperature: ");
        Serial.print(record.Temperature);
        Serial.print("TemperatureDht: ");
        Serial.print(record.TemperatureDht);
        Serial.print("Humidity: ");
        Serial.print(record.Humidity);
    }
    Serial.println("========================");
}
