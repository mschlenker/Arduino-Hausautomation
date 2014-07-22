#define DCF77PIN 2

int prevSensorValue=0;
  
void setup() {
  Serial.begin(9600);
  pinMode(DCF77PIN, INPUT);
  Serial.println("0ms.......100ms.....200ms.....300ms.....400ms");
}

void loop() {
  int sensorValue = digitalRead(2);
  if (sensorValue==1 && prevSensorValue==0) { Serial.println("");   }
  Serial.print(sensorValue);   
  prevSensorValue = sensorValue;
  delay(10);
}
