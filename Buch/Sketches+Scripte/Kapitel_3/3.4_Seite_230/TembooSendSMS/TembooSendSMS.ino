
#include <Bridge.h>
#include <Temboo.h>

const String TEMBOO_ACCOUNT = "horstvonforst"; // anpassen!
const String TEMBOO_APP_KEY_NAME = "ZwitschernderWeihnachtsbaum"; // anpassen!
const String TEMBOO_APP_KEY = "1e6243af-81e5-49c3-b";
const String TWILIO_ACCOUNT_SID = "ACba26ae2ec53a7ee275ad800102ef1127";
const String TWILIO_AUTH_TOKEN = "76f8045ad22909dafe7a102efb99504c";
const String TWILIO_NUMBER = "+1 765-637-0190";
const String RECIPIENT_NUMBER = "+49 163-695-3657";

boolean success = false; // erfolgreich?

void sendSMS() {
  Serial.println("Sende SMS...");
  TembooChoreo SendSMSChoreo;
  SendSMSChoreo.begin();
  // Bei Temboo anmelden
  SendSMSChoreo.setAccountName(TEMBOO_ACCOUNT);
  SendSMSChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
  SendSMSChoreo.setAppKey(TEMBOO_APP_KEY);
  // SMS mit Inhalt fuellen
  SendSMSChoreo.setChoreo("/Library/Twilio/SMSMessages/SendSMS");
  SendSMSChoreo.addInput("AccountSID", TWILIO_ACCOUNT_SID);
  SendSMSChoreo.addInput("AuthToken", TWILIO_AUTH_TOKEN);
  SendSMSChoreo.addInput("From", TWILIO_NUMBER);
  SendSMSChoreo.addInput("To", RECIPIENT_NUMBER);
  SendSMSChoreo.addInput("Body", "Hallo Welt, Gruesse vom Arduino Yun!");
  // Senden!
  unsigned int returnCode = SendSMSChoreo.run();
  // Alles OK?
  if (returnCode == 0) {
    Serial.println("Erfolgreich gesendet!");
    success = true;
  } else {
    // Fehler anzeigen
    while (SendSMSChoreo.available()) {
      char c = SendSMSChoreo.read();
      Serial.print(c);
    } 
    SendSMSChoreo.close();
  }
}

void setup() {
  Serial.begin(9600);
  delay(4000);
  while(!Serial);
  Bridge.begin();
}

void loop() {
  // nur einmal senden!
  if (!success) {
    sendSMS();
  }
  delay(30); 
}
