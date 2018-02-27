#ifndef TOURNAMENT_H
#define TOURNAMENT_H
typedef struct tournament
{
    int bestof;
    int human;    // Number of games that human player has won.
    int computer; // Number of games that computer player has won.
    int tie;      // Number of ties.
} tournament;

// Set human, computer and tie to 0.
void init_tournament(tournament *t);

// Check who won the tournament.
// Human Wins = 1
// Computer Wins = 2
// Not Over = 0
// Tie = 3
int check_tournament_over(tournament *t);

// Given game result and human player,
// update the tournament data.
void update_tournament(tournament *t, int game_result, int human_player);
#endif