
#include "irda.h"
#include "keyboard.h"

IRDA::IRDA()
{   
    this->m_iPin = GPIO0;
    this->m_sPath = IRDA_PATH;
    
    this->m_iFileIRDA = open(this->m_sPath.c_str(), O_RDWR);
    if (this->m_iFileIRDA < 0)
        perror("IRDA: can't open device");

    if(ioctl(this->m_iFileIRDA, IRDA_IOCINIT, &this->m_iPin) < 0) 
        perror("IRDA: Failed to init to the device\n");
    
    ostringstream ostr;
    ostr << getEventNumber("gpio_irda-ir");
    this->m_sPath = IRDA_EVENT_PATH + ostr.str();
    
    this->m_iFileEvent = open(this->m_sPath.c_str(), O_RDONLY);  
    if (this->m_iFileEvent < 0) {  
        perror("IRDA: open file failed\n");  
    }  
}

IRDA::IRDA(int pin)
{   
    this->m_iPin = pin;
    this->m_sPath = IRDA_PATH;
    
    this->m_iFileIRDA = open(this->m_sPath.c_str(), O_RDWR);
    if (this->m_iFileIRDA < 0)
        perror("IRDA: can't open device");

    if(ioctl(this->m_iFileIRDA, IRDA_IOCINIT, &this->m_iPin) < 0) 
        perror("IRDA: Failed to init to the device\n");
    
    ostringstream ostr;
    ostr << getEventNumber("gpio_irda-ir");
    this->m_sPath = IRDA_EVENT_PATH + ostr.str();
    
    this->m_iFileEvent = open(this->m_sPath.c_str(), O_RDONLY);  
    if (this->m_iFileEvent < 0) {  
        perror("IRDA: open file failed\n");  
    }  
}

IRDA::~IRDA(void)
{
    close(this->m_iFileIRDA);
    close(this->m_iFileEvent);
}

int IRDA::readKey(void)
{
    int ret;
    struct input_event ev;
    
    ret = read(this->m_iFileEvent , &ev, sizeof(struct input_event));  
    if (ret < 0) {  
        perror("IRDA: read event error!\n");  
        return -1;
    }  
        
    if (ev.type == EV_KEY) 
    {
        this->m_iCode  = ev.code;
        this->m_iValue = ev.value;
        return 0;
    }
    else
        return -1;
}

int IRDA::getCode(void)
{
    return this->m_iCode;
}

int IRDA::getValue(void)
{
    return this->m_iValue;
}


