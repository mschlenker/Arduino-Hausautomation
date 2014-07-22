#include <RF12.h>
#include <Ports.h>
#include <Bridge.h>
#include <Console.h>
#define MSG_SIZE 2
 
// RFM12 stuff
uint8_t payload[MSG_SIZE]; 
const byte network = 100;
const byte myNodeId = 2;
const byte freq = RF12_433MHZ;
const byte RF12_NORMAL_SENDWAIT = 0;
const char prefix[] = "sensor-";

void saveToBridge(uint8_t sensorId) {
  unsigned int val = payload[0] << 8;
  val |= payload[1];
  char auxBuffer[6] = {0};
  char sensorName[13] = {0};
  char valueString[10] = {0};
  itoa(val, valueString, 10);
  itoa((int)sensorId, auxBuffer, 6);
  for (int i=0; i<7; i++) {
    sensorName[i] = prefix[i];
  }
  for (int i=0; i<6; i++) {
    sensorName[i+7] = auxBuffer[i];
  }
  // Console.println(val);
  Console.print("Received: ");
  Console.println(valueString);
  Console.print("Sender ID: ");
  Console.println(sensorName);
  Bridge.put(sensorName, valueString);
}

void setup() {
  rf12_initialize(myNodeId, freq, network);
  Bridge.begin();
  Console.begin();
  // Naechste Zeile auskommentieren, wenn Sketch ohne Konsole
  // lauffaehig sein soll!
  while (!Console){ ; }
  Console.println("Empfangsbereit...");
}

void loop() {
  if (rf12_recvDone() && rf12_len == MSG_SIZE  && rf12_crc == 0) {
    if ((rf12_hdr & B11100000) == 0) {
      char* auxpayload = (char*)rf12_data;
      for (int i=0; i<MSG_SIZE; i++) {
        payload[i] = auxpayload[i];
      }
      saveToBridge(rf12_hdr);    
    }
  }
}


