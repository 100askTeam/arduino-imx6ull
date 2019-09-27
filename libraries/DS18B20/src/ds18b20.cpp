#include "ds18b20.h"

DS18B20::DS18B20()
{   
    this->m_iPin = GPIO0;
    this->m_sPath = "/dev/ds18b20";
    
    this->m_iFile = open(this->m_sPath.c_str(), O_RDWR);
    if (this->m_iFile < 0)
        perror("DS18B20:can't open device");

    if(ioctl(this->m_iFile, DS18B20_IOCINIT, &this->m_iPin) < 0) 
        perror("DS18B20: Failed to init to the device\n");
}

DS18B20::DS18B20(int pin)
{   
    this->m_iPin = pin;
    this->m_sPath = "/dev/ds18b20";
    
    this->m_iFile = open(this->m_sPath.c_str(), O_RDWR);
    if (this->m_iFile < 0)
        perror("DS18B20:can't open device");

    if(ioctl(this->m_iFile, DS18B20_IOCINIT, &this->m_iPin) < 0) 
        perror("DS18B20: Failed to init to the device\n");
}

DS18B20::~DS18B20(void)
{
    close(this->m_iFile);
}

float DS18B20::readTemperature(void)
{
    float temperature;
    struct ds18b20_value_msg msg;
    
    if(ioctl(this->m_iFile, DS18B20_IOCGVALUE, &msg) < 0) 
	{	
        perror("DS18B20: DS18B20_IOCGVALUE Failed\n");
		return -1;
	}
    
    temperature = (((msg.value[1] & 0x07)<<4) + ((msg.value[0] & 0xF0)>>4)) + (msg.value[0] & 0x0F)*0.0625;
    
    if (msg.value[1] & 0xF8)
        return -(temperature);
    else
        return temperature;
}

int DS18B20::readFamilyCode(void)
{
    struct ds18b20_info_msg msg;
    
    if(ioctl(this->m_iFile, DS18B20_IOCGINFO, &msg) < 0) 
        perror("DS18B20: DS18B20_IOCGINFO Failed\n");
    
    return msg.family_code;
}

int DS18B20::readCRC(void)
{
    struct ds18b20_info_msg msg;
    
    if(ioctl(this->m_iFile, DS18B20_IOCGINFO, &msg) < 0) 
        perror("DS18B20: DS18B20_IOCGINFO Failed\n");
    
    return msg.crc;
}


void DS18B20::readSerialNum(unsigned char* array)
{
    struct ds18b20_info_msg msg;
    
    if(ioctl(this->m_iFile, DS18B20_IOCGINFO, &msg) < 0) 
        perror("DS18B20: DS18B20_IOCGINFO Failed\n");
    
    array = msg.serial_num;
}
