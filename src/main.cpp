#include "search.h"
#include "stdlib.h"
int main()
{
	node nodes[50];
	nodes[7]._board.init_board();
	
	for(int i = 0; i < 40; i++)
	{
		transposition_table tt(1e07);
		printf("%i %f\n", 7, negamax(nodes, tt, 7, -1e06, 1e06, -1));
		nodes[7]._board.play_move(nodes[7].dank);
		nodes[7]._board.print_board();
	}
	return 0;
}