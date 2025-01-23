#include "I2C.h"
#include <Wire.h>
#include <BluetoothSerial.h>



int I2C_scan()
{
 Wire.begin(15, 16);
    byte error, address;
    int nDevices = 0;

    Serial.println("Scanning...");

    for (address = 1; address < 127; address++)
    {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0)
        {
            Serial.print("I2C device found at address 0x");
            if (address < 16)
                Serial.print("0");
            Serial.print(address, HEX);
            Serial.println(" !");
            nDevices++;
        }
    }

    return address;

    if (nDevices == 0)
        Serial.println("No I2C devices found");
    else
        Serial.println("done");
}