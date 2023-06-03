#ifndef WEATHERDATAPOOL_H
#define WEATHERDATAPOOL_H

#include <string>
#include <vector>

class WeatherDataPool
{
public:
    void AddRecord(const std::string &recordString);
    std::string GetLastRecord() const;

private:
    std::vector<std::string> records_;
};

#endif
