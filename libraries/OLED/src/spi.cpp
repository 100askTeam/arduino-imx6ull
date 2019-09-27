
#include "spi.h"


static int spi_cs = -1;
static int spidev0_fd = -1;
static int spidev1_fd = -1;

static void func1(int signal)
{
    struct spidevx_info_msg spi_info_msg;
    
    if (spidev0_fd > 0)
    {
        spi_info_msg.chip_select = 0;
        if(ioctl(spidev0_fd, SPIDEVX_IOCEXIT, &spi_info_msg) < 0) 
            perror("SPIDEVX: Failed to exit to the device\n");  
        spidev0_fd = -1;
    }
    
    if (spidev1_fd > 0)
    {
        spi_info_msg.chip_select = 1;
        if(ioctl(spidev1_fd, SPIDEVX_IOCEXIT, &spi_info_msg) < 0) 
            perror("SPIDEVX: Failed to exit to the device\n");  
        spidev1_fd = -1;
    }
    
    exit(0);
}


int SPI::m_iUseCount = 0;

SPI::SPI(SPI::SPIMODE mode, unsigned int speed, unsigned int bits, int cs) 
: m_sMode(mode), m_iSpeed(speed), m_iBits(bits), m_iCS(cs)
{
    m_iUseCount++;
    
    static int flag = 0;
    struct spidevx_info_msg spi_info_msg;
    spi_info_msg.chip_select = this->m_iCS;
    
    //解决实例化子类时，父类会先被调用一次，导致/dev/spidev1.x被反复创建
    if (flag%2 == 1)
    {
        this->m_iSPIDEVXFile = open("/dev/spidevx", O_RDWR);
        if (this->m_iSPIDEVXFile < 0)
            perror("SPIDEVX: can't open device");
        if(ioctl(this->m_iSPIDEVXFile, SPIDEVX_IOCINIT, &spi_info_msg) < 0) 
            perror("SPIDEVX: Failed to init to the device\n");
    
        //解决CTRL+C 退出时，没有清除/dev/spidev1.x 
        spi_cs = this->m_iCS;
        if (spi_cs == 0)
            spidev0_fd= this->m_iSPIDEVXFile;
        else if (spi_cs == 1)
            spidev1_fd= this->m_iSPIDEVXFile;
        signal(SIGINT, func1);
        signal(SIGTERM, func1); 
        signal(SIGKILL, func1); //无法捕获kill -9 ,应用层不能kill -9 退出，不然会导致/dev/spidev1.x没有释放  
        
        string s="/dev/spidev2.";
        stringstream ss;
        ss << this->m_iCS;
        this->m_sPath = s.append(ss.str());
        
        //this->m_sPath = "/dev/spidev1.0";
        this->m_iFile = open(this->m_sPath.c_str(), O_RDWR);
        if (this->m_iFile < 0)
            perror("can't open device");
        
        this->setMode(mode);
        this->setSpeed(speed);
        this->setBitsPerWord(bits);
    }
    
    flag++;
}   

int SPI::setMode(SPI::SPIMODE mode)
{
    this->m_sMode = mode;
    if (ioctl(this->m_iFile, SPI_IOC_WR_MODE, &this->m_sMode)==-1){
        perror("SPI: Can't set SPI mode.");
        return -1;
    }
    if (ioctl(this->m_iFile, SPI_IOC_RD_MODE, &this->m_sMode)==-1){
        perror("SPI: Can't get SPI mode.");
        return -1;
    }
    return 0;
}

int SPI::setSpeed(unsigned int speed)
{
    this->m_iSpeed = speed;
    if (ioctl(this->m_iFile, SPI_IOC_WR_MAX_SPEED_HZ, &this->m_iSpeed)==-1){
        perror("SPI: Can't set max speed HZ");
        return -1;
    }
    if (ioctl(this->m_iFile, SPI_IOC_RD_MAX_SPEED_HZ, &this->m_iSpeed)==-1){
        perror("SPI: Can't get max speed HZ.");
        return -1;
    }
    return 0;
}
    
int SPI::setBitsPerWord(unsigned int bits)
{
    this->m_iBits = bits;
    if (ioctl(this->m_iFile, SPI_IOC_WR_BITS_PER_WORD, &this->m_iBits)==-1){
        perror("SPI: Can't set bits per word.");
        return -1;
    }
    if (ioctl(this->m_iFile, SPI_IOC_RD_BITS_PER_WORD, &this->m_iBits)==-1){
        perror("SPI: Can't get bits per word.");
        return -1;
    }
    return 0;
}

int SPI::transfer(unsigned char *write, unsigned char *read, int length)
{
    struct spi_ioc_transfer transfer;
    memset(&transfer, 0, sizeof(transfer)); //must 
    transfer.tx_buf = (unsigned long)write;
    transfer.rx_buf = (unsigned long)read;
    transfer.len = length;
    transfer.speed_hz = this->m_iSpeed;
    transfer.bits_per_word = this->m_iBits;
    transfer.delay_usecs = 0;
    
    int status = ioctl(this->m_iFile, SPI_IOC_MESSAGE(1), &transfer);
    if (status < 0) {
        perror("SPI: SPI_IOC_MESSAGE Failed");
        return -1;
    }
    return status;  
}

int SPI::transfer(unsigned int *write, unsigned int *read, int length)
{
    struct spi_ioc_transfer transfer;
    memset(&transfer, 0, sizeof(transfer)); //must 
    transfer.tx_buf = (unsigned long)write;
    transfer.rx_buf = (unsigned long)read;
    transfer.len = length;
    transfer.speed_hz = this->m_iSpeed;
    transfer.bits_per_word = this->m_iBits;
    transfer.delay_usecs = 0;
    
    int status = ioctl(this->m_iFile, SPI_IOC_MESSAGE(1), &transfer);
    if (status < 0) {
        perror("SPI: SPI_IOC_MESSAGE Failed");
        return -1;
    }
    return status;  
}

SPI::~SPI() {
    m_iUseCount--;
    
    if (m_iUseCount == 0)
    {
        close(this->m_iFile);
        this->m_iFile = -1; 
        
        struct spidevx_info_msg spi_info_msg;
        
        if (spidev0_fd > 0)
        {
            spi_info_msg.chip_select = 0;
            if(ioctl(spidev0_fd, SPIDEVX_IOCEXIT, &spi_info_msg) < 0) 
                perror("SPIDEVX: Failed to exit to the device\n");  
            
            spidev0_fd = -1;
        }
        
        if (spidev1_fd > 0)
        {
            spi_info_msg.chip_select = 1;
            if(ioctl(spidev1_fd, SPIDEVX_IOCEXIT, &spi_info_msg) < 0) 
                perror("SPIDEVX: Failed to exit to the device\n");  
            
            spidev1_fd = -1;
        }
    }
}
