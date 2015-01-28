#include "fixed.h"
// filename ******** fixed.c ************** 
// Design specification for Lab 1 
// Jonathan Valvano
// August 28, 2014
/* Do not post, solution to lab for the book
   "Embedded Systems: Real Time Interfacing to the Arm Cortex M",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2014

 Copyright 2014 by Jonathan W. Valvano, valvano@mail.utexas.edu
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */
#define DIGIT_TO_ASCII 48
#define FALSE 0
#define TRUE 1
#define TOTAL_DISPLAYED 6
#define TOTAL_UNSIGNED_DIGITS 5
#define TOTAL_SIGNED_DIGITS 4
#define BASE 10
#define RESOLUTION 100.0/256.0
#define MAX 99999
/****************Fixed_uDecOut2s***************
 converts fixed point number to ASCII string
 format unsigned 32-bit with resolution 0.01
 range 0 to 999.99
 Input: unsigned 32-bit integer part of fixed point number
         greater than 99999 means invalid fixed-point number
 Output: null-terminated string exactly 6 characters plus null
 Examples
 12345 to "123.45"  
 22100 to "221.00"
   102 to "  1.02" 
    31 to "  0.31" 
100000 to "***.**"    */ 

uint32_t get_remainder(uint32_t n) {
	//printf("n: %u. BASE: %u\n", n, BASE);
	int32_t quotient = n/BASE;
	uint32_t remainder = n - quotient * BASE;
  //printf("Remainder: %u\n", remainder);
	return n - (n/BASE) * BASE;
}

void blank_str(char* string) {
	 for (uint32_t i = 0; i < TOTAL_DISPLAYED; i ++) {
		 string[i] = ' ';
	 }
	 string[TOTAL_DISPLAYED] = 0;
}

void output(char* string) {
	printf(string);
	printf("\n");
}

void convert_unsigned(uint32_t n, char* string, uint32_t fractional_digits) {
							 
	 // spaces and null terminate off the bat
	 blank_str(string);
							 
	 // handle the too-big case
   if (n > MAX) {
		 for (uint32_t i = 0; i < TOTAL_DISPLAYED; i++) {
			 string[i] = '*';
		 }
		 string[TOTAL_UNSIGNED_DIGITS - fractional_digits] = '.';
		 return;
	 }
	 
	 for (uint32_t i = 0; i < fractional_digits; i++) {
		 uint32_t remainder = get_remainder(n);
		 string[TOTAL_UNSIGNED_DIGITS - i] = remainder + DIGIT_TO_ASCII;
		 // printf("Setting string[%u] to %u\n", TOTAL_UNSIGNED_DIGITS - i, remainder + DIGIT_TO_ASCII);
		 n = n/BASE;
	 }
	 string[TOTAL_UNSIGNED_DIGITS - fractional_digits] = '.';
	 for (uint32_t i = fractional_digits + 1; i < TOTAL_DISPLAYED; i++) {
		 uint32_t remainder = get_remainder(n);
		 string[TOTAL_UNSIGNED_DIGITS - i] = remainder + DIGIT_TO_ASCII;
		 // printf("Setting string[%u] to %u\n", TOTAL_UNSIGNED_DIGITS - i, remainder + DIGIT_TO_ASCII);
		 n = n/BASE;
		 if (n == 0) {
			 return;
		 }
	 }
}	

void Fixed_uDecOut2s(uint32_t n,  char *string){
	convert_unsigned(n, string, 2);
}


 /****************Fixed_uDecOut2***************
 outputs the fixed-point value on the display
 format unsigned 32-bit with resolution 0.01
 range 0 to 999.99
 Input: unsigned 32-bit integer part of fixed point number
         greater than 99999 means invalid fixed-point number
 Output: none
 Examples
 12345 to "123.45"  
 22100 to "221.00"
   102 to "  1.02" 
    31 to "  0.31" 
100000 to "***.**"    */ 
void Fixed_uDecOut2(uint32_t n){
	char string[10];
	Fixed_uDecOut2s(n, string);
	output(string);
}


 /****************Fixed_uDecOut3***************
 outputs the fixed-point value on the display
 format unsigned 32-bit with resolution 0.001
 range 0 to 99.999
 Input: unsigned 32-bit integer part of fixed point number
         greater than 99999 means invalid fixed-point number
 Output: none
 Examples
 12345 to "12.345"  
 22100 to "22.100"
   102 to " 0.102" 
    31 to " 0.031" 
100000 to "**.***"    */ 
void Fixed_uDecOut3(uint32_t n){
	char string[10];
	Fixed_uDecOut3s(n, string);
	output(string);
}

void Fixed_uDecOut3s(uint32_t n, char* string) {
	convert_unsigned(n, string, 3);
}

/****************Fixed_sDecOut3s***************
 converts fixed point number to ASCII string
 format signed 32-bit with resolution 0.001
 range -9.999 to +9.999
 Input: signed 32-bit integer part of fixed point number
 Output: null-terminated string exactly 6 characters plus null
 Examples
  2345 to " 2.345"  
 -8100 to "-8.100"
  -102 to "-0.102" 
    31 to " 0.031" 
   
 */ 
void Fixed_sDecOut3s(int32_t n, char *string){
}


/****************Fixed_sDecOut3s***************
 converts fixed point number to the display
 format signed 32-bit with resolution 0.001
 range -9.999 to +9.999
 Input: signed 32-bit integer part of fixed point number
 Output: none
 Output to display has exactly 6 characters
 Examples
  2345 to " 2.345"  
 -8100 to "-8.100"
  -102 to "-0.102" 
    31 to " 0.031" 
 */ 
void Fixed_sDecOut3(int32_t n){
}




/**************Fixed_uBinOut8s***************
 unsigned 32-bit binary fixed-point with a resolution of 1/256. 
 The full-scale range is from 0 to 999.99. 
 If the integer part is larger than 256000, it signifies an error. 
 The Fixed_uBinOut8 function takes an unsigned 32-bit integer part 
 of the binary fixed-point number and outputs the fixed-point value on the OLED. 
 Input: unsigned 32-bit integer part of fixed point number
 Output: null-terminated string
Parameter output string
     0     "  0.00"
     2     "  0.01"
    64     "  0.25"
   100     "  0.39"
   50      "  1.95"
   512     "  2.00"
  5000     " 19.53"
 30000     "117.19"
255997     "999.99"
256000     "***.**"
*/
void Fixed_uBinOut8s(uint32_t n, char *string){
	n = round(n * RESOLUTION);
	convert_unsigned(n, string, 2);
}


/**************Fixed_uBinOut8***************
 unsigned 32-bit binary fixed-point with a resolution of 1/256. 
 The full-scale range is from 0 to 999.99. 
 If the integer part is larger than 256000, it signifies an error. 
 The Fixed_uBinOut8 function takes an unsigned 32-bit integer part 
 of the binary fixed-point number and outputs the fixed-point value on the OLED. 
 Input: unsigned 32-bit integer part of fixed point number
 Output: none
Parameter LCD display
     0	  0.00
     2	  0.01
    64	  0.25
   100	  0.39
   500	  1.95
   512	  2.00
  5000	 19.53
 30000	117.19
255997	999.99
256000	***.**
*/
void Fixed_uBinOut8(uint32_t n){
	char string[10];
	Fixed_uBinOut8s(n, string);
	output(string);
}


