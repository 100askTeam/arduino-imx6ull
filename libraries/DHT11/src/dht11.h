#ifndef _DHT11_H
#define _DHT11_H

#include <Arduino.h>
#include <gpio.h>

#define DHT11_IOC_MAGIC    'd'
#define DHT11_IOCINIT      _IOW(DHT11_IOC_MAGIC, 0, int)
#define DHT11_IOCGVALUE    _IOWR(DHT11_IOC_MAGIC, 2, void *)

struct dht11_value_msg {
    unsigned char humdity;
    unsigned char temperature;
};


class DHT11  {
    private:
        int m_iPin;
        string m_sPath;
        int m_iFile;
    
    public:
        DHT11();
        DHT11(int pin);
        
        virtual int readTemperature(void);
        virtual int readHumdity(void);
        
        ~DHT11(void);
};

#endif


