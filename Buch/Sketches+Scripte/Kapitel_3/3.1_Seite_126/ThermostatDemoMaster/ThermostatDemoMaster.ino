
#include <RF12.h>
#include <Ports.h>

const int led = 9;
const byte network = 100;
const byte myNodeId = 2;
const byte otherNode = 3;
const byte freq = RF12_433MHZ;
const byte RF12_NORMAL_SENDWAIT = 0;

typedef struct { 
  byte increments;
  byte command;
} Payload;
Payload inData, outData;

MilliTimer sendTimer;
byte pendingOutput = 0; 
byte sendRequest = 0; 

void blink(int n) {
  for (int i=0; i<n; i++) {
    digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(led, LOW);
    delay(500);
  } 
}

void setup() {
  rf12_initialize(myNodeId, freq, network);
  pinMode(led, OUTPUT);
  blink(10); 
}

static byte produceOutData () {
  byte rnd = random(52); 
  blink(1);
  outData.increments = rnd;
  outData.command = 0x00;
  return 1;
}

void loop () {
    if (rf12_recvDone() && rf12_crc == 0 && rf12_len == sizeof inData) {
        memcpy(&inData, (byte*) rf12_data, sizeof inData);
        byte targetNode = rf12_hdr & RF12_HDR_MASK;
        if (targetNode == myNodeId) {
          sendRequest = 1;  
        }
    }
    if (sendTimer.poll(100) && sendRequest) {
        pendingOutput = produceOutData();
    }
    if (pendingOutput && rf12_canSend()) {
        // blink(2); 
        byte newHeader = otherNode | RF12_HDR_DST;
        rf12_sendStart(newHeader, &outData, sizeof outData);
        rf12_sendWait(2);
        delay(100); 
        pendingOutput = 0;
        sendRequest = 0;
    }
}

