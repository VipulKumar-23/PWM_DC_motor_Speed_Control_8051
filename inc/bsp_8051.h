/**
 * @file bsp_8051.h
 * @brief Board Support Package & Pin Definitions for 8051 Microcontroller
 */

#ifndef BSP_8051_H
#define BSP_8051_H

#include <reg51.h>

/* System Clock Definition */
#define FOSC_FREQ_HZ        11059200UL      /* 11.0592 MHz Crystal Oscillator */
#define MACHINE_CYCLE_US    (12.0 / 11.0592)/* ~1.085 microseconds per machine cycle */

/* Pin Definitions - Port 0 */
sbit PWM_OUT   = P0^0;  /* PWM signal output connected to L298N IN1/ENA */
sbit BTN_LOW   = P0^4;  /* Active-LOW input: Speed Low (40% Duty Cycle) */
sbit BTN_MED   = P0^5;  /* Active-LOW input: Speed Medium (60% Duty Cycle) */
sbit BTN_HIGH  = P0^6;  /* Active-LOW input: Speed High (100% Duty Cycle) */
sbit BTN_STOP  = P0^7;  /* Active-LOW input: Motor Stop */

#endif /* BSP_8051_H */
