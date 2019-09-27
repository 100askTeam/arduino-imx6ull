#ifndef _DAC_H
#define _DAC_H


#include <Arduino.h>
#include "spi.h"


class DAC : public SPI {
    private:
        float m_fVoltage;
        int m_SPInum;
            
    public:
        DAC(int num = 0);
        virtual int setVoltage(float vol = 0);
        virtual int setVoltage(int vol = 0);
        virtual ~DAC();
};

    
#endif