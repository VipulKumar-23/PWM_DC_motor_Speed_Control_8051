/**
 * @file pwm.c
 * @brief Pulse Width Modulation (PWM) Implementation via Timer 0 ISR
 */

#include "bsp_8051.h"
#include "pwm.h"

static volatile unsigned char current_duty = 0;
static volatile unsigned char is_enabled   = 0;
static unsigned int timer_reload           = 0;

void PWM_Init(void)
{
    /* Configure Timer 0 in Mode 1 (16-bit Timer/Counter) */
    TMOD &= 0xF0;
    TMOD |= 0x01;

    TH0 = 0x00;
    TL0 = 0x00;

    ET0 = 1;  /* Enable Timer 0 Interrupt */
    EA  = 1;  /* Enable Global Interrupts */
    TR0 = 1;  /* Start Timer 0 */
}

void PWM_SetDuty(unsigned char duty)
{
    current_duty = duty;
}

void PWM_Enable(unsigned char state)
{
    is_enabled = state;
    if (!state)
    {
        PWM_OUT = 0;
    }
}

/**
 * @brief Timer 0 Interrupt Service Routine (Vector 1)
 */
void Timer0_ISR(void) interrupt 1
{
    TR0 = 0; /* Halt timer during reload configuration */

    if (PWM_OUT == 1 && is_enabled)
    {
        PWM_OUT = 0;
        timer_reload = (255 - current_duty);
        TH0 = 0xFF;
        TL0 = (unsigned char)(0xFF - timer_reload);
    }
    else if (PWM_OUT == 0 && is_enabled)
    {
        PWM_OUT = 1;
        timer_reload = current_duty;
        TH0 = 0xFF;
        TL0 = (unsigned char)(0xFF - timer_reload);
    }

    TF0 = 0; /* Clear overflow flag */
    TR0 = 1; /* Restart timer */
}
