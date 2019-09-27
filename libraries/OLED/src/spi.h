#ifndef _SPI_H
#define _SPI_H

#include <Arduino.h>

#define SPIDEVX_IOC_MAGIC    's'
#define SPIDEVX_IOCINIT      _IOWR(SPIDEVX_IOC_MAGIC, 0, void *)
#define SPIDEVX_IOCEXIT      _IOWR(SPIDEVX_IOC_MAGIC, 1, void *)

#define  SPI_A  1
#define  SPI_B  2

struct spidevx_info_msg {
    int max_speed_hz;
    unsigned short mode;
    unsigned short chip_select;
};


class SPI {
    private:
        static int m_iUseCount;
    public:
        enum SPIMODE {
            MODE0 = 0,   //!< Low at idle, capture on rising clock edge
            MODE1 = 1,   //!< Low at idle, capture on falling clock edge
            MODE2 = 2,   //!< High at idle, capture on falling clock edge
            MODE3 = 3    //!< High at idle, capture on rising clock edge
        };
        
        string m_sPath;
        SPIMODE m_sMode; 
        unsigned int m_iSpeed;
        unsigned int m_iBits;
        int m_iFile;
        int m_iCS;
        int m_iSPIDEVXFile;
        
            
    public:
        SPI(SPI::SPIMODE mode = MODE0, unsigned int speed = 25000000, unsigned int bits = 8, int cs = 0);
        virtual int setMode(SPI::SPIMODE mode);
        virtual int setSpeed(unsigned int speed);   
        virtual int setBitsPerWord(unsigned int bits);
        virtual int transfer(unsigned char *write, unsigned char *read, int length);
        virtual int transfer(unsigned int *write, unsigned int *read, int length);
        virtual ~SPI();
};


#endif 


