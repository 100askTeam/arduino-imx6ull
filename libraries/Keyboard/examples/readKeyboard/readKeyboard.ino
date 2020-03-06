/* 
* Filename:    readKeyboard.ino
* Revision:    1.0
* Date:        2020/03/03
* Author:      hceng
* Email:       huangcheng.job@foxmail.com
* Website:     http://www.100ask.net/
* Function:    Get Keyboard value. 
* Notes:       none.
* Description: 
* 1. 实例化KEYBOARD(KEY1、KEY2)；
* 2. 循环里，调用readKey()读取按键状态，并判断返回值；
* 3. 调用getCode()获取按键编号code，调用getValue()获取按键值value，并打印：
* 4. 按键编号对应如下：
*    KEY1 2
*    KEY2 3
* 5. 按键值含义如下：
*    松开按键 0
*    按下按键 1
*    长按按键 2
*/
#include <Arduino.h>
#include <keyboard.h>

int main(int argc, char **argv)
{
    int ret;
	
    KEYBOARD keyboard;
    
    while(1)
    {
        ret = keyboard.readKey();
        
        if (ret == 0)
            cout << "Code:" << keyboard.getCode() << " Value:" << keyboard.getValue() << endl;  
    }
    
    return 0;
}

