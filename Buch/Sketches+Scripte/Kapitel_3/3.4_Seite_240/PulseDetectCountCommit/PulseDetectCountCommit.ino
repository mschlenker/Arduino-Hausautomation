
#define PIN_SIZE 8

const int buttonPin = 12;   
const int ledPin =  13; 
const int redPin = 10;
const int greenPin = 11;

int buttonState = 0;  
uint32_t lastChange = 0;
byte lastState = 1;
byte changePointer = 0;
byte counter = 0; 
byte pincode[PIN_SIZE] = {0};
byte validPin[PIN_SIZE] = { 2, 3, 10, 4, 2, 0, 0, 0 }; // 23042 
byte pcpoint = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  delay(1000); 
  Serial.println("Bereit...");
}

void comparePin() {
  int lightUp = greenPin;
  for (int i=0; i<PIN_SIZE; i++) {
    if (pincode[i] != validPin[i])
      lightUp = redPin;
    Serial.print((int)pincode[i]);
    Serial.print(" ");
    pincode[i] = 0;         
  } 
  Serial.println();
  if (lightUp == greenPin) {
    Serial.println("PIN matches! :-)");
  } else {
    Serial.println("PIN failed! :-(");
  }
  pcpoint = 0;
  digitalWrite(lightUp, HIGH);
  delay(5000);
  digitalWrite(lightUp, LOW);
}

void loop() {
  uint32_t now = millis();
  buttonState = digitalRead(buttonPin);
  digitalWrite(ledPin, buttonState);
  if (buttonState == HIGH) {
    if (lastState == 0 && (now - lastChange) > 40 && (now - lastChange) < 80) {
      counter++;
      Serial.print("   Impuls: ");
      Serial.print(now - lastChange); 
      Serial.print(" ");
      Serial.println(counter);
      lastState = 1;
      lastChange = now; 
    } else if (now - lastChange > 200 && counter > 0) {
      Serial.print("-> Dialed: ");
      Serial.println(counter);
      pincode[pcpoint] = counter;
      pcpoint = (pcpoint + 1) % PIN_SIZE;
      counter = 0; 
    } else if (now - lastChange > 3000 && pcpoint > 0) {
      Serial.print(">> DONE! ");
      Serial.println();
      comparePin();
    } else if (lastState == 0) {
      Serial.println("** ERROR! ");
      delay(10);
    }
  } else if (lastState == 1) {
     lastState = 0;
     lastChange = now;
  }
  delay(5); 
}
