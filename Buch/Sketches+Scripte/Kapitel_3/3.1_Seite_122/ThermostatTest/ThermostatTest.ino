
// adjust pins!
const int up = 6;
const int down = 8;

void setup() {
  pinMode(up, OUTPUT);
  pinMode(down, OUTPUT);
  delay(10000);
}

void goUpWards(int n) {
  for (int i=0; i<n; i++) {
    digitalWrite(up, HIGH);
    delay(50); 
    digitalWrite(up, LOW);
    delay(300); 
  } 
}

void goDownWards(int n) {
  for (int i=0; i<n; i++) {
    digitalWrite(down, HIGH);
    delay(50); 
    digitalWrite(down, LOW);
    delay(300);  
  } 
}

void loop() {
  delay(5000);
  goUpWards(10);
  delay(5000);
  goDownWards(10);
}


