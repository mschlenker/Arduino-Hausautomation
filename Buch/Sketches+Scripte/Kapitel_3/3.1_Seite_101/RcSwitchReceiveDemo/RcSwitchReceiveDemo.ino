#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  Serial.println("Bitte Taste auf Fernbedienung druecken..."); 
  mySwitch.enableReceive(0);  // Int 0 = Pin 2
}

void loop() {
  if (mySwitch.available()) {
    Serial.print("Uptime: ");
    Serial.println(millis());
    output(mySwitch.getReceivedValue(), 
      mySwitch.getReceivedBitlength(), 
      mySwitch.getReceivedDelay(), 
      mySwitch.getReceivedRawdata(),
      mySwitch.getReceivedProtocol());
    mySwitch.resetAvailable();
  }
}

