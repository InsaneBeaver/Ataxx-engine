#include "search_tree.h"
#include "stdlib.h"
#include "sys/time.h"
#include "interface.h"
int main()
{
	srand(0);
	interface foo;
	while(true)
	{	
		char commande[1024] = {0};
		printf("> ");
		gets(commande);
		foo.parse_command(commande);
	}
	return 0;
}