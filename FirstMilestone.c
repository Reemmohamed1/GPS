#include "tm4c123gh6pm.h"
#include <stdint.h>
#include <math.h>
#define M_PI 3.14159265359

// CLK, PORTS/Addresses are already defined in the included file tm4c123gh6pm.h
#define RS 0x20                                 // PA5 Mask 
#define RW 0x40                                 // PA6 Mask
#define EN 0x80                                 // PA7 Mask 

void LCD_command(unsigned char comnd);
void SystemInit () {};                          // we could have deleted this line from startup file and hence we won't need to write it here but it's always good not to modify built in files :)
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
   delay_Ms(20); 
   LCD_command(0x30);                           // WakeUp @LCD
   delay_Ms(5);
   LCD_command(0x30);                           // WakeUp @LCD
   delay_Us(100);
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
 
void readGPSModule();
  double latitude = 0, longitude = 0;
  double distance_calc (void);
void led_on (double s);
 
int main(void)
 {
	   double dist = 0;
	    portf_init();
	    LCD_Init();
       LCD_command(1);                           // clear LCD
       LCD_command(0x80);                        // Set cursor location to write in first line 
       LCD_DATA('G');
	     LCD_DATA('P');
	     LCD_DATA('S');
	     LCD_DATA(' ');
	     LCD_DATA('T');
	     LCD_DATA('R');
	     LCD_DATA('A');
	     LCD_DATA('C');                            // Display 'GPS TRACKING SYS' 
	     LCD_DATA('K');
	     LCD_DATA('I');	 
	     LCD_DATA('N');
	     LCD_DATA('G');
	     LCD_DATA(' ');
	     LCD_DATA('S');
	     LCD_DATA('Y');
	     LCD_DATA('S');	
       delay_Ms(500);
			 LCD_command(0xC0);                       // Set cursor location to write in second line
	     LCD_DATA(' ');
       LCD_DATA('C');
	     LCD_DATA('S');
	     LCD_DATA('E');                           // Display 'CSE211'
	     LCD_DATA('2');
	     LCD_DATA('1');
	     LCD_DATA('1');
	     LCD_DATA('-');                                 
	     LCD_DATA('-');
			 LCD_DATA('T');
	     LCD_DATA('E');	 
	     LCD_DATA('A');                             // Display 'TEAM62'
	     LCD_DATA('M');
	     LCD_DATA('6');
	     LCD_DATA('2');
       LCD_DATA(' ');	
       delay_Ms(3000);
			 LCD_command(1);                           // clear LCD
       LCD_command(0x80);                        // Set cursor location to write in first line 
			 
			 
	 
    
    
    do {
			 LCD_DATA('D');
	     LCD_DATA('I');
	     LCD_DATA('S');
	     LCD_DATA('T');
	     LCD_DATA('A');
	     LCD_DATA('N');
	     LCD_DATA('C');                            // Display 'DISTANCE=100' 
	     LCD_DATA('E');
	     LCD_DATA('=');	
       delay_Ms(500);			 
	     LCD_DATA('1');
	     LCD_DATA('0');
	     LCD_DATA('0');
	     LCD_DATA(' ');
	     LCD_DATA(' ');
	     LCD_DATA(' ');	
			 LCD_DATA(' ');
			 delay_Ms(500);
			 LCD_command(0xC0);                         // Set cursor location to write in second line
	     LCD_DATA(' ');
       LCD_DATA(' ');
	     LCD_DATA(' ');
	     LCD_DATA(' ');                             
	     LCD_DATA(' ');
	     LCD_DATA('(');
	     LCD_DATA('I');                                 
	     LCD_DATA('N');
			 LCD_DATA(' ');
	     LCD_DATA('M');	 
	     LCD_DATA('E');                             // Display '(IN METERS)'
	     LCD_DATA('T');
	     LCD_DATA('E');
	     LCD_DATA('R');
			 LCD_DATA('S');
       LCD_DATA(')');	
	       readGPSModule();
            dist = distance_calc();
             led_on (dist);
    } while ((GPIO_PORTF_DATA_R & 0x01) != 1)
	}

	double distance_calc (void)
 {
   double distance = 0;
   int counter = 1;
   double xpoints [300];                                                 // array for storing the latitude values of points of path 
   double ypoints [300];                                                 // array for storing the longitude values of points of path
           
           if (xpoints[counter - 1] != latitude || ypoints[counter - 1] != longitude) {
            xpoints[counter] = latitude;                                 //to save the values of latitude in array 
            ypoints[counter] = longitude;                                //to save the values of longitude in array
            counter++;    
            if (counter != 2)                                            // to start calculations on the second and third elements in the array 
              {
          double x1 = xpoints[counter-2] * (M_PI/180);                   // convert first point latitude from degree to radian 
          double x2 = xpoints[counter-1] * (M_PI/180);                   // convert second point latitude from degree to radian 
          double deltax = (xpoints[counter-1] - xpoints[counter-2]) * (M_PI/180);          // convert differenc  latitude between two points from degree to radian
          double deltay = (ypoints[counter-1] - ypoints[counter-2]) * (M_PI/180);          // convert differenc  longitude between two points from degree to radian
          double a = sin(deltax/2) * sin(deltax/2) + cos(x1) * cos (x2) * sin (deltay/2) * sin (deltay/2);      // using haversine formula to calculate the distance between two points
          double c = 2 * atan2 (sqrt (a) , sqrt (1-a));
          distance += c * 6371 * 1000;                                                                          // overall distance will equal the sum of the displacements between the two points.
              }
                 }
          return distance;   
            }

					
void led_on (double distance)                                             // RED LED ON When Distance Exceeds 100 m 
 {
   if ( distance >= 100)
   GPIO_PORTF_DATA_R |= 0x02;
 }
 
 
 
