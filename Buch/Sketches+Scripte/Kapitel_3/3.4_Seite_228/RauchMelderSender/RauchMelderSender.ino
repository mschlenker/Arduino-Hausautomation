#include <RF12.h>
#include <Ports.h>
#define MSG_SIZE 2

const byte network = 100;
const byte myNodeId = 7;
const byte freq = RF12_433MHZ;
const byte RF12_NORMAL_SENDWAIT = 0;
const unsigned long waitMillis = 3000; // Millisekunden zw. Updates

char outdata[MSG_SIZE] = {0};
void produceOutData() {
    // immer 1023 senden!
    outdata[0] = B00000011;
    outdata[1] = B11111111;
}

void setup() {
    rf12_initialize(myNodeId, freq, network);
}

void loop() {
    while (!rf12_canSend()) {
        // Serial.println("Warte auf Modul!");
       rf12_recvDone();
    }
    produceOutData();
    // CDA-Bits sind je 0 -> Message ist Broadcast
    // – die folgenden fuenf Bit sind Absender
    byte newHdr = B00011111 & myNodeId;
    rf12_sendStart(newHdr, outdata, MSG_SIZE);
    rf12_sendWait(RF12_NORMAL_SENDWAIT);
    delay(waitMillis);
}

