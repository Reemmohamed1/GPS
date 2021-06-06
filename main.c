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
			 LCD_command(1);                           // clear LCD
       LCD_command(0x80);                        // Set cursor location to write in first line 
 }
