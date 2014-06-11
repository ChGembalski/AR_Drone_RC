/*
 * PulseDebug.h
 */
 
#ifndef PULSE_DEBUG_H
#define PULSE_DEBUG_H

// Uncomment for Debug Output
//#define DEBUG_SER

#ifdef DEBUG_SER

#define DBG(x) Serial.print(x)
#define DBGLN(x) Serial.println(x)

#else

#define DBG(x)
#define DBGLN(x)

#endif // DEBUG_SER

#endif // PULSE_DEBUG_H

