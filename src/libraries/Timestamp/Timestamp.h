#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <Arduino.h>

class Timestamp
{
public:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

    Timestamp(int year, int month, int day, int hour, int minute, int second);
    Timestamp(unsigned long timestamp);

    // Check if a year is a leap year
    static bool isLeapYear(int year);

    unsigned long getTimestampFromComponents();
    void getComponentsFromTimestamp(unsigned long timestamp);

    String getDateString();
    String getTimeString();
    String getString();
};

#endif