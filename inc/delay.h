/**
 * @file delay.h
 * @brief Calibrated Delay Routines for 8051 Microcontroller (11.0592 MHz)
 */

#ifndef DELAY_H
#define DELAY_H

/**
 * @brief Generates approximate millisecond delay calibrated for 11.0592 MHz crystal.
 * @param ms Delay duration in milliseconds
 */
void Delay_ms(unsigned int ms);

#endif /* DELAY_H */
