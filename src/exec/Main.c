#include "Lobster.h"
//Lobster header built into executable

int main(int argc, char const *argv[])
{
	char* cod = "+ (9 -(3 4 ))";
	Lobster_translate(cod);
	Lobster_debug();
	return 0;

}
