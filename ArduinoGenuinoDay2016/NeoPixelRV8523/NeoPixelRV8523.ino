#include <Wire.h>
#include <RV8523.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Pin connected to Neopixels DI
#define PIN 9

// Pixel offset depending on how a neopixel ring is mounted
// Pixel 0 usually is where the solder pads are:
// #define PIXELOFFSET 0
#define PIXELOFFSET 6
// #define PIXELOFFSET 12
// #define PIXELOFFSET 30

// How many pixels does our neopixel ring use?
#define NUMPIXELS 12
// #define NUMPIXELS 24
// #define NUMPIXELS 60

// some colors
// black is off:
#define BLACK strip.Color(0,0,0)
// use bright white for the hour
#define WHITE strip.Color(255,255,255)
// use alighter blue for the minute
#define BLUE strip.Color(0,0,127)
// red for seconds
#define RED strip.Color(255,0,0)
#define GREEN strip.Color(0,255,0) 

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
RV8523 rtc;

void setup()
{
  //init Serial port
  Serial.begin(9600);
  while(!Serial); //wait for serial port to connect - needed for Leonardo only

  //init RTC
  Serial.println("Init RTC...");

  //set 24 hour mode
  rtc.set24HourMode();

  //start RTC
  rtc.start();

  //When the power source is removed, the RTC will keep the time.
  rtc.batterySwitchOver(1); //battery switch over on

  // Start with an empty neopixel ring 
  strip.begin();
  strip.show();
}


void loop()
{
  uint8_t sec, min, hour, day, month;
  uint16_t year;
  
  //get time from RTC
  rtc.get(&sec, &min, &hour, &day, &month, &year);

  //serial output
  Serial.print("Time: ");
  Serial.print(hour, DEC);
  Serial.print(":");
  Serial.print(min, DEC);
  Serial.print(":");
  Serial.println(sec, DEC);
  
  //wait a second
  delay(1000);
  showClock(hour, min, sec);
}

void showClock (int hour, int minute, int sec) {
  // wipe the ring
  for(int i=0; i<NUMPIXELS; i++){
      strip.setPixelColor(i, BLACK);
  }
  strip.setPixelColor(( (sec*NUMPIXELS) / 60 + PIXELOFFSET ) % NUMPIXELS, RED);
  strip.setPixelColor(( (minute*NUMPIXELS) / 60 + PIXELOFFSET ) % NUMPIXELS, BLUE);
  strip.setPixelColor(( (hour*NUMPIXELS) / 12 + PIXELOFFSET ) % NUMPIXELS, WHITE);
  strip.show();
}
