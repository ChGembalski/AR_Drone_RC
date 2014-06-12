/*
 * RC_to_i2c_Debug.h
 */
 
#ifndef RC_TO_I2C_DEBUG_H
#define RC_TO_I2C_DEBUG_H

// Uncomment for Debug Output
//#define DEBUG_SER

#ifdef DEBUG_SER

#define DBG(x) Serial.print(x)
#define DBGLN(x) Serial.println(x)

#else

#define DBG(x)
#define DBGLN(x)

#endif // DEBUG_SER

#endif // RC_TO_I2C_DEBUG_H

