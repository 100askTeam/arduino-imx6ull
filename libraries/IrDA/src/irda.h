#ifndef _IRDA_H
#define _IRDA_H

#include <Arduino.h>
#include <gpio.h>

#define IRDA_IOC_MAGIC    'i'
#define IRDA_IOCINIT      _IOW(IRDA_IOC_MAGIC, 0, int)

#define IRDA_PATH         "/dev/irda"
#define IRDA_EVENT_PATH   "/dev/input/event"

class IRDA  {
    private:
        int m_iPin;
        string m_sPath;
        int m_iFileIRDA;
        int m_iFileEvent;
        int m_iCode;
        int m_iValue;
    
    public:
        IRDA(void);
        IRDA(int pin);
        virtual int readKey(void);
        virtual int getCode(void);
        virtual int getValue(void);
        ~IRDA(void);
};


#endif 


