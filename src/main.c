/**
 * @file main.c
 * @brief Main Application Loop - 8051 PWM Motor Speed Controller with Debouncing
 */

#include "bsp_8051.h"
#include "motor.h"
#include "pwm.h"
#include "delay.h"

#define DEBOUNCE_DELAY_MS   25

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
        /* Active-LOW button detection with software debouncing */
        if (BTN_LOW == 0)
        {
            Delay_ms(DEBOUNCE_DELAY_MS);
            if (BTN_LOW == 0)
            {
                Motor_SetSpeed(MOTOR_STATE_LOW);
                while (BTN_LOW == 0); /* Wait for button release */
            }
        }
        else if (BTN_MED == 0)
        {
            Delay_ms(DEBOUNCE_DELAY_MS);
            if (BTN_MED == 0)
            {
                Motor_SetSpeed(MOTOR_STATE_MED);
                while (BTN_MED == 0); /* Wait for button release */
            }
        }
        else if (BTN_HIGH == 0)
        {
            Delay_ms(DEBOUNCE_DELAY_MS);
            if (BTN_HIGH == 0)
            {
                Motor_SetSpeed(MOTOR_STATE_HIGH);
                while (BTN_HIGH == 0); /* Wait for button release */
            }
        }
        else if (BTN_STOP == 0)
        {
            Delay_ms(DEBOUNCE_DELAY_MS);
            if (BTN_STOP == 0)
            {
                Motor_Stop();
                while (BTN_STOP == 0); /* Wait for button release */
            }
        }
    }
}
