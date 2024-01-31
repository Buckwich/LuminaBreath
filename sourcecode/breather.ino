#include "FastLED.h"

#define DURATION 480  //total time of the breathing exercise in seconds
#define SLOWBREATH 39
#define FASTBREATH 21

#define LED_TYPE NEOPIXEL
#define DATA_PIN 6
#define NUM_LEDS 24

CRGB leds[NUM_LEDS];

void breath(int);
void setup() {
  delay(1000);  // Power-up delay
  Serial.begin(9600);  // Allows serial monitor output (check baud rate)
  FastLED.addLeds<LED_TYPE, DATA_PIN>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  int seconds = DURATION;
  long oldMillis = millis();
  while (seconds > 0) {
    long currentMillis = millis();
    long deltaMillis = currentMillis - oldMillis;
    oldMillis = currentMillis;
    seconds = seconds - deltaMillis / 1000;
    Serial.print("Second: ");
    Serial.print(seconds);
    
    int delayMillis = map(seconds, 0, DURATION, SLOWBREATH, FASTBREATH);
    Serial.print(" | Delay: ");
    Serial.print(delayMillis);
    
    unsigned long startMillis = millis();
    breath(delayMillis);
    unsigned long endMillis = millis();

    Serial.print(" | Duration: ");
    Serial.println(endMillis - startMillis);
  }
  FastLED.clear();
  FastLED.show();
}


void loop() {}

void breath(int delayMillis) {
  for (int i = 0; i < 255; i++) {
    int test = quadwave8(i);
    for (int led = 0; led < NUM_LEDS; led++) {
      leds[led] = CHSV(160, 255, test*0.5 );
    }
    FastLED.show();
    delay(delayMillis);
  }
}