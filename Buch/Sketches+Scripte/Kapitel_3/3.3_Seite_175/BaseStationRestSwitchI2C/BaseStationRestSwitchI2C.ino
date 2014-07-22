
#include <Wire.h>
#include <RCSwitch.h>
#define SLAVE_ADDRESS 0x03

#define TX_PIN 3 
#define NUM_SWITCHES 3
#define HOUSE_CODE 1

// Array fuer bekannte Schalter
const char Switches[NUM_SWITCHES][16] = {
  "licht-flur", "licht-wohnen", "licht-arbeiten" 
};
// Array fuer korrespondierende Geraetecodes
const byte Codes[NUM_SWITCHES] = { 1, 2, 3 }; 

RCSwitch mySwitch = RCSwitch();

void receiveData(int byteCount){
    char rcvBuffer[16]; 
    uint8_t pos = 0;
    uint8_t val = 0;
    while(Wire.available()) {
        if (pos == 0) {
          val = Wire.read();
        } else {
          rcvBuffer[pos-1] = Wire.read();
        }
        pos++;
    }
    // terminierendes Nullbyte ergaenzen
    rcvBuffer[pos-1] = '\0';
    Serial.print("Value: ");
    Serial.println((int)val);
    Serial.print("Target: ");
    Serial.println(rcvBuffer); 
    for (int i=0; i<NUM_SWITCHES; i++) {
      // noetig wegen terminierendem Nullbyte
      String place = Switches[i];
      if (place == rcvBuffer) {
        if (val == 0)
          mySwitch.switchOff(HOUSE_CODE, Codes[i]);
        if (val == 1)
          mySwitch.switchOn(HOUSE_CODE, Codes[i]);
      }
    } 
}

void setup() {
  mySwitch.enableTransmit(TX_PIN);
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
}

void loop() {
  delay(50);
}



