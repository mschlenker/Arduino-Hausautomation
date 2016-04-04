#include <RCSwitch.h>
 
#define SYSTEMCODE "11111"
#define UNITCODE "00010"

RCSwitch mySwitch = RCSwitch();

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  mySwitch.enableTransmit(12);
  digitalWrite(13, LOW);
}

void loop() {
  digitalWrite(13, HIGH);
  mySwitch.switchOn(SYSTEMCODE, UNITCODE);
  delay(3000);
  digitalWrite(13, LOW);
  mySwitch.switchOff(SYSTEMCODE, UNITCODE);
  delay(3000);
}
