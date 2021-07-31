#include "SegDisplay.h"
#include <Arduino.h>
#include <LedControl.h>
#include "enums.h"
#include "MainsClock.h"

SegDisplay::SegDisplay(LedControl* rlc, MainsClock* clockObject)
{
    lc = rlc;
    clock = clockObject;
    cursor = 2;
}

void SegDisplay::hour(uint8_t newHour){
    
    if(newHour/10 == 0){
        lc->setRow(0,6,0);
    }else{
        lc->setDigit(0,6,newHour/10,false);
    }
    lc->setDigit(0,5,newHour%10,false);
}

void SegDisplay::minute(uint8_t newMinute){
    lc->setDigit(0,4,newMinute/10,false);
    lc->setDigit(0,3,newMinute%10,false);
}

void SegDisplay::sec(uint8_t newSecond){
    lc->setDigit(0,2,newSecond/10,false);
    lc->setDigit(0,1,newSecond%10,false);
}

void SegDisplay::milS(uint8_t newMilS){
    lc->setDigit(0,0,newMilS/100,false);
}

void SegDisplay::clear(uint8_t device){
    lc->clearDisplay(device);
}

void SegDisplay::updateDisplay(bool blink)
{
    if(clock->getState() == setMode || clock->getState() == alarmSetMode){
        if(blink){
            hour(clock->getTime()[0]);
            minute(clock->getTime()[1]);
            sec(clock->getTime()[2]);
        }else{
            switch(cursor){
                case 0:
                    lc->setRow(0,6,0);
                    lc->setRow(0,5,0);
                    minute(clock->getTime()[1]);
                    sec(clock->getTime()[2]);
                    break;
                case 1:
                    hour(clock->getTime()[0]);
                    lc->setRow(0,4,0);
                    lc->setRow(0,3,0);
                    sec(clock->getTime()[2]);
                    break;
                case 2:
                    hour(clock->getTime()[0]);
                    minute(clock->getTime()[1]);
                    lc->setRow(0,2,0);
                    lc->setRow(0,1,0);
                    break;
            }      
        } 
    }else{
      hour(clock->getTime()[0]);
      minute(clock->getTime()[1]);
      sec(clock->getTime()[2]);
      milS(clock->getMillis());
  }
}

uint8_t SegDisplay::getCursor() {
    return cursor;
}

void SegDisplay::moveCursor() {
    if(cursor==0)
        cursor = 2;
    else
        cursor = cursor - 1;
}