
// Refering to the Third point in the First Milestone 

#include "tm4c123gh6pm.h"
#include <stdint.h>

void led_on (double distance)                          // RED LED ON When Distance Exceeds 100 m 
 {
   if ( distance >= 100)
   GPIO_PORTF_DATA_R |= 0x02;
 }