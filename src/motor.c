/**
 * @file motor.c
 * @brief L298N DC Motor Driver Control Implementation with Soft-Start Ramping
 */

#include "bsp_8051.h"
#include "motor.h"
#include "pwm.h"
#include "delay.h"

static MotorSpeed_t active_speed = MOTOR_STATE_STOP;

static unsigned char SpeedToDuty(MotorSpeed_t speed)
{
    switch (speed)
    {
        case MOTOR_STATE_LOW:  return PWM_DUTY_LOW;
        case MOTOR_STATE_MED:  return PWM_DUTY_MED;
        case MOTOR_STATE_HIGH: return PWM_DUTY_HIGH;
        case MOTOR_STATE_STOP:
        default:               return PWM_MIN_DUTY;
    }
}

void Motor_Init(void)
{
    PWM_OUT = 0;
    PWM_Init();
    Motor_Stop();
}

void Motor_SetSpeed(MotorSpeed_t speed)
{
    active_speed = speed;
    if (speed == MOTOR_STATE_STOP)
    {
        Motor_Stop();
    }
    else
    {
        PWM_SetDuty(SpeedToDuty(speed));
        PWM_Enable(1);
    }
}

void Motor_SetSpeedRamped(MotorSpeed_t target_speed, unsigned int step_delay_ms)
{
    unsigned char start_duty = SpeedToDuty(active_speed);
    unsigned char end_duty   = SpeedToDuty(target_speed);

    if (start_duty == end_duty)
    {
        return;
    }

    PWM_Enable(1);

    if (start_duty < end_duty)
    {
        /* Accelerate smoothly */
        unsigned int d;
        for (d = start_duty; d <= end_duty; d += 5)
        {
            PWM_SetDuty((unsigned char)d);
            Delay_ms(step_delay_ms);
        }
    }
    else
    {
        /* Decelerate smoothly */
        int d;
        for (d = (int)start_duty; d >= (int)end_duty; d -= 5)
        {
            if (d < 0) d = 0;
            PWM_SetDuty((unsigned char)d);
            Delay_ms(step_delay_ms);
        }
    }

    Motor_SetSpeed(target_speed);
}

MotorSpeed_t Motor_GetCurrentSpeed(void)
{
    return active_speed;
}

void Motor_Stop(void)
{
    active_speed = MOTOR_STATE_STOP;
    PWM_Enable(0);
    PWM_OUT = 0;
}
