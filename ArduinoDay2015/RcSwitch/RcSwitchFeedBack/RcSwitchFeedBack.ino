#include <RCSwitch.h>

#define SYSTEMCODE "11111"
#define UNITCODE "00010"
#define THRESHOLD_ON 300
#define THRESHOLD_OFF 700

byte state = 0; 
int val = 0; 

RCSwitch mySwitch = RCSwitch();

void setup() {
  pinMode(A3, OUTPUT);
  digitalWrite(A3, HIGH);
  pinMode(A2, OUTPUT);
  digitalWrite(A2, HIGH);
  mySwitch.enableTransmit(13);
}

void loop() {
  val = analogRead(A1);
  if (state < 1 && val < THRESHOLD_ON) { 
    mySwitch.switchOn(SYSTEMCODE, UNITCODE);
    state = 1;
  } else if (state > 0 && val > THRESHOLD_OFF) {
    mySwitch.switchOff(SYSTEMCODE, UNITCODE);
    state = 0; 
  }
  delay(2000);
}
