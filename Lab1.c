#include <stdio.h>
#include <stdint.h>
#include "string.h"
#include "UART.h"
#include "fixed.h"
#include "inc/tm4c123gh6pm.h"
// const will place these structures in ROM
const struct outTestCase{  // used to test routines
  uint32_t InNumber;       // test input number
  char OutBuffer[10];      // Output String  
};
typedef const struct outTestCase outTestCaseType;
outTestCaseType Fixed_uDecOut2sTest[9]={
		{0 , "  0.00"},
		{1 , "  0.01"},
	  {12345, "123.45"},
		{22100 , "221.00"},
    {102 , "  1.02"},
    {31 , "  0.31"},
		{100000 , "***.**" },
		{999999 , "***.**"},
		{-1 , "***.**"}
};

outTestCaseType Fixed_uDecOut3sTest[8] = { 
		{0 , " 0.000"},
		{1 , " 0.001"},
	  {12345 , "12.345" },
    {22100 , "22.100"},
    {102 , " 0.102" },
    {31 , " 0.031" },
		{100000 , "**.***"},
		{999999 , "**.***"}
};

outTestCaseType Fixed_sDecOut3sTest[10] = {
	 {0 , " 0.000"},
	 {1 , " 0.001"},
	 {-1 , "-0.001"},
   {2345 , " 2.345"  },
   {-8100 , "-8.100" },
   {-102 , "-0.102" },
   {31 , " 0.031" },
	 {10000, " *.***" },
	 {-9999, "-9.999"},
	 {-10000, " *.***"}
};

outTestCaseType Fixed_uBinOut8sTest[16]={ 
{     0,  "  0.00" }, //      0/256 = 0.00  
{     4,  "  0.01" }, //      4/256 = 0.01  
{    10,  "  0.03" }, //     10/256 = 0.03
{   200,  "  0.78" }, //    200/256 = 0.78
{   254,  "  0.99" }, //    254/256 = 0.99
{   505,  "  1.97" }, //    505/256 = 1.97
{  1070,  "  4.17" }, //   1070/256 = 4.17
{  5120,  " 20.00" }, //   5120/256 = 20.00
{ 12184,  " 47.59" }, //  12184/256 = 47.59
{ 26000,  "101.56" }, //  26000/256 = 101.56
{ 32767,  "127.99" }, //  32767/256 = 127.99
{ 32768,  "128.00" }, //  32768/256 = 128
{ 34567,  "135.02" }, //  34567/256 = 135.02
{123456,  "482.25" }, // 123456/256 = 482.25
{255998,  "999.99" }, // 255998/256 = 999.99
{256000,  "***.**" }  // error
};
uint32_t Errors,AnError;
char Buffer[10];

int check(uint32_t num, const char* found, const char* expected) {
	// Checks an expected string against a given string. Outputs if an error.
	// Errors return 1. Passes return 0.
	printf("%s\n", found);
    if(strcmp(expected, found)){
			printf("FAIL: Expected: %s. Found: %s\n", expected, found); 
			return 1;
    }
		return 0;
}

void main(void){
  uint32_t i;
	// initialize output device
  Output_Init();              
	
	// run test suite
	printf("Testing...\n");
	printf("Testing Fixed_uBinOut8s...\n");
  Errors = 0;
  for(i=0; i<16; i++){
    Fixed_uBinOut8s(Fixed_uBinOut8sTest[i].InNumber, Buffer);
		Errors += check(Fixed_uBinOut8sTest[i].InNumber, Buffer, Fixed_uBinOut8sTest[i].OutBuffer);
  }
	printf("Done.\n");
	printf("Testing Fixed_uDecOut3s...\n");
	for (i=0; i<8; i++) {
		Fixed_uDecOut3s(Fixed_uDecOut3sTest[i].InNumber, Buffer);
		Errors += check(Fixed_uDecOut3sTest[i].InNumber, Buffer, Fixed_uDecOut3sTest[i].OutBuffer);
	}
	printf("Done.\n");
	printf("Testing Fixed_uDecOut2s...\n");
	for (i=0; i<9; i++) {
		Fixed_uDecOut2s(Fixed_uDecOut2sTest[i].InNumber, Buffer);
		Errors += check(Fixed_uDecOut2sTest[i].InNumber, Buffer, Fixed_uDecOut2sTest[i].OutBuffer);
	}
	printf("Done.\n");
	printf("Testing Fixed_sDecOut3s...\n");
	for (i=0; i<10; i++) {
		Fixed_sDecOut3s(Fixed_sDecOut3sTest[i].InNumber, Buffer);
		Errors += check(Fixed_sDecOut3sTest[i].InNumber, Buffer, Fixed_sDecOut3sTest[i].OutBuffer);
	}
	printf("Done.\n");
	printf("Errors: %u\n", Errors);
}
