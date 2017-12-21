#include "transposition_table.h"


inline int irand()
{
	return rand() ^ (rand() << 16);
}
inline uint64_t lrand()
{
	return ((uint64_t)irand() << 32) ^ ((uint64_t)irand());
}


transposition_table::transposition_table(size_t memory) : number_of_positions(memory / sizeof(position))
{
	assert(number_of_positions > 0);
	positions = new position[number_of_positions]();
	
	const unsigned int hash_keys_size = (WIDTH - 2) * (HEIGHT - 2);
	hash_keys = new uint64_t*[hash_keys_size];
	for(int i = 0; i < hash_keys_size; i++)
	{
		hash_keys[i] = new uint64_t[4];
		for(int j = 0; j < 4; j++)
			hash_keys[i][j] = lrand();
	}
}

transposition_table::~transposition_table()
{
	delete[] positions;

	for(int i = 0; i < (WIDTH - 2) * (HEIGHT - 2); i++)
		delete[] hash_keys[i];
	
	delete[] hash_keys;
}

uint64_t transposition_table::hash_board(board & _board)
{
	unsigned int position_counter = 0;
	uint64_t hash = 0;
	for(int i = 0; i < PRODUCTDIMENSIONS; i++)
	{
		if(_board.board_representation[i] == BLOCKED_SQUARE) continue;
		hash ^= hash_keys[position_counter][_board.board_representation[i]];
		position_counter++;
	}	
		
	return hash;
}

position & transposition_table::get_position(uint64_t hash)
{
	return positions[hash % number_of_positions];
}
int a = 0;
void transposition_table::add_position(board & _board, uint64_t hash, double eval, unsigned char depth)
{
	unsigned int index = hash % number_of_positions;
	position & new_position = positions[index];
	new_position.hash = hash;
	new_position._board.load_board(_board);
	new_position.eval = eval;
	new_position.depth = depth;

}
