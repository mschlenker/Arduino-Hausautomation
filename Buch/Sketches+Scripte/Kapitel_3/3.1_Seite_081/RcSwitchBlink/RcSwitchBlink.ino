
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
int ledPin = 13;

void setup() {
  mySwitch.enableTransmit(10);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  mySwitch.switchOn(1, 1);
  digitalWrite(ledPin, HIGH);
  delay(2000);  
  mySwitch.switchOff(1, 1);
  digitalWrite(ledPin, LOW);
  delay(2000);  
}


