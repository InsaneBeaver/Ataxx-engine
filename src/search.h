#ifndef __SRC_SEARCH
#define __SRC_SEARCH
#include "board.h"
#include "eval.h"
#include "transposition_table.h"
#include <algorithm>

using namespace std;
struct node
{
	board _board;
	short int dank;
	short int moves[256];
};

double negamax(node nodes[50], transposition_table & tt, int depth_to_go, double alpha, double beta, int color);



#endif