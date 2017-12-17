#include "search.h"
#include "stdlib.h"
int main()
{
	node nodes[50];
	for(int i = 7; i < 10; i++)
	{
		nodes[i]._board.init_board();
		printf("%i %f\n", i, negamax(nodes, i, -1e06, 1e06, -1));
		nodes[i].dank.print_board();
	}
	return 0;
}