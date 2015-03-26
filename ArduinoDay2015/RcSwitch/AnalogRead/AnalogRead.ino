int val = 0;       

void setup() {
  Serial.begin(9600);
  pinMode(A2, OUTPUT);
  digitalWrite(A2, HIGH);
}

void loop() {
  val = analogRead(A1);   
  Serial.println(val); 
  delay(1000); 
}

