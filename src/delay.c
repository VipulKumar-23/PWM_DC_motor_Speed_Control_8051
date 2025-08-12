/**
 * @file delay.c
 * @brief Software Delay Loop Implementation
 */

#include "delay.h"

void Delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for (i = 0; i < ms; i++)
    {
        /* Loop tuned for 11.0592 MHz crystal (~1.085 us per machine cycle) */
        for (j = 0; j < 112; j++)
        {
            /* 1 ms delay loop */
        }
    }
}
