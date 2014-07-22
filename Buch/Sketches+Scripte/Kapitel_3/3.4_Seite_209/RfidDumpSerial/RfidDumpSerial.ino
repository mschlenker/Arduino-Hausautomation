 
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10 // Slave Select/Cable Select
#define RST_PIN 5 // Reset-Ping
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

void setup() {
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
  Serial.print(mfrc522.uid.uidByte[0], HEX); 
  Serial.print(" ");
  Serial.print(mfrc522.uid.uidByte[1], HEX);
  Serial.print(" ");
  Serial.print(mfrc522.uid.uidByte[2], HEX); 
  Serial.print(" ");
  Serial.println(mfrc522.uid.uidByte[3], HEX);
  delay(1000);
}

