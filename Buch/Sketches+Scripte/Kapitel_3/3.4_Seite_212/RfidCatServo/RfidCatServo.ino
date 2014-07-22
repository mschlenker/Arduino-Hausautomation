 
#include <SPI.h>
#include <MFRC522.h>
// #include <SoftwareServo.h> 

#define SS_PIN 10 // Slave Select/Cable Select
#define RST_PIN 5 // Reset-Ping
#define LED_PIN 8
#define SERVO_PIN 2 // Sollte nicht PWM Pin sein
#define NUM_CATS 2
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.
// SoftwareServo lockServo;
int servoPos = 0;

const byte myCats[NUM_CATS][4] = {
  { 0x74, 0x9A, 0xF7, 0x84 },
  { 0xC0, 0x01, 0xCA, 0x75 }
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

void servoNinety(int incs) {
  for (int i=0; i<incs; i++) {
    digitalWrite(SERVO_PIN,HIGH);
    delayMicroseconds(2050);
    digitalWrite(SERVO_PIN, LOW);
    delayMicroseconds(17820);
  } 
}

void servoZero(int incs) {
  for (int i=0; i<incs; i++) { 
    digitalWrite(SERVO_PIN,HIGH);
    delayMicroseconds(1500);
    digitalWrite(SERVO_PIN, LOW);
    delayMicroseconds(18470);
  } 
}

void openCatDoor() {
  digitalWrite(LED_PIN, HIGH); 
  servoZero(30);
  delay(5000); 
  servoNinety(30);
  digitalWrite(LED_PIN, LOW); 
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(SERVO_PIN, OUTPUT);
  servoNinety(30);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.begin(9600);
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

