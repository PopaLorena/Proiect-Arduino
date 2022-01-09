#ifndef DHT11_GUARD
#define DHT11_GUARD


#include <arduino.h>
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
    // static void dht11DataChange();   <<ARDUINO LIBRARY IMPLEMENTATION>>

    /* Parameters for register implementation */
    volatile static int ovfl_iterations;
    volatile static int resp_delay_match;
    
  public:
    
   
    DHT11( int dataPin ){
       // Set the pin direction as output by default
    DDRD |= (1 << dataPin);

    // Reset the Timer2 registers
    TCCR2A = 0x00; // set the normal compare output mode
    TCCR2B = 0x00;
    TCNT2 = 0x00;

    // Set up the Timer2 registers
    TCCR2B = 0x05; // set the clock select prescaler as clk/128
    TIMSK2 |= (1 << 0); // overflow interrupt enable
    OCR2A = 0x05;  // output compare register
    }
 
    /* Read from DHT11 function */
    bool read( uint16_t &temp, uint16_t &humidity ) ;
} ;

#endif
