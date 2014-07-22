 
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10 // Slave Select/Cable Select
#define RST_PIN 5 // Reset-Ping
#define LED_PIN A2
#define NUM_CATS 1
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

const byte myCats[NUM_CATS][4] = {
  { 0x74, 0x9A, 0xF7, 0x84 }
};

int checkCat(byte rfserial[4]) {
  for (int j=0; j<NUM_CATS; j++) {
    Serial.println("Check...");
    byte matches = 1;
    for (int i=0; i<4; i++) {
      if (rfserial[i] != myCats[j][i])
        matches = 0;
    }
    if (matches == 1)
      return 1; 
  }
  return 0;
}

void openCatDoor() {
  digitalWrite(LED_PIN, HIGH); 
  delay(10000);
  digitalWrite(LED_PIN, LOW); 
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Bitte RFID-Chip annaehern!");
}

void loop() {
  // Neue Karte präsent?
  if ( ! mfrc522.PICC_IsNewCardPresent())
    return;
  // Kann die Seriennummer gelesen werden?
  if ( ! mfrc522.PICC_ReadCardSerial())
    return;
  byte auxId[4] = {0};
  for (int i=0; i<4; i++) {
    auxId[i] = mfrc522.uid.uidByte[i]; 
  } 
  if (checkCat(auxId)) {
    Serial.println("Eigene Katze erkannt"); 
    openCatDoor();
  } else {
    Serial.println("Unbekannte RFID Seriennummer");
  }
  delay(500);
}

