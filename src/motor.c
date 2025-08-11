/**
 * @file motor.c
 * @brief L298N DC Motor Driver Control Implementation
 */

#include "bsp_8051.h"
#include "motor.h"
#include "pwm.h"

void Motor_Init(void)
{
    PWM_OUT = 0;
    PWM_Init();
    Motor_Stop();
}

void Motor_SetSpeed(MotorSpeed_t speed)
{
    switch (speed)
    {
        case MOTOR_STATE_LOW:
            PWM_SetDuty(PWM_DUTY_LOW);
            PWM_Enable(1);
            break;

        case MOTOR_STATE_MED:
            PWM_SetDuty(PWM_DUTY_MED);
            PWM_Enable(1);
            break;

        case MOTOR_STATE_HIGH:
            PWM_SetDuty(PWM_DUTY_HIGH);
            PWM_Enable(1);
            break;

        case MOTOR_STATE_STOP:
        default:
            Motor_Stop();
            break;
    }
}

void Motor_Stop(void)
{
    PWM_Enable(0);
    PWM_OUT = 0;
}
