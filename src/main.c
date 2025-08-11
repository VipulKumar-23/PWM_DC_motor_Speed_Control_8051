/**
 * @file main.c
 * @brief Main Application Loop - 8051 PWM Motor Speed Controller
 */

#include "bsp_8051.h"
#include "motor.h"
#include "pwm.h"

static void Hardware_Init(void)
{
    /* Set push button pins as inputs (write 1 to 8051 quasi-bidirectional port pins) */
    BTN_LOW  = 1;
    BTN_MED  = 1;
    BTN_HIGH = 1;
    BTN_STOP = 1;

    Motor_Init();
}

int main(void)
{
    Hardware_Init();

    while (1)
    {
        /* Active-LOW button detection (pull-up resistor configuration) */
        if (BTN_LOW == 0)
        {
            Motor_SetSpeed(MOTOR_STATE_LOW);
        }
        else if (BTN_MED == 0)
        {
            Motor_SetSpeed(MOTOR_STATE_MED);
        }
        else if (BTN_HIGH == 0)
        {
            Motor_SetSpeed(MOTOR_STATE_HIGH);
        }
        else if (BTN_STOP == 0)
        {
            Motor_Stop();
        }
    }
}
