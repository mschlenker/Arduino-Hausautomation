#include <SoftwareSerial.h>
#define rxPin 12
#define txPin 13
#define houseCode1 0xCA
#define houseCode2 0xFE

SoftwareSerial softSerial =  SoftwareSerial(rxPin, txPin);

void fs20toggle(int actuator) {
  softSerial.write(0x02); // Präfix  
  softSerial.write(0x06); // Befehlslänge
  softSerial.write(0xF1); // einfach ausführen
  softSerial.write(houseCode1);
  softSerial.write(houseCode2);
  softSerial.write(actuator);
  softSerial.write(0x12); // "toggle"
  softSerial.write(0x01); // wird ignoriert
  delay(50);
  while (softSerial.available()) {
    int b; 
    b = softSerial.read();
    Serial.print(b);
  }
  Serial.println();
}

void setup() {
  softSerial.begin(9600);
  Serial.begin(9600);
  Serial.println("Arduino ist bereit");
}

void loop() {
  fs20toggle(0x00);
  delay(3000);
}
