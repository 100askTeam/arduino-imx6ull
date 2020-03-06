/* 
* Filename:    readBrightness.ino
* Revision:    1.0
* Date:        2020/03/04
* Author:      hceng
* Email:       huangcheng.job@foxmail.com
* Website:     http://www.100ask.net/
* Function:    Get the voltage value corresponding to the brightness.
* Notes:       none.
* Description: 
* 1. 实例化ADC，传入参数为对应的ADC接口编号；
* 2. 循环里，使用getValue()获取光敏电阻两端的电压(单位:mv)，并打印；
*/
#include <Arduino.h>
#include <adc.h>

int main(int argc, char **argv)
{
    ADC adc(ADC_B);
    
    while(1)
    {
        cout << "voltage: " << adc.getValue()  << "mv" << endl;
        sleep(1);
    }
    
    return 0;
}
