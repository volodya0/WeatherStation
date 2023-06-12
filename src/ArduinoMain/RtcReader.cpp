#include <Arduino.h>
#include "virtuabotixRTC.h"
#include "RtcReader.h"
#include "Timestamp.h"

RtcReader::RtcReader(uint8_t clc_pin, uint8_t dat_pin, uint8_t rst_pin) : rtc(virtuabotixRTC(clc_pin, dat_pin, rst_pin))
{
}

// seconds, minutes, hours, day of the week, day of the month, month, year
void RtcReader::SetTime(int s, int m, int h, int dw, int dm, int mn, int y)
{
    this->rtc.setDS1302Time(s, m, h, dw, dm, mn, y);
}

String RtcReader::GetCurrentTimeString()
{
    this->rtc.updateTime();
    String result = String(rtc.dayofmonth) + "/" + String(rtc.month) + "/" + String(rtc.year);
    return result;
}

String RtcReader::GetCurrentDateString()
{
    this->rtc.updateTime();
    String result = String(rtc.hours) + ":" + String(rtc.minutes) + ":" + String(rtc.seconds);
    return result;
}

String RtcReader::GetLogString()
{
    return this->GetCurrentTimeString() + " " + this->GetCurrentDateString();
}

Timestamp RtcReader::GetCurrentTimeStamp()
{
    this->rtc.updateTime();

    // Serial.println("RtcReader::GetCurrentTimeStamp : logString = " + GetLogString());

    Timestamp timestamp(rtc.year, rtc.month, rtc.dayofmonth, rtc.hours, rtc.minutes, rtc.seconds);

    return timestamp;
}