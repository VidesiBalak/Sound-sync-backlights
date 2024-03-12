#include <Adafruit_NeoPixel.h>

#define LED_PIN     6
#define LED_COUNT   60 // Change this according to your LED strip length
#define SOUND_PIN   A0

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  int soundValue = analogRead(SOUND_PIN);
  int brightness = map(soundValue, 0, 1023, 0, 255);

  // Smoothly transition colors
  static uint16_t hue = 0;
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, Wheel((i * 256 / strip.numPixels() + hue) & 255));
  }
  strip.setBrightness(brightness);
  strip.show();

  // Increment hue for next iteration
  hue += 1;

  // Delay for smoother transition
  delay(50);
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
