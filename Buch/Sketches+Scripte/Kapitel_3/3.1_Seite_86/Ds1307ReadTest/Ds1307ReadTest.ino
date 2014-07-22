#include <DS1307RTC.h>
#include <Time.h>
#include <Wire.h>

void setup() {
  Serial.begin(9600);
}

void loop() {
  tmElements_t tm;
  if (RTC.read(tm)) {
    print2digits(tm.Hour); Serial.write(':');
    print2digits(tm.Minute); Serial.write(':');
    print2digits(tm.Second); Serial.print(", Datum: ");
    Serial.print(tm.Day); Serial.write('.');
    Serial.print(tm.Month); Serial.write('.');
    Serial.print(tmYearToCalendar(tm.Year));
    Serial.println();
  } 
  delay(1000);
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}

