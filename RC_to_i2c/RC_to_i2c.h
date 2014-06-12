/*
 * RC_to_i2c.h
 */
 
#ifndef RC_TO_I2C_H
#define RC_TO_I2C_H


// Pins Configuration (4,6,8)
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
void Clear_Values();
void Clear_Counter();
void Setup_i2c();
void i2c_Request();

#endif // RC_TO_I2C_H

