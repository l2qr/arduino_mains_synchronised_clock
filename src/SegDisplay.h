#include <Arduino.h>
#include <LedControl.h>
#include "enums.h"
#include "MainsClock.h"

#ifndef SEGDISPLAY_H
#define SEGDISPLAY_H

class SegDisplay
{ 
    public:
        SegDisplay(LedControl* rlc, MainsClock* clockObject);
        SegDisplay() = default;
        void hour(uint8_t newHour);
        void minute(uint8_t newMinute);
        void sec(uint8_t newMinute);
        void milS(uint8_t newMilS);
        void clear(uint8_t device);
        void updateDisplay(bool blink);
        uint8_t getCursor();
        void moveCursor();
    private:
        LedControl *lc;
        uint8_t cursor;
        MainsClock *clock;
};

#endif