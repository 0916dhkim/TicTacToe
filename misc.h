#ifndef MISC_H
#define MISC_H
#include <state.h>
#include <tournament.h>

// Ask the user for the board size.
// Return the desired board size.
int prompt_board_size();

// Ask the user if one wants to play first or second.
// Return 1 if the user plays first.
// Return 2 otherwise.
int prompt_initial_player();

// Ask the user for the next move.
coordinates prompt_next_move();

// Ask the user to define the tournament.
// Return value is x if the tournament is best of x games.
int prompt_tournament();

void print_board(state *s);

// Print the result of the game.
// Pass the return value of check_game_over()
void print_game_result(int game_result);

// Print the result of the tournament.
void print_tournament_result(tournament *t);
#endif