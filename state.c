#include <state.h>

void init_state(state *s)
{
	// Fill the board with 0s.
	int i, j;
	for (i = 0; i < s->board_size; i++)
	{
		for (j = 0; j < s->board_size; j++)
		{
			s->board[i][j] = 0;
		}
	}

	// X plays first.
	s->current_player = 1;
}

// Make the next player to play its turn.
void switch_player(state *s)
{
	if (s->current_player == 1)
		s->current_player = 2;
	else if (s->current_player == 2)
		s->current_player = 1;
}

int make_move(state *s, coordinates c)
{
	if (c.row < 0 || c.column < 0 || c.row >= s->board_size || c.column >= s->board_size)
	{
		// If the given coordinates were out of bound.
		return 2;
	}
	else if (s->board[c.row][c.column] != 0)
	{
		// If the cell is already occupied
		return 1;
	}
	else
	{
		// If the cell is not occupied,
		// mark the cell and end turn.
		s->board[c.row][c.column] = s->current_player;
		switch_player(s);

		return 0;
	}
}

int check_game_over(state *s)
{
	int i, j;
	int full = 1;

	for (i = 0; i < s->board_size; i++)
	{
		for (j = 0; j < s->board_size; j++)
		{
			// Check full.
			if (s->board[i][j] == 0)
			{
				// Coordinate i,j is empty.
				full = 0;
			}
			else
			{
				// Coordinate i,j is not empty.

				// Check vertical.
				if (i < s->board_size - 2 && s->board[i][j] == s->board[i + 1][j] && s->board[i][j] == s->board[i + 2][j])
					return s->board[i][j];
				// Check horizontal.
				else if (j < s->board_size - 2 && s->board[i][j] == s->board[i][j + 1] && s->board[i][j] == s->board[i][j + 2])
					return s->board[i][j];
				// Check right diagonal.
				else if (i < s->board_size - 2 && j < s->board_size - 2 && s->board[i][j] == s->board[i + 1][j + 1] && s->board[i][j] == s->board[i + 2][j + 2])
					return s->board[i][j];
				// Check left diagonal.
				else if (i < s->board_size - 2 && j >= 2 && s->board[i][j] == s->board[i + 1][j - 1] && s->board[i][j] == s->board[i + 2][j - 2])
					return s->board[i][j];
			}
		}
	}

	if (full)
		return 3; // Tie.
	else
		return 0; // Not over.
}
