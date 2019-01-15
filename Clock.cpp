#include "Clock.h"
#include "GraphicContext.h"

#define TONE_PIN 5

extern GraphicContext* GC;


void Clock::display() {
  GC->clear();
  GC->text(13, 0, h < 10 ? (String("0") + h) : String(h), RIGHT);
  GC->text(19, 0, m < 10 ? (String("0") + m) : String(m), LEFT);
  GC->text(14, 0, ":");
}


bool Clock::run() {
  static unsigned long int lastTimeMs = millis();
  unsigned long int now = millis();

  if ((now - lastTimeMs) >= 60 * 1000L) {
    lastTimeMs = now;
    
    m++;
    if (m > 59) {
      m = 0;
      h++;
      if (h > 23) {
        h = 0;
      }
    }

    checkAlaram();

    return true;
  }

  return false;
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
