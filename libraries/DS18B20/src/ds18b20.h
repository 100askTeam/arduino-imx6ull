#ifndef _DS18B20_H
#define _DS18B20_H

#include <Arduino.h>
#include <gpio.h>

#define DS18B20_IOC_MAGIC    'd'
#define DS18B20_IOCINIT      _IOW(DS18B20_IOC_MAGIC, 0, int)
#define DS18B20_IOCGVALUE    _IOWR(DS18B20_IOC_MAGIC, 1, void *)
#define DS18B20_IOCGINFO     _IOWR(DS18B20_IOC_MAGIC, 2, void *)


struct ds18b20_value_msg {
    unsigned char value[2];
};

struct ds18b20_info_msg {
    int dq_pin;
    unsigned char family_code;
    unsigned char serial_num[6];
    unsigned char crc;
};


class DS18B20  {
    private:
        int m_iPin;
        string m_sPath;
        int m_iFile;
    
    public:
        DS18B20();
        DS18B20(int pin);
        
        virtual float readTemperature(void);
        virtual int readFamilyCode(void);
        virtual int readCRC(void);
        virtual void readSerialNum(unsigned char* array);
        
        ~DS18B20(void);
};

#endif


