
#include "eeprom.h"

EEPROM::EEPROM(int num)
{
    if (num == 1)
        I2C(I2C0, AT24C256);
    else if(num == 2)
        I2C(I2C1, AT24C256);
    
    this->m_iDevAddr = AT24C256; 
}

int EEPROM::readEEPROM(unsigned int addr, unsigned int len, string& rxBuffer)
{
    unsigned int i;
    char data[len];

    len = len + 1;
    
    for (i=0; i<len; i++)
    {
        data[i] = readRegister(addr);
        if (data[i] < 0)
            return -1;
        addr++;
    }
    
    rxBuffer = data;
    
    return 0;
}

int EEPROM::writeEEPROM(unsigned int addr, unsigned int len, string txBuffer)
{
    unsigned int i;
    unsigned char *data = (unsigned char *)txBuffer.c_str();
    
    len = len + 1;
    
    for (i=0; i<len; i++)
    {
        if (writeRegister(addr, data[i]) <0)
            return -1;
        addr++;
    }

    return 0;
}


int EEPROM::readEEPROM(unsigned int addr, unsigned int len, int *rxBuffer)
{
    unsigned int i;
    
    for (i=0; i<len; i++)
    {
        rxBuffer[i] = readRegister(addr);
        if (rxBuffer[i] <0)
            return -1;
        addr++;
    }
    
    return 0;
}

int EEPROM::writeEEPROM(unsigned int addr, unsigned int len, int txBuffer[])
{
    unsigned int i;
    
    for (i=0; i<len; i++)
    {
        if (writeRegister(addr, txBuffer[i]) <0)
            return -1;
        addr++;
    }

    return 0;
}



EEPROM::~EEPROM()
{
    
}
