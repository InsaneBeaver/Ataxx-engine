#ifndef __SRC_SEARCH
#define __SRC_SEARCH
#include "board.h"
#include "eval.h"
#include "transposition_table.h"
#include <algorithm>
#include <sys/time.h>
#include "assert.h"

using namespace std;

constexpr unsigned int MAX_DEPTH = 50;
constexpr size_t DEFAULT_TT_MEMORY = 1e06;


struct node
{
	board _board;
	short int pv[MAX_DEPTH];
	short int moves[MAX_MOVES_IN_POSITION];
	unsigned int hits = 0;
};


class search_tree 
{
public:
	search_tree();
	~search_tree();
	unsigned int get_node_count();
	void get_pv(short int moves[MAX_DEPTH]);
	uint64_t get_search_time();
	unsigned int get_depth();
	double get_score();
	void start_search(int _depth, uint64_t max_time, board & _board);

private:
	double negamax(int depth_to_go, double alpha, double beta, int color);
	node nodes[MAX_DEPTH];
	transposition_table * tt;
	uint64_t time_limit;
	uint64_t search_time;
	unsigned int depth;
	double score;
	int ranks[MAX_MOVES_IN_POSITION];
	int rank_move(short int move, board & _board);
	void sort_moves(node & _node); 


};



#endif