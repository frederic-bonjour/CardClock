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


App* currentApp;

// Apps
Clock clock;


/**
 * Setup hardware and initial state.
 */
void setup() {
  Serial.begin(9600);
  
  GC = new GraphicContext(32, 8);

  SPI.begin();        // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522
  mfrc522.PCD_DumpVersionToSerial();

  currentApp = &clock;
  currentApp->display();
}


void applyBadge(String action) {

  // ALARM
  
  if (action.startsWith("alarm:")) {
    String time = action.substring(6);
    int p = time.indexOf("h");
    if (p > -1) {
      clock.setAlarm(
        time.substring(0, p).toInt(),
        time.substring(p + 1).toInt()
      );
    }
  }
  
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

  // Clock App always runs in background, even if it does not display.
  if (currentApp != &clock) {
    clock.run();
  }
  
  if (currentApp->run()) {
    currentApp->display();
  } 
}
