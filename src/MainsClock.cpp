#include "MainsClock.h"
#include <Arduino.h>
#include "enums.h"

MainsClock::MainsClock()
{
    state = clockState::setMode;
    time[0] = 23;
    time[1] = 59;
    time[2] = 59;
    alarmTime[0] = 23;
    alarmTime[1] = 59;
    alarmTime[2] = 59;
    milliseconds = 0;
}

void MainsClock::increaseHour(int h, uint8_t timeOrAlarm){
    if(timeOrAlarm == 0)
    {
        if(h < 0){
            if(time[0] == 0)
                time[0] = 23;
            else
                time[0] += h;
        }else{
            time[0] += h;
        }
        if(time[0] >= 24){
            time[0] = 0;
        }
    }
    if(timeOrAlarm == 1)
    {
        if(h < 0){
            if(alarmTime[0] == 0)
                alarmTime[0] = 23;
            else
                alarmTime[0] += h;
        }else{
            alarmTime[0] += h;
        }
        if(alarmTime[0] >= 24){
            alarmTime[0] = 0;
        }
    }
}

void MainsClock::increaseMinute(int m, uint8_t timeOrAlarm){
    if(timeOrAlarm == 0){
        if(m < 0){
            if(time[1] == 0){
                time[1] = 59;
                increaseHour(-1, timeSetting);
            }else{
                time[1] += m;
            }
        }else{
            time[1] += m;
        }
        if(time[1] >= 60){
            time[1] = 0;
            increaseHour(1, timeSetting);
        }
    }
    if(timeOrAlarm == 1){
        if(m < 0){
            if(alarmTime[1] == 0){

                alarmTime[1] = 59;
                increaseHour(-1, alarmSetting);
            }else{
                alarmTime[1] += m;
            }
        }else{
            alarmTime[1] += m;
        }
        if(alarmTime[1] >= 60){
            alarmTime[1] = 0;
            increaseHour(1, alarmSetting);
        }
    }
}

void MainsClock::increaseSecond(int s, uint8_t timeOrAlarm){
    if(timeOrAlarm == 0){
        if(s < 0){
            if(time[2] == 0){
                time[2] = 59;
                increaseMinute(-1, timeSetting);
            }else{
                time[2] += s;
            }
        }else{
            time[2] += s;
        }
        if(time[2] >= 60){
            time[2] = 0;
            increaseMinute(1, timeSetting);
        }
    }
    if(timeOrAlarm == 1){
        if(s < 0){
            if(alarmTime[2] == 0){
                alarmTime[2] = 59;
                increaseMinute(-1, alarmSetting);
            }else{
                alarmTime[2] += s;
            }
        }else{
            alarmTime[2] += s;
            increaseMinute(1, alarmSetting);
        }
        if(alarmTime[2] >= 60){
            alarmTime[2] = 0;
        }
    }
}

void MainsClock::increaseMillis() {
    if(state == clockMode || state == alarmMode) {
        milliseconds += 20;
    }

}

void MainsClock::updateTime() {
    if(milliseconds>=1000)
    {
        milliseconds = milliseconds%1000;
        increaseSecond(1, timeSetting);
    };
}

void MainsClock::printTime(){
    Serial.print("Time now:\t");
    Serial.print(time[0]);
    Serial.print(":");
    Serial.print(time[1]);
    Serial.print(":");
    Serial.println(time[2]);
}

clockState MainsClock::getState() {
    return state;
}

void MainsClock::setState(clockState newState) {
    state = newState;
}

uint8_t * MainsClock::getTime() {
    return time;
}

uint16_t MainsClock::getMillis() {
    return milliseconds;
}

uint8_t * MainsClock::getAlarm() {
    return alarmTime;
}