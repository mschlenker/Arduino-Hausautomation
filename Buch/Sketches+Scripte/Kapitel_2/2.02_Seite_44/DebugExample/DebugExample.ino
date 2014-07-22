#define SERIAL_DEBUG;
int led = 13;

void setup() {
	pinMode(led, OUTPUT);
	#ifdef SERIAL_DEBUG;
		Serial.begin(9600);
	#endif
}

void loop() {
	#ifdef SERIAL_DEBUG;
		Serial.println("LED an");
	#endif
	digitalWrite(led, HIGH);
	delay(1000);
	#ifdef SERIAL_DEBUG;
		Serial.println("LED aus");
	#endif
	digitalWrite(led, LOW);
	delay(1000);
}

