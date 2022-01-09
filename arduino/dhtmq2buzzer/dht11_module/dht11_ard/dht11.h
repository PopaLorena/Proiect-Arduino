#ifndef DHT11_GUARD
#define DHT11_GUARD


#include <arduino.h>
class DHT11
{
  private:
    
    
  public:
    int dataPin;
   
    DHT11( int dataPin );
 
    /* Read from DHT11 function */
    bool read( uint16_t &temp, uint16_t &humidity ) ;
} ;

#endif
