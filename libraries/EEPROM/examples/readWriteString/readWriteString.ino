/* 
* Filename:    readWriteString.ino
* Revision:    1.0
* Date:        2019/09/01
* Author:      hceng
* Email:       huangcheng.job@foxmail.com
* Website:     http://www.100ask.net/
* Function:    Read and write string form EEPROM.
* Notes:       none.
* Description: 
* 1. 定义发送/接收字符串，并设置待发送数据；
* 2. 实例化EEPROM，传入参数为对应的I2C接口编号；
* 3. 调用writeEEPROM()写EEPROM，参数为：待写起始地址、待写字符串长度、待写数据；
* 4. 调用readEEPROM()读EEPROM，参数为：待读起始地址、待读字符串长度、待保存位置；
* 5. 打印接收的数据，观察是否和写的数据一致；  
*/
#include <Arduino.h>
#include <eeprom.h>

int main(int argc, char **argv)
{
    int ret;
    string txString = "www.100ask.net";
    string rxString;

    EEPROM eeprom(I2C_A);

    ret = eeprom.writeEEPROM(0, txString.size(), txString);
    if (ret < 0)
    {
        cout << "writeEEPROM error" << endl;
        return -1;
    }
    
   ret =  eeprom.readEEPROM(0, txString.size(), rxString);
    if (ret < 0)
    {
        cout << "readEEPROM error" << endl;
        return -1;
    }
    
    cout << "rxString: " << rxString << endl;
    
    return 0;
}
