#ifndef _CLOCK_H_

#define _CLOCK_H_

#include <Arduino.h>
#include "App.h"

class Clock : public App {

  byte h = 16;
  byte m = 58;

  public:
    bool run();
    void display();
};

#endif
