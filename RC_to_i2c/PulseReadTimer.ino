// PulseRead Timer

/*
 * INCLUDE
 */
#include "PulseDebug.h"
#include "PulseReadTimer.h"
#include <Arduino.h>
#include <Wire.h>

uint8_t  PIN_MASK;
uint8_t  PIN_BIT_THRO;
uint8_t  PIN_BIT_AILE;
uint8_t  PIN_BIT_ELEV;
uint8_t  PIN_BIT_RUDD;
uint8_t  PIN_BIT_GEAR;
uint8_t  PIN_BIT_AUX1;
uint8_t  PIN_BIT_AUX2;
uint8_t  PIN_BIT_AUX3;
uint8_t  PIN_PORT;

volatile uint8_t  PIN_STATE_PREV;
volatile uint8_t  VAL_THRO;
volatile uint8_t  VAL_AILE;
volatile uint8_t  VAL_ELEV;
volatile uint8_t  VAL_RUDD;
volatile uint8_t  VAL_GEAR;
volatile uint8_t  VAL_AUX1;
volatile uint8_t  VAL_AUX2;
volatile uint8_t  VAL_AUX3;

volatile unsigned long  VAL_THRO_CNT;
volatile unsigned long  VAL_AILE_CNT;
volatile unsigned long  VAL_ELEV_CNT;
volatile unsigned long  VAL_RUDD_CNT;
volatile unsigned long  VAL_GEAR_CNT;
volatile unsigned long  VAL_AUX1_CNT;
volatile unsigned long  VAL_AUX2_CNT;
volatile unsigned long  VAL_AUX3_CNT;

#ifdef DEBUG_SER
unsigned long LOOP_SHOW;
#endif // DEBUG_SER

/*
 * SETUP
 */
void setup()
{
  Setup_Channel();
  Clear_Values();
  Clear_Counter();
  //Setup_Timer();
  #ifdef DEBUG_SER
  LOOP_SHOW = 0;
  #endif //DEBUG_SER
  Setup_i2c();
  
  #ifdef DEBUG_SER
  Serial.begin(115200);
  #endif // DEBUG_SER
  
  DBG("Setup done.");
}
 
/*
 * LOOP
 */
void loop()
{
  Read_Channel();
  
  #ifdef DEBUG_SER
  
  LOOP_SHOW++;
  
  if (LOOP_SHOW > 1000)
  {
    LOOP_SHOW = 0;
    
    DBG("THRO = ");
    DBG(VAL_THRO);
    DBG("  AILE = ");
    DBG(VAL_AILE);
    DBG("  ELEV = ");
    DBG(VAL_ELEV);
    DBG("  RUDD = ");
    DBG(VAL_RUDD);
    
    DBG("  GEAR = ");
    DBG(VAL_GEAR);
    DBG("  AUX1 = ");
    DBG(VAL_AUX1);
    DBG("  AUX2 = ");
    DBG(VAL_AUX2);
    DBG("  AUX3 = ");
    DBG(VAL_AUX3);
    
    DBGLN("");
  }
  
  #endif // DEBUG_SER
}




/*
 * Setup Channel
 */
void Setup_Channel()
{
  // Set Bitmask
  PIN_MASK = 0;
  
  // Get Port all on same
  PIN_PORT = digitalPinToPort(PIN_THRO);
  
  // 4 Channel
  if (CHANNEL_COUNT >= 4)
  {
    pinMode(PIN_THRO, INPUT);
    PIN_BIT_THRO = digitalPinToBitMask(PIN_THRO);
    PIN_MASK |= PIN_BIT_THRO;
    
    pinMode(PIN_AILE, INPUT);
    PIN_BIT_AILE = digitalPinToBitMask(PIN_AILE);
    PIN_MASK |= PIN_BIT_AILE;
    
    pinMode(PIN_ELEV, INPUT);
    PIN_BIT_ELEV = digitalPinToBitMask(PIN_ELEV);
    PIN_MASK |= PIN_BIT_ELEV;
    
    pinMode(PIN_RUDD, INPUT);
    PIN_BIT_RUDD = digitalPinToBitMask(PIN_RUDD);
    PIN_MASK |= PIN_BIT_RUDD;
  }
  // 6 Channel
  if (CHANNEL_COUNT >= 6)
  {
    pinMode(PIN_GEAR, INPUT);
    PIN_BIT_GEAR = digitalPinToBitMask(PIN_GEAR);
    PIN_MASK |= PIN_BIT_GEAR;
    
    pinMode(PIN_AUX1, INPUT);
    PIN_BIT_AUX1 = digitalPinToBitMask(PIN_AUX1);
    PIN_MASK |= PIN_BIT_AUX1;
  }
  // 8 Channel reserved
  if (CHANNEL_COUNT == 8)
  {
    pinMode(PIN_AUX2, INPUT);
    PIN_BIT_AUX2 = digitalPinToBitMask(PIN_AUX2);
    PIN_MASK |= PIN_BIT_AUX2;
    
    pinMode(PIN_AUX3, INPUT);
    PIN_BIT_AUX3 = digitalPinToBitMask(PIN_AUX3);
    PIN_MASK |= PIN_BIT_AUX3;
  }
  
  // Clear State
  PIN_STATE_PREV = 0;
}

/*
 * Clear Values
 */
void Clear_Values()
{
  // 4 Channel
  if (CHANNEL_COUNT >= 4)
  {
    VAL_THRO = 0;
    VAL_AILE = 0;
    VAL_ELEV = 0;
    VAL_RUDD = 0;
  }
  // 6 Channel
  if (CHANNEL_COUNT >= 6)
  {
    VAL_GEAR = 0;
    VAL_AUX1 = 0;
  }
  // 8 Channel reserved
  if (CHANNEL_COUNT == 8)
  {
    VAL_AUX2 = 0;
    VAL_AUX3 = 0;
  }
}

/*
 * Clear Counter
 */
void Clear_Counter()
{
  // 4 Channel
  if (CHANNEL_COUNT >= 4)
  {
    VAL_THRO_CNT = 0;
    VAL_AILE_CNT = 0;
    VAL_ELEV_CNT = 0;
    VAL_RUDD_CNT = 0;
  }
  // 6 Channel
  if (CHANNEL_COUNT >= 6)
  {
    VAL_GEAR_CNT = 0;
    VAL_AUX1_CNT = 0;
  }
  // 8 Channel reserved
  if (CHANNEL_COUNT == 8)
  {
    VAL_AUX2_CNT = 0;
    VAL_AUX3_CNT = 0;
  }
}

/*
 * Read All Channel
 */
inline void Read_Channel()
{
  volatile register uint8_t  PIN_STATE_CUR = 0;
  register uint8_t  PIN_FALL;
  
  PIN_STATE_CUR = *portInputRegister(PIN_PORT);
  
  // 4 Channel
  if ((PIN_STATE_CUR & PIN_BIT_THRO) == PIN_BIT_THRO)
  {
    VAL_THRO_CNT++;
  }
  if ((PIN_STATE_CUR & PIN_BIT_AILE) == PIN_BIT_AILE)
  {
    VAL_AILE_CNT++;
  }
  if ((PIN_STATE_CUR & PIN_BIT_ELEV) == PIN_BIT_ELEV)
  {
    VAL_ELEV_CNT++;
  }
  if ((PIN_STATE_CUR & PIN_BIT_RUDD) == PIN_BIT_RUDD)
  {
    VAL_RUDD_CNT++;
  }
  // 6 Channel
  if (CHANNEL_COUNT >= 6)
  {
    if ((PIN_STATE_CUR & PIN_BIT_GEAR) == PIN_BIT_GEAR)
    {
      VAL_GEAR_CNT++;
    }
    if ((PIN_STATE_CUR & PIN_BIT_AUX1) == PIN_BIT_AUX1)
    {
      VAL_AUX1_CNT++;
    }
  }
  // 8 Channel
  if (CHANNEL_COUNT == 8)
  {
    if ((PIN_STATE_CUR & PIN_BIT_AUX2) == PIN_BIT_AUX2)
    {
      VAL_AUX2_CNT++;
    }
    if ((PIN_STATE_CUR & PIN_BIT_AUX3) == PIN_BIT_AUX3)
    {
      VAL_AUX3_CNT++;
    }
  }
  
  PIN_FALL = ~PIN_STATE_CUR & PIN_STATE_PREV;
  
  // 4 Channel
  if ((PIN_FALL & PIN_BIT_THRO) == PIN_BIT_THRO)
  {
    VAL_THRO = VAL_THRO_CNT;
    VAL_THRO_CNT = 0;
  }
  if ((PIN_FALL & PIN_BIT_AILE) == PIN_BIT_AILE)
  {
    VAL_AILE = VAL_AILE_CNT;
    VAL_AILE_CNT = 0;
  }
  if ((PIN_FALL & PIN_BIT_ELEV) == PIN_BIT_ELEV)
  {
    VAL_ELEV = VAL_ELEV_CNT;
    VAL_ELEV_CNT = 0;
  }
  if ((PIN_FALL & PIN_BIT_RUDD) == PIN_BIT_RUDD)
  {
    VAL_RUDD = VAL_RUDD_CNT;
    VAL_RUDD_CNT = 0;
  }
  // 6 Channel
  if (CHANNEL_COUNT >= 6)
  {
    if ((PIN_FALL & PIN_BIT_GEAR) == PIN_BIT_GEAR)
    {
      VAL_GEAR = VAL_GEAR_CNT;
      VAL_GEAR_CNT = 0;
    }
    if ((PIN_FALL & PIN_BIT_AUX1) == PIN_BIT_AUX1)
    {
      VAL_AUX1 = VAL_AUX1_CNT;
      VAL_AUX1_CNT = 0;
    }
  }
  // 8 Channel
  if (CHANNEL_COUNT == 8)
  {
    if ((PIN_FALL & PIN_BIT_AUX2) == PIN_BIT_AUX2)
    {
      VAL_AUX2 = VAL_AUX2_CNT;
      VAL_AUX2_CNT = 0;
    }
    if ((PIN_FALL & PIN_BIT_AUX3) == PIN_BIT_AUX3)
    {
      VAL_AUX3 = VAL_AUX3_CNT;
      VAL_AUX3_CNT = 0;
    }
  }
  
  PIN_STATE_PREV = PIN_STATE_CUR;
    
}

/*
 * Timer
 */
void Setup_Timer()
{
  cli();

  TCCR1A = 0;          // normal operation
  TCCR1B = _BV(WGM12) | _BV(CS10);   // CTC, no prescaling
  OCR1A =  10;       // compare A register value (1000 * clock speed)
  TIMSK1 = _BV (OCIE1A);             // interrupt on Compare A Match




/*
  // set up timer 1
  TCCR1B &= 0b11111000 | 1;
  // enable overflow interrupt
  TIMSK1 |= 0b00000001;
*/

  sei();
  
}

/*
 * ISR TIMER 1 COMPA
 */
ISR( TIMER1_COMPA_vect ) // TIMER1_OVF_vect
{
  Read_Channel();
}

/*
 * Setup i2C
 */
void Setup_i2c()
{
  Wire.begin(I2C_ADDRESS);
  Wire.onRequest(i2c_Request);
}

/*
 * i2c Request
 */
void i2c_Request()
{
  uint8_t  VAL_DATA[8];
 
  // Fill
  VAL_DATA[0] = VAL_THRO;
  VAL_DATA[1] = VAL_AILE;
  VAL_DATA[2] = VAL_ELEV;
  VAL_DATA[3] = VAL_RUDD;
  VAL_DATA[4] = VAL_GEAR;
  VAL_DATA[5] = VAL_AUX1;
  VAL_DATA[6] = VAL_AUX2;
  VAL_DATA[7] = VAL_AUX3;
  
  // Return all Values via i2c
  Wire.write(VAL_DATA, 8);
  
}

