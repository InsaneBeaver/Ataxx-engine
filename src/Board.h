#ifndef __SRC_BOARD
#define __SRC_BOARD
#include "stdio.h"
#include <cstdint>
#include <stddef.h>


const char EMPTY_SQUARE = 0;
const char BLUE_STONE = 1;
const char RED_STONE = 2;
const char BLOCKED_SQUARE = 3;

enum BoardType {NORMAL, CENTRALGAPS};

enum Sides {BLUE, RED};

const char WIDTH = 11;
const char HEIGHT = 11;
const char PRODUCTDIMENSIONS = WIDTH * HEIGHT;

/* Move convention: Moves are represented using chars. The first 4 bits encode the original position of the piece. The last 4 encode the destination square. */
/* If a stone is being duplicated, the first 4 bits are PRODUCTDIMENSIONS if the stone is blue and PRODUCTDIMENSIONS + 1 if red. */
const char BLUE_STONE_DUPLICATION_ORIGIN_SQUARE = PRODUCTDIMENSIONS;
const char RED_STONE_DUPLICATION_ORIGIN_SQUARE = PRODUCTDIMENSIONS + 1;
const char NULLMOVE = 0; 

constexpr unsigned int MAX_MOVES_IN_POSITION = 256;


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
			square_repr = '?';
			break;
	}
	return square_repr;
}

inline char get_square(char square_repr)
{
	char square;
	switch(square_repr)
	{
		case '.':
			square = EMPTY_SQUARE; break;	
		case 'B':
			square = BLUE_STONE; break;
		case 'R':
			square = RED_STONE; break;
		case 'x':
			square = BLOCKED_SQUARE; break;
	}
	return square;
}

inline void get_coordinate_repr(char repr[2], char coordinate)
{
	char x = (coordinate - 1) % WIDTH;
	char y = ((coordinate - 1) - x) / WIDTH;
	
	sprintf(repr, "%c%c", x + '`', y + '/');
	
}

inline char get_coordinate(char repr[2])
{
	char x = repr[0] - '_';
	char y = repr[1] - '/';
	
	return x + y * WIDTH;
}

inline void get_move_repr(char repr[4], short int move)
{
	char origin_square = move >> 8;
	char destination_square = (move << 8) >> 8;
	if(origin_square >= PRODUCTDIMENSIONS)
	{
		get_coordinate_repr(repr, destination_square);
		repr[2] = 0;
	}
	else
	{
		get_coordinate_repr(repr, origin_square);
		get_coordinate_repr(&repr[2], destination_square);
	}
}

inline short int get_move(char repr[4], Sides side)
{
	char origin_square, destination_square;
	if(repr[2] == 0)
	{
		origin_square = PRODUCTDIMENSIONS;
		if(side == RED) origin_square++;
		destination_square = get_coordinate(repr);
	}
	else
	{
		origin_square = get_coordinate(repr);
		destination_square = get_coordinate(&repr[2]);
	}

	return (origin_square << 8) + destination_square;
	
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
	void load_board(board & _board);
	void load_board(const char * fen);
	void undo_move(board & old_board, short int move);
	
	bool compare(board & _board);
	
	Sides side_to_move;
	unsigned char move_count;
	char * board_representation;
	const BoardType board_type;
};

#endif