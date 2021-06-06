#include "tm4c123gh6pm.h"
#include <stdint.h>


//#define RS 0x20                                 // PA5 Mask 
//#define RW 0x40                                 // PA6 Mask
//#define EN 0x80                                 // PA7 Mask 

// Initializing PORTS A,B For LCD Requirements 
void LCD_Init (void)
 {
   SYSCTL_RCGCGPIO_R |= 0x23;                   // Activate Both PORTS A,B,F 
   while ((SYSCTL_PRGPIO_R & 0x23) == 0) {};    // Check if PORTS A,B are Activated
   GPIO_PORTA_AMSEL_R &= ~0xE0;                 // Disable Analoge on PA5,PA6,PA7 
   GPIO_PORTA_AFSEL_R &= ~0xE0;                 // Needn't Func. Selection on PA5,PA6,PA7
   GPIO_PORTA_PCTL_R &= ~0xFFF00000;            // No Function Selected on PA5,PA6,PA7
   GPIO_PORTA_DEN_R |= 0xE0;                    // Enable Digital on PA5,PA6,PA7
   GPIO_PORTA_DIR_R |= 0XE0;                    // Set PA5,PA6,PA7 to be Outputs (CONTROL)
   GPIO_PORTB_AMSEL_R &= ~0xFF;                 // Disable Analoge on PB0-PB7 
   GPIO_PORTB_AFSEL_R &= ~0xFF;                 // Needn't Alt Func. Selection on PB0-PB7
   GPIO_PORTB_PCTL_R &= ~0xFFFFFFFF;            // No Function Selected on PB0-PB7
   GPIO_PORTB_DEN_R |= 0xFF;                    // Enable Digital on PB0-PB7
   GPIO_PORTB_DIR_R |= 0XFF;                    // Set PB0-PB7 to be Outputs (DATA)
   LCD_command(0x30);                           // WakeUp @LCD
   LCD_command(0x30);                           // WakeUp @LCD
   LCD_command(0x30);                           // WakeUp @LCD
   LCD_command(0x38);                           // set data to 8-bit, 2-line, 5x7 Character
   LCD_command(0x06);                           // Increment Curser (Shifting it Right)  
   LCD_command(0x01);                           // clear LCD
   LCD_command(0x0F);                           // Display On, cursor blinking or blinking */
 }
void portf_init (void)
 {
	 GPIO_PORTF_LOCK_R = 0x4C4F434B;              // Unlock PORTF
   GPIO_PORTF_CR_R |= 0x03;                     // Enable Changing in PORTF Pins 
   GPIO_PORTF_AMSEL_R &= ~0x03;                 // Disable Analoge on PF0,PF1
   GPIO_PORTF_AFSEL_R &= ~0x03;                 // Needn't Func. Selection on PF0,PF1
   GPIO_PORTF_PCTL_R &= ~0x000000FF;            // No Function Selected on PF0,PF1
   GPIO_PORTF_PUR_R |= 0x01;                    // Enable Pull Up Resistance For Switch 1 as it's Active low 
   GPIO_PORTF_DEN_R |= 0x03;                    // Enable Digital on PF0,PF1
   GPIO_PORTF_DIR_R |= 0X02;                    // Set PF0 to be Input,PF1 to be Output 
 }
 
      
    
 
 
 
