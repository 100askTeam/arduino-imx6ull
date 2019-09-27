#ifndef _UART_H
#define _UART_H

#include <Arduino.h>

#define UART0_PATH  "/dev/ttymxc0"
#define UART1_PATH  "/dev/ttymxc1"
#define UART2_PATH  "/dev/ttymxc2"
#define UART3_PATH  "/dev/ttymxc3"
#define UART4_PATH  "/dev/ttymxc4"

#define UART_A  2
#define UART_B  4

class UART {
    private:
        string m_sPath;
        int m_iFile;
        //设置串口参数
        
    public:
        UART();
        UART(int num);
        ~UART(void);
        
        int setUART(void);
        
        int sendData(char *data, int len);
        int reviceData(char *data, int len);
};

#endif 


