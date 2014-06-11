/*
 * PulseReadTimer.h
 */
 
#ifndef PULSE_READ_TIMER_H
#define PULSE_READ_TIMER_H


// Pins Configuration
#define CHANNEL_COUNT  6

// Pins 4 Channel
#define PIN_THRO    A0
#define PIN_AILE    A1
#define PIN_ELEV    A2
#define PIN_RUDD    A3
// Pins 6 Channel
#define PIN_GEAR    A4
#define PIN_AUX1    A5
// Reserved future Use 8 Channel
#define PIN_AUX2    A6
#define PIN_AUX3    A7

// i2c Configuration
#define I2C_ADDRESS  7


// PROTO
void Setup_Channel();
inline void Read_Channel();
void Setup_Timer();
void Clear_Values();
void Clear_Counter();
void Setup_i2c();
void i2c_Request();

#endif // PULSE_READ_TIMER_H

