#include "Clock.h"
#include "GraphicContext.h"

#define TONE_PIN 5

// --- RTC  ------------------------------

#include <Wire.h>
#include "PCF85063TP.h"

PCD85063TP clock;


void Clock::setup() {
  clock.begin();
  clock.calibratBySeconds(0, -0.000041);
}


void Clock::display(GraphicContext* gc) {
  gc->clear();
  gc->text(13, 0, String(h), RIGHT);
  gc->text(19, 0, m < 10 ? (String("0") + m) : String(m), LEFT);
  gc->text(14, 0, ":");
}


void Clock::overlay(GraphicContext* gc) {
  gc->setPixel(0, 0, alarmActivated);
}


bool Clock::run() {
  clock.getTime();

  bool changed = false;
  if (clock.minute != m) {
    changed = true;
    m = clock.minute;
  }
  if (clock.hour != h) {
    changed = true;
    h = clock.hour;
  }

  if (changed) {
    checkAlaram();
  }

  return changed;
}


void Clock::checkAlaram() {
  if (alarmH == h && alarmM == m) {
    tone(TONE_PIN, 500); // FIME
  }
}


void Clock::deactivateAlarm() {
  alarmActivated = false;
}


void Clock::stopAlarm() {
  noTone(TONE_PIN);
}


void Clock::activateAlarm() {
  alarmActivated = true;
}


void Clock::setAlarm(byte ah, byte am) {
  alarmH = ah;
  alarmM = am;
  activateAlarm();
}
