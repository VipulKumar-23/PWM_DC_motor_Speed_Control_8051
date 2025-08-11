/**
 * @file pwm.h
 * @brief Pulse Width Modulation (PWM) Generator using 8051 Timer 0
 */

#ifndef PWM_H
#define PWM_H

/* PWM Resolution: 8-bit (0 - 255) */
#define PWM_MIN_DUTY    0
#define PWM_DUTY_LOW    102  /* ~40% Duty Cycle */
#define PWM_DUTY_MED    153  /* ~60% Duty Cycle */
#define PWM_DUTY_HIGH   255  /* 100% Duty Cycle */

/**
 * @brief Initializes Timer 0 in Mode 1 (16-bit timer) for PWM generation.
 */
void PWM_Init(void);

/**
 * @brief Sets the PWM duty cycle value (0 to 255).
 * @param duty 8-bit duty cycle value
 */
void PWM_SetDuty(unsigned char duty);

/**
 * @brief Enables or disables the PWM output pin.
 * @param state 1 to start/enable output, 0 to stop
 */
void PWM_Enable(unsigned char state);

#endif /* PWM_H */
