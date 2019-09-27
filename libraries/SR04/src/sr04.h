#ifndef _SR04_H
#define _SR04_H

#include <Arduino.h>
#include "gpio.h"

class SR04 : public GPIO {
    private:
        int m_iTrigPin; 
        int m_iEchoPin; 
        
    public:
        SR04();
        ~SR04(void);
        
        virtual int getDistance(void);
};

#endif


