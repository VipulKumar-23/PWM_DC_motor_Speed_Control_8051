/**
 * @file motor.h
 * @brief DC Motor Driver Controller (L298N Interface)
 */

#ifndef MOTOR_H
#define MOTOR_H

typedef enum {
    MOTOR_STATE_STOP = 0,
    MOTOR_STATE_LOW,
    MOTOR_STATE_MED,
    MOTOR_STATE_HIGH
} MotorSpeed_t;

/**
 * @brief Initializes motor driver control pins.
 */
void Motor_Init(void);

/**
 * @brief Sets motor operation speed preset immediately.
 * @param speed Speed state preset
 */
void Motor_SetSpeed(MotorSpeed_t speed);

/**
 * @brief Smoothly transitions motor to target speed to prevent high inrush current.
 * @param target_speed Target speed state preset
 * @param step_delay_ms Delay in milliseconds between duty cycle adjustment steps
 */
void Motor_SetSpeedRamped(MotorSpeed_t target_speed, unsigned int step_delay_ms);

/**
 * @brief Returns the current active motor speed preset.
 * @return Current speed preset
 */
MotorSpeed_t Motor_GetCurrentSpeed(void);

/**
 * @brief Stops motor rotation immediately.
 */
void Motor_Stop(void);

#endif /* MOTOR_H */
