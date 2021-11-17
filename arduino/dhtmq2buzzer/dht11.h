#ifndef DHT11_GUARD
#define DHT11_GUARD

#include "C:\Users\User\AppData\Local\Arduino15\packages\arduino\hardware\avr\1.8.3\cores\arduino\Arduino.h"

class DHT11
{
  private:
    int dataPin;

    /* Number of transitions (state changes) on dataPin during DHT11 transfer */
    volatile static int dht11_trans_cnt;
    /* The last time when dataPin changed its state */
    volatile static long prev_dht11_change;
    /* Array to store timings between pin transitions (state changes) */
    volatile static long dht11_data_time[100];

    /* ISR - to call at every pin state change */
    static void dht11DataChange() ;

  public:
    /* CLass constructor */
    DHT11( int dataPin );
    /* Read from DHT11 function */
    bool read( uint16_t &temp, uint16_t &humidity ) ;
} ;

#endif