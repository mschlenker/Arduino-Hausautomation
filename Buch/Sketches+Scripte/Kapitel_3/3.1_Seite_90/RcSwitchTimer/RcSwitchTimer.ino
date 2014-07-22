#include <DS1307RTC.h>
#include <Time.h>
#include <Wire.h>
#include <RCSwitch.h>

const int h = 1;
RCSwitch mySwitch = RCSwitch();
int onMatrix[3][2] = {
  { 10, 17 },
  { 11, 18 },
  { 10, 11 }
};
int offMatrix[3][2] = {
  { 11, 22 },
  { 12, 23 },
  { 3, 19 }
};
int savedState[3] = { 0, 0, 0 };
int startState[3] = { 0, 0, 0 };

void setStartState(int hour) {
  for (int k=0; k<=24+hour; k++) {
    for (int i=0; i<3; i++) {
      for (int j=0; j<2; j++) {
        if (onMatrix[i][j] == k % 24) {
          startState[i] = 1; 
        }
        if (offMatrix[i][j] == k % 24) {
          startState[i] = 0; 
        }
      }
    }
  }
  for (int i=0; i<3; i++) {
     if (startState[i] > 0) { mySwitch.switchOn(h, i+1); }
     if (startState[i] < 1) { mySwitch.switchOff(h, i+1); }
     delay(100); 
  }
}

void traverseMatrix(int hour) {
  for (int i=0; i<3; i++) {
    for (int j=0; j<2; j++) {
      if (onMatrix[i][j] == hour && savedState[i] < 1) {
        Serial.print("Switch on: ");
        Serial.println(i); 
        mySwitch.switchOn(h, i+1);
        savedState[i] = 1; 
        delay(500);
      }
      if (offMatrix[i][j] == hour && savedState[i] > 0) {
        Serial.print("Switch off: ");
        Serial.println(i); 
        mySwitch.switchOff(h, i+1);
        savedState[i] = 0; 
        delay(500);
      }
    }
  }
}

void setup() {
  Serial.begin(9600);
  mySwitch.enableTransmit(10);
  delay(5000);
  tmElements_t tm;
  if (RTC.read(tm)) { setStartState(tm.Hour); } 
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
    traverseMatrix(tm.Hour); 
  } 
  delay(50000);
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}

