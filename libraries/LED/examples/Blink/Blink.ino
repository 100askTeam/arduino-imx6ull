/* 
* Filename:    Blink.ino
* Revision:    1.0
* Date:        2020/03/02
* Author:      hceng
* Email:       huangcheng.job@foxmail.com
* Website:     http://www.100ask.net/
* Function:    Timing 1 second flashing LED.
* Notes:       Only support LED1.
* Description: 
* 1. 实例化LED，需指定LED(LED1)；
* 2. 在循环里，每间隔1s，调用on()/off()，控制LED亮灭；  
*/
#include <Arduino.h>
#include <led.h>

int main(int argc, char **argv)
{
    LED led(LED1);

    while(1)
    {
        led.on();  
        sleep(1);
            
        led.off(); 
        sleep(1);
    }
    
    return 0;
}
    

