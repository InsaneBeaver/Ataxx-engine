#include "search.h"
#include "stdlib.h"
int main()
{
	node nodes[50];
	printf("%f\n", negamax(nodes, 1, -1e06, 1e06, -1));
	printf("foobar\n");
	exit(1);
	return 0;
}