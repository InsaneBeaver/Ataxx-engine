#include "eval.h"


double evaluate(board & _board)
{
	double tot = 0;
	double abstot = 0;
	for(int pos = 0; pos < PRODUCTDIMENSIONS; pos++)
	{
		if(_board.board_representation[pos] == BLUE_STONE)
		{
			tot++;
			abstot++;
		}
		else if(_board.board_representation[pos] == RED_STONE)
		{
			tot--;
			abstot++;
		}
	}
	if(_board.side_to_move == RED) tot *= -1;
	//tot += abstot * sqrt(abstot) / 10000;
	return tot;
}