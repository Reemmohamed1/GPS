#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "stdint.h"
#include "stdlib.h"
 

void getco(double a, double b){
	char lat[10]="";          //for storing the latitude as an array of characters.
	char lon[10]="";          //for storing the longitude as an array of characters.
	char input[] = "" ;       //for storing the incoming input from the GPS-module as an array of characters.
	int i=0;                  //used as a counter in several loops.
        char temp[]=" ";
	int num1 = 0;
	int num2 = 0;
	int num3 =0 ;
	double num4 =0;           //temp, num1, num2, num3 & num4 are just temporary used to calculate the final latitude and longotude that will be used in the distance calculation.
	double latfinal =0;       //To store the final latitude.
	double lonfinal =0;       //To store the final longitude.
	char latword[]={'l','a','t','=',' '};
	char space=' ';
	char lonword[]={'l','o','n','=',' '};
	UART0_Init();
        UART5_Init();

	
        // Storing the input from the gps in input array.
        // The loop stops when it moves on to read a new line from the GPS-module.
	while(input[i]!='\n')
		{ 
			input[i]=UART5_read();	
			i++;
			//We are working on the line that starts with $GPRMC, sho that loop is checking if that's the line we're on, if not it starts over.
                        if(i==6){                 
			if(input[3]!='R'){
			for(i=0;i<7;i++){
			input[i]=' ';
			}              
			i=0;
			}}
	}

        //Storing latitude in lat array.
	if((i==0)&(input[i+21]==0)){               //cheking if the first number is zero and if so it will skip it. 
	for(i=0;i<10;i++){lat[i]=input[i+22];	
	if(input[i+23]==','){i=10;}
	}}
	else{
	for(i=0;i<10;i++){lat[i]=input[i+21];	
	if(input[i+22]==','){i=10;}
	}}
	//Storing longitude in lon array.
	if((i==0)&(input[i+35]==0)){               //cheking if the first number is zero and if so it will skip it.   
	for(i=0;i<10;i++){lon[i]=input[i+36];	
	if(input[i+37]==','){i=10;}
	}}
	else{
	for(i=0;i<10;i++){lon[i]=input[i+35];	
	if(input[i+36]==','){i=10;}
	}}

        //The following loops is just to print the output on a serial monitor, we're using Putty program to show the results.
        //Printing "lat=" and then the lat number.
        for(i=0;i<=sizeof(latword);i++){ 
		UART0_write(latword[i]); 
	}
	for(i=0;i<=sizeof(lat);i++){ 
		UART0_write(lat[i]); 
	} 
        //Printing space between the words lat and lon.
	for(i=0;i<=6;i++){ 
		UART0_write(space); 
	}
        //Printing "lon=" and then the lon number.
        for(i=0;i<=sizeof(lonword);i++){ 
		UART0_write(lonword[i]); 
	}
        for(i=0;i<=sizeof(lon);i++){ 
		UART0_write(lon[i]); 
	}	
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
b=lonfinal;
}
