
#include "keyboard.h"

KEYBOARD::KEYBOARD()
{
    ostringstream ostr;
    ostr << getEventNumber("gpio-keys");
    this->m_sPath = KEYBOARD_EVENT_PATH + ostr.str();
    
    this->m_iFileEvent = open(this->m_sPath.c_str(), O_RDONLY);  
    if (this->m_iFileEvent < 0) {  
        perror("KEYBOARD: open file failed\n");  
    }  
}

KEYBOARD::~KEYBOARD(void)
{
    close(this->m_iFileEvent);
}

int KEYBOARD::readKey(void)
{
    int ret;
    struct input_event ev;
    
    ret = read(this->m_iFileEvent , &ev, sizeof(struct input_event));  
    if (ret < 0) {  
        perror("KEYBOARD: read event error!\n"); 
        return -1;
    }  
        
    if (ev.type == EV_KEY) 
    {
        this->m_iCode  = ev.code;
        this->m_iValue = ev.value;

        return 0;
    }
    else 
        return 0;
}

int KEYBOARD::getCode(void)
{
    return this->m_iCode;
}

int KEYBOARD::getValue(void)
{   
    return this->m_iValue;  
}



int getEventNumber(char *name)
{
    FILE *fd;
    int i, len, num;
    char *str;
    char buf[64], temp[4];
    int flag = 0, file_row = 0, cur_row = 0;
    
    fd = fopen("/proc/bus/input/devices", "r"); 
    if(fd == NULL) 
    {
        printf("getEventNumber:Can not open file\r\n");
        return -1;
    }
    
    while(!feof(fd))
    {
        flag = fgetc(fd);
        if(flag == '\n')
            file_row++;
    }
    file_row = file_row + 1; 
    fseek(fd, 0, SEEK_SET);
    
    cur_row = 1;
    while(cur_row < file_row)
    {
        memset(buf, 0x00, sizeof(buf)); 
        fgets(buf,sizeof(buf),fd); 
        cur_row ++;
        
        if(strstr(buf, name) != NULL)
        {
            for(i=0; i<5; i++)
            {
                memset(buf, 0x00, sizeof(buf));
                fgets(buf,sizeof(buf),fd);
                if(strstr(buf, "Handlers") != NULL)
                {
                    str = strchr(buf,'event') + 1;
                    strncpy(temp, str, 1);
                    num = (int)(temp[0]-'0');

                    fclose(fd);
                    return num;
                }
            }
        }   
    }
    fclose(fd);
    return -1;
}

