#include "WeatherDataPool.h"

void WeatherDataPool::AddRecord(const std::string &recordString) {
    records_.push_back(recordString);
}

std::string WeatherDataPool::GetLastRecord() const {
    if (!records_.empty()) {
        return records_.back();
    } else {
        return "";
    }
}
