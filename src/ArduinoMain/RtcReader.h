#ifndef RTCREADER_H
#define RTCREADER_H

#include <Arduino.h>
#include "virtuabotixRTC.h"
#include "Timestamp.h"

class RtcReader
{
public:
    RtcReader(uint8_t clc_pin, uint8_t dat_pin, uint8_t rst_pin);
    void SetTime(int s, int m, int h, int dw, int dm, int mn, int y);
    String GetCurrentTimeString();
    String GetCurrentDateString();
    String GetLogString();
    Timestamp GetCurrentTimeStamp();

private:
    virtuabotixRTC rtc;
};

#endif