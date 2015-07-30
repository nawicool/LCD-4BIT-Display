# 4BIT HD44780 16x2 Character LCD

This is an avr-gcc library for the HD44780 16x2 Character LCD (4Bit Mode) display.
This library is tested on AVR 2560, Arduino Mega and on AVR 328P

Important Note:

1.This library was only developed to try lcd display on my AVR Mega.Many things in this library could be optimised 
in respect to memory usage,timing requirements etc. and could be written in much intelligent way.

2.Please change the libraray according to your requirements. For that change  the DDRC and PORTS I/O registers in
"define statements".


3. I am not using BusyFlag as mentioned in many books. Therefore i am longer delay statements to be on safe side.

4. There is also (8Bit Mode) working library with busy flag available on my github account. 
Most of functions in 8Bit mode have same name in 4Bit mode.



Licensed under the GNU General Public License, Version 2.0 or above.

Written by: Nawi

