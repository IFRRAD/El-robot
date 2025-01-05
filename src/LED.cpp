#include <FastLED.h>
#include "LED.h"


void set_collor(CRGB color) {
    
    for (int i = 0; i < 4; i++) {
        FastLED.leds()[i] = color;  
    }
    FastLED.show();  
}