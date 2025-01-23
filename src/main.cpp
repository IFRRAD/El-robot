#include <Arduino.h>
#include <FastLED.h>
#include "LED.h"
#include "AKKU.h"
#include "DAC.h"
#include "I2C.h"	
#include <BluetoothSerial.h>

#define ADC 36
#define NUM_LEDS 4      // Anzahl der LEDs
#define DATA_PIN 23     // Datenpin für die LEDs
#define CLOCK_PIN 18    // Clockpin für die LEDs
#define ADC_PIN 36

int connect = 0;
float Vbatt = 0;
float ADC_Voltage = 0;
int Adress = 0;
String x = "";
String Aufbgabe = "";
String Aufgabe = "";
String ADC_VOLT = "";

CRGB leds[NUM_LEDS];
BluetoothSerial SerialBT;

bool menuShown = false;  

void setup() {
  pinMode(ADC, INPUT);
  Serial.begin(115200);
  FastLED.addLeds<SK9822, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);
  SerialBT.begin("ESP32Test");
}

void loop() {
  while (!SerialBT.hasClient()) {
    set_collor(CRGB::Blue);
    delay(200);
    set_collor(CRGB(0, 0, 0));
    delay(200);
  }

  if (!menuShown) {
    SerialBT.println("Connected");
    SerialBT.println("Was willst du machen? 1. Farbe ändern 2. Akku anzeigen 3. Spannung setzen 4. um I²C zu scannen. zum beenden 'end' eingeben");
    menuShown = true;  
  }

  Aufbgabe = SerialBT.readString();
  Aufbgabe.trim();

  if (Aufbgabe == "end") {
    menuShown = false;  
    return;  
  }

  if (Aufbgabe == "1") {

    SerialBT.println("Welche Farbe möchtest du? Green, Red, Blue, Yellow, White, Black (oder 'end' zum Hauptmenü zurück)");
    
    while(menuShown)
    {
      x = SerialBT.readString();
      x.trim();

      if(x == "Green")
      {
        set_collor(CRGB::Red);
      }
      else if(x == "Red")
      {
        set_collor(CRGB::Blue);
      }
      else if(x == "Blue")
      {
        set_collor(CRGB::Green);
      }
      else if(x == "Yellow")
      {
        set_collor(0xFFFF00);
      }
      else if(x == "White")
      {
        set_collor(CRGB::White);
      }
      else if(x == "Black")
      {
        set_collor(CRGB::Black);
      }

      if (x == "end") {
        menuShown = false;
        return;
      }
    }
  }

  else if (Aufbgabe == "2") {
    while (menuShown) {
      Vbatt = get_akku();
      SerialBT.println("Akku Ladung: " + String(Vbatt) + "V");
      SerialBT.println("Gib 'end' ein, um zum Hauptmenü zurückzukehren.");

      x = SerialBT.readString();
      x.trim();

      if (x == "end") {
        menuShown = false;
        return;
      }
    }
  }

  else if (Aufbgabe == "3") {
    SerialBT.println("Welche Spannung möchtest du einstellen? (oder 'end' zum Hauptmenü zurück)");

    while (menuShown) {
    ADC_VOLT = SerialBT.readString();
    ADC_VOLT.trim();

    ADC_Voltage = ADC_VOLT.toFloat();
    SerialBT.println("Eingestellte Spannung: " + String(ADC_Voltage) + "V");
      x = SerialBT.readString();
      x.trim();
      if (x == "end") {
        menuShown = false;
        return;
      }
    }
  }

  else if (Aufbgabe == "4") {
    
    while (menuShown) {
      Adress = I2C_scan();

      SerialBT.println("I²C Geräte gefunden: " + String(Adress));


      SerialBT.println("Gib 'end' ein, um zum Hauptmenü zurückzukehren.");

      x = SerialBT.readString();
      x.trim();

      if (x == "end") {
        menuShown = false;
        return;
      }
    }

}
}
