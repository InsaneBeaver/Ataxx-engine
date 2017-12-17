#ifndef __SRC_TRANSPOSITIONTABLE
#define __SRC_TRANSPOSITIONTABLE

#include <inttypes.h>
#include <cstdlib>
#include <cmath>
#include "board.h"
#include "assert.h"


struct position
{
	uint64_t hash;
	board _board;
	double eval;
};



class transposition_table
{
	public:
		transposition_table(int _number_of_positions);
		~transposition_table();
		
		uint64_t hash_board(board & _board);
		position * get_position(uint64_t hash);
		void add_position(board & _board, uint64_t hash, double eval);
	private:
		uint64_t **hash_keys;
		const unsigned int number_of_positions;
		position* * positions;
		
};





#endif