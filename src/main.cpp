#include "search.h"
#include "stdlib.h"
#include "sys/time.h"
#include <iostream>
#include <iostream>
int main()
{
	struct timeval tv;
	node nodes[50];
	short int foo = ((short int)PRODUCTDIMENSIONS);
	foo = (foo << 8) +  WIDTH + 2;
	printf("%i\n", foo);
	int depth = 7;
	nodes[depth]._board.init_board();
	while(1)
	{
		transposition_table tt(1e07);
		gettimeofday(&tv,NULL);
		negamax(nodes, tt, (tv.tv_usec + (tv.tv_sec + 180)* 1e06), depth, -1e06, 1e06, 1);
		nodes[depth]._board.play_move(nodes[depth].dank);
		nodes[depth]._board.print_board();
		
		std::string coup;
		std::cin >> coup;
		short int partie1;
		if(coup[0] == '*')
			partie1 = PRODUCTDIMENSIONS + 1;
		else
		{
			int x1, y1;
			x1 = coup[0] - '_';
			y1 = coup[1] - '.' - 1;
			partie1 = x1 + y1 * WIDTH;
		}
		
		short int partie2;
		int x2, y2;
		x2 = coup[2] - '_';
		y2 = coup[3] - '.' - 1;
		partie2 = x2 + y2 * WIDTH;
		printf("%i %i\n", partie1, partie2);
		short int moncoup = (partie1 << 8) + partie2;
		nodes[depth]._board.play_move(moncoup);
		
		
	}
	/*
	for(int i = 0; i < 1; i++)
	{
		transposition_table tt(1e07);
		gettimeofday(&tv,NULL);
		negamax(nodes, tt, (tv.tv_usec + (tv.tv_sec + 5)* 1e06), 5, -1e06, 1e06, -1);
		nodes[5]._board.play_move(nodes[5].dank);
		nodes[5]._board.print_board();
		printf("---\n");
	}
	*/
	return 0;
}