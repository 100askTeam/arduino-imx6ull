
#include "i2c.h"

int I2C::m_iUseCount = 0;
int I2C::m_iFile = 0;

I2C::I2C()
{
    m_iUseCount++;
}

I2C::I2C(string bus, unsigned int dev) : m_sPath(bus), m_iDevAddr(dev)
{
    m_iUseCount++;

    this->m_iFile = open(this->m_sPath.c_str(), O_RDWR|O_LARGEFILE);
    if (this->m_iFile < 0)
        perror("I2C:can't open device");
    
    if(ioctl(this->m_iFile, I2C_SLAVE_FORCE, this->m_iDevAddr) < 0)  //I2C_SLAVE or I2C_SLAVE_FORCE
        perror("I2C: Failed to connect to the device\n");
}

unsigned char I2C::readRegister(unsigned int registerAddress)
{
#if 0 //该方法无法连续读，每次读后会有stop
    unsigned char buffer;
    
    if(write(this->m_iFile, &registerAddress, 1) != 1) 
        perror("I2C: Failed to write to the device\n");
    else
    {
        if(read(this->m_iFile, &buffer, 1) != 1) 
            perror("I2C: Failed to read in the value\n");
    }
    
    usleep(2000); //must add, Otherwise error: Remote I/O error
    printf("readRegister:0x%x\n", buffer);
    return buffer;
    
#else 
    
    int ret;
    struct i2c_rdwr_ioctl_data work_queue;
    
    work_queue.nmsgs  = 2;
    
    work_queue.msgs=(struct i2c_msg*)malloc(work_queue.nmsgs*sizeof(struct i2c_msg));
    if(!work_queue.msgs)
    {
        perror("readRegister:malloc error");
        return -1;
    }
        
    (work_queue.msgs[0]).len = 1;
    (work_queue.msgs[0]).flags = 0; 
    (work_queue.msgs[0]).addr = this->m_iDevAddr;
    (work_queue.msgs[0]).buf = (unsigned char *)malloc(1);
    (work_queue.msgs[0]).buf[0] = registerAddress; 
    
    (work_queue.msgs[1]).len = 1;
    (work_queue.msgs[1]).flags = I2C_M_RD;
    (work_queue.msgs[1]).addr = this->m_iDevAddr;
    (work_queue.msgs[1]).buf = (unsigned char *)malloc(1);
    (work_queue.msgs[1]).buf[0] = 0; 

    ret = ioctl(this->m_iFile, I2C_RDWR, (unsigned long)&work_queue);
    if(ret < 0)
        printf("readRegister:error during I2C_RDWR ioctl with error code %d\n", ret);
    usleep(2000);
    
    return (work_queue.msgs[1]).buf[0];
#endif
}


unsigned char I2C::readRegister(unsigned int registerAddress, int count, unsigned char * buf)
{
    int ret;
    struct i2c_rdwr_ioctl_data work_queue;
    
    work_queue.nmsgs  = 2;
    
    work_queue.msgs=(struct i2c_msg*)malloc(work_queue.nmsgs*sizeof(struct i2c_msg));
    if(!work_queue.msgs)
    {
        perror("readRegister:malloc error");
        return -1;
    }
        
    (work_queue.msgs[0]).len = 1;
    (work_queue.msgs[0]).flags = 0; 
    (work_queue.msgs[0]).addr = this->m_iDevAddr;
    (work_queue.msgs[0]).buf = (unsigned char *)malloc(1);
    (work_queue.msgs[0]).buf[0] = registerAddress; 
    
    (work_queue.msgs[1]).len = count;
    (work_queue.msgs[1]).flags = I2C_M_RD;
    (work_queue.msgs[1]).addr = this->m_iDevAddr;
    (work_queue.msgs[1]).buf = (unsigned char *)malloc(count);

    ret = ioctl(this->m_iFile, I2C_RDWR, (unsigned long)&work_queue);
    if(ret < 0)
    {
        printf("readRegister:error during I2C_RDWR ioctl with error code %d\n", ret);
        return -1;
    }
    
    memcpy(buf, work_queue.msgs[1].buf, count);
    usleep(2000);
    
    return 0;
}

int I2C::writeRegister(unsigned int registerAddress, unsigned char value)
{
#if 0
    unsigned char buffer[2];
    buffer[0] = registerAddress;
    buffer[1] = value;
    
    if(write(this->m_iFile, buffer, 2) != 2) 
    {
        perror("I2C: Failed to write to the device\n");
        return 1;
    }
    usleep(2000); //must add, Otherwise error: Remote I/O error

#else
    int ret;
    struct i2c_rdwr_ioctl_data work_queue;
    
    work_queue.nmsgs  = 1;  
    
    work_queue.msgs=(struct i2c_msg*)malloc(work_queue.nmsgs*sizeof(struct i2c_msg));
    if(!work_queue.msgs)
    {
        perror("writeRegister:malloc error");
        return -1;
    }
    
    (work_queue.msgs[0]).len = 2;
    (work_queue.msgs[0]).flags = 0; //write
    (work_queue.msgs[0]).addr = this->m_iDevAddr;
    (work_queue.msgs[0]).buf = (unsigned char *)malloc(2);
    (work_queue.msgs[0]).buf[0] = registerAddress; 
    (work_queue.msgs[0]).buf[1] = value; 

    ret = ioctl(this->m_iFile, I2C_RDWR, (unsigned long)&work_queue);
    if(ret < 0)
    {
        printf("writeRegister:error during I2C_RDWR ioctl with error code %d\n", ret);  
        return -1;
    }
    usleep(2000);
#endif

    return 0;
}

int I2C::writeRegister(unsigned int registerAddress, int count, unsigned char* buf)
{
    int ret;
    int i;
    struct i2c_rdwr_ioctl_data work_queue;
    
    work_queue.nmsgs  = 1;  
    
    work_queue.msgs=(struct i2c_msg*)malloc(work_queue.nmsgs*sizeof(struct i2c_msg));
    if(!work_queue.msgs)
    {
        perror("writeRegister:malloc error");
        return -1;
    }
    
    (work_queue.msgs[0]).len = count+1;
    (work_queue.msgs[0]).flags = 0; //write
    (work_queue.msgs[0]).addr = this->m_iDevAddr;
    (work_queue.msgs[0]).buf = (unsigned char *)malloc(count+1);
    (work_queue.msgs[0]).buf[0] = registerAddress; 
    for (i=0; i<count; i++)
        work_queue.msgs[0].buf[i+1] = buf[i];
    
    ret = ioctl(this->m_iFile, I2C_RDWR, (unsigned long)&work_queue);
    if(ret < 0)
    {
        printf("writeRegister:error during I2C_RDWR ioctl with error code %d\n", ret);  
        return -1;
    }
    usleep(2000);
    
    return 0;
}

I2C::~I2C()
{
    m_iUseCount--;
    if (m_iUseCount == 0)
        close(this->m_iFile);
}