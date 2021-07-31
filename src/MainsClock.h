#include <Arduino.h>
#include "enums.h"

#ifndef MAINSCLOCK_H
#define MAINSCLOCK_H

class MainsClock
{   
    public:
        MainsClock();
        void increaseHour(int h, uint8_t timeOrAlarm);
        void increaseMinute(int m, uint8_t timeOrAlarm);
        void increaseSecond(int s, uint8_t timeOrAlarm);
        void increaseMillis();
        void updateTime();
        void printTime();
        clockState getState();
        void setState(clockState newState);
        uint8_t * getTime();
        uint16_t getMillis();
        uint8_t * getAlarm();


    private:
        clockState state;
        uint8_t time[3];
        uint8_t alarmTime[3];
        uint16_t milliseconds;
};

#endif