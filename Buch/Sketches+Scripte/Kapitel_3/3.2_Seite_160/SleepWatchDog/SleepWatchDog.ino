#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>
#define LED_PIN 13

void enterSleep(void) {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
  sleep_enable();
  sleep_mode(); // Zzzzzz...
  sleep_disable(); // aufwachen
  power_all_enable(); // Periperie aktivieren
}

void setup() {
  Serial.begin(9600);
  Serial.println("Initialising...");
  pinMode(LED_PIN,OUTPUT);
  delay(100);
  // DANGEROUS!
  ADCSRA = 0; // ADC abschalten 
  PRR = B10010111;
  // MCUCR = _BV (BODS) | _BV (BODSE);
  // MCUCR = _BV (BODS);
  // DANGEROUS
  MCUSR &= ~(1<<WDRF); // Reset Flag zurücksetzen
  WDTCSR |= (1<<WDCE) | (1<<WDE); // WDCE setzen: Watch Dog Change Enable
  WDTCSR = 1<<WDP0 | 1<<WDP3; // Timeout-Register setzen: 8s
  WDTCSR |= _BV(WDIE); // Interupt aktivieren
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(500); 
  digitalWrite(LED_PIN, LOW);
  enterSleep();
}

