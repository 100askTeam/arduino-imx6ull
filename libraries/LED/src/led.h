#ifndef _LED_H
#define _LED_H

#include "gpio.h"

#define LED1 ((5-1)*32+3)

class LED : public GPIO {
    public:

        LED(int pin);
        ~LED(void);
        
        int on(void);
        int off(void);
};


#endif 


