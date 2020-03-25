/* 
* Filename:    turnOffLED.ino
* Revision:    1.0
* Date:        2020/03/03
* Author:      hceng
* Email:       huangcheng.job@foxmail.com
* Website:     http://www.100ask.net/
* Function:    turn Off LED1. 
* Notes:       none.
* Description: 
* 1. 实例化LED；
* 2. 实例KEYBOARD；
* 3. 调用readKey()读取按键状态，并判断返回值；
* 4. 如果KEY1按下，或者长按，关闭LED1;
*/
#include <Arduino.h>
#include <led.h>
#include <gpio.h>
#include <keyboard.h>

int main(int argc, char **argv)
{
    int ret;
    LED led(LED1); 
    KEYBOARD keyboard;
    
    while(1)
    {
        ret = keyboard.readKey();
        
        if (ret == 0)
        {
            //如果KEY1按下，或者长按，关闭LED1
            if((keyboard.getCode() == KEY1) && (keyboard.getValue() == 1 || keyboard.getValue() == 2)) 
                led.off();
            else
                led.on();   
        }
    }
    
    return 0;
}
