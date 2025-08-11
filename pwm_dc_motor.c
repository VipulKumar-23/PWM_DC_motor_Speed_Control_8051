#include <reg51.h>

/**
 * ============================================================================
 * 8051 Microcontroller - PWM-Based DC Motor Speed Controller
 * ============================================================================
 * Target MCU   : AT89C51 / AT89S51 / standard 8051
 * Oscillator   : 11.0592 MHz Crystal
 * Motor Driver : L298N Dual H-Bridge Driver
 * ============================================================================
 */

/* Pin Allocations (Port 0) */
sbit PWM_Pin = P0^0;    /* PWM output to L298N (IN1 / ENA) */
sbit low     = P0^4;    /* Push Button: Low Speed (~40% Duty Cycle) */
sbit medium  = P0^5;    /* Push Button: Medium Speed (~60% Duty Cycle) */
sbit high    = P0^6;    /* Push Button: High Speed (100% Duty Cycle) */
sbit off     = P0^7;    /* Push Button: Motor Stop */

/* Function Declarations */
void InitPWM_timer(void);

/* Global Variables */
unsigned char PWM = 0;   /* 8-bit PWM Duty Cycle Register (0 - 255) */
unsigned int temp = 0;   /* Timer reload calculation register */
char a = 1;             /* Motor Run State: 0 = Running, 1 = Stopped */

int main(void)
{
    /* Initialize switch pins as inputs by writing logic 1 */
    low     = 1;
    medium  = 1;
    high    = 1;
    off     = 1;
    PWM_Pin = 0;

    InitPWM_timer();

    while (1)
    {
        /* Active-LOW button detection (External Pull-up configuration) */
        if (low == 0)
        {
            PWM = 102; /* ~40% Duty Cycle */
            a = 0;
        }
        else if (medium == 0)
        {
            PWM = 153; /* ~60% Duty Cycle */
            a = 0;
        }
        else if (high == 0)
        {
            PWM = 255; /* 100% Duty Cycle */
            a = 0;
        }
        else if (off == 0)
        {
            a = 1;
            PWM_Pin = 0;
        }
    }
}

/**
 * @brief Initialize 8051 Timer 0 in Mode 1 (16-bit timer)
 */
void InitPWM_timer(void)
{
    TMOD &= 0xF0;
    TMOD |= 0x01; /* Timer 0 in 16-bit timer mode */

    TH0 = 0x00;
    TL0 = 0x00;

    ET0 = 1;      /* Enable Timer 0 interrupt */
    EA  = 1;      /* Enable global interrupts */
    TR0 = 1;      /* Start Timer 0 */
}

/**
 * @brief Timer 0 Interrupt Service Routine (Vector 1) for PWM Generation
 */
void Timer0_ISR(void) interrupt 1
{
    TR0 = 0; /* Halt timer */

    if (PWM_Pin == 1 && a == 0)
    {
        PWM_Pin = 0;
        temp = (255 - PWM);
        TH0  = 0xFF;
        TL0  = (unsigned char)(0xFF - temp);
    }
    else if (PWM_Pin == 0 && a == 0)
    {
        PWM_Pin = 1;
        temp = PWM;
        TH0  = 0xFF;
        TL0  = (unsigned char)(0xFF - temp);
    }

    TF0 = 0; /* Clear overflow flag */
    TR0 = 1; /* Restart timer */
}
