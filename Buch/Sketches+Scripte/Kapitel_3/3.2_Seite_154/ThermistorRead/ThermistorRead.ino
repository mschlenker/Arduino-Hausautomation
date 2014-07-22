#include <Math.h>

int sourcePin = 13;
int sensorPin = A0;
int sensorValue = 0;
int resistorTwo = 22000;
double fact = -21.10;
double offset = 235.4;
 
void setup() {
  pinMode(sourcePin, OUTPUT);
  Serial.begin(9600);
}
 
unsigned long getResistor(int sensorVal) {
   unsigned long frac = 1047552 / sensorVal - 1024;
   return ( frac * resistorTwo ) / 1024;
}
 
int getTemperature(int resistor) {
  double temp = fact * log((double)resistor) + offset;
  // Zenhtelgrad als Integer zurückliefern
  return (int)(temp * 10.0);  
}
 
 
void loop() {
  digitalWrite(sourcePin, HIGH);
  delay(1000);
  sensorValue = analogRead(sensorPin);
  if (sensorValue > 0) {
      int resist = getResistor(sensorValue);
      Serial.println(resist);
      Serial.println(getTemperature(resist));
  } // sonst division by zero!
  digitalWrite(sourcePin, LOW);
  delay(2000);
}
