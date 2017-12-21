#include "search_tree.h"
#include "stdlib.h"
#include "sys/time.h"
#include "interface.h"
int main()
{
	srand(0);
	interface foo;

	char command[1024];
	while(true)
	{	
		size_t bufsize = sizeof(command);
		char * ligne = fgets(command, bufsize, stdin);
		if(ligne == NULL) break;
		foo.parse_command(command);
	}

	return 0;
}