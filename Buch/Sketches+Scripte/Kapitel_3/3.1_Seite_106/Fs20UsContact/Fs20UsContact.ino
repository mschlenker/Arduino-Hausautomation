#include <SoftwareSerial.h>
#define rxPin 12
#define txPin 13

SoftwareSerial softSerial =  SoftwareSerial(rxPin, txPin);

void setup() {
  softSerial.begin(9600);
  Serial.begin(9600);
  Serial.println("Arduino ist bereit");
}

void loop() {
  softSerial.write(0x02); // Präfix  
  softSerial.write(0x01); // Befehlslänge
  softSerial.write(0xF0); // Befehl: Status
  delay(15);
  while (softSerial.available()) {
    int b; 
    b = softSerial.read();
    Serial.print(b);
  }
  Serial.println();
  delay(1000);
}
