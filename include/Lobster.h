#ifndef LOBSTER_HEADER
#define LOBSTER_HEADER
/* The Lobster Programming Language
 * @Author: Joshua Weinstein
 * @email: jweinstein@berkeley.edu
 * @date: December 7 2017
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRANSLATE_BUF_SIZE 10000

typedef enum
{
	Instruction_Stop,
	Instruction_Int,
	Instruction_Add,
	Instruction_Sub,
	Instruction_ExpStart,
	Instruction_ExpEnd
} Instruction;

static unsigned char TRANSLATE_BUF[TRANSLATE_BUF_SIZE];



/** Debugs the translated instructions
  *
  */
void Lobster_debug(void)
{
	unsigned char* reader;
	puts("---Lobster--Instructions----");
	for(reader = TRANSLATE_BUF; *reader != Instruction_Stop;)
	{
		switch(*reader)
		{
			case Instruction_Add:
			    puts("Add;");
			    reader++;
			    break;
			case Instruction_Sub:
			    puts("Sub;");
			    reader++;
			    break;
			case Instruction_ExpStart:
			    puts("ExpStart;");
			    reader++;
			    break;
			case Instruction_ExpEnd:
			    puts("ExpEnd;");
			    reader++;
			    break;
			case Instruction_Int:
			    reader++;
			    printf("Int %ld\n", *(long*)reader);
			    reader+= sizeof(long);
			    break;
			default:
			    printf("Unknown Instruction: %u;\n", *reader++);
		}
	}
	puts("Stop;");
	puts("---Lobster--Debug----End----");
}

/** Translates source code into bytes, puts on TRANSLATE_BUF
  * @srcCode = null terminated string that contains Lobster code
  */
void Lobster_translate(char* code)
{
	unsigned char* writer = TRANSLATE_BUF;
	unsigned char* writeEnd = writer + TRANSLATE_BUF_SIZE;
	char* srcCode = code;
	while(*srcCode)
	{
		if(writer >= writeEnd) 
		{
			fprintf(stderr, "%s\n", "Translation Error: Code input too large.");
			exit(1);
		}
		switch(*srcCode)
		{
			case ' ':
            case '\n':
            case '\t':
            case '\v':
                 srcCode++;
                 break;
            case '\0':
                 return;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                //writes integer 
                *writer++ = Instruction_Int;
                *(long*)(writer) = strtol(srcCode, &srcCode, 10);
                writer += sizeof(long);
                break;
			case '+':
			    *writer++ = Instruction_Add;
			    srcCode++;
			    break;
			case '-':
			    *writer++ = Instruction_Sub;
			    srcCode++;
			    break;
			case '(':
			    *writer++ = Instruction_ExpStart;
			    srcCode++;
			    break;
			case ')':
			    *writer++ = Instruction_ExpEnd;
			    srcCode++;
			    break;
			default:
			    fprintf(stderr, "Syntax Error: Unrecognized token: %c\n", *srcCode);
			    exit(1);
		}
	}
	*writer = Instruction_Stop;
	return;
}

// Determines if an instruction is an operator
int Lobster_is_op(unsigned char code)
{
	switch(code)
	{
		case Instruction_Add:
		case Instruction_Sub:
		    return 1;
		default:
		    return 0;

	}
}

// Evaluates a binary expression
long Lobster_evaluate(unsigned char** ins)
{
	Instruction oper = **ins;
	long result = 0;
	// validation phase
	if(!Lobster_is_op(oper))
	{
		fprintf(stderr, "Instruction Error: Expected oper or call, found: %u\n", **ins);
		exit(1);		
	}
	*ins += 1;
	if(**ins != Instruction_ExpStart)
	{
		fprintf(stderr, "Instruction Error: Expected  ( , found: %u\n", **ins);
		exit(1);		
	}
	*ins += 1;
	//load phase
			
	if(**ins == Instruction_Int)
	{
		*ins += 1;
		result = *(long*)(*ins);
		*ins += sizeof(long);			
	}
	else if (**ins == Instruction_Add || **ins == Instruction_Sub)
		result = Lobster_evaluate(ins);
	// evaluation phase
	while(**ins != Instruction_Stop)
	{
		switch(oper)
		{
			case Instruction_Add:
			switch(**ins)
			{
				case Instruction_Int:
				    *ins += 1;
				    result += *(long*)(*ins);
				    *ins += sizeof(long);
				    break;
				case Instruction_Add:
				case Instruction_Sub:
				    result += Lobster_evaluate(ins);
				    break;
				case Instruction_ExpStart:
				    fprintf(stderr, "Syntax Error: Unexpected '('\n");
				    exit(1);
				case Instruction_ExpEnd:
				    //ends the evaluation
				    *ins += 1;
				    return result;
				default:
				    fprintf(stderr, "Byte Error: Unrecognized instruction: %u\n", **ins);
				    exit(1);			    		
			}
			    break;
			case Instruction_Sub:
			switch(**ins)
			{
				case Instruction_Int:
				    *ins += 1;
				    result -= *(long*)(*ins);
				    *ins += sizeof(long);
				    break;
				case Instruction_Add:
				case Instruction_Sub:
				    result -= Lobster_evaluate(ins);
				    break;
				case Instruction_ExpStart:
				    fprintf(stderr, "Syntax Error: Unexpected '('\n");
				    exit(1);
				case Instruction_ExpEnd:
				    //ends the evaluation
				    *ins += 1;
				    return result;
				default:
				    fprintf(stderr, "Byte Error: Unrecognized instruction: %u\n", **ins);
				    exit(1);			    		
			}
			    break;
			default:
			    fprintf(stderr, "%s\n", "Oper Error: Fatal");
			    exit(1);
		}
	}
	return result;
}

// translates and evaluates a lobster expression
long Lobster_compile(char* code)
{
	Lobster_translate(code);
	unsigned char* instrucs = TRANSLATE_BUF;
	return Lobster_evaluate(&instrucs);
}


#endif