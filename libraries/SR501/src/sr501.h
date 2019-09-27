#ifndef _SR501_H
#define _SR501_H

#include <Arduino.h>
#include "gpio.h"

class SR501 : public GPIO {
    public:
        SR501();
        SR501(int pin);
        ~SR501(void);
        
        virtual int getSignal(void);
};

#endif


