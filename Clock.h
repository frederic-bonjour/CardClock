#ifndef _CLOCK_H_

#define _CLOCK_H_

#include <Arduino.h>
#include "App.h"
#include "GraphicContext.h"


class Clock : public App {

  byte h = 0;
  byte m = 0;

  byte alarmH = 17;
  byte alarmM = 0;
  bool alarmActivated = false;

  void checkAlaram();

  public:
    void setup();
    bool run();
    void display(GraphicContext* gc);
    void overlay(GraphicContext* gc);

    void activateAlarm();
    void setAlarm(byte ah, byte am);
    void deactivateAlarm();
    void stopAlarm();
};

#endif
