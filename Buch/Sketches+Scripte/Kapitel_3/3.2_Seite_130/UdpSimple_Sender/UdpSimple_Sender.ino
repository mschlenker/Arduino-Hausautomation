#include <UIPEthernet.h>

const IPAddress myIP(10,76,23,111);
const IPAddress targetIP(10,76,23,232);
const int targetPort = 5678;
const byte myMac[6] = { 0x23, 0x42, 0xDE, 0xAD, 0xBE, 0xEA };

int success;
char sensorData[] = "0000";
EthernetUDP udp;

void getData() {
   unsigned long uptime = millis(); 
   itoa( uptime % 10000 / 1000, &sensorData[0], 10);
   itoa( uptime % 1000 / 100, &sensorData[1], 10);
   itoa( uptime % 100 / 10, &sensorData[2], 10);
   itoa( uptime % 10 , &sensorData[3], 10);
}

void setup() {
  Serial.begin(9600);
  Ethernet.begin( myMac, myIP );
}

void loop() {
  int len = 0;
  getData(); 
  success = udp.beginPacket(targetIP, targetPort);
  udp.write("uptime:");
  udp.write(sensorData);
  success = udp.endPacket();
  Serial.print("endPacket: ");
  Serial.println(success ? "success" : "failed");
  delay(5000); 
}

