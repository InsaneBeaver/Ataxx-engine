#include "search_tree.h"

inline uint64_t get_time_millis()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * (uint64_t)1e03 + tv.tv_usec / 1e03;
}

search_tree::search_tree() 
{
	tt = new transposition_table(DEFAULT_TT_MEMORY);
}	



search_tree::~search_tree()
{
	delete tt;
}

void search_tree::start_search(int _depth, uint64_t max_time, board & _board)
{
	depth = _depth;
	time_limit = get_time_millis() + max_time;
	nodes[depth]._board.load_board(_board);
	for(int i = 0; i < depth; i++) nodes[i].hits = 0;

	uint64_t time_at_start = get_time_millis();
	score = negamax(depth, -1e06, 1e06, (_board.side_to_move == BLUE ? 1 : -1));
	search_time = get_time_millis() - time_at_start;
}


int search_tree::rank_move(short int move, board & _board)
{
	int rank = 0;
	char first_part = move >> 8;
	if(first_part >= PRODUCTDIMENSIONS) rank += 4;
	char second_part = (move << 8) >> 8;
	int count = 0;
	const char ennemy_stone = _board.side_to_move == BLUE ? RED_STONE : BLUE_STONE;	
	for(char delta1 = -1; delta1 <= 1; delta1++)
		for(char delta2 = -WIDTH; delta2 <= WIDTH; delta2+= WIDTH)
			if(_board.board_representation[second_part + delta1 + delta2] == ennemy_stone)
				count++;
	
	rank += count * 5;
	return rank;
}


void search_tree::sort_moves(node & _node)
{
	int iMove;
	for(iMove = 0; _node.moves[iMove] != 0; iMove++)
		ranks[iMove] = rank_move(_node.moves[iMove], _node._board);
	
	for(int i = iMove - 1; i > 0; i--)
		for(int j = 0; j < i - 1; j++)
			if(ranks[j + 1] > ranks[j])
			{
				int temp = ranks[j];
				ranks[j] = ranks[j + 1];
				ranks[j + 1] = temp;
				
				temp = _node.moves[j];
				_node.moves[j] = _node.moves[j + 1];
				_node.moves[j + 1] = temp;
				
			}
}

double search_tree::negamax(int depth_to_go, double alpha, double beta, int color)
{
	node & current_node = nodes[depth_to_go];
	current_node.hits++;
	double best_value = -10000;
	uint64_t hash = tt->hash_board(current_node._board);
	position & position = tt->get_position(hash);
	bool is_same_position = (position.hash == hash) && (position.depth >= depth_to_go) && (position._board.compare(current_node._board));
	
	if(is_same_position)
	{
		best_value = position.eval;
		for(int i = 0; i < depth_to_go; i++)
			nodes[i].pv[depth_to_go] = 0;
		
		current_node.pv[depth_to_go] = 0;
	}

	
	else if(depth_to_go == 0)
		best_value = evaluate(current_node._board);
	
	
	else
	{
		double v = -10000;
		node & next_node = nodes[depth_to_go - 1];
		current_node._board.generate_moves(current_node.moves);
		sort_moves(current_node);

		for(unsigned int iMoves = 0; current_node.moves[iMoves] != NULLMOVE; iMoves++)
		{

			if(depth_to_go >= 4 && get_time_millis() >= time_limit) 
				goto end;

			if(iMoves == 0)
				next_node._board.load_board(current_node._board.board_representation, current_node._board.side_to_move);
			
			else
				next_node._board.undo_move(current_node._board, current_node.moves[iMoves - 1]);
			

			next_node._board.play_move(current_node.moves[iMoves]);
			
			v = -negamax(depth_to_go - 1,  -beta, -alpha, -color);
			if(best_value < v)
			{
				current_node.pv[depth_to_go] = current_node.moves[iMoves];
				for(int i = 1; i < depth_to_go; i++)
					nodes[i].pv[depth_to_go] = nodes[i].pv[depth_to_go - 1];

				best_value = v;
				
			}
			
			alpha = max(alpha, v);
			
			if(alpha >= beta)
				break;
			

		}
	}
	if(!is_same_position)
		tt->add_position(current_node._board, hash, best_value, depth_to_go);

	end: 
	return best_value;
}


unsigned int search_tree::get_node_count()
{
	unsigned int node_count = 0;
	for(int i = 0; i <= depth; i++)
		node_count += nodes[i].hits;
	
	return node_count;
}

unsigned int search_tree::get_depth()
{
	return depth;
}

void search_tree::get_pv(short int moves[MAX_DEPTH])
{
	for(int i = depth; i >= 0; i--)
		moves[depth - i] = nodes[i].pv[depth];
}

uint64_t search_tree::get_search_time()
{
	return search_time;
}

double search_tree::get_score()
{
	return score;
}
