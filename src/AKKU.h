#ifndef AKKU_H
#define AKKU_H

#include <Arduino.h>
#include <FastLED.h>
#include "LED.h"

// ADC-Pin für Spannungsmessung
#define ADC_PIN 36

float get_akku();  // Nur die Deklaration der Funktion

void akku_farbe(float Vbatt);  // Nur die Deklaration der Funktion

#endif
