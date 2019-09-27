
#include "sr04.h"

SR04::SR04()
{
    this->m_iTrigPin = GPIO0;
    this->m_iEchoPin = GPIO1;
    
    setPin(this->m_iTrigPin);
    exportGPIO();
    usleep(25000);
    setDirection(0); 
    setValue(0); //先拉低，下次拉高就开始工作
    
    setPin(this->m_iEchoPin);
    exportGPIO();
    usleep(25000);
    setDirection(1); 
}

SR04::~SR04(void)
{
    setPin(this->m_iTrigPin);
    unexportGPIO();
    
    setPin(this->m_iEchoPin);
    unexportGPIO();
}

int SR04::getDistance(void)
{
    setPin(this->m_iTrigPin);
    setValue(1);
    msleep(10);
    setValue(0);
    
    setPin(this->m_iEchoPin);
    
    struct timeval t1, t2;
    while( getValue() == 0); //直到有回响信号开始
    gettimeofday(&t1, NULL);
    while( getValue() == 1); //直到有回响信号结束
    gettimeofday(&t2, NULL);

    //cout << "us=" << (t2.tv_sec-t1.tv_sec) * 1000000 + t2.tv_usec-t1.tv_usec << endl;
    //cout << "cm=" << ((t2.tv_sec-t1.tv_sec)*1000000 + t2.tv_usec-t1.tv_usec)*34/2/1000 << endl;
    
    return ((t2.tv_sec-t1.tv_sec)*1000000 + t2.tv_usec-t1.tv_usec)*34/2/1000;
}
