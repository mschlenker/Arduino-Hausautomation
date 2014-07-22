const int buttonPin = 12;   
const int ledPin =  13;   

int buttonState = 0;    
byte lastState = 0;
uint32_t lastBreak = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  Serial.println("Bereit...");
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    if (lastState == 0) {
      lastState = 1;
    }
    digitalWrite(ledPin, HIGH);
    Serial.print("1");
  }
  else {
    if (lastState == 1) {
      lastState = 0;
    }
    digitalWrite(ledPin, LOW);
    Serial.print("0");
  }
  uint32_t now = millis();
  if (now - 1000 > lastBreak) {
    lastBreak = now;
    Serial.println(); 
  }
  delay(5); 
}
