
// Referring to the Forth point in the First Milestone 

#include "tm4c123gh6pm.h"
#include <stdint.h>

#define RS 0x20                                 // PA5 Mask 
#define RW 0x40                                 // PA6 Mask
#define EN 0x80                                 // PA7 Mask 

void delay_Ms(uint32_t n)
{
int i, j;
for(i = 0 ; i < n; i++)
for(j = 0; j < 3180; j++)
{} 
}
void delay_Us(uint32_t n)
{
int i, j;
for(i = 0 ; i < n; i++)
for(j = 0; j < 3; j++)
{} 
}

void LCD_command(unsigned char comnd)
 {
   GPIO_PORTA_DATA_R = 0x00;                    // RS = 0 , R/W = 0 
   GPIO_PORTB_DATA_R = comnd;                   // Whatever Command is assigned set PORTB Pins to it
   GPIO_PORTA_DATA_R |= EN;                     // High Pulse on E    
    delay_Us(0);
   GPIO_PORTA_DATA_R = 0x00;                    // Low Pulse on E 
    if (comnd < 4)
        delay_Ms(2); 
    else
        delay_Us(40); 
 }
void LCD_DATA(unsigned char data)
 {
   GPIO_PORTA_DATA_R = RS;                       // RS = 1 , R/W = 0 = 0x20
   GPIO_PORTB_DATA_R = data;                     // Whatever Data is written set PORTB Pins to it
   GPIO_PORTA_DATA_R |= EN;                      // High Pulse on E    
    delay_Us(0);
   GPIO_PORTA_DATA_R = 0x00;                     // Low Pulse on E 
    delay_Us(40);
 }
