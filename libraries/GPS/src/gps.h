#ifndef _GPS_H
#define _GPS_H


#include <Arduino.h>
#include "uart.h"

class GPS : public UART {
    private:
        char RawData[256];
        
    public:
        GPS(int num);
        ~GPS();
        
        virtual int readRawData(char *data);
        virtual int readAnalyzeData(float *data);
        virtual void printfRawData(void);
        virtual void printfAnalyzeData(void);
};

    
#endif