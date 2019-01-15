#ifndef _CLOCK_H_

#define _CLOCK_H_

#include <Arduino.h>
#include "App.h"

class Clock : public App {

  byte h = 16;
  byte m = 58;

  byte alarmH = 17;
  byte alarmM = 0;
  bool alarmActivated = false;

  void checkAlaram();

  public:
    bool run();
    void display();

    void activateAlarm();
    void setAlarm(byte ah, byte am);
    void deactivateAlarm();
    void stopAlarm();
};

#endif
