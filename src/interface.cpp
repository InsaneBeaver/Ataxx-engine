#include "interface.h"


interface::interface()
{
	_board = new board();
	_board->init_board();
}

interface::~interface()
{
	delete _board;
}


void interface::parse_command(char command[1024])
{
	if(command == NULL) return;
	char argv[MAX_ARG_LENGTH][MAX_ARG_NUMBER] = {{0}};
	int i_argv = 0;
	int i_arg = 0;
	
	bool is_in_quotation_marks = false;
	char current_char;
	for(int i_command = 0; command[i_command] != '\0'; i_command++)
	{
		current_char = command[i_command];
		if(current_char == '\n')
			break;

		else if(current_char == '"') 
			is_in_quotation_marks = !is_in_quotation_marks;

		else if(current_char == ' ' && !is_in_quotation_marks && i_arg != 0)
		{
			i_argv++;
			i_arg = 0;
		}
		
		else
		{
			argv[i_argv][i_arg] = current_char;
			i_arg++;
		}
	}
	call_command(argv);
	
}

void interface::call_command(char argv[MAX_ARG_LENGTH][MAX_ARG_NUMBER])
{
	if(strcmp(argv[0], "position") == 0)
		position(argv);
	
	else if(strcmp(argv[0], "go") == 0)
		go(argv);
	
	else if(strcmp(argv[0], "isready") == 0)
		isready(argv);
	
	else if(strcmp(argv[0], "quit") == 0)
		exit(0);

	else
		printf("Unknown command: %s\n", argv[0]);
}

void interface::position(char argv[MAX_ARG_LENGTH][MAX_ARG_NUMBER])
{

	int i_argv = 1;
	if(strcmp(argv[i_argv], "fen") == 0)
	{
		_board->load_board(argv[1]);
		i_argv += 2;
	}
	
	else if(strcmp(argv[i_argv], "startpos") == 0)
	{
		_board->init_board();
		i_argv++;
	}
	
	if(strcmp(argv[i_argv], "moves") == 0)
	{
		while((argv[++i_argv][0] != 0))
			_board->play_move(get_move((char*)argv[i_argv], _board->side_to_move));
		
	}	
	_board->print_board();

}

void interface::go(char argv[MAX_ARG_LENGTH][MAX_ARG_NUMBER])
{
	int depth = 9;
	uint64_t max_time = 1e09;
	
	for(int i = 1; argv[i][0] != 0; i++)
	{
		if(strcmp(argv[i], "depth") == 0)
		{
			depth = atoi(argv[i + 1]);
			i++;
		}
		else if(strcmp(argv[i], "movetime") == 0)
		{
			max_time = atoi(argv[i + 1]);
			i++;
		}
	}
	_search_tree.start_search(depth, max_time, *_board);

	info();
}

void interface::isready(char argv[MAX_ARG_LENGTH][MAX_ARG_NUMBER])
{
	printf("readyok\n");
}

void interface::info()
{
	short int pv[MAX_DEPTH];
	_search_tree.get_pv(pv);
	int search_time = _search_tree.get_search_time();
	int node_count = _search_tree.get_node_count();
	int nps = search_time != 0 ? node_count / search_time * 1000 : -1;
	int depth = _search_tree.get_depth();
	int score = floor(_search_tree.get_score() * 100);

	char bestmove_repr[4];
	get_move_repr(bestmove_repr, pv[0]);

	char pv_repr[MAX_DEPTH * 4] = {0};
	int i_pv_repr = 0;
	for(int i_pv = 0; pv[i_pv] != 0; i_pv++)
	{
		while(pv_repr[i_pv_repr] != 0) i_pv_repr++;
		
		if(i_pv != 0) 
		{
			pv_repr[i_pv_repr] = ' ';
			i_pv_repr++;
		}

		get_move_repr(&pv_repr[i_pv_repr], pv[i_pv]);
	}
	printf("info depth %i score %i time %i nodes %i nps %i ", depth, score, search_time, node_count, nps);
	printf("pv %s\n", pv_repr);
	printf("bestmove %s\n", bestmove_repr);
}