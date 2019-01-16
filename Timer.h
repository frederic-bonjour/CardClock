#ifndef _TIMER_H_

#define _TIMER_H_

#include <Arduino.h>
#include "App.h"

class Timer : public App {

  void checkTimerEnd();
  unsigned long int startedAt;
  unsigned long int willStopAt;
  unsigned long int duration;

  public:
    bool run();
    void display(GraphicContext* gc);
    void overlay(GraphicContext* gc);

    void set(byte seconds);
    void deactivate();
};

#endif
