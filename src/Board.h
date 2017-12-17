#ifndef __SRC_BOARD
#define __SRC_BOARD
#include "stdio.h"
#include <cstdint>
#include <stddef.h>


const char EMPTY_SQUARE = 0;
const char BLUE_STONE = 1;
const char RED_STONE = 2;
const char BLOCKED_SQUARE = 3;

enum BoardType {NORMAL};

enum Sides {BLUE, RED};

const char WIDTH = 11;
const char HEIGHT = 11;
const char PRODUCTDIMENSIONS = WIDTH * HEIGHT;

/* Move convention: Moves are represented using chars. The first 4 bits encode the original position of the piece. The last 4 encode the destination square. */
/* If a stone is being duplicated, the first 4 bits are PRODUCTDIMENSIONS if the stone is blue and PRODUCTDIMENSIONS + 1 if red. */
const char BLUE_STONE_DUPLICATION_ORIGIN_SQUARE = PRODUCTDIMENSIONS;
const char RED_STONE_DUPLICATION_ORIGIN_SQUARE = PRODUCTDIMENSIONS + 1;
const char NULLMOVE = 0; 


inline char get_square_repr(char square_type)
{
	char square_repr;
	switch(square_type)
	{
		case EMPTY_SQUARE:
			square_repr = '.';
			break;
		case BLUE_STONE:
			square_repr = 'B';
			break;
		case RED_STONE:
			square_repr = 'R';
			break;
		case BLOCKED_SQUARE:
			square_repr = 'x';
			break;
		default:
			square_repr = ' ';
			break;
	}
	return square_repr;
}

struct board
{
	board();
	board(BoardType);
	~board();
	void print_board();
	char get_type(char x, char y);
	void set_type(char type, char x, char y);
	void generate_moves(short int * moves);
	void play_move(short int move);
	void init_board();
	void load_board(const char * board_representation, Sides side_to_move);
	
	Sides side_to_move;
	char * board_representation;
	const BoardType board_type;
};

#endif