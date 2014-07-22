#include <Manchester.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>
#define LED_PIN 13
#define TX_PIN 12 

const int sensorPin = A0;
volatile int heartBeat = 0;

uint8_t data[10] = {
  100, // Network ID
  0,  // Target Node, 0 = broadcast
  41,  // My Node
  0,   // Metadata
  0,   // payload byte 1
  0,   // payload byte 2
  0,   // payload byte 3
  0,   // payload byte 4
  0,   // payload byte 5
  0    // checksum
};

// Interrupt Service Routine
ISR(WDT_vect) {
  heartBeat += 1;
}

void insertPayload(int val) {
  // split the value to two bytes
  data[4] = val & 0xFF;
  data[5] = (val >> 8) & 0xFF;
  // calculate checksum:
  byte checksum = B10101010;
  for (int i=0; i<sizeof(data)-1; i++) {
    checksum = checksum ^ data[i];
  }
  data[9] = checksum; 
}

void enterSleep(void) {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
  sleep_enable();
  sleep_mode(); // Zzzzzz...
  sleep_disable(); // aufwachen
  power_all_enable(); // Periperie aktivieren
}

void setup() {
  pinMode(LED_PIN,OUTPUT);
  man.setupTransmit(TX_PIN, MAN_1200);
  delay(100);
  MCUSR &= ~(1<<WDRF); // Reset Flag zurücksetzen
  WDTCSR |= (1<<WDCE) | (1<<WDE); // WDCE setzen: Watch Dog Change Enable
  WDTCSR = 1<<WDP0 | 1<<WDP3; // Timeout-Register setzen: 8s
  WDTCSR |= _BV(WDIE); // Interupt aktivieren
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  int sensorValue = analogRead(sensorPin);
  if (sensorValue > 400) {
    insertPayload(sensorValue); 
    for (int i=0; i<3; i++) {
      man.transmitArray(sizeof(data), data);
      delay(250);
    } 
    heartBeat = 0;
  } else {
    if (heartBeat > 5) {
      insertPayload(0);
      man.transmitArray(sizeof(data), data);
      heartBeat = 0;
    }
  }
  digitalWrite(LED_PIN, LOW);
  enterSleep();
}

