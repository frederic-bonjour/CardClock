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


/**
 * Setup hardware and initial state.
 */
void setup() {
  Serial.begin(9600);
  
  GC = new GraphicContext(32, 8);

  SPI.begin();        // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522
  mfrc522.PCD_DumpVersionToSerial();

  currentApp = new Clock();
  currentApp->display();
}


/**
 * Main loop.
 */
void loop() {

  // Check RFID
  if ( mfrc522.PICC_IsNewCardPresent() ) {
    if ( mfrc522.PICC_ReadCardSerial() ) {
      status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(blockAddr, (byte*)buffer, &bufferSize);
      buffer[4] = '\0';
      Serial.print("RFID: ");
      Serial.println(buffer);
    }
  }
  
  if (currentApp->run()) {
    currentApp->display();
  } 
}
