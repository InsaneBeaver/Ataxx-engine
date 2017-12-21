#ifndef __SRC_ENGINE
#define __SRC_ENGINE

#include <iostream>
#include <cstring>

#include "Board.h"
#include "search_tree.h"
#include "transposition_table.h"

using namespace std;

constexpr unsigned int DEFAULT_DEPTH = 9;
constexpr char MAX_ARG_NUMBER = 16;
constexpr char MAX_ARG_LENGTH = 64;

class interface
{	
public:
	interface();
	 ~interface();
	

	void parse_command(char command[1024]);
private:
	board * _board;
	search_tree _search_tree;

	void info();
	void call_command(char argv[MAX_ARG_LENGTH][MAX_ARG_NUMBER]);
	void isready(char argv[MAX_ARG_LENGTH][MAX_ARG_NUMBER]);
	void position(char argv[MAX_ARG_LENGTH][MAX_ARG_NUMBER]);
	void go(char argv[MAX_ARG_LENGTH][MAX_ARG_NUMBER]);

};




#endif