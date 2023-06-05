#include <Arduino.h>
#include "virtuabotixRTC.h"
#include "Time.h"

Time::Time(uint8_t clc_pin, uint8_t dat_pin, uint8_t rst_pin) : rtc(virtuabotixRTC(clc_pin, dat_pin, rst_pin))
{
}

// seconds, minutes, hours, day of the week, day of the month, month, year
void Time::SetTime(int s, int m, int h, int dw, int dm, int mn, int y)
{
    this->rtc.setDS1302Time(s, m, h, dw, dm, m, y);
}

String Time::GetCurrentTimeString()
{
    this->rtc.updateTime();
    String result = String(rtc.dayofmonth) + "/" + String(rtc.month) + "/" + String(rtc.year);
    return result;
}

String Time::GetCurrentDateString()
{
    this->rtc.updateTime();
    String result = String(rtc.hours) + ":" + String(rtc.minutes) + ":" + String(rtc.seconds);
    return result;
}

String Time::GetLogString()
{
    return this->GetCurrentTimeString() + " " + this->GetCurrentDateString();
}

unsigned long Time::GetCurrentTimeStamp()
{
    this->rtc.updateTime();
    unsigned long timeStamp = 0;

    // Calculate the timestamp manually
    timeStamp += rtc.seconds;
    timeStamp += rtc.minutes * 60;
    timeStamp += rtc.hours * 3600;
    timeStamp += (rtc.dayofmonth - 1) * 86400;
    timeStamp += (rtc.month - 1) * 2678400;    // Assuming 30 days per month
    timeStamp += (rtc.year - 1970) * 31536000; // Assuming non-leap years

    // Adjust for leap years
    unsigned int leapYears = (rtc.year - 1969) / 4;
    if (rtc.year % 4 == 0 && rtc.month <= 2)
        leapYears--;
    timeStamp += leapYears * 86400;

    return timeStamp;
}