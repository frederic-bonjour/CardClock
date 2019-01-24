#ifndef _APP_H_

#define _APP_H_

#include "GraphicContext.h"


class App {
  public:
    virtual bool run() = 0;
    virtual void setup() {};
    virtual void display(GraphicContext* gc) = 0;
    virtual void overlay(GraphicContext* gc) = 0;
};

#endif
