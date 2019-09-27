
#include "led.h"

LED::LED(int pin)
{
    setPin(pin);
    
    exportGPIO();
    usleep(25000);
    
    setDirection(0);
}

LED::~LED(void)
{
    unexportGPIO();
}

int LED::on(void)
{
    return setValue(0);
}

int LED::off(void)
{
    return setValue(1);
}