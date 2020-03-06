/* 
* Filename:    stepperMotor.ino
* Revision:    1.0
* Date:        2020/03/04
* Author:      hceng
* Email:       huangcheng.job@foxmail.com
* Website:     http://www.100ask.net/
* Function:    Driving stepper motor. 
* Notes:       none.
* Description: 
* 1. 实例化MOTOR；
* 2. 调用setSpeed()设置电机转速，范围（1~10）；
* 3. 调用motorForward()设置电机正转，512为一圈；
* 4. 调用motorStop()设置电机停止转动；
* 5. 调用motorReverse()设置电机反向转动，512为一圈；
*/
#include <Arduino.h>
#include <motor.h>

int main(int argc, char **argv)
{
    MOTOR motor;
    
    motor.setSpeed(2); //1~10

    motor.motorForward(512); //正转一圈
    motor.motorStop(); //停止

    motor.motorReverse(512); //反转一圈
    motor.motorStop(); //停止 
    
    return 0;
}

