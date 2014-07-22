const int sensorPin = A0;
const int ledPin = 13;
const int limit = 300;
int sensorValue = 0;

void setup() {
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);
}

void loop() {
    sensorValue = analogRead(sensorPin);
    if (sensorValue >= limit) {
        digitalWrite(ledPin, HIGH); // LED an!
    } else {
        digitalWrite(ledPin, LOW); // LED aus!
    }
    Serial.print("Sensorwert: " );
    Serial.println(sensorValue);
    delay(1000);
}


