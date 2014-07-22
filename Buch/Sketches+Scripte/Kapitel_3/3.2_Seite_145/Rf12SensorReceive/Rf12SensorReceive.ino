#include <RF12.h>
#include <Ports.h>
#define MSG_SIZE 2
 
// RFM12 stuff
uint8_t payload[MSG_SIZE]; 
const byte network = 100;
const byte myNodeId = 2;
const byte freq = RF12_433MHZ;
const byte RF12_NORMAL_SENDWAIT = 0;
   
void setup() {
  rf12_initialize(myNodeId, freq, network);
  Serial.begin(9600);
  while(!Serial){;} 
  Serial.println("Empfangsbereit...");
}

void loop() {
  if (rf12_recvDone() && rf12_len == MSG_SIZE  && rf12_crc == 0) {
    if ((rf12_hdr & B11100000) == 0) {
      char* auxpayload = (char*)rf12_data;
      for (int i=0; i<MSG_SIZE; i++) {
        payload[i] = auxpayload[i];
      }
      unsigned int val = payload[0] << 8;
      val |= payload[1];
      Serial.print("Received: ");
      Serial.println(val);
      Serial.print("Sender ID: ");
      Serial.println((int)rf12_hdr);
    }
  }
}


