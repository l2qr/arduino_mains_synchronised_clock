#include <Arduino.h>
#include "MainsClock.h"
#include "SegDisplay.h"
#include "enums.h"

#ifndef BUTTONHANDLER_H
#define BUTTONHANDLER_H

class ButtonHandler
{
    public:
        ButtonHandler(MainsClock* clockObject, SegDisplay* displayObject, uint8_t blinkCounter);
        void initButtons(uint8_t modeButton, uint8_t minusButton, uint8_t plusButton, uint8_t alarmButton);
        void plusPress();
        void minusPress();
        void modePress();
        void alarmPress();
        void pressButton(uint8_t button);
        void updateButtons();
        MainsClock *clock;
        uint8_t counter;
        SegDisplay *display;
        

    private:
        uint8_t DEBOUNCE_TIME = 50;
        uint16_t LONGPRESS_TIME = 300;
        uint8_t buttons[4]; // 0: mode, 1: minus, 2: plus, 3: alarm
        uint8_t lastState[4]; // 0: mode, 1: minus, 2: plus, 3: alarm
        uint32_t lastChange[4] = {0, 0, 0, 0};
        boolean pressed[4];
        boolean longpressed[4];
        uint32_t longpressTimer = 0;
};

#endif