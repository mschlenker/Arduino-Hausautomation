#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  mySwitch.enableTransmit(10);
}

void loop() {
  for (int h = 1; h < 5; h++) {
    for (int o = 1; o < 5; o++) { 
      mySwitch.switchOn(h, o);
      delay(1000);
    }
    for (int o = 1; o < 5; o++) { 
      mySwitch.switchOff(h, o);
      delay(1000);
    }
  }
}
