#include "search.h"


double negamax(node * nodes, int depth_to_go, double alpha, double beta, int color)
{
	node & current_node = nodes[depth_to_go];
	
	if(depth_to_go == 0)
	{
		current_node.dank.load_board(current_node._board.board_representation, current_node._board.side_to_move);
		return color * evaluate(current_node._board);
	}
	
	node & next_node = nodes[depth_to_go - 1];
	
	current_node._board.generate_moves(current_node.moves);
	double best_value = -10000;
	double v;
	for(unsigned int iMoves = 0; current_node.moves[iMoves] != NULLMOVE; iMoves++)
	{
		next_node._board.load_board(current_node._board.board_representation, current_node._board.side_to_move);
		next_node._board.play_move(current_node.moves[iMoves]);
		v = -negamax(nodes, depth_to_go - 1, -beta, -alpha, -color);
		if(best_value < v)
		{
			current_node.dank.load_board(next_node.dank.board_representation, next_node.dank.side_to_move);
			best_value = v;
		}
		
		alpha = max(alpha, v);
		if(alpha >= beta)
			break;
	}
	return best_value;
}