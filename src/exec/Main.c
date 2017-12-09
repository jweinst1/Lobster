#include "Lobster.h"
//Lobster header built into executable

int main(int argc, char *argv[])
{
	if(argc == 2)
	{
		printf("%ld\n", Lobster_compile(argv[1]));
	}
	else printf("Must have one argument, got %d arguments\n", argc);
	
	return 0;

}
