
#include "dac.h"

DAC::DAC(int num) : m_SPInum(num)
{
    SPI s(MODE0, 25000000, 12, this->m_SPInum-1);
    this->m_sPath = s.m_sPath;
    this->m_iFile= s.m_iFile;   
    this->m_sMode = s.m_sMode ;
    this->m_iSpeed= s.m_iSpeed;
    this->m_iBits = s.m_iBits;  
}

int DAC::setVoltage(float vol)
{
    unsigned int i_val;
    unsigned int write[1], read[1];
    
    this->m_fVoltage = vol;
    
    if (this->m_fVoltage > 4.092)
    {
        perror("Maximum output voltage 4.092V");
        this->m_fVoltage = 4.092;
    }
    if (this->m_fVoltage < 0)
    {
        perror("Minimum output voltage 0V");
        this->m_fVoltage = 0;
    }   
    i_val = (unsigned int)(this->m_fVoltage*250);

    write[0] = i_val<<2; 
    this->transfer(write, read, 2); //2Bytes
    
    return 1;
}

int DAC::setVoltage(int vol)
{
    unsigned int i_val;
    unsigned int write[1], read[1];
    
    this->m_fVoltage = (float)vol;
    
    if (this->m_fVoltage > 4.092)
    {
        perror("Maximum output voltage 4.092V");
        this->m_fVoltage = 4.092;
    }
    if (this->m_fVoltage < 0)
    {
        perror("Minimum output voltage 0V");
        this->m_fVoltage = 0;
    }   
    i_val = (unsigned int)(this->m_fVoltage*250);

    write[0] = i_val<<2; 
    this->transfer(write, read, 2); //2Bytes
    
    return 1;
}


DAC::~DAC()
{
    //close(this->m_iFile);
    //this->m_iFile = -1;
}
