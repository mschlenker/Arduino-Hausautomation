#include <avr/sleep.h>
#include <avr/power.h>

const int pin2 = 2;
const int ledPin = 13;

void pin2Interrupt(void) {
  detachInterrupt(0);
}

void enterSleep(void) {
  attachInterrupt(0, pin2Interrupt, LOW);
  delay(100);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
  // Hier geht es nach dem Aufwachen weiter:
  sleep_disable(); 
}

void setup() {
  Serial.begin(9600);
  pinMode(pin2, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.println("Initialisierung abgeschlossen...");
}

int seconds=0;
void loop() {
  for (int i=0; i<5; i++) {
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
  }
  seconds++;
  Serial.print("Wach seit: ");
  Serial.println(seconds, DEC);
  if(seconds > 2 && digitalRead(pin2) == HIGH) {
    Serial.println("Zzzzzzzz....");
    delay(200);
    seconds = 0;
    enterSleep();
  }
}


