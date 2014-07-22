
#include <Manchester.h>
#define RX_PIN 7
#define BUFFER_SIZE 10

const uint8_t networkId = 100;
const uint8_t myNodeId = 23;

uint8_t rcvBuffer[BUFFER_SIZE];

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
    Serial.println("Checksum failed. :-("); 
    return 1;
  }
  return 0;
}

void printMessage() {
  unsigned int sensorVal = rcvBuffer[5] << 8;
  sensorVal |= rcvBuffer[4];
  Serial.print("Received: "); 
  Serial.println(sensorVal); 
}

void setup() {
  man.setupReceive(RX_PIN, MAN_600);
  man.beginReceiveArray(BUFFER_SIZE, rcvBuffer);
  Serial.begin(9600);
  Serial.println("Setup complete..."); 
}

void loop() {
  if (man.receiveComplete()) {
    uint8_t receivedSize = 0;
    if (checkValidity())
      printMessage();
    man.beginReceiveArray(BUFFER_SIZE, rcvBuffer);
  }
}
