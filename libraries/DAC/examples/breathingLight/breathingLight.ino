/* 
* Filename:    breathingLight.ino
* Revision:    1.0
* Date:        2020/03/05
* Author:      hceng
* Email:       huangcheng.job@foxmail.com
* Website:     http://www.100ask.net/
* Function:    DAC implements breathing light.
* Notes:       none.
* Description: 
* 1. 实例化DAC，传入参数为对应的SPI接口编号；
* 2. 定义电压变量val，范围为0 ~ 4.092，这里设置为1.7，即LED刚开始亮的电压值；
* 3. 循环里，当vol小于3.6V，不断增加val值，并调用setVoltage()设置电压，让LED逐渐变亮；
* 4. 之后，当vol大于1.7V，不断减少val值，并调用setVoltage()设置电压，让LED逐渐变暗；
*/
#include <Arduino.h>
#include <dac.h>

int main(int argc, char **argv)
{
    DAC dac(SPI_A);
    float vol = 1.7;//vol range: 0 ~ 4.092

    while(1)
    {
        while(vol < 3.6) //逐渐变亮
        {
            dac.setVoltage(vol);
            vol = vol + 0.01;
            msleep(5);
        }
        
        while(vol > 1.7) //逐渐变暗
        {
            dac.setVoltage(vol);
            vol = vol - 0.01;
            msleep(5);
        }
    } 

    return 0;
}
