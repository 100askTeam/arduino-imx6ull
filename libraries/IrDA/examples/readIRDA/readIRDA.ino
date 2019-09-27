/* 
* Filename:    readIRDA.ino
* Revision:    1.0
* Date:        2019/09/01
* Author:      hceng
* Email:       huangcheng.job@foxmail.com
* Website:     http://www.100ask.net/
* Function:    Get IrDA value. 
* Notes:       none.
* Description: 
* 1. 实例化IRDA；
* 2. 调用readKey()读取按键，并判断返回值；
* 3. 调用getCode()获取按键编号code，调用getValue()获取按键值value，并打印：
* 4. 按键编号对应如下：
*    KEY_POWER         116
*    KEY_MENU          139
*    KEY_INFO          358
*    KEY_VOLUMEUP      115
*    KEY_BACK          158
*    KEY_PREVIOUS      412
*    KEY_PLAYPAUSE     164
*    KEY_NEXT          407
*    KEY_0             11           
*    KEY_VOLUMEDOWN    114
*    KEY_CLEAR         355
*    KEY_1             2             
*    KEY_2             3
*    KEY_3             4
*    KEY_4             5
*    KEY_5             6
*    KEY_6             7
*    KEY_7             8
*    KEY_8             9
*    KEY_9             10  
*        
* 5. 按键值含义如下：
*    松开按键          0
*    按下按键          1
*    长按按键          2
*/
#include <Arduino.h>
#include <irda.h>

int main(int argc, char **argv)
{
    int ret;
    IRDA irda(GPIO0);
    
    while(1)
    {
        ret = irda.readKey();
        
        if(ret == 0)
            cout << "Code:" << irda.getCode() << " Value:" << irda.getValue() << endl;
    }
    
    return 0;
}

