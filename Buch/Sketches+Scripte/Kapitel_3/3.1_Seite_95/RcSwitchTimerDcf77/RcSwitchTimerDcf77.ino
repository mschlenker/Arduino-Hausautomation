#include <DCF77.h>
#include <Time.h>
#include <Wire.h>
#include <RCSwitch.h>

#define DCF_PIN 2
#define DCF_INTERRUPT 0	

const int h = 1;
RCSwitch mySwitch = RCSwitch();
DCF77 DCF = DCF77(DCF_PIN,DCF_INTERRUPT);
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
        delay(250);
        mySwitch.switchOn(h, i+1);
        savedState[i] = 1; 
        delay(250);
      }
      if (offMatrix[i][j] == hour && savedState[i] > 0) {
        Serial.print("Switch off: ");
        Serial.println(i); 
        mySwitch.switchOff(h, i+1);
        delay(250);
        mySwitch.switchOff(h, i+1);
        savedState[i] = 0; 
        delay(250);
      }
    }
  }
}

void setup() {
  Serial.begin(9600);
  mySwitch.enableTransmit(10);
  DCF.Start();
  delay(5000);
  tmElements_t tm;
  time_t DCFtime = DCF.getTime();
  while (DCFtime == 0) {
    Serial.println("Warte auf DCF77...");
    delay(1000); 
    DCFtime = DCF.getTime();
  }
  setTime(DCFtime);
  setStartState(hour());
}

void loop() {
  print2digits(hour()); Serial.write(':');
  print2digits(minute()); Serial.write(':');
  print2digits(second()); Serial.print(", Datum: ");
  Serial.print(day()); Serial.write('.');
  Serial.print(month()); Serial.write('.');
  Serial.print(year());
  Serial.println();
  traverseMatrix(hour()); 
  time_t DCFtime = DCF.getTime();
  if (DCFtime!=0) {
    setTime(DCFtime);
    delay(50000);
  } else {
    delay(1000);  
  }
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}

