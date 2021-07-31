#include "ButtonHandler.h"
#include <Arduino.h>
#include "MainsClock.h"
#include "SegDisplay.h"
#include "enums.h"

ButtonHandler::ButtonHandler(MainsClock* clockObject, SegDisplay* displayObject, uint8_t blinkCounter)
{
    clock = clockObject;
    counter = blinkCounter;
    display = displayObject;
}

void ButtonHandler::initButtons(uint8_t modeBut, uint8_t minusBut, uint8_t plusBut, uint8_t alarmBut)
{
    buttons[0] = modeBut;
    buttons[1] = minusBut;
    buttons[2] = plusBut;
    buttons[3] = alarmBut;
}

void ButtonHandler::plusPress()
{
    // Serial.println("plus press");

    switch (clock->getState())
    {
        case clockMode:
            break;
        case alarmMode:
            break;
        case setMode:
            switch(display->getCursor()){
                case 0:
                    clock->increaseHour(1, timeSetting);
                    break;
                case 1:
                    clock->increaseMinute(1, timeSetting);
                    break;
                case 2:
                    clock->increaseSecond(1, timeSetting);
                    break;
            }
            break;
        case alarmSetMode:
            switch(display->getCursor()){
                case 0:
                    clock->increaseHour(1, alarmSetting);
                    break;
                case 1:
                    clock->increaseMinute(1, alarmSetting);
                    break;
            }
            break;
    }
}

void ButtonHandler::minusPress()
{
    // Serial.println("minus press");

    switch (clock->getState())
    {
        case clockMode:
            break;
        case alarmMode:
            break;
        case setMode:
            switch(display->getCursor()){
                case 0:
                    clock->increaseHour(-1, timeSetting);
                    break;
                case 1:
                    clock->increaseMinute(-1, timeSetting);
                    break;
                case 2:
                    clock->increaseSecond(-1, timeSetting);
                    break;
            }
            break;
        case alarmSetMode:
            switch(display->getCursor()){
                case 0:
                    clock->increaseHour(-1, alarmSetting);
                    break;
                case 1:
                    clock->increaseMinute(-1, alarmSetting);
                    break;
            }
            break;
    }
}

void ButtonHandler::modePress()
{
    // Serial.println("mode press");
    switch (clock->getState())
    {
        case clockMode:
            clock->setState(setMode);
            break;
        case setMode:            
            clock->setState(alarmMode);
            counter = 0;
            break;
        case alarmMode:
            clock->setState(alarmSetMode);
            break;
        case alarmSetMode:
            clock->setState(clockMode);
            break;
    }
}

void ButtonHandler::alarmPress()
{
    // Serial.println("alarm press");
    switch (clock->getState())
    {
        case clockMode:
            clock->setState(alarmMode);
            break;
        case alarmMode:
            clock->setState(clockMode);
            break;
        case setMode:
            display->moveCursor();
            break;
        case alarmSetMode:
            break;
    }
}
void ButtonHandler::pressButton(uint8_t button)
{    
  // BUTTON HANDLING ROUTINE
  switch((buttonFlag) button) 
  {
    case modeFlag:
      modePress();
      break;
    case minusFlag:
      minusPress();
      break;
    case plusFlag:
      plusPress();
      break;
    case alarmFlag:
      alarmPress();
      break;
    default:
      break;
  };
}

void ButtonHandler::updateButtons() {
    for (uint8_t i = 0; i < 4; i++)
    {
        uint8_t btnState;
        switch (i)
        {
        case 0:
        case 1:
            btnState = (PIND & (1 << buttons[i])) >> buttons[i];
            break;
        case 2: 
            btnState = (PINB & (1 << buttons[i])) >> buttons[i];
            break;
        case 3: 
            btnState = (PINC & (1 << buttons[i])) >> buttons[i];
            break;
        default:
            break;
        }
        // Serial.print("\nBUTTON: ");
        // Serial.print(i);
        // Serial.print("\n");
        // Serial.println(btnState);

        uint32_t timeStamp = millis();
        if(btnState != lastState[i]){
            if(lastState[i] == LOW
            && timeStamp - lastChange[i] > DEBOUNCE_TIME
            && timeStamp - lastChange[i] < LONGPRESS_TIME) {
                lastState[i] = btnState;
                pressed[i] = false;
/*                 Serial.print("\nBUTTON: ");
                Serial.print(i);
                Serial.println(" RELEASED!"); */
                pressButton(i);
                lastChange[i] = millis();
            }
            if(lastState[i] == LOW
            && timeStamp - lastChange[i] > LONGPRESS_TIME) {
                pressed[i] = false;
                longpressed[i] = false;
                lastState[i] = btnState;
                lastChange[i] = millis();
/*                 Serial.print("\nBUTTON: ");
                Serial.print(i);
                Serial.println(" RELEASED!"); */
            }
            if(lastState[i] == HIGH
            && timeStamp - lastChange[i] > DEBOUNCE_TIME) {
                pressed[i] = true;
                lastState[i] = LOW;
                lastChange[i] = millis();
/*                 Serial.print("\nBUTTON: ");
                Serial.print(i);
                Serial.println(" PRESSED!"); */
            }
        }
        if(btnState == lastState[i] 
        && pressed[i] == true
        && longpressed[i] == false
        && timeStamp - lastChange[i] > LONGPRESS_TIME) {
            longpressed[i] = true;
            longpressTimer = millis();
            pressButton(i);
/*             Serial.print("\nBUTTON: ");
            Serial.print(i);
            Serial.println(" LONG PRESSED!"); */
        }
        if(longpressed[i] && btnState == LOW
        && timeStamp - longpressTimer > 125) {
            pressButton(i);
            longpressTimer = millis();
/*             Serial.print("\nBUTTON: ");
            Serial.print(i);
            Serial.println(" HELD!"); */
        }
    }
}