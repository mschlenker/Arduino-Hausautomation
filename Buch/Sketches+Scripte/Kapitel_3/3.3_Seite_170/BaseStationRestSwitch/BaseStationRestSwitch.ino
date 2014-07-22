
#include <Bridge.h>
#include <Console.h>
#include <RCSwitch.h>

#define TX_PIN 3 
#define NUM_SWITCHES 3
#define HOUSE_CODE 1

// Struct fuer Licht/Steckdose
typedef struct { 
  String place;
  char state;
} Switch;

// Array fuer bekannte Schalter
const char Switches[NUM_SWITCHES][16] = {
  "licht-flur", "licht-wohnen", "licht-arbeiten" 
};
// Array fuer korrespondierende Geraetecodes
const byte Codes[NUM_SWITCHES] = { 1, 2, 3 }; 

// Array fuer Schalterzustaende
Switch SwitchSettings[NUM_SWITCHES];

RCSwitch mySwitch = RCSwitch();

void setup() {
  mySwitch.enableTransmit(TX_PIN);
  pinMode(13, OUTPUT);
  Bridge.begin();
  Console.begin();
  while (!Console){ ; }
}

void loop() {
  digitalWrite(13, HIGH);
  for (int i=0; i<NUM_SWITCHES; i++) {
    SwitchSettings[i].place = Switches[i];
    char oldState = SwitchSettings[i].state;
    Bridge.get(Switches[i], &SwitchSettings[i].state, 1);
    if (SwitchSettings[i].state == '0' || SwitchSettings[i].state == '1') {
      if (oldState == SwitchSettings[i].state ) {
        Console.print("Do nothing for ");
        Console.println(SwitchSettings[i].place); 
      } else {
        Console.print("Toggle ");
        Console.println(SwitchSettings[i].place);
        if (SwitchSettings[i].state == '0')
          mySwitch.switchOff(HOUSE_CODE, Codes[i]);
        if (SwitchSettings[i].state == '1')
          mySwitch.switchOn(HOUSE_CODE, Codes[i]);
      }
    }
  } 
  digitalWrite(13, LOW);  delay(1000);
}



