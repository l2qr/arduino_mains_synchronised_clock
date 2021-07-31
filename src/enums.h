#ifndef ENUMS_H
#define ENUMS_H

enum clockState
{
    clockMode, 
    alarmMode, 
    setMode, 
    alarmSetMode
};

enum buttonFlag{
  modeFlag,
  minusFlag,
  plusFlag,
  alarmFlag
};

enum timeOrAlarm{
  timeSetting,
  alarmSetting
};

#endif