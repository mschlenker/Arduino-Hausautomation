#include <DCF77.h>
#include <DS1307RTC.h>
#include <Time.h>
#include <Wire.h>

#define DCF_PIN 2
#define DCF_INTERRUPT 0	

time_t time;
DCF77 DCF = DCF77(DCF_PIN,DCF_INTERRUPT);
int ledPin = 13;

void setup() {
 pinMode(ledPin, OUTPUT);
 Serial.begin(9600); 
 DCF.Start();
}

void loop() {
  time_t DCFtime = DCF.getTime();
  if (DCFtime!=0) {
    tmElements_t tm; 
    breakTime(DCFtime, tm);
    if (RTC.write(tm)) {
      Serial.println("RTC erfolgreich gesetzt!");
      digitalClockDisplay(DCFtime);
      digitalWrite(ledPin, HIGH);
      delay(45000);
      digitalWrite(ledPin, LOW);
    } else {
      delay(250); 
    } 
  } else {
    digitalWrite(ledPin, HIGH);
    delay(250);
    digitalWrite(ledPin, LOW);  
    delay(250);
  }
}

void digitalClockDisplay(time_t _time){
  tmElements_t tm;   
  breakTime(_time, tm);
  Serial.println("");
  Serial.print("Time: "); Serial.print(tm.Hour);
  Serial.print(":"); printDigits(tm.Minute);
  Serial.print(":"); printDigits(tm.Second);
  Serial.print(" Date: "); Serial.print(tm.Day);
  Serial.print("."); Serial.print(tm.Month);
  Serial.print("."); Serial.println(tm.Year+1970);
}

void printDigits(int digits){
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
