
#include <Ports.h>
#include <RF12.h>

const byte network = 100;
const byte myNodeId = 3;
const byte otherNode = 2;
const byte freq = RF12_433MHZ;
const byte RF12_NORMAL_SENDWAIT = 0; 
const byte up = 6;
const byte down = 8;
const byte led = 9;
const unsigned long waitMillis = 180000; // Millisekunden zw. Updates 

MilliTimer sendTimer;
// move this to header!
typedef struct { 
  byte increments;
  byte command;
} Payload;
Payload inData, outData;
byte pendingOutput;
unsigned long uptime = 0;
unsigned long lastSend = 0;

void blink(int n) {
  for (int i=0; i<n; i++) {
    digitalWrite(led, HIGH);
    delay(300);
    digitalWrite(led, LOW);
    delay(300);
  } 
}

void goUpWards(int n) {
  for (int i=0; i<n; i++) {
    digitalWrite(up, HIGH);
    delay(20); 
    digitalWrite(up, LOW);
    delay(150); 
  } 
}

void goDownWards(int n) {
  for (int i=0; i<n; i++) {
    digitalWrite(down, HIGH);
    delay(20); 
    digitalWrite(down, LOW);
    delay(150);  
  } 
}

static void consumeInData () {
  // Debug: Kann theoretisch bleiben - während des Stellens
  // muss weder gesendet noch empfanden werden!
  // blink(inData.increments); 
  blink(2);
  goDownWards(52);
  goUpWards(inData.increments);
  delay(waitMillis); 
  blink(5);
}

static byte produceOutData () {
  outData.increments = 0x00;
  outData.command = 0x00;
  return 1; 
}

void setup () {
  rf12_initialize(myNodeId, freq, network);
  pinMode(led, OUTPUT);
  pinMode(up, OUTPUT);
  pinMode(down, OUTPUT);
  blink(5);
  uptime = millis();
}

void loop () {
  if (rf12_recvDone() && rf12_crc == 0 && rf12_len == sizeof inData) {
    memcpy(&inData, (byte*) rf12_data, sizeof inData);
    byte targetNode = rf12_hdr & RF12_HDR_MASK;
    rf12_recvDone();
    if (targetNode == myNodeId) {
      consumeInData();
    }
  }
  unsigned long now = millis();
  if (sendTimer.poll(100) && pendingOutput < 1 && 
   ( uptime > now || now - uptime > 1000 ) ) {
    pendingOutput = produceOutData();
    uptime = now; 
  }
  if (pendingOutput && rf12_canSend()) {
    byte newHeader = otherNode | RF12_HDR_DST;
    rf12_sendStart(newHeader, &outData, sizeof outData);
    rf12_sendWait(2);
    pendingOutput = 0;
    // Nur zur Kontrolle, ob gesendet wird! Verhindert Empfang!
    // delay(1000);
    // blink(1);
  }
}

