/* 
* Filename:    readDHT11.ino
* Revision:    1.0
* Date:        2019/09/01
* Author:      hceng
* Email:       huangcheng.job@foxmail.com
* Website:     http://www.100ask.net/
* Function:    Read DHT11 temperature and humidity values. 
* Notes:       none.
* Description: 
* 1. 实例化DHT11，可指定所接GPIO，默认GPIO0；
* 2. 调用readTemperaturey()读取当前环境温度，并打印；
* 3. 调用readHumdity()读取当前环境湿度，并打印；
* 4. 读取间隔需1S以上；
*/
#include <Arduino.h>
#include <dht11.h>

int main(int argc, char **argv)
{
    DHT11 dht11(GPIO0);

    while(1)
    {
        cout << "Temperature: " << dht11.readTemperature() << "'C" << endl;
        cout << "Humdity: " << dht11.readHumdity() << "%" << endl;

        sleep(1);
    }
    
    return 0;
}

