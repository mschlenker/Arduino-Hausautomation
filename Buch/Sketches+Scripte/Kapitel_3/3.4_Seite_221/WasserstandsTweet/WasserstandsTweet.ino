#include <Bridge.h>
#include <Temboo.h>

const String TEMBOO_ACCOUNT = "horstvonforst";
const String TEMBOO_APP_KEY_NAME = "ZwitschernderWeihnachtsbaum";
const String TEMBOO_APP_KEY = "geheim";
const String TWITTER_ACCESS_TOKEN = "nichtgeheim";
const String TWITTER_ACCESS_TOKEN_SECRET = "geheim";
const String TWITTER_CONSUMER_KEY = "nichtgeheim";
const String TWITTER_CONSUMER_SECRET = "geheim";

const int sourcePin = 2; 
const int sensorPin = A0;
const int resistorTwo = 10000;
const int maxResist = 10000;
const int critResist = 20000;
int sensorValue = 0;

unsigned long getResistor(int sensorVal) {
   if (sensorVal == 0) {
     return 4294967295;
   }
   unsigned long frac = 1023000 / sensorVal - 1000;
   return frac * resistorTwo / 1000;
}

int tweet(String tweetText) {
  TembooChoreo StatusesUpdateChoreo;
  StatusesUpdateChoreo.begin();
  StatusesUpdateChoreo.setAccountName(TEMBOO_ACCOUNT);
  StatusesUpdateChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
  StatusesUpdateChoreo.setAppKey(TEMBOO_APP_KEY);
  // Temboo mit Twitter verknüpfen
  StatusesUpdateChoreo.setChoreo("/Library/Twitter/Tweets/StatusesUpdate");
  StatusesUpdateChoreo.addInput("AccessToken", TWITTER_ACCESS_TOKEN);
  StatusesUpdateChoreo.addInput("AccessTokenSecret", TWITTER_ACCESS_TOKEN_SECRET);
  StatusesUpdateChoreo.addInput("ConsumerKey", TWITTER_CONSUMER_KEY);    
  StatusesUpdateChoreo.addInput("ConsumerSecret", TWITTER_CONSUMER_SECRET);
  // Tweet absetzen
  StatusesUpdateChoreo.addInput("StatusUpdate", tweetText);
  // Return Code ermitteln
  unsigned int returnCode = StatusesUpdateChoreo.run();
  if (returnCode == 0) {
    StatusesUpdateChoreo.close();
    return 0;
  } else {
    StatusesUpdateChoreo.close();
    return 1;
  } 
}

void setup() {
  pinMode(sourcePin, OUTPUT);
  Bridge.begin();
}

/*
const int maxResist = 10000;
const int critResist = 20000;
*/

void loop() { 
  String tweetText = "";
  digitalWrite(sourcePin, HIGH); 
  delay(1000);     
  sensorValue = analogRead(sensorPin); 
  digitalWrite(sourcePin, LOW);
  unsigned long resist = getResistor(sensorValue);
  unsigned int returnCode = 1;
  if (resist > critResist) {
    tweetText = "Hilfe! Ich verdurste! Gemessener Widerstand: " + String(resist);  
  } else if (resist > maxResist) {
    tweetText = "Ich brauche bald Wasser. Gemessener Widerstand: " + String(resist); 
  } else {
    tweetText = "Alles Prima! Gemessener Widerstand: " + String(resist); 
  } 
  returnCode = tweet(tweetText);
  if (returnCode > 0) {
    delay(120000); // zwei Minuten warten
  } else if (resist > critResist) {
    delay(7200000); // zwei Stunden warten
  } else if (resist > maxResist) {
    delay(14400000); // vier Stunden warten
  } else {
    delay(28800000); // acht Stunden warten
  }
}

