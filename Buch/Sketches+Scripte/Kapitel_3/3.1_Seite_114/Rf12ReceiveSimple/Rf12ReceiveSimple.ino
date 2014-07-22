
#include <RF12.h>
#include <Ports.h>

const byte network = 100;
const byte myNodeId = 2;
const byte freq = RF12_433MHZ;
const byte RF12_NORMAL_SENDWAIT = 0;

void setup() {
  rf12_initialize(myNodeId, freq, network);
  Serial.begin(9600);
  Serial.println("Empfangsbereit!");
}

void loop() {
  if (rf12_recvDone() && rf12_crc == 0 && (rf12_hdr & RF12_HDR_CTL) == 0) {
    Serial.println("Empfangen!"); 
    char *payload = (char*)rf12_data;
    for (int i=0; i<11; i++) { Serial.print(payload[i]); }
    Serial.println(); 
  }
}

