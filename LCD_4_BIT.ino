#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include "LCD_4_BIT_Display.h"

int main(void){
	
	unsigned char n = 'A';

	_delay_ms(30);
	init_Pin_Ports();
	//_delay_ms(30);
	
	init_Display_Start();
	_delay_ms(120);

	send_Data_Char('A');
	send_Data_Char('B');
	send_Data_Char('H');
	go_To_Position(2, 4);
	//_delay_ms(10);
	send_Data_Char('O');
	send_Data_String_Default("Hello");
	//send_Data_String_Default("Bye");

	unsigned int Battery0[] = { 0x0A, 0x1F, 0x11, 0x11, 0x11, 0x0E, 0x04, 0x04 };
	unsigned int Battery1[] = { 0x0E, 0x1B, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1F };
	unsigned int Battery2[] = { 0x0E, 0x1B, 0x11, 0x11, 0x11, 0x11, 0x1F, 0x1F };
	unsigned int Battery3[] = { 0x0E, 0x1B, 0x11, 0x11, 0x11, 0x1F, 0x1F, 0x1F };
	unsigned int Battery4[] = { 0x0E, 0x1B, 0x11, 0x11, 0x1F, 0x1F, 0x1F, 0x1F };
	unsigned int Battery5[] = { 0x0E, 0x1B, 0x11, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F };
	unsigned int Battery6[] = { 0x0E, 0x1B, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F };
	
	

	create_CGRAM_Data(Battery0, 0);
	create_CGRAM_Data(Battery1, 1);
	create_CGRAM_Data(Battery2, 2);
	create_CGRAM_Data(Battery3, 3);
	create_CGRAM_Data(Battery4, 4);
	create_CGRAM_Data(Battery5, 5);
	create_CGRAM_Data(Battery6, 6);
	

	show_CGRAM_Data_At_Row_Col(0, 1, 5);
	show_CGRAM_Data_At_Row_Col(1, 1, 6);
	show_CGRAM_Data_At_Row_Col(2, 1, 7);
	show_CGRAM_Data_At_Row_Col(3, 1, 8);
	show_CGRAM_Data_At_Row_Col(4, 1, 9);
	show_CGRAM_Data_At_Row_Col(5, 1, 10);
	show_CGRAM_Data_At_Row_Col(6, 1, 11);
	


	while (1){
		
		/*display_Shift(0x18);
		_delay_ms(300);
	*/
	}

	return 0;

}
