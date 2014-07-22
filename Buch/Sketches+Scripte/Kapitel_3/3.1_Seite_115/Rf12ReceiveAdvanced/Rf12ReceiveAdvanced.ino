
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
  boolean forMe = false;
  if (rf12_recvDone() && rf12_crc == 0 && (rf12_hdr & RF12_HDR_CTL) == 0) {
    Serial.println("Empfange etwas, das kein ACK ist...");
    Serial.println(rf12_hdr, BIN); 
    if ( (rf12_hdr & RF12_HDR_DST) ==  0) {
      Serial.println("Nachricht ist Broadcast!"); 
      forMe = true;
    } else {
      byte targetNode = rf12_hdr & RF12_HDR_MASK;
      if (targetNode == myNodeId) {
        Serial.println("Ich bin das Ziel!");
        forMe = true;
      } else {
         Serial.print("Jemand anderes ist das Ziel!"); 
         Serial.println(targetNode); 
      }
    }  
    if (forMe == true) {
      char *payload = (char*)rf12_data;
      for (int i=0; i<11; i++) { Serial.print(payload[i]); }
      Serial.println();
    }
  }
}

