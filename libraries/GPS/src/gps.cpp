
#include "gps.h"

GPS::GPS(int num)
{
    UART uart(num);
}


int GPS::readRawData(char *data)
{
    char read_tmp[256];
    
    while(1)
    {
        memset(read_tmp,0,sizeof(read_tmp));
        
        if (this->reviceData(read_tmp, sizeof(read_tmp)) == 0)
        {
            if(read_tmp[0]=='$') //start
            { 
                memcpy(data, read_tmp, sizeof(read_tmp)); //copy
                return 1;
            }
            else
                return -1;
        }
        else
        {
            msleep(200);
            return -1; //no data
        }       
    }
    return 0;
}

int GPS::readAnalyzeData(float *data)
{
    char read_data[256];
    char temp_data[20];
    float temp_float;
    int m, n;

    memset(read_data, 0, sizeof(read_data));
    
    if (readRawData(read_data))
    {
        if (read_data[3] == 'R')
        {
            if (read_data[17] == 'V')
                printf("Invalid data, Please move the module to the open area and wait 3-5 minutes.\n");    
            else
            {
                //latitude
                memset(temp_data,0,sizeof(temp_data));
                strncpy(temp_data, read_data+20, 10);
                //temp_data[11] = '\0'; 
                temp_float = atof(temp_data);
                m = (int)temp_float/100;
                n = (int)((temp_float-m*100)*100000/60);
                data[0] = (float)m + (float)n/100000;
                //if(read_data[30] == 'S')
                    //data[0] = data[0] * (-1);
            
                //longitude
                memset(temp_data,0,sizeof(temp_data));
                strncpy(temp_data, read_data+33, 11);
                temp_float = atof(temp_data);
                m = (int)temp_float/100;
                n = (int)((temp_float-m*100)*100000/60);
                data[1] = (float)m + (float)n/100000;
                
                //if(read_data[44] == 'W')
                    //data[1] = data[1] * (-1);         
            }
        }
    }
    
    return 0;
}


void GPS::printfRawData(void)
{
    memset(this->RawData,0,sizeof(this->RawData));
    
    if(this->readRawData(this->RawData))
        cout << this->RawData << endl;    
    
}

//$GPRMC,075303.00,A,2239.08762,N,11407.16857,E,0.363,,290419,,,A*7C
void GPS::printfAnalyzeData()
{
    char read_data[256];
    char temp_data[20];
    float temp_float;
    int m, n;

    memset(read_data, 0, sizeof(read_data));
    
    if (readRawData(read_data))
    {
        if (read_data[3] == 'R')
        {
            if (read_data[17] == 'V')
                printf("Invalid data, Please move the module to the open area and wait 3-5 minutes.\n");    
            else
            {
                //latitude
                if(read_data[30] == 'S')
                    printf("-");
                memset(temp_data,0,sizeof(temp_data));
                strncpy(temp_data, read_data+20, 10);
                //temp_data[11] = '\0'; 
                temp_float = atof(temp_data);
                m = (int)temp_float/100;
                n = (int)((temp_float-m*100)*100000/60);
                printf("%d.%d , ", m, n);
            
                //longitude
                if(read_data[44] == 'W')
                    printf("-");
                memset(temp_data,0,sizeof(temp_data));
                strncpy(temp_data, read_data+33, 11);
                temp_float = atof(temp_data);
                m = (int)temp_float/100;
                n = (int)((temp_float-m*100)*100000/60);
                printf("%d.%d\n", m, n);
            }
        }
    }
}



GPS::~GPS()
{

}