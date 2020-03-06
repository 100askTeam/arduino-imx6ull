/* 
* Filename:    turnOnLED.ino
* Revision:    1.0
* Date:        2020/03/04
* Author:      hceng
* Email:       huangcheng.job@foxmail.com
* Website:     http://www.100ask.net/
* Function:    turn On LED1. 
* Notes:       none.
* Description: 
* 1. 实例化LED,并先关闭；
* 2. 实例IRDA；
* 3. 调用readKey()读取按键状态；
* 4. 如果KEY_1按下，或者长按，打开LED1;
*/
#include <Arduino.h>
#include <led.h>
#include <irda.h>

int main(int argc, char **argv)
{
    int ret;
    LED led(LED1); 
    led.off();
    IRDA irda(GPIO0);
    
    while(1)
    {
        ret = irda.readKey();
        
        if(ret == 0)
        {
            //如果KEY_1按下，或者长按，打开LED1
            if((irda.getCode() == KEY_1) && (irda.getValue() == 1 || irda.getValue() == 2)) 
                led.on();
            else
                led.off();          
        }
    }
    
    return 0;
}
