#ifndef _EEPROM_H
#define _EEPROM_H

#include <Arduino.h>
#include "i2c.h"

class EEPROM : public I2C {
    
public:
    EEPROM(int num);
    virtual int readEEPROM(unsigned int addr, unsigned int len, string& rxBuffer);
    virtual int writeEEPROM(unsigned int addr, unsigned int len, string txBuffer);
    
    virtual int readEEPROM(unsigned int addr, unsigned int len, int *rxBuffer);
    virtual int writeEEPROM(unsigned int addr, unsigned int len, int txBuffer[]);
    
    virtual ~EEPROM();
};
    
#endif