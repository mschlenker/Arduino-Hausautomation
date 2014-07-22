
#include <RF12.h>
#include <Ports.h>
#define POWER_PIN A0
#define MSG_SIZE 2

const int sensorPin = A2;
const byte network = 100;
const byte myNodeId = 5;
const byte freq = RF12_433MHZ;
const byte RF12_NORMAL_SENDWAIT = 0; 
const unsigned long waitMillis = 3000; // Millisekunden zw. Updates 

unsigned int sVal;
char outdata[MSG_SIZE] = {0};

void produceOutData() {
  digitalWrite(POWER_PIN, HIGH);
  delay(3); 
  sVal = analogRead(sensorPin);
  digitalWrite(POWER_PIN, LOW);
  // Integer in zwei Bytes zerlegen
  outdata[0] = (sVal >> 8) & 0xFF;
  outdata[1] = sVal & 0xFF;
}

void setup() {
  rf12_initialize(myNodeId, freq, network);
  // serielle Ausgabe wird beim Senden 
  // zerstueckelt!
  // Serial.begin(9600);
  pinMode(POWER_PIN, OUTPUT);
  // Serial.println("Sendebereit!");
}

void loop() {
  while (!rf12_canSend()) { 
    // Serial.println("Warte auf Modul!");
    rf12_recvDone();
  }
  produceOutData();
  // CDA-Bits sind je 0 -> Message ist Broadcast 
  // - die folgenden fuenf Bit sind Absender
  byte newHdr = B00011111 & myNodeId;
  rf12_sendStart(newHdr, outdata, MSG_SIZE);
  rf12_sendWait(RF12_NORMAL_SENDWAIT);
  delay(waitMillis);
}

