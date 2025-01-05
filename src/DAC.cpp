#include "DAC.h"

void set_dac(float voltage, int channel)
{

    int value = voltage / 3.3 * 4095;

    dacWrite(channel, value);
}