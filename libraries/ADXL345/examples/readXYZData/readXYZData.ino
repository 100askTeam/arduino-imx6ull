/* 
* Filename:    readXYZData.ino
* Revision:    1.0
* Date:        2019/09/01
* Author:      hceng
* Email:       huangcheng.job@foxmail.com
* Website:     http://www.100ask.net/
* Function:    Read ADXL345 X、Y、Z data.
* Notes:       none.
* Description: 
* 1. 实例化ADXL345，传入参数为对应的SPI接口编号；
* 2. 在循环里，调用readData()获取数据；
* 3. getXValue()、getYValue()、getZValue()获取传感器X轴、Y轴、Z轴状态，并打印；
*/
#include <Arduino.h>
#include <adxl345.h>

int main(int argc, char **argv)
{
    ADXL345 adxl345(SPI_A);

    while(1)
    {
        adxl345.readData();
          
        cout << "X: " << setw(4) << adxl345.getXValue() 
          <<  "  Y: " << setw(4) << adxl345.getYValue() 
          <<  "  Z: " << setw(4) << adxl345.getZValue() << endl;

        msleep(200);    
    }
    
    return 0;
}
