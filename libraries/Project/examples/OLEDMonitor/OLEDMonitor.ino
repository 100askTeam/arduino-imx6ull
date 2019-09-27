/*
* Filename:    OLEDMonitor.ino
* Revision:    1.0
* Date:        2019/09/01
* Author:      hceng
* Email:       huangcheng.job@foxmail.com
* Website:     http://www.100ask.net/
* Function:    OLED shows cpu, ram, temperature information.
* Notes:       none.
* Description:
* 1. 实例化OLED、DS18B20；
* 2. 清空OLED显示，第一行显示"System info"；
* 3. 调用getCPUInfo()获取CPU利用率、 numToString()转换为字符串，传给OLEDPrint()显示；
* 4. 调用getMemInfo()获取RAM利用率、 numToString()转换为字符串，传给OLEDPrint()显示；
* 5. 调用readTemperature()获取DS18B20温度、 numToString()转换为字符串，传给OLEDPrint()显示；
*/

#include <Arduino.h>
#include <oled.h>
#include <ds18b20.h>

/*
* Description: 定义结构体CPU_OCCUPY，保存CPU各部分时间  
* Note: none
*/
typedef struct CPU_PACKED
{
    char name[20];
    unsigned int user;    //从系统启动累计到当前时刻，用户态的CPU时间（单位：jiffies），不包含NICED的进程。1 jiffies=10ms
    unsigned int nice;    //从系统启动累计到当前时刻，NICED的进程在用户态下执行时间（单位：jiffies）
    unsigned int system;  //从系统启动累计到当前时刻，进程在内核态的执行时间累积（单位：jiffies）
    unsigned int idle;    //从系统启动累计到当前时刻，空闲时间累积（单位：jiffies）
    unsigned int iowait;  //从系统启动累计到当前时刻，硬盘IO等待时间累积（单位：jiffies）
    unsigned int irq;     //从系统启动累计到当前时刻，硬中断时间（单位：jiffies）
    unsigned int softirq; //从系统启动累计到当前时刻，软中断时间（单位：jiffies）
}CPU_OCCUPY;

/*
* FunctionName:getCPUOccupy
* Purpose: 获取节点/proc/stat内容，保存在cpu_occupy 
* Parameters:cpu_occupy 
* Return: return 0 if sucess,else return -1 
* Note: none
*/
int getCPUOccupy(CPU_OCCUPY *cpu_occupy) 
{
    FILE *fd;
    char buff[256];

    fd = fopen("/proc/stat", "r"); //打开节点/proc/stat
    if(fd == NULL) //如果打开失败
    {
        printf("getCPUOccupy:Can not open file\r\n");
        return -1;
    }

    fgets(buff, sizeof(buff), fd); //获取节点/proc/stat数据保存在buff
    sscanf(buff, "%s %u %u %u %u %u %u %u", cpu_occupy->name, &cpu_occupy->user, &cpu_occupy->nice, &cpu_occupy->system, \
           &cpu_occupy->idle, &cpu_occupy->iowait, &cpu_occupy->irq, &cpu_occupy->softirq); //把buff的数据依次保存到cpu_occupy里
           
    fclose(fd); //关闭节点/proc/stat

    return 0;
}

/*
* FunctionName:getCPUInfo
* Purpose: 获取CPU利用率
* Parameters: 无
* Return: cpu_use CPU利用率
* Note: none
*/
float getCPUInfo(void) 
{
    float cpu_use;
    unsigned long od, nd;
    unsigned long sum, idle;
    CPU_OCCUPY cpu_stat1;
    CPU_OCCUPY cpu_stat2;

    getCPUOccupy(&cpu_stat1); //第一次获取CPU时间
    msleep(500); //间隔时间，需大于10ms
    getCPUOccupy(&cpu_stat2); //第二次获取CPU时间

    od = (unsigned long) (cpu_stat1.user + cpu_stat1.nice + cpu_stat1.system + cpu_stat1.idle 
                         + cpu_stat1.iowait + cpu_stat1.irq + cpu_stat1.softirq); //第一次CPU所有时间
    nd = (unsigned long) (cpu_stat2.user + cpu_stat2.nice + cpu_stat2.system + cpu_stat2.idle
                         + cpu_stat2.iowait + cpu_stat2.irq + cpu_stat2.softirq); //第二次CPU所有时间

    sum = nd - od; //两次采集间隔总时间
    idle = cpu_stat2.idle - cpu_stat1.idle; //增加的空闲时间
    if (sum > 0) //防止除0
        cpu_use = (sum - idle) / sum; //利用率=(总时间-空闲时间)/总时间
    else
        cpu_use = 0;

    return cpu_use;
}

/*
* Description: 定义结构体MEM_PACKED，保存内存的总大小和空闲大小 
* Note: none
*/
typedef struct MEM_PACKED
{
    float total;
    float free;
}MEM_OCCUPY;

/*
* FunctionName:getMemInfo
* Purpose: 获取内存利用率
* Parameters:无 
* Return: info 内存利用率
* Note: none
*/
float getMemInfo(void)
{
    FILE *fd;
    char buf[64], name[32];
    float ram_use;

    MEM_OCCUPY meminfo;
    memset(&meminfo, 0x00, sizeof(MEM_OCCUPY));
    
    fd = fopen("/proc/meminfo", "r"); //打开节点/proc/meminfo
    if(fd == NULL) //如果打开失败
    {
        printf("getMemInfo:Can not open file\r\n");
        return 0;
    }

    memset(buf, 0x00, sizeof(buf)); //清空buf
    fgets(buf, sizeof(buf), fd); //获取节点/proc/meminfo内容
    sscanf(buf, "%s %f %s", name, &meminfo.total, name); //得到第一行总内存
    
    memset(buf, 0x00, sizeof(buf)); //清空buf
    fgets(buf, sizeof(buf), fd); //获取节点/proc/meminfo内容
    sscanf(buf, "%s %f %s", name, &meminfo.free, name); //得到第二行空闲内存

    ram_use = (meminfo.total - meminfo.free) / meminfo.total; //利用率=(总内存-空闲内存)/总内存

    fclose(fd); //关闭节点/proc/meminfo

    return ram_use;
}

/*
* FunctionName:numToString
* Purpose: 数字转字符串
* Parameters:i 
* Return: string 字符串
* Note: none
*/
string numToString(float i)
{
    char str[10];
    
    sprintf(str, "%02.2f", i);
    
    return str;
}

int main(int argc, char **argv)
{
    OLED oled(SPI_A); //实例化OLED
    DS18B20 ds18b20(GPIO0); //实例化DS18B20

    oled.OLEDClearAll(); //清空OLED
    
    oled.OLEDPrint(0, 0, "System info"); //OLED第一行显示System info
    
    while(1)
    {
        oled.OLEDPrint(0, 2, "CPU:" + numToString(getCPUInfo()*100) + "%"); //第二行显示CPU信息
        oled.OLEDPrint(0, 4, "RAM:" + numToString(getMemInfo()*100) + "%"); //第三行显示RAM信息
        oled.OLEDPrint(0, 6, "TEP:" + numToString(ds18b20.readTemperature()) + "'C"); //第四行显示DS18B20信息
        sleep(1);
    }
    
    return 0;
}