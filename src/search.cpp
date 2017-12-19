#include "search.h"



double negamax(node * nodes, transposition_table & tt, uint64_t time_limit, int depth_to_go, double alpha, double beta, int color)
{
	node & current_node = nodes[depth_to_go];
	double best_value = -10000;
	uint64_t hash = tt.hash_board(current_node._board);
	position * position = tt.get_position(hash);
	bool collision = position != NULL && position->_board.compare(current_node._board);
	
	if(collision)
	{
		best_value = position->eval;
	}
	
	
	else if(depth_to_go == 0)
	{
		//current_node.dank.load_board(current_node._board.board_representation, current_node._board.side_to_move);
		best_value = /*color **/ evaluate(current_node._board);
	}
	
	else
	{
		struct timeval tv;
		double v;
		node & next_node = nodes[depth_to_go - 1];
		
		current_node._board.generate_moves(current_node.moves);

		for(unsigned int iMoves = 0; current_node.moves[iMoves] != NULLMOVE; iMoves++)
		{
			gettimeofday(&tv,NULL);
			if(tv.tv_usec + tv.tv_sec * 1e06 > time_limit) 
				goto end;
			
			next_node._board.load_board(current_node._board.board_representation, current_node._board.side_to_move);
			next_node._board.play_move(current_node.moves[iMoves]);
			
			v = -negamax(nodes, tt, time_limit, depth_to_go - 1, -beta, -alpha, -color);
			if(best_value < v)
			{
				current_node.dank = current_node.moves[iMoves];
				best_value = v;
			}
			
			alpha = max(alpha, v);
			if(alpha >= beta)
				break;
		}
	}
	
	if(!collision)
		tt.add_position(current_node._board, hash, best_value);
	
	end: 
	return best_value;
}