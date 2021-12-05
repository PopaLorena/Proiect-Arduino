/* MCU send start signal (voltage low for 18ms) 
* MCU wait for response (voltage high for 20-40 us)
* DHT send response signal (voltage low for 80 us)
* DHT preparation for sendign data - (voltage high 80us)
* Start data transmission (40 bit ~ 4-5ms)
* How data transmission works
*  - each bit of data begins with the 50us low-voltage-length pulse
*  - 26-28 us of high-voltage-length means bit "0"
*  - 70 us of high-voltage-length means bit "1"
* Once the data transmission is done, DHT pulls down voltage (50us)*/

/* DATA ITEM
* 8 bit int RH (Relative Humidity) data
* 8 bit decimal RH data
* 8 bit int temperature data
* 8 bit decimal temperature data
* 8 bit checksum (the last 8 bits of int_RH + dec_RH + int_temp + dec_temp)
*/

#include "dht11.h"

// Build the DHT11 class / give the working pin / set up registers
DHT11::DHT11( int _dataPin ) : dataPin(_dataPin) {
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

// The interrupt handler for DHT11 pin - ISR
ISR(PCINT2_vect) {
    long curr_time = micros();
    /* For the current dataPin transition, store the time difference between it and the last transition */
    dht11_data_time[dht11_trans_cnt] = curr_time - prev_dht11_change;
    prev_dht11_change = curr_time;
    dht11_trans_cnt++;
}

// Overflow interrupt handler
ISR(TIMER2_OVF_vect) {
    ovfl_iterations += 1;
}

// Compare match interrupt handler
ISR(TIMER2_COMPA_vect) {
    resp_delay_match = 1;
}

// Read from DHT11 through serial
DHT11::read(uint16_t &temp, uint16_t &humidity) {
    /* Reset the parameters */
    ovfl_iterations = 0;
    resp_delay_match = 0;

    /* Control the frequency of reading from DHT11 sensor (1Hz) */
    while(ovfl_iterations != 488);
    ovfl_iterations = 0;

    /* BOOLEAN - Indicates whether the data transmission is right or not*/
    bool trans_checksum = false;

    /* MCU REQUEST for Data - Pull pin down for 18 ms (START signal) */
    DDRD |= (1 << dataPin);
    PORTD &= ~(1 << dataPin);
    while(ovfl_iterations != 9);
    ovfl_iterations = 0;

    /* MCU wait for RESPONSE - Pull pin up for 40us */
    TIMSK2 |= (1 << 1); // enable match iterrupt on output compare A
    PORTD |= (1 << dataPin);
    while(resp_delay_match != 1);
    TIMSK2 &= ~(1 << 1); // disable match iterrupt on output compare A

    /* Prepare to read the pin - DATA come from DHT11 */
    DDRD &= ~(1 << dataPin);

    /* Clear the timing array */
    memset((void *) dht11_data_time, 0, sizeof(dht11_data_time));
    /* Reset the transition count for the data pin */
    dht11_trans_cnt = 0;
    /* Take the current timing as the last time for dataPin change*/
    prev_dht11_change = micros();

    /* Attach an interrupt to the dataPin on any state change (rising and falling edges) */
    PCICR |= (1 << 2);  // pin change interrupt enable 2 (PCINT[23:16])
    PCMSK2 |= (1 << dataPin);

    /* Delay for how long a transfer (complete reading) lasts  ~ 6ms */
    while(ovfl_iterations != 3);
    ovfl_iterations = 0;

    /* Deattach the interrupt from dataPin */
    PCICR &= ~(1 << 2);
    PCMSK2 &= ~(1 << dataPin);

    /* MCU take back the MASTER control over dataPin and drives high voltage */ 
    DDRD |= (1 << dataPin);
    PORTD |= (1 << dataPin);

    /* Array to store received 40 bit (5 x 8bit) of data */
    uint16_t data[5];
    data[0] = 0x00;
    data[1] = 0x00;
    data[2] = 0x00;
    data[3] = 0x00;
    data[4] = 0x00;

    /* Parse the data */

    // A complete reading (transfer) should have at least 82 dataPin transitions
    // because of DHT RESPONSE (2 transitions) and 40 bit of DATA (2 transitions for each bit)
    // resulting 2 + 40 * 2 = 82
    if (dht11_trans_cnt < 82) {
        return false;
    }

    // Look for 2 x 80uS pulses from DHT
    int start = 1;       // index at which 40 bit data transfer started
    int num_of_80us = 0; // number of 80us intervals in our timing array

    for(int i = 0; i < dht11_trans_cnt; i++, start++){
        if (dht11_data_time[i] > 70) num_of_80us++;
        if (num_of_80us == 2) break;
    }

    // Look for 40 data bits
    int data_curr_index = 0;
    uint16_t mask = 0x80;

    // Loop with a step of 2 transitions (1 bit transfer)
    for(int i = start; i < dht11_trans_cnt; i = i + 2){
        // Verify that a 1 bit transfer have around 50us low pulses between
        if (dht11_data_time[i] > 60 || dht11_data_time[i] < 40) return false;

        // Verify the next pulse length, determine the bit and append it to data
        data[data_curr_index] += (dht11_data_time[i + 1] > 50) ? mask : 0;
        mask = mask >> 1;

        // Change data current index (16 transitions for 8bit data)
        if (((i - start) % 16) == 14){
            mask = 0x80;
            data_curr_index++;
        }
    }

    /* Assign the humidity and temperature */
    humidity = data[0];
    temp = data[2];

    /* Verify checksum */
    if (data[4] == (data[0] + data[1] + data[2] + data[3])) trans_checksum = true;

    return trans_checksum; 
}
