
#include "dht11.h"

DHT11::DHT11()
{   
    this->m_iPin = GPIO0;
    this->m_sPath = "/dev/dht11";
    
    this->m_iFile = open(this->m_sPath.c_str(), O_RDWR);
    if (this->m_iFile < 0)
        perror("can't open device");

    if(ioctl(this->m_iFile, DHT11_IOCINIT, &this->m_iPin) < 0) 
        perror("DHT11: Failed to init to the device\n");
    
    msleep(1500);
}

DHT11::DHT11(int pin)
{   
    this->m_iPin = pin;
    this->m_sPath = "/dev/dht11";
    
    this->m_iFile = open(this->m_sPath.c_str(), O_RDWR);
    if (this->m_iFile < 0)
        perror("can't open device");

    if(ioctl(this->m_iFile, DHT11_IOCINIT, &this->m_iPin) < 0) 
        perror("DHT11: Failed to init to the device\n");
    
    msleep(1500);
}

DHT11::~DHT11(void)
{
    close(this->m_iFile);
}

int DHT11::readTemperature(void)
{
    struct dht11_value_msg msg;
    
    if(ioctl(this->m_iFile, DHT11_IOCGVALUE, &msg) < 0) 
        perror("DHT11: DHT11_IOCGVALUE Failed\n");
    
    return msg.temperature;
}

int DHT11::readHumdity(void)
{
    struct dht11_value_msg msg;
    
    if(ioctl(this->m_iFile, DHT11_IOCGVALUE, &msg) < 0) 
        perror("DHT11: DH1T1_IOCGVALUE Failed\n");
    
    return msg.humdity;
}


