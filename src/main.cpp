#include "search.h"
#include "stdlib.h"
#include "sys/time.h"
int main()
{
	struct timeval tv;
	node nodes[50];
	nodes[5]._board.init_board();
	
	for(int i = 0; i < 400; i++)
	{
		transposition_table tt(1e07);
		gettimeofday(&tv,NULL);
		negamax(nodes, tt, (tv.tv_usec + (tv.tv_sec + 5)* 1e06), 5, -1e06, 1e06, -1);
		nodes[5]._board.play_move(nodes[5].dank);
		nodes[5]._board.print_board();
		printf("---\n");
	}
	
	return 0;
}