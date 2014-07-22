#include <Wire.h>
#include <Manchester.h>
#include <RF12.h>
#include <Ports.h>

#define RX_PIN 7
#define BUFFER_SIZE 10
#define SLAVE_ADDRESS 0x03 
#define NUM_SENSORS 16
#define RF12_MSG_SIZE 7

const uint8_t networkId = 100;
const uint8_t myNodeId = 23;

uint8_t rcvBuffer[BUFFER_SIZE];

byte sensorAdresses[NUM_SENSORS] = {0};
int  sensorValues[NUM_SENSORS] = {-1}; 
static volatile int nextSensor = 0;

// RFM12 stuff
char rf12payload[RF12_MSG_SIZE]; 
const byte myRf12Network = 100;
const byte myRf12NodeId = 2;
const byte freq = RF12_433MHZ;
const byte RF12_NORMAL_SENDWAIT = 0;

int checkValidity() {
  if (rcvBuffer[1] > 0 && rcvBuffer[1] != myNodeId) {
    return 0; 
  }
  byte checksum = B10101010;
  for (int i=0; i<sizeof(rcvBuffer)-1; i++) {
    checksum = checksum ^ rcvBuffer[i];
  }
  if (checksum == rcvBuffer[BUFFER_SIZE - 1]) {
    return 1;
  } 
  return 0;
}

void saveData() {
  unsigned int sensorVal = rcvBuffer[5] << 8;
  sensorVal |= rcvBuffer[4];
  Serial.print("Received: "); 
  Serial.println(sensorVal); 
  Serial.print("Source: ");
  Serial.println(rcvBuffer[2]); 
  byte saved = 0;
  for (int i=0; i<NUM_SENSORS; i++) {
    if ((sensorAdresses[i] == 0 || sensorAdresses[i] == rcvBuffer[2]) 
      && saved == 0) {
        sensorAdresses[i] = rcvBuffer[2];
        sensorValues[i] = sensorVal;
        saved = 1;
      }
  }
}

byte saveRf12Data() {
  // Serial.println("Save RF12 data");
  // DO NOT TRY THIS AT HOME!
  // weird hack: use same array for sensor IDs!
  // Serial.println((int)rf12payload[0]);
  for (int i=0; i<NUM_SENSORS; i++) {
    if (sensorAdresses[i] == 0 || sensorAdresses[i] == rf12payload[0]) {
        sensorAdresses[i] = rf12payload[0];
        sensorValues[i] = rf12payload[1] << 8;
        sensorValues[i] |= rf12payload[2];
        return 1;
      }
  }
  return 0;
}

void receiveData(int byteCount){
  while(Wire.available()) {
    Wire.read();
    // do nothing!  
  }
}

void sendData(){
  while (sensorAdresses[nextSensor] == 0)
    nextSensor = (nextSensor + 1) % NUM_SENSORS; 
  uint8_t txData[3];
  // Integer wieder in zwei Bytes zerlegen
  txData[2] = sensorValues[nextSensor] & 0xFF;
  txData[1] = (sensorValues[nextSensor] >> 8) & 0xFF;
  txData[0] = sensorAdresses[nextSensor];
  Wire.write(txData, 3);
  nextSensor = (nextSensor + 1) % NUM_SENSORS;
}

void setup() {
  man.setupReceive(RX_PIN, MAN_600);
  man.beginReceiveArray(BUFFER_SIZE, rcvBuffer);
  rf12_initialize(myRf12NodeId, freq, myRf12Network);
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onRequest(sendData);
  Wire.onReceive(receiveData);
  // add some fake data
  sensorAdresses[0] = 41;
  sensorValues[0] = 123;
  sensorAdresses[1] = 43;
  sensorValues[1] = 623;
  // Serial.println("I2cTxSensorData ready...");
}

void loop() {
  if (man.receiveComplete()) {
    uint8_t receivedSize = 0;
    if (checkValidity())
      saveData();
    man.beginReceiveArray(BUFFER_SIZE, rcvBuffer);
  }
  if (rf12_recvDone() && rf12_len == RF12_MSG_SIZE  && rf12_crc == 0) {
    Serial.println("Empfangen!"); 
    char* auxpayload = (char*)rf12_data;
    for (int i=0; i<RF12_MSG_SIZE; i++) {
      rf12payload[i] = auxpayload[i];
    }
    saveRf12Data(); 
  }
}
