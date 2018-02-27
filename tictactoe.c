#include <stdio.h>
#include <state.h>
#include <tournament.h>
#include <minmax.h>
#include <misc.h>

int main()
{
	tournament t;
	init_tournament(&t);
	t.bestof = prompt_tournament();

	// Play games until tournament ends.
	int tournament_result;
	do
	{
		// Declare and initialize new board state.
		state s;
		s.board_size = prompt_board_size();
		init_state(&s);

		// Determine the human player.
		int human_player = prompt_initial_player();

		print_board(&s);

		// Make moves until game ends.
		int game_result;
		do
		{
            if (s.current_player == human_player)
            {
                // Player turn.
                while (make_move(&s, prompt_next_move()))
                {
                }
            }
            else
            {
                // Computer turn.
                make_move(&s, determine_next_move(s));
            }

			print_board(&s);

			// Determine game result.
			game_result = check_game_over(&s);
			print_game_result(game_result);
		} while (game_result == 0);

		// Update tournament data and check tournament over.
		update_tournament(&t, game_result, human_player);
		tournament_result = check_tournament_over(&t);

		print_tournament_result(&t);
	} while (tournament_result == 0);
	return 0;
}
