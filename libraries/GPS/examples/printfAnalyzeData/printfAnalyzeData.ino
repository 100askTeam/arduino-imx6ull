/* 
* Filename:    printfAnalyzeData.ino
* Revision:    1.0
* Date:        2020/03/04
* Author:      hceng
* Email:       huangcheng.job@foxmail.com
* Website:     http://www.100ask.net/
* Function:    Get GPS Analyze data.
* Notes:       none.
* Description: 
* 1. 实例化GPS，传入参数为对应的UART接口编号；
* 2. 循环里，使用printfAnalyzeData()打印GPS解析过后的数据；
*/
#include <Arduino.h>
#include <gps.h>

int main(int argc, char **argv)
{
    GPS gps(UART_A);
    
    while(1)
    {   
        gps.printfAnalyzeData();    
    } 

    return 0;   
}
