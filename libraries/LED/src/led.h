#ifndef _LED_H
#define _LED_H

#include "gpio.h"

#define LED1 ((1-1)*32+4)
#define LED2 ((4-1)*32+20)
#define LED3 ((4-1)*32+19)


class LED : public GPIO {
    public:

        LED(int pin);
        ~LED(void);
        
        int on(void);
        int off(void);
};


#endif 


