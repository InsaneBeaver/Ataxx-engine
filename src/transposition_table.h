#ifndef __SRC_TRANSPOSITIONTABLE
#define __SRC_TRANSPOSITIONTABLE

#include <inttypes.h>
#include <cstdlib>
#include <cmath>
#include "board.h"
#include "assert.h"


struct position
{
	uint64_t hash = 0;
	board _board;
	double eval = 0;
	unsigned char depth = 0;
};



class transposition_table
{
	public:
		transposition_table(size_t _memory);
		~transposition_table();
		
		uint64_t hash_board(board & _board);
		position & get_position(uint64_t hash);
		void add_position(board & _board, uint64_t hash, double eval, unsigned char depth);
	private:
		uint64_t **hash_keys;
		const size_t number_of_positions;
		position *positions;
		
};





#endif