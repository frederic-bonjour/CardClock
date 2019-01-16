#include "Timer.h"
#include "GraphicContext.h"


void Timer::display(GraphicContext* gc) {
  /*GC->clear();
  GC->text(13, 0, h < 10 ? (String("0") + h) : String(h), RIGHT);
  GC->text(19, 0, m < 10 ? (String("0") + m) : String(m), LEFT);
  GC->text(14, 0, ":");*/
}


void Timer::overlay(GraphicContext* gc) {
  byte progress = startedAt ? map(millis(), startedAt, willStopAt, 8, 0) : 0;
  for (byte p=0; p<8; p++) {
    gc->setPixel(31, p, p < progress);
  }
}


bool Timer::run() {
  if (startedAt && millis() >= willStopAt) {
    startedAt = 0;
    // TODO Biiiiiip!
    Serial.println("Timer end!");
  }
}


void Timer::deactivate() {
  startedAt = 0;
}


void Timer::set(byte seconds) {
  duration = seconds * 1000L;
  startedAt = millis();
  Serial.println(startedAt);
  willStopAt = startedAt + duration;
}
