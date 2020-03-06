/* 
* Filename:    getDistance.ino
* Revision:    1.0
* Date:        2020/03/04
* Author:      hceng
* Email:       huangcheng.job@foxmail.com
* Website:     http://www.100ask.net/
* Function:    Measuring distance. 
* Notes:       none.
* Description: 
* 1. 实例化SR04；
* 2. 循环里，调用getDistance()获取距离数据，打印对应结果；
*/
#include <Arduino.h>
#include <sr04.h>

int main(int argc, char **argv)
{
    SR04 sr04;

    while(1)
    {
        cout << "distance: " << sr04.getDistance() << "cm" <<endl;
        msleep(200);
    }
    
    return 0;
}

