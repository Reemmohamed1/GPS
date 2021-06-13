#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "stdlib.h"
#include <math.h>
#define M_PI 3.14159265359
void SystemInit () {};                          // we could have deleted this line from startup file and hence we won't need to write it here but it's always good not to modify built in files :)

// CLK, PORTS/Addresses are already defined in the included file tm4c123gh6pm.h
#define RS 0x20                                 // PA5 Mask 
#define RW 0x40                                 // PA6 Mask
#define EN 0x80                                 // PA7 Mask 

void LCD_command(unsigned char comnd);
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

void UART5_Init(void){
SYSCTL_RCGCUART_R |= 0x20; //Activate UART5
SYSCTL_RCGCGPIO_R |= 0x10; //Activate port E

UART5_CTL_R = 0x0; //Disable UART5
UART5_IBRD_R = 104; //IBRD = int(16000000/(16*9600))=int(104.16666)
UART5_FBRD_R = 11; //FBER = round(0.16666*0.64)
UART5_LCRH_R = 0x70; //8 bit length ,enablefifo,1-stop bit 
UART5_CTL_R = 0x301; //enable control registers , RXE,TXE
GPIO_PORTE_AFSEL_R =0x30; //use ports E4 and E5 alternate functions
GPIO_PORTE_PCTL_R = 0x00110000; //configure ports E4 and E5 for uart
GPIO_PORTE_DEN_R = 0x30; //make ports E4 and E5 as digital
GPIO_PORTE_AMSEL_R &= ~0x00; // no analog on ports E4 and E5
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
   LCD_command(0x0F);                           // Display On, cursor blinking or blinking 
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
int l = 0;
void LCD_printInt(int no)
{
  char toprint[4] = {0};
  sprintf(toprint, "%d", no);

  while(toprint[l] != '\0')
  {
    LCD_DATA(toprint[l]);
    l++;
  }
}

char UART5_read(void){
    while((UART5_FR_R & 0x10) == 0x10);
    return UART5_DR_R & 0xFF;
}

void getco(double a, double b){  
	char lat[]="";
	char lon[]="";
	char input[] = " " ;
	int i=0;
	char temp[]=" ";
	int num1 = 0;
	int num2 = 0;
	int num3 =0 ;
	double num4 =0;
	double latfinal =0;
	double lonfinal =0;

	UART5_Init();
	
while(input[i]!='\n')
		{ 
			input[i]=UART5_read();	
			i++;
			if(i==6){
			if(input[3]!='R'){
			for(i=0;i<7;i++){
			input[i]=' ';
			}
			i=0;
			}}
	  }
	if((i==0)&(input[i+21]==0)){
	for(i=0;i<10;i++){lat[i]=input[i+22];	
	if(input[i+23]==','){i=10;}
	}}
	else{
	for(i=0;i<10;i++){lat[i]=input[i+21];	
	if(input[i+22]==','){i=10;}
	}}
	
	if((i==0)&(input[i+35]==0)){
	for(i=0;i<10;i++){lon[i]=input[i+36];	
	if(input[i+37]==','){i=10;}
	}}
	else{
	for(i=0;i<10;i++){lon[i]=input[i+35];	
	if(input[i+36]==','){i=10;}
	}}
// getting final lat

for (i=0;i<2;i++){temp[i]=lat[i];}
num1=atoi(temp);
for (i=0;i<2;i++){temp[i]=lat[i+2];}
num2=atoi(temp);
for (i=0;i<5;i++){temp[i]=lat[i+5];}
num3=atoi(temp);
num4= 1.0*num2 + 0.0001*num3;
latfinal = 1.0*num1+(num4/60.0);

// getting final lon

for (i=0;i<2;i++){temp[i]=lon[i];}
num1=atoi(temp);
for (i=0;i<2;i++){temp[i]=lon[i+2];}
num2=atoi(temp);
for (i=0;i<5;i++){temp[i]=lon[i+5];}
num3=atoi(temp);
num4= 1.0*num2 + 0.0001*num3;
lonfinal = 1.0*num1+(num4/60.0);
a= latfinal;
b= lonfinal;

}


double distance_calc (double lat12, double lon12)
 {
   double distance = 0;
   int counter = 1;
   double xpoints [300];                                                 // array for storing the latitude values of points of path 
   double ypoints [300];                                                 // array for storing the longitude values of points of path
           
           if (xpoints[counter - 1] != lat12 || ypoints[counter - 1] != lon12) {
            xpoints[counter] = lat12;                                 //to save the values of latitude in array 
            ypoints[counter] = lon12;                                //to save the values of longitude in array
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

int main(){
	portf_init();
	LCD_Init();
	int dist = 0;
	double latitude = 0, longitude = 0; 
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
	     delay_Ms(1000);
	
}

