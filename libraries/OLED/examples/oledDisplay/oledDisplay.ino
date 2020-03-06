/* 
* Filename:    oledDisplay.ino
* Revision:    1.0
* Date:        2020/03/05
* Author:      hceng
* Email:       huangcheng.job@foxmail.com
* Website:     http://www.100ask.net/
* Function:    OLED display.
* Notes:       none.
* Description: 
* 1. 实例化OLED，传入参数为对应的SPI接口编号；
* 2. y为OLED显示高度，总共为8，每行字符占据两行；
* 3. 使用OLEDPrint显示数据，参数为：行位置、列位置、数据内容；
* 4. 如果y小于8，显示数据，超过8则清空显示；
*/
#include <Arduino.h>
#include <oled.h>

int main(int argc, char **argv)
{
    OLED oled(SPI_A);
    int y = 0;

    while(1)
    {
        if(y < 8)
        {
            oled.OLEDPrint(0, y, "1234567890123456"); 
            y += 2;
            sleep(1);   
        }
        else
        {
            y = 0;
            oled.OLEDClearAll();    
            sleep(1);
        }   
    }
    
    return 0;
}
