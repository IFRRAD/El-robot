#include <Arduino.h>
#include <FastLED.h>
#include "LED.h"
#include "AKKU.h"
#include "DAC.h"
#include <BluetoothSerial.h>

#define ADC 36
#define NUM_LEDS 4      // Anzahl der LEDs
#define DATA_PIN 23     // Datenpin für die LEDs
#define CLOCK_PIN 18    // Clockpin für die LEDs
#define ADC_PIN 36

int connect = 0;
float Vbatt = 0;
float ADC_Voltage = 0;
String x = "";
String Aufbgabe = "";
String Aufgabe = "";
String ADC_VOLT = "";

CRGB leds[NUM_LEDS];
BluetoothSerial SerialBT;

bool menuShown = false;  // Variable zum Verfolgen, ob das Menü bereits gezeigt wurde

void setup() {
  pinMode(ADC, INPUT);
  Serial.begin(115200);
  FastLED.addLeds<SK9822, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);
  SerialBT.begin("ESP32Test");
}

void loop() {
  // Warten auf Bluetooth-Verbindung
  while (!SerialBT.hasClient()) {
    set_collor(CRGB::Blue);
    delay(200);
    set_collor(CRGB(0, 0, 0));
    delay(200);
  }

  // Menü nur anzeigen, wenn es noch nicht gezeigt wurde
  if (!menuShown) {
    SerialBT.println("Connected");
    SerialBT.println("Was willst du machen? 1. Farbe ändern 2. Akku anzeigen 3. Spannung setzen. zum beenden 'end' eingeben");
    menuShown = true;  // Menü als angezeigt markieren
  }

  // Aufgabe vom Benutzer lesen
  Aufbgabe = SerialBT.readString();
  Aufbgabe.trim();

  if (Aufbgabe == "end") {
    menuShown = false;  // Menü wieder anzeigen, wenn "end" eingegeben wurde
    return;  // Zurück zum Anfang der Schleife
  }

  if (Aufbgabe == "1") {

    SerialBT.println("Welche Farbe möchtest du? Green, Red, Blue, Yellow, White, Black (oder 'end' zum Hauptmenü zurück)");
    
    while(menuShown)
    {
    // In einer Schleife bleiben, um immer wieder die Farbe ändern zu können
      x = SerialBT.readString();
      x.trim();

      if(x == "Green")
      {
        set_collor(CRGB::Red);
        Serial.println("Green");
      }
      else if(x == "Red")
      {
        set_collor(CRGB::Blue);
        Serial.println("Red");
      }
      else if(x == "Blue")
      {
        set_collor(CRGB::Green);
        Serial.println("Blue");
      }
      else if(x == "Yellow")
      {
        set_collor(CRGB::Yellow);
        Serial.println("Yellow");
      }
      else if(x == "White")
      {
        set_collor(CRGB::White);
        Serial.println("White");
      }
      else if(x == "Black")
      {
        set_collor(CRGB::Black);
        Serial.println("Black");
      }

      if (x == "end") {
        // Schleife verlassen und zurück ins Hauptmenü
        menuShown = false;
        return;
      }
    }
  }

  else if (Aufbgabe == "2") {
    // In einer Schleife bleiben, um immer wieder den Akkustand anzeigen zu können
    while (menuShown) {
      Vbatt = get_akku();
      SerialBT.println("Akku Ladung: " + String(Vbatt) + "V");
      SerialBT.println("Gib 'end' ein, um zum Hauptmenü zurückzukehren.");

      x = SerialBT.readString();
      x.trim();

      if (x == "end") {
        // Schleife verlassen und zurück ins Hauptmenü
        menuShown = false;
        return;
      }
    }
  }

  else if (Aufbgabe == "3") {
    // In einer Schleife bleiben, um immer wieder eine Spannung setzen zu können
    SerialBT.println("Welche Spannung möchtest du einstellen? (oder 'end' zum Hauptmenü zurück)");

    while (menuShown) {
    ADC_VOLT = SerialBT.readString();
    ADC_VOLT.trim();

    ADC_Voltage = ADC_VOLT.toFloat();
    SerialBT.println("Eingestellte Spannung: " + String(ADC_Voltage) + "V");
    // Hier kannst du die Spannung mit deiner Funktion setzen, z.B. set_dac(ADC_Voltage, ADC_PIN);
      x = SerialBT.readString();
      x.trim();
      if (x == "end") {
        // Schleife verlassen und zurück ins Hauptmenü
        menuShown = false;
        return;
      }
    }
  }
}
