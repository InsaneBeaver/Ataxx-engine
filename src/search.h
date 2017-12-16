#ifndef __SRC_SEARCH
#define __SRC_SEARCH
#include "board.h"
#include "eval.h"
#include <algorithm>

using namespace std;
struct node
{
	board _board;
	short int moves[100];
};

double negamax(node nodes[50], int depth_to_go, double alpha, double beta, int color);



#endif