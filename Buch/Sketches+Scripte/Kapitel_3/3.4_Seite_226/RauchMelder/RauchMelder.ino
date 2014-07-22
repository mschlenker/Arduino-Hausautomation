int sourcePin = 13;
int sensorValue = 0;

void setup() {
	pinMode(sourcePin, OUTPUT);
	attachInterrupt(1, burning, RISING);
	Serial.begin(9600);
	Serial.println("Los geht's...");
}

void burning() {
	Serial.println("Es brennt!");
}

void loop() {
	digitalWrite(sourcePin, HIGH);
	delay(1000);
	digitalWrite(sourcePin, LOW);
	delay(2000);
}

