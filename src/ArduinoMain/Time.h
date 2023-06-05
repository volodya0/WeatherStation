#ifndef TIME_H
#define TIME_H

#include <Arduino.h>
#include "virtuabotixRTC.h"

class Time
{
public:
    Time(uint8_t clc_pin, uint8_t dat_pin, uint8_t rst_pin);
    void SetTime(int s, int m, int h, int dw, int dm, int mn, int y);
    String GetCurrentTimeString();
    String GetCurrentDateString();
    String GetLogString();
    unsigned long GetCurrentTimeStamp();

private:
    virtuabotixRTC rtc;
};

#endif