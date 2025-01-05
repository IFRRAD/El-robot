#include "AKKU.h"
#include "LED.h"
#include <FastLED.h>

float get_akku()
{
    int x = analogRead(ADC_PIN);        // Lokale Variable x
    float Vout = (x * 3.3) /4095;    // Berechnung der Spannung Vout
    float Vbatt = Vout * 1.47; // Umrechnung der Batteriespannung
    akku_farbe(Vbatt);
    return Vbatt;
}

void akku_farbe(float Vbatt)
{
    if (Vbatt > 3.5)
    {
        set_collor(CRGB::Red);
    }
    else if (Vbatt > 3.0)
    {
        set_collor(CRGB::Yellow);
    }
    else
    {
        set_collor(CRGB::Blue);
    }
}