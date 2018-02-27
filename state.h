#ifndef STATE_H
#define STATE_H
#define TICTACTOE_MAX_SIZE 5

typedef struct state
{
	// Contains the state of the board.
	// X = 1
	// O = 2
	// No Marking = 0
	int board[TICTACTOE_MAX_SIZE][TICTACTOE_MAX_SIZE];
	int board_size;
	int current_player;
} state;

typedef struct coordinates
{
	int row;
	int column;
} coordinates;

// Initializes the given state.
void init_state(state *s);

// Place a marking on the board.
// Next player is automatically determined (alternates between X and O).
// Return 0 if the move was successful.
// Return 1 if the cell is already occupied.
// Return 2 if the given coordinates were out of bound.
int make_move(state *s, coordinates c);

// Check who won the game.
// X Wins = 1
// O Wins = 2
// Not Over = 0
// Tie = 3
int check_game_over(state *s);
#endif
