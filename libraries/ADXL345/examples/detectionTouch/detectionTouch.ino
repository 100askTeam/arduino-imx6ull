/* 
* Filename:    detectionTouch.ino
* Revision:    1.0
* Date:        2020/03/05
* Author:      hceng
* Email:       huangcheng.job@foxmail.com
* Website:     http://www.100ask.net/
* Function:    Check if touch ADXL345.
* Notes:       none.
* Description: 
* 1. 实例化ADXL345，传入参数为对应的SPI接口编号；
* 2. 在循环里，调用readData()获取数据；
* 3. 通过getTouchValue()获取传感器状态；
* 4. 如果getTouchValue()返回值为0，即没发生触碰(直到上次触碰结束)，再次读取数据，如果为1，打印触碰信息；
*/
#include <Arduino.h>
#include <adxl345.h>

int main(int argc, char **argv)
{
    ADXL345 adxl345(SPI_A);

    while(1)
    {
        adxl345.readData();
        
        while(adxl345.getTouchValue() == 0)
        {
            adxl345.readData();
            if(adxl345.getTouchValue() == 1)
                cout << "You hit it" << endl;
        }
    }
    
    return 0;
}
