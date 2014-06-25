
#include <Wire.h>
#define SLAVE_ADDRESS 0x03
int number = 0;
int state = 0;

void setup() {
    pinMode(13, OUTPUT);
    Serial.begin(9600);
    Wire.begin(SLAVE_ADDRESS);
    Wire.onReceive(receiveData);
    Wire.onRequest(sendData);
    Serial.println("Los geht's!");
}

void loop() { delay(50); }

void receiveData(int byteCount){
    while(Wire.available()) {
        number = Wire.read();
        Serial.print("data received: ");
        Serial.println(number);
        if (number == 1){
	    digitalWrite(13, HIGH);
	    state = 1;
	} else {
	    digitalWrite(13, LOW);
	    state = 0;
	}
     }
}

void sendData(){ Wire.write(number); }

