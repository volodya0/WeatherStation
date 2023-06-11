#include "Timestamp.h"
#include <Arduino.h>

const int SECONDS_PER_MINUTE = 60;
const int MINUTES_PER_HOUR = 60;
const int HOURS_PER_DAY = 24;
const int UNIX_YEAR_START = 1970;

const int MONTH_LENGTHS[2][12] = {
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, // Non-leap year
    {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}  // Leap year
};

Timestamp::Timestamp(int year, int month, int day, int hour, int minute, int second)
    : year(year), month(month), day(day), hour(hour), minute(minute), second(second)
{
}

Timestamp::Timestamp(unsigned long timestamp)
{
    getComponentsFromTimestamp(timestamp);
}

// Check if a year is a leap year
bool Timestamp::isLeapYear(int year)
{
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

unsigned long Timestamp::getTimestampFromComponents()
{
    unsigned long totalSeconds = second;
    totalSeconds += minute * (unsigned long)SECONDS_PER_MINUTE;
    totalSeconds += hour * (unsigned long)MINUTES_PER_HOUR * SECONDS_PER_MINUTE;
    totalSeconds += (day - 1) * (unsigned long)HOURS_PER_DAY * MINUTES_PER_HOUR * SECONDS_PER_MINUTE;

    for (int y = UNIX_YEAR_START; y < year; ++y)
    {
        totalSeconds += (isLeapYear(y) ? 366 : 365) * (unsigned long)HOURS_PER_DAY * MINUTES_PER_HOUR * SECONDS_PER_MINUTE;
    }

    for (int m = 0; m < month - 1; ++m)
    {
        totalSeconds += MONTH_LENGTHS[isLeapYear(year)][m] * (unsigned long)HOURS_PER_DAY * MINUTES_PER_HOUR * SECONDS_PER_MINUTE;
    }

    return totalSeconds;
}

void Timestamp::getComponentsFromTimestamp(unsigned long timestamp)
{
    second = timestamp % SECONDS_PER_MINUTE;
    timestamp /= SECONDS_PER_MINUTE;
    minute = timestamp % MINUTES_PER_HOUR;
    timestamp /= MINUTES_PER_HOUR;
    hour = timestamp % HOURS_PER_DAY;
    timestamp /= HOURS_PER_DAY;
    for (year = UNIX_YEAR_START; timestamp >= (isLeapYear(year) ? 366 : 365); ++year)
    {
        timestamp -= isLeapYear(year) ? 366 : 365;
    }
    for (month = 0; timestamp >= MONTH_LENGTHS[isLeapYear(year)][month]; ++month)
    {
        timestamp -= MONTH_LENGTHS[isLeapYear(year)][month];
    }
    ++month;
    day = timestamp + 1;
}

String Timestamp::getDateString()
{
    String result = String(day) + "/" + String(month) + "/" + String(year);
    return result;
}

String Timestamp::getTimeString()
{
    String result = String(hour) + ":" + String(minute) + ":" + String(second);
    return result;
}

String Timestamp::getString()
{
    return getDateString() + ' ' + getTimeString();
}
