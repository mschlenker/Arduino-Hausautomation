
#include <RF12.h>
#include <Ports.h>

const byte network = 100;
const byte myNodeId = 1;
const byte freq = RF12_433MHZ;
const byte RF12_NORMAL_SENDWAIT = 0;
const int payloadSize = 11;
char payload[] = "Hallo Welt!";

void setup() {
  rf12_initialize(myNodeId, freq, network);
  Serial.begin(9600);
  Serial.println("Sendebereit!");
}

void loop() {
  while (!rf12_canSend()) { 
    Serial.println("Warte auf Modul!");
    rf12_recvDone();
  }
  Serial.println("Sende...");
  rf12_sendStart(rf12_hdr, payload, payloadSize); 
  Serial.println("Warte...");
  rf12_sendWait(RF12_NORMAL_SENDWAIT); 
  delay(2000);
}
