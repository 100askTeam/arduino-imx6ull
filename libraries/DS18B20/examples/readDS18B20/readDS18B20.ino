/* 
* Filename:    readDS18B20.ino
* Revision:    1.0
* Date:        2019/09/01
* Author:      hceng
* Email:       huangcheng.job@foxmail.com
* Website:     http://www.100ask.net/
* Function:    Read DS18B20 temperature values. 
* Notes:       none.
* Description: 
* 1. 创建数组变量SerialNum；
* 2. 实例化DS18B20；；
* 3. 调用readSerialNum()读取DS18B20的唯一编号，返回结果保存在SerialNum里，打印出来；(不重要)
* 4. 调用readTemperature()读取DS18B20的温度，并打印；(重要)
* 5. 调用readFamilyCode()读取DS18B20的系列编号，并打印；(不重要)
* 6. 调用readTemperature()读取DS18B20的CRC校验值，并打印；(不重要)
*/
#include <Arduino.h>
#include <ds18b20.h>

int main(int argc, char **argv)
{
    int i;
    unsigned char SerialNum[6];
    
    DS18B20 ds18b20(GPIO0);
    
    ds18b20.readSerialNum(SerialNum);
    cout << "SerialNum: ";
    for (i=0; i<6; i++)
        cout << (int)SerialNum[i];
    cout << endl;
    
    cout << "Temperature: " << ds18b20.readTemperature() << endl;
    cout << "FamilyCode: " <<  ds18b20.readFamilyCode() << endl;
    cout << "CRC: " <<  ds18b20.readCRC() << endl;
    
    return 0;
}



