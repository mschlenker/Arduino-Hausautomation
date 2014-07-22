

// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 12;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
uint32_t lastChange = 0;
byte lastState = 0;
byte changePointer = 0;
byte counter = 0; 
byte commited = 1; 
byte done = 1;
// byte pincode[6] = {0};

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  Serial.println("Bereit...");
}

void loop() {
  uint32_t now = millis();
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    if (lastState == 0) {
      lastState = 1;
      lastChange = now; 
    } else if (now - lastChange > 300 && commited == 0) {
      Serial.print("=> Dialed: ");
      Serial.println(counter);
      commited = 1;
    //  done = 0;
    //} else if (now - lastChange > 3000 && done == 0) {
    //  Serial.println("===> DONE!");
    //  done = 1;
    }
    digitalWrite(ledPin, HIGH);
    // Serial.print("1");
  }
  else {
    // turn LED off:
    if (lastState == 1) {
      lastState = 0;
      Serial.print("Delta: ");
      Serial.print(now - lastChange);
      if (now - lastChange > 300) {
        counter = 1;  
        commited = 0;
      } else {
        counter++; 
      }
      Serial.print(" ");
      Serial.println(counter);
      lastChange = now;
    }
    digitalWrite(ledPin, LOW);
  }
  delay(2); 
}
