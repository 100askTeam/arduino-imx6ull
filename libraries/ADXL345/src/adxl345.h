#ifndef _ADXL345_H
#define _ADXL345_H


#include <Arduino.h>
#include <gpio.h>
#include <spi.h>

#define ADXL34X_IOC_MAGIC    'a'
#define ADXL34X_IOCINIT      _IOWR(ADXL34X_IOC_MAGIC, 0, void *)
#define ADXL34X_IOCEXIT      _IOWR(ADXL34X_IOC_MAGIC, 1, void *)

#define ADXL345_EVENT_PATH   "/dev/input/event"

struct adxl34x_info_msg {
    int max_speed_hz;
    unsigned short mode;
    unsigned short chip_select;
    int irq_pin;
};


class ADXL345 {
    private:
        string m_sPath;
        int m_iCS;
        int m_iEventFile;
        int m_iAdxl345File;
    
        int touch_value;    
        int x_value;    
        int y_value;
        int z_value;
        
    public:
        ADXL345(int num);
        virtual int readData(void);
        virtual int getTouchValue(void);
        virtual int getXValue(void);
        virtual int getYValue(void);
        virtual int getZValue(void);
        virtual ~ADXL345();
};

    
#endif