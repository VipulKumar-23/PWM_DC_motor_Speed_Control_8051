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
 * @brief Sets motor operation speed preset.
 * @param speed Speed state preset
 */
void Motor_SetSpeed(MotorSpeed_t speed);

/**
 * @brief Stops motor rotation immediately.
 */
void Motor_Stop(void);

#endif /* MOTOR_H */
