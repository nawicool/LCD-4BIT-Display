/*
This is avr-gcc library for the HD44780 16x2 Character LCD (4Bit Mode) display.
This library is tested with AVR Mega 2560, Arduino Mega and AVR 328P

Important Note:
1.This library was only developed to try my lcd display on AVR Mega. Many things in this library could be optimised (in respect to memory,timing requirements and others) and could be written in much intelligent way.
2.Please change  according to your requirements the DDRC and PORTS I/O registers in the follwing "define statements" .
3. I am not using BusyFlag as mentioned in many books. Therefore i am using more delay statements to be on safe side.
4. There is also  16x2 Character LCD (8Bit Mode) working library with busy flag available on my github account. Most of functions in 8Bit mode have same name.



Licensed under the GNU General Public License, Version 2.0 or above.
Written by: Nawi


*/

#ifndef LCD_4_BIT_DISPLAY_H
#define LCD_4_BIT_DISPLAY_H

/* 8 BIT Display
PORTC --> D0-D3
PORTL --> RS(0),RW(1),EN(2)
*/

#define DDR_LCD DDRC // C0-C3 --> D4-D7
#define PORT_LCD PORTC  //C0-C3 --> D4-D7
#define DDR_CONTROL DDRL
#define PORT_CONTROL PORTL
#define C0_D4 0
#define C1_D5 1
#define C2_D6 2
#define C3_D7 3
#define REGISTER_SELECT 0 
#define READ_WRITE 1      
#define ENABLE 2          

/******  Functions ******/

/* init_Pin_Ports() initialise  directions and default values i.e. DDR and PORT*/
void init_Pin_Ports(void);

/* set_Unset_Enable_Bit  Set and unset Enable bit - from LOW-HIGH-LOW
This function is  always required for reading and writing LCD
*/
void set_Unset_Enable_Bit(void);

/*check_BusyFlag() Checks Busy Flag on PIN D7.
check_BusyFlag()  sets the pins RS and RW to 0 and 1.
After checking the BusyFlag it resets the Pin RS and  RW to 0
*/
void check_BusyFlag(void);

/*
These functions  Initilise the screen  as required by manual
Required Function from Manual,8Bit mode, cursor Position, Display on etc.
*/

void init_Display_Start(void); //Must be implemented  and call following functions
void init_Sub_Function(void); //used inside init_Display_Start
void write_Command(unsigned char command); //Writing Commands
void function_Set(unsigned char command); //used inside init_Display_Start
void display_ON(unsigned char command); //used inside init_Display_Start
void display_OFF(unsigned char command);//used inside init_Display_Start
void clear_Display(unsigned char command);  //used inside init_Display_Start
void entry_Mode(unsigned char command); //used inside init_Display_Start
void return_Home(unsigned char command); // 0x02 used inside init_Display_Start
void Cursor_Off(unsigned char command); // 0x0C Cursor OFF 
void display_Shift(unsigned char command); //0x18 shift display to left. Can be used with loop


/*go_To_Position: Allows you to go to any position on screen and use  set_DDRAM_Adress function
for setting the cursor at required position*/
void go_To_Position(uint8_t row, uint8_t col); // Row 1 or 2, COl 0-15
void set_DDRAM_Adress(uint8_t pos); //Used inside go_To_Position


/*Send Data to LCD*/
void send_Data_Char(unsigned char charchter); //A chrachter to default position
void send_Data_String_Default(char *stringP);  //A String to default position
void send_Data_String_At_Position(char *stringP, uint8_t row, uint8_t col); //A String to  position ROW 1 and 2 and COL up to 16.
void send_Int_At_Position(int value, uint8_t row, uint8_t col); //A Integer to  position ROW 1 and 2 and COL up to 16.
void send_Double_At_Position_Int(double value, uint8_t row, uint8_t col); //A Double to  position ROW 1 and 2 and COL up to 16.

/*Create and Display own Data*/
/*With create_CGRAM you can create your own data. This data can be addressed later
by pointing the DDRAM register fromm address 0-7*/
void create_CGRAM_Data(unsigned int *arrayTo_Store, uint8_t at_Pos_in_CGRAM);
/* Calls the function  send_Data_Char with  from_Pos between
0 and 7 (which is CRAM addresses)*/
void show_CGRAM_Data_At_Row_Col(char from_Pos, uint8_t which_row, uint8_t which_col);


#endif