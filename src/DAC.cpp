#include "DAC.h"

void set_dac(int voltage, int channel)
{
    
    int value = voltage / (3.3 / 255);
    dacWrite(26, value);

}