#include "I2C.h"
#include <Wire.h>
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

int I2C_scan()
{
 Wire.begin();
    byte error, address;
    int nDevices = 0;

    SerialBT.println("Scanning...");

    for (address = 1; address < 127; address++)
    {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0)
        {
            SerialBT.print("I2C device found at address 0x");
            if (address < 16)
            SerialBT.print("0");
            SerialBT.print(address, HEX);
            SerialBT.println(" !");
            nDevices++;
        }
    }

    return address;

    if (nDevices == 0)
        SerialBT.println("No I2C devices found");
    else
        SerialBT.println("done");
}