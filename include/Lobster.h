#ifndef LOBSTER_HEADER
#define LOBSTER_HEADER
/* The Lobster Programming Language
 * @Author: Joshua Weinstein
 * @email: jweinstein@berkeley.edu
 * @date: December 7 2017
 *
 */

#include <stdlib.h>
#include <string.h>

#define TRANSLATE_BUF_SIZE 10000
#define TRANSLATE_BUF_FITS(string) (strlen(string) < 10000)

typedef enum
{
	Instruction_Stop,
	Instruction_Int,
	Instruction_Add,
	Instruction_ExpStart,
	Instruction_ExpEnd
} Instruction;

static unsigned char TRANSLATE_BUF[TRANSLATE_BUF_SIZE];


/** Translates source code into bytes, puts on TRANSLATE_BUF
  * @srcCode = null terminated string that contains Lobster code
  */
void Lobster_translate(char* srcCode)
{
	unsigned char* writer = TRANSLATE_BUF;
	unsigned char* writeEnd = writer + TRANSLATE_BUF_SIZE;

	while(*srcCode)
	{
		if(writeEnd >= writer)
		{
			fprintf(stderr, "%s\n", "Translation Error: Code input too large.");
			exit(1);
		}
		switch(*srcCode)
		{
			case '+':
			    *writer++ = Instruction_Add;
			    break;
		}
	}
}



#endif