#ifndef __SRC_SEARCH
#define __SRC_SEARCH
#include "board.h"
#include "eval.h"
#include "transposition_table.h"
#include <algorithm>
#include <sys/time.h>

using namespace std;
struct node
{
	board _board;
	short int dank;
	short int moves[256];
};

double negamax(node nodes[50], transposition_table & tt, uint64_t time_limit, int depth_to_go, double alpha, double beta, int color);



#endif