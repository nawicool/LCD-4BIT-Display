#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "LCD_4_BIT_Display.h"


void init_Pin_Ports(void){
	DDR_LCD = 0x0F;
	DDR_CONTROL |= (1 << REGISTER_SELECT) | (1 << READ_WRITE) | (1 << ENABLE);
	PORT_CONTROL &= ~((1 << REGISTER_SELECT) | (1 << READ_WRITE) | (1 << ENABLE));

}
void init_Display_Start(void){
	_delay_ms(30); //More than 15ms
	
	init_Sub_Function();
	_delay_ms(10); // More than 5 ms
	
	init_Sub_Function();
	_delay_us(300); // More than 160 us
	
	init_Sub_Function();
	_delay_us(300); // More than 160 us
	
	
	PORT_CONTROL |= (1 << ENABLE);
	_delay_us(2);
	PORT_LCD = 0x02;
	_delay_us(2);
	PORT_CONTROL &= ~(1 << ENABLE);
	_delay_us(200);
	
    function_Set(0x28);
	_delay_ms(1);

	display_OFF(0x08);
	_delay_ms(1);

	display_ON(0x0F);
	_delay_ms(1);

	entry_Mode(0x06);
	_delay_ms(1);

	clear_Display(0x01);
	_delay_ms(1);
}


void write_Command(unsigned char value){
	unsigned char value_intern=value;
	
	/*Control Bits*/
	PORT_CONTROL &= ~(1 << REGISTER_SELECT);
	PORT_CONTROL &= ~(1 << READ_WRITE);

	/*Higher Bits(Upper Nibble)*/
	PORT_CONTROL |= (1 << ENABLE);
	_delay_us(1);
	PORT_LCD = ((PORT_LCD & 0xF0) | (value_intern >> 4));               
	_delay_us(1);
	PORT_CONTROL &= ~(1 << ENABLE);
	_delay_us(200);
	
	/*Lower Bits (Lower Nibble) */
	PORT_CONTROL |= (1 << ENABLE);
	_delay_us(1);
	PORT_LCD = ((PORT_LCD & 0xF0) | (value_intern & 0x0F));  
	_delay_us(1);
	PORT_CONTROL &= ~(1 << ENABLE);
	_delay_us(200);
		
}
void write_Data(unsigned char value){
	unsigned char value_intern = value;

	/*Control Bits*/
	PORT_CONTROL |= (1 << REGISTER_SELECT);
	PORT_CONTROL &= ~(1 << READ_WRITE);
	
	/*Higher Bits*/
	PORT_CONTROL |= (1 << ENABLE);
	_delay_us(1);
	PORT_LCD = ((PORT_LCD & 0xF0) | (value_intern >> 4));  
	_delay_us(1);
	PORT_CONTROL &= ~(1 << ENABLE);
	_delay_us(200);

	/*Lower Bits*/
	PORT_CONTROL |= (1 << ENABLE);
	_delay_us(1);
	PORT_LCD = ((PORT_LCD & 0xF0) | (value_intern & 0x0F)); 
	_delay_us(1);
	PORT_CONTROL &= ~(1 << ENABLE);
	_delay_us(200);
}

void init_Sub_Function(void){
	
	/*Control Bits*/
	PORT_CONTROL &= ~(1 << REGISTER_SELECT);
	PORT_CONTROL &= ~(1 << READ_WRITE);

	/*Upper Byte*/
	PORT_CONTROL |= (1 << ENABLE);
	_delay_us(1);
	PORT_LCD = 0x03;
	_delay_us(1);
	PORT_CONTROL &= ~(1 << ENABLE);
	_delay_ms(10);
}

void function_Set(unsigned char command){
	unsigned char value_intern = command;
	write_Command(value_intern);	
}

void display_OFF(unsigned char command){
	unsigned char value_intern = command;
	write_Command(value_intern);
}
void display_ON(unsigned char command){
	unsigned char value_intern = command;
	write_Command(value_intern);
}

void clear_Display(unsigned char command){
	unsigned char value_intern = command;
	write_Command(value_intern);
}

void entry_Mode(unsigned char command){
	unsigned char value_intern = command;
	write_Command(value_intern);
}

void return_Home(unsigned char command){
	unsigned char value_intern = command;
	write_Command(value_intern);

}

void Cursor_Off(unsigned char command){
	//0x0C
	unsigned char value_intern = command;
	write_Command(value_intern);
	
}

void display_Shift(unsigned char command){
	//0x18
	unsigned char value_intern = command;
	write_Command(value_intern);
}


void go_To_Position(uint8_t row, uint8_t col){

	uint8_t row_pos = 0x00;
	uint8_t col_pos = 0x00;
	uint8_t final_Pos = 0x00;
	uint8_t col_pos_A[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E,0x0F};


	if (row == 1){
		row_pos = 0x00;
		col_pos = col_pos_A[col];
		final_Pos = row_pos + col_pos;

	}
	else {
		row_pos = 0x40;
		col_pos = col_pos_A[col];
		final_Pos = row_pos + col_pos;
	}
	set_DDRAM_Adress(final_Pos);
	_delay_us(120); //
}

void set_DDRAM_Adress(uint8_t pos){
	uint8_t pos_intern = 0x80 + pos;
	write_Command(pos_intern);
}


void send_Data_Char(unsigned char charchter){
	unsigned char value_intern = charchter;
	write_Data(value_intern);
}



void send_Data_String_Default(char *stringP){

	char *pi = stringP;

	while (*pi != '\0'){


		send_Data_Char(*stringP++);
		_delay_ms(2);
		pi = stringP;
	}
	PORT_LCD = 0x00;
}

void send_Data_String_At_Position(char *stringP, uint8_t row, uint8_t col){


	char *stringLok = stringP;
	uint8_t row_i = row;
	uint8_t col_i = col;
	go_To_Position(row_i, col_i);

	send_Data_String_Default(stringLok);
	PORT_LCD = 0x00;
}

void send_Int_At_Position(int value, uint8_t row, uint8_t col){

	uint8_t row_i = row;
	uint8_t col_i = col;
	char buffer[10];
	itoa(value, buffer, 10);
	send_Data_String_At_Position(buffer, row_i, col_i);

	PORT_LCD = 0x00;
}

void send_Double_At_Position_Int(double value, uint8_t row, uint8_t col){

	uint8_t row_i = row;
	uint8_t col_i = col;
	char buffer[10];

	dtostrf(value, 6, 3, buffer);
	send_Data_String_At_Position(buffer, row_i, col_i);
	PORT_LCD = 0x00;
}


void create_CGRAM_Data(unsigned int *arrayTo_Store, uint8_t at_Pos_in_CGRAM){

	//unsigned int Celcius[] = { 0x6, 0x9, 0x9, 0x6, 0x0, 0, 0, 0 }; //Celcius
	//unsigned int StickMan[] = { 0x0E,0x11,0x0E,0x04,0x1F,0x04,0x0A,0x11 }; //StickMan
	//unsigned int Battery[] = { 0x0E, 0x1B, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1F };
	//unsigned int Battery1[] = { 0x0E, 0x1B, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1F };
	//unsigned int Battery2[] = { 0x0E, 0x1B, 0x11, 0x11, 0x11, 0x11, 0x1F, 0x1F };
	//unsigned int Battery3[] = { 0x0E, 0x1B, 0x11, 0x11, 0x11, 0x1F, 0x1F, 0x1F };
	//unsigned int Battery4[] = { 0x0E, 0x1B, 0x11, 0x11, 0x1F, 0x1F, 0x1F, 0x1F };
	//unsigned int Battery5[] = { 0x0E, 0x1B, 0x11, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F };
	//unsigned int Battery6[] = { 0x0E, 0x1B, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F };
	//unsigned int Battery7[] = { 0x0E, 0x1B, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F };

	unsigned int *customCharPtr = arrayTo_Store; //Give the Write string
	uint8_t pos_i = at_Pos_in_CGRAM;
	uint8_t i;
	/*Limit the Positions up to 7 positions*/
	if (pos_i == 0) {
		pos_i = at_Pos_in_CGRAM;
	}
	else if (pos_i >= 7){
		pos_i = 7 * 0x08;
	}
	else {
		pos_i = pos_i * 0x08;
	}

	write_Command(0x40+pos_i);

	for (i = 0; i < 8; i++){
		
		switch (i)
		{
		case 0: 
			write_Data(*customCharPtr++);
			//PORT_LCD = (PORT_LCD & 0xF0);
			//_delay_us(30);
			break;

		case 1:
			write_Data(*customCharPtr++);
			//PORT_LCD = (PORT_LCD & 0xF0);
			//_delay_us(30);
			break;

		case 2: 
			write_Data(*customCharPtr++);
			//PORT_LCD = (PORT_LCD & 0xF0);
			//_delay_us(30);
			break;

		case 3: 
			write_Data(*customCharPtr++);
			//PORT_LCD = (PORT_LCD & 0xF0);
			//_delay_us(30);
			break;

		case 4: 
			write_Data(*customCharPtr++);
			//PORT_LCD = (PORT_LCD & 0xF0);
			//_delay_us(30);
			break;

		case 5:
			write_Data(*customCharPtr++);
			//PORT_LCD = (PORT_LCD & 0xF0);
			//_delay_us(30);
			break;

		case 6: 
			write_Data(*customCharPtr++);
			//PORT_LCD = (PORT_LCD & 0xF0);
			//_delay_us(30);
			break;

		case 7: 
			write_Data(*customCharPtr++);
			//PORT_LCD = (PORT_LCD & 0xF0);
			//_delay_us(30);
			break;

		default:

			write_Data(0x00);
			//PORT_LCD = (PORT_LCD & 0xF0);
			//_delay_us(30);
			break;
		}

	}
	
}
void show_CGRAM_Data_At_Row_Col(char from_Pos, uint8_t which_row, uint8_t which_col){

	uint8_t row_i = which_row;
	uint8_t col_i = which_col;
	uint8_t pos_i = from_Pos;
	if ((pos_i < 0) || (pos_i>7)){
		pos_i = 0;
	}
	else {
		go_To_Position(row_i, col_i);
		send_Data_Char(pos_i);
	}
	
}



