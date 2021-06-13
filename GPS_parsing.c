#include "tm4c123gh6pm.h"
#include "stdint.h"
  
void SystemInit() {}

void UART0_Init(void){
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0;
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;
    
    UART0_CTL_R &= ~UART_CTL_UARTEN;
    //set buad rate devider
    UART0_IBRD_R = 104;
    UART0_FBRD_R = 11;
		UART0_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);
    UART0_CTL_R |= (UART_CTL_UARTEN | UART_CTL_RXE | UART_CTL_TXE);

    GPIO_PORTA_AFSEL_R |= 0x03;
    GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & ~0xFF) | (GPIO_PCTL_PA0_U0RX | GPIO_PCTL_PA1_U0TX);
    GPIO_PORTA_DEN_R |= 0x03;
}


void UART0_write(int c){
    while((UART0_FR_R & UART_FR_TXFF) != 0);
    UART0_DR_R = c;
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

char UART5_read(void){
    while((UART5_FR_R & 0x10) == 0x10);
    return UART5_DR_R & 0xFF;
}
int main(){
	char lat[10]="";
	char lon[10]="";
	char input[] = " " ;
	int i=0;
	char latw[]={'l','a','t','=',' '};
	char space=' ';
	char lonw[]={'l','o','n','=',' '};
	UART0_Init();
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
  for(i=0;i<=sizeof(latw);i++){ 
		UART0_write(latw[i]); 
	}
	for(i=0;i<=sizeof(lat);i++){ 
		UART0_write(lat[i]); 
	} 
	for(i=0;i<=4;i++){ 
		UART0_write(space); 
	}
  for(i=0;i<=sizeof(lonw);i++){ 
		UART0_write(lonw[i]); 
	}
  for(i=0;i<=sizeof(lon);i++){ 
		UART0_write(lon[i]); 
	}	
	UART0_write('\n');
}