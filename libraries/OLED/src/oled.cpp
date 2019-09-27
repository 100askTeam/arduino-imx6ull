
#include "oled.h"

OLED::OLED(int num) : m_SPInum(num)
{
    SPI s(MODE0, 25000000, 8, this->m_SPInum - 1);
    
    this->m_sPath = s.m_sPath;
    this->m_iFile = s.m_iFile;  
    this->m_sMode = s.m_sMode ;
    this->m_iSpeed= s.m_iSpeed;
    this->m_iBits = s.m_iBits;      
    
    if (this->m_SPInum == 1)
    {
        m_cDCPin = GPIO(GPIO1);
        m_cDCPin.exportGPIO();
        usleep(1000);
        m_cDCPin.setDirection(0);
    }
    else if (this->m_SPInum == 2)
    {
        m_cDCPin = GPIO(GPIO2);
        m_cDCPin.exportGPIO();
        usleep(1000);
        m_cDCPin.setDirection(0);
    }
    
    this->OLEDInit();
    this->OLEDClearAll();
}

//private
void OLED::setDC(char val)
{
    this->m_cDCPin.setValue(val);
}

void OLED::writeCmd(unsigned char cmd)
{
    this->setDC(0);  
    this->transfer(&cmd, NULL, 1); 
    this->setDC(1); 
}

void OLED::writeData(unsigned char data)
{
    this->setDC(1);  
    this->transfer(&data, NULL, 1); 
    this->setDC(1); 
}

void OLED::setPageAddrMode(void)
{
    this->writeCmd(0x20);
    this->writeCmd(0x02);
}

void OLED::setPos(int x, int y)
{
    this->writeCmd(0xB0 + y); 
    this->writeCmd(x & 0xF);   
    this->writeCmd(0x10 + (x >> 4)); 

}

void OLED::putChar(int x, int y, char c)
{
    unsigned char *dots = (unsigned char *)oled_asc2_8x16[c - ' '];

    this->setPos(x, y);
    this->transfer(&dots[0] , NULL, 8); 
    
    this->setPos(x, y+1);
    this->transfer(&dots[8] , NULL, 8);
}


void OLED::OLEDPrint(int x, int y, string str)
{
    int i = 0;

    char *c = (char *)str.c_str(); 

    //this->OLEDClearPage(y);
    //this->OLEDClearPage(y+1);
    
    while (c[i])
    {
        this->putChar(x, y, c[i]);
        x += 8;
        if (x > 127)
        {
            x = 0;
            y += 2;
#if 0
            if (y <= 6) 
            {
                this->OLEDClearPage(y);
                this->OLEDClearPage(y+1);    
            }
#endif
        }
        i++;
    }
}

void OLED::OLEDClearAll(void)
{
    int y, i;
    for (y = 0; y < 8; y++)
    {
        this->setPos(0, y);
        for (i = 0; i < 128; i++)
            this->writeData(0);
    }
}

void OLED::OLEDClearPage(int y)
{
    int i;
    
    this->setPos(0, y);
    for (i = 0; i < 128; i++)
        this->writeData(0);     
}

void OLED::OLEDInit(void)
{
    this->writeCmd(0xAE); /*display off*/ 
    this->writeCmd(0x00); /*set lower column address*/ 
    this->writeCmd(0x10); /*set higher column address*/ 
    this->writeCmd(0x40); /*set display start line*/ 
    this->writeCmd(0xB0); /*set y address*/ 
    this->writeCmd(0x81); /*contract control*/ 
    this->writeCmd(0x66); /*128*/ 
    this->writeCmd(0xA1); /*set segment remap*/ 
    this->writeCmd(0xA6); /*normal / reverse*/ 
    this->writeCmd(0xA8); /*multiplex ratio*/ 
    this->writeCmd(0x3F); /*duty = 1/64*/ 
    this->writeCmd(0xC8); /*Com scan direction*/ 
    this->writeCmd(0xD3); /*set display offset*/ 
    this->writeCmd(0x00); 
    this->writeCmd(0xD5); /*set osc division*/ 
    this->writeCmd(0x80); 
    this->writeCmd(0xD9); /*set pre-charge period*/ 
    this->writeCmd(0x1f); 
    this->writeCmd(0xDA); /*set COM pins*/ 
    this->writeCmd(0x12); 
    this->writeCmd(0xdb); /*set vcomh*/ 
    this->writeCmd(0x30); 
    this->writeCmd(0x8d); /*set charge pump enable*/ 
    this->writeCmd(0x14); 

    this->setPageAddrMode();

    this->OLEDClearAll();
    
    this->writeCmd(0xAF); /*display ON*/    
}

OLED::~OLED()
{
    this->OLEDClearAll();
    this->writeCmd(0xAE); /*display off*/ 
    m_cDCPin.unexportGPIO();
}

