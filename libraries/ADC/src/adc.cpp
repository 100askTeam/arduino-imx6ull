
#include "adc.h"

ADC::ADC(int num)
{
    if (num == 1)
        this->m_sPath = ADC1_PATH;
    else if(num == 2)
        this->m_sPath = ADC2_PATH;
    else
    {
        perror("ADC: Only adc1 and adc2, use adc1");
        this->m_sPath = ADC1_PATH;
    }
}


int ADC::getValue(void)
{
    char buff[128] = {0};
    memset(buff, 0, 128);
    
    this->m_iFile = open(this->m_sPath.c_str(), O_RDONLY);
    if (this->m_iFile < 0)
        perror("ADC: can't open device");
    
    if(read(this->m_iFile, &buff, sizeof(buff)) < 0) 
        perror("ADC: Failed to read the device\n");

    this->m_iValue = atoi(buff);
    
    close(this->m_iFile);
    
    return this->m_iValue;
}

ADC::~ADC()
{
    
}