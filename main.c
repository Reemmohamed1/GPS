#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "stdlib.h"
#include <math.h>
#define M_PI 3.14159265359
#define RS 0x20                                 // PA5 Mask 
#define RW 0x40                                 // PA6 Mask
#define EN 0x80                                 // PA7 Mask 
void SystemInit () {};                          // we could have deleted this line from startup file and hence we won't need to write it here but it's always good not to modify built in files :)



int main(){
	
	portf_init();
	LCD_Init();
	UART5_Init();
	int dist = 0;
	double latitude = 0, longitude = 0; 
	do{
	getco(latitude , longitude);
        dist = (int) (distance_calc(latitude,longitude));
	
	     LCD_command(1);                           // clear LCD
             LCD_command(0x80);                        // Set cursor location to write in first line 
             LCD_DATA('D');
	     LCD_DATA('I');
	     LCD_DATA('S');
	     LCD_DATA('T');
	     LCD_DATA('A');
	     LCD_DATA('N');
	     LCD_DATA('C');                            
	     LCD_DATA('E');
	     LCD_DATA('=');
	     LCD_printInt(dist);
	     delay_Ms(1000);} while ((GPIO_PORTF_DATA_R & 0x01)!=1)
	
}

