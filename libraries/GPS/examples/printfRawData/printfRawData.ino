/* 
* Filename:    printfRawData.ino
* Revision:    1.0
* Date:        2020/03/04
* Author:      hceng
* Email:       huangcheng.job@foxmail.com
* Website:     http://www.100ask.net/
* Function:    Get GPS raw data.
* Notes:       none.
* Description: 
* 1. 实例化GPS，传入参数为对应的UART接口编号；
* 2. 使用printfRawData()打印输出原始数据；
*/
#include <Arduino.h>
#include <gps.h>

int main(int argc, char **argv)
{
    GPS gps(UART_A);
    
    while(1)
    {
        gps.printfRawData();   
    }  

    return 0;
}
