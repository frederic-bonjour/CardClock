// --- RFID ------------------------------

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 13
#define SS_PIN  8

MFRC522 mfrc522(SS_PIN, RST_PIN);

char buffer[20];
byte bufferSize = 18;
byte blockAddr    = 4;
byte trailerBlock = 7;
MFRC522::StatusCode status;

// ---------------------------------------

#include "GraphicContext.h"
GraphicContext *GC;

#include "App.h"
#include "Clock.h"
#include "Timer.h"


App* currentApp;

// Apps
Clock clockApp;
Timer timerApp;

#define APPS_COUNT 2
App* apps[APPS_COUNT] = { &clockApp, &timerApp };


/**
 * Setup hardware and initial state.
 */
void setup() {
  Serial.begin(9600);

  // Dsplay.
  GC = new GraphicContext(32, 8);

  // RFID.
  SPI.begin();        // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522
  mfrc522.PCD_DumpVersionToSerial();

  // Apps.
  for (byte a=0; a<APPS_COUNT; a++) {
    apps[a]->setup();
  }
  currentApp = &clockApp;
  currentApp->display(GC);

  //timerApp.set(20);
}


/**
 * Applies the given action (badge ID).
 */
void applyBadge(String action) {

  if (action.startsWith("ALM:")) {
    
    // Alarm
    
    String param = action.substring(4);
    if (param == "activate") {
      clockApp.activateAlarm();
    } else if (param == "deactivate") {
      clockApp.deactivateAlarm();
    } else if (param == "view") {
      // TODO
    } else {
      int p = param.indexOf(":");
      if (p > -1) {
        clockApp.setAlarm(
          param.substring(0, p).toInt(),
          param.substring(p + 1).toInt()
        );
      }
    }
    
  } else if (action.startsWith("INT:")) {

    // Intensity
    
    String param = action.substring(4);
    if (param == "min") {
      GC->setIntensity(Min);
    } else if (param == "low") {
      GC->setIntensity(Low);
    } else if (param == "medium") {
      GC->setIntensity(Medium);
    } else if (param == "high") {
      GC->setIntensity(High);
    } else if (param == "max") {
      GC->setIntensity(Max);
    }
    
  } else if (action.startsWith("TMR:")) {

    // Timer
    
    byte timerMinutes = action.substring(4).toInt();
    
  }

  // TODO: timer, dessins, ...  
}


/**
 * Main loop.
 */
void loop() {

  // Check RFID
  if ( mfrc522.PICC_IsNewCardPresent() ) {
    if ( mfrc522.PICC_ReadCardSerial() ) {
      status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(blockAddr, (byte*)buffer, &bufferSize);
      buffer[16] = '\0';
      Serial.print("RFID: ");
      Serial.println(buffer);
      applyBadge(String(buffer));
    }
  }

  // Run ALL apps
  for (byte a=0; a<APPS_COUNT; a++) {
    bool needsDisplay = apps[a]->run();
    // If current app requests a display update, call its display() method.
    if (apps[a] == currentApp && needsDisplay) {
      apps[a]->display(GC);
    }
  }
  // Ask ALL apps to display their overlay info.
  for (byte a=0; a<APPS_COUNT; a++) {
    apps[a]->overlay(GC);
  }
}
