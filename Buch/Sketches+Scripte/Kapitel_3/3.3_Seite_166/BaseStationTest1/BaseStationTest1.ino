
#include <RCSwitch.h>
#include <Manchester.h>
#include <RF12.h>
#include <Ports.h>

#define RX_PIN 7
#define TX_PIN 3 
#define BUFFER_SIZE 10
#define LOOP_DURATION 15000

// Daten fuer die Manchester-Vernetzung
const byte networkId = 100;
const byte myNodeId = 23;

// Daten fuer die RFM12B-Vernetzung
const byte rfm12networkId = 100;
const byte rfm12myNodeId = 2;
const byte rfm12otherNode = 3;
const byte freq = RF12_433MHZ;
const byte RF12_NORMAL_SENDWAIT = 0;

signed long loopTimer = 0;
byte outletState = 0; // Status der Steckdose
uint8_t rcvBuffer[BUFFER_SIZE];

RCSwitch mySwitch = RCSwitch();

// Struct fuer Kommunikation mit Thermostat
typedef struct { 
  byte increments;
  byte command;
} Payload;
Payload inData, outData;
MilliTimer sendTimer;
byte pendingOutput = 0; 
byte sendRequest = 0; 

int checkValidity() {
  if (rcvBuffer[1] > 0 && rcvBuffer[1] != myNodeId) {
    Serial.println("Other node is target!");
    return 0; 
  }
  byte checksum = B10101010;
  for (int i=0; i<sizeof(rcvBuffer)-1; i++) {
    checksum = checksum ^ rcvBuffer[i];
  }
  if (checksum == rcvBuffer[BUFFER_SIZE - 1]) {
    Serial.println("Checksum matches!"); 
    return 1;
  } else {
    Serial.println("Bad checksum :-("); 
  }
  return 0;
}

static byte produceOutData () {
  byte rnd = random(52); 
  outData.increments = rnd;
  outData.command = 0x00;
  return 1;
}

void printRFLMessage() {
  unsigned int sensorVal = rcvBuffer[5] << 8;
  sensorVal |= rcvBuffer[4];
  Serial.print("Received (RF-Link): "); 
  Serial.println(sensorVal); 
}

void sendQueue() {
  // Demo: Steckdose aus- und anschalten
  if (outletState < 1) {
    outletState = 1;
    mySwitch.switchOn(1, 1);
  } else {
    outletState = 0;
    mySwitch.switchOff(1, 1);
  }
}

void setup() {
  rf12_initialize(rfm12myNodeId, freq, rfm12networkId);
  mySwitch.enableTransmit(TX_PIN);
  man.setupReceive(RX_PIN, MAN_300);
  man.beginReceiveArray(BUFFER_SIZE, rcvBuffer);
  Serial.begin(9600);
  while (!Serial);
}

void loop() {
  if (millis() - loopTimer > LOOP_DURATION) {
    loopTimer = millis();
    Serial.println("Sending (RC-Switch)..."); 
    sendQueue(); 
  } 
  // Staendiges Pollen fuer RF-Link Receiver
  if (man.receiveComplete()) {
    uint8_t receivedSize = 0;
    if (checkValidity())
      printRFLMessage();
    man.beginReceiveArray(BUFFER_SIZE, rcvBuffer);
  }
  // Verarbeiten von RFM12-Nachrichten
  if (rf12_recvDone() && rf12_crc == 0 && rf12_len == sizeof inData) {
        memcpy(&inData, (byte*) rf12_data, sizeof inData);
        byte targetNode = rf12_hdr & RF12_HDR_MASK;
        if (targetNode == rfm12myNodeId) {
          sendRequest = 1;  
        }
    }
    if (sendTimer.poll(100) && sendRequest) {
        pendingOutput = produceOutData();
    }
    if (pendingOutput && rf12_canSend()) {
        // Will be garbled!
        // Serial.println("Sending (RFM12B)...");
        byte newHeader = rfm12otherNode | RF12_HDR_DST;
        rf12_sendStart(newHeader, &outData, sizeof outData);
        rf12_sendWait(2);
        delay(100); 
        pendingOutput = 0;
        sendRequest = 0;
    }
}
