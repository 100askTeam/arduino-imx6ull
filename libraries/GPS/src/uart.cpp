
#include "uart.h"

UART::UART()
{
    
}

UART::UART(int num)
{
    if (num == 0)
        this->m_sPath = UART0_PATH;
    else if(num == 1)
        this->m_sPath = UART1_PATH;
    else if(num == 2)
        this->m_sPath = UART2_PATH;
    else if(num == 3)
        this->m_sPath = UART3_PATH;
	else if(num == 4)
        this->m_sPath = UART4_PATH;
	else if(num == 5)
        this->m_sPath = UART5_PATH;
    else
    {
        perror("Only uart5, use uart5");
        this->m_sPath = UART5_PATH; 
    }
    
    this->setUART();
    
}

//设置串口参数
int UART::setUART(void)
{
    if ((this->m_iFile = open(UART2_PATH, O_RDWR | O_NOCTTY | O_NDELAY))<0)
    {
      perror("UART: Failed to open the file.\n");
      return -1;
    }
    
    struct termios options;               //The termios structure is vital
    tcgetattr(this->m_iFile, &options);   //Sets the parameters associated with file

    // Set up the communications options:
    // 9600 baud, 8-bit, enable receiver, no modem control lines
    options.c_cflag = B9600 | CS8 | CREAD | CLOCAL;
    options.c_iflag = IGNPAR | ICRNL;    //ignore partity errors, CR -> newline
    tcflush(this->m_iFile, TCIFLUSH);             //discard file information not transmitted
    tcsetattr(this->m_iFile, TCSANOW, &options);  //changes occur immmediately

    close(this->m_iFile);
    
    return 0;
}


int UART::sendData(char *data, int len)
{
    if ((this->m_iFile = open(UART2_PATH, O_RDWR | O_NOCTTY | O_NDELAY))<0)
    {
      perror("UART: Failed to open the file.\n");
      close(this->m_iFile); 
      return -1;
    }

    if ((write(this->m_iFile, data, len)) < 0) {        //send the string
      perror("Failed to write to the output\n");
      close(this->m_iFile); 
      return -1;
    }   
    
    close(this->m_iFile);
    
    return 0;
}


static int uart_fd = -1;
static void func1(int signal)
{
    if (uart_fd > 0)
        close(uart_fd);     

    uart_fd = -1;
    exit(0);
}

int UART::reviceData(char *data, int len)
{
    static int i = 0;
    
    if (i == 0)
    {
        i++;
        if ((this->m_iFile = open(UART2_PATH, O_RDWR | O_NOCTTY | O_NDELAY))<0)
        {
          perror("UART: Failed to open the file.\n");
          return -1;
        }
    }
    uart_fd = this->m_iFile;
    signal(SIGINT, func1);
    signal(SIGTERM, func1); 
        
    
    if ((read(this->m_iFile, data, len)) < 0) 
    {  
      //perror("Failed to read from the input\n");
      //msleep(10);
      return -1;
    }
        
    return 0;
}

UART::~UART()
{
    close(this->m_iFile);
}
