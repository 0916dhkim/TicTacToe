#include <stdio.h>
#include <misc.h>
#include <stdlib.h> // atoi
#define MAX_INPUT_LENGTH 100
#define MAX_BOARD_SIZE 5
#define MIN_BOARD_SIZE 3

int prompt_board_size()
{
	// Return variable.
	int ret = 0;
	// Space to hold the user response.
	char response[MAX_INPUT_LENGTH];

	while (ret == 0)
	{
		printf("How big do you want your board to be?(3-5) ");
		fgets(response, MAX_INPUT_LENGTH, stdin);

		ret = atoi(response);

		if (ret < MIN_BOARD_SIZE || ret > MAX_BOARD_SIZE)
		{
			// ret is out of bound.
			ret = 0; // Ask again.
		}
		else
		{
			// ret is inside boundary.
			return ret;
		}
	}

	// This shouldn't be reachable.
	return -1;
}

int prompt_initial_player()
{
	// Space to hold the user response.
	char response[MAX_INPUT_LENGTH];

	do
	{
		printf("Do you want to go first?(y/n) ");
		fgets(response, MAX_INPUT_LENGTH, stdin);

		switch (response[0])
		{
		case 'y':
		case 'Y':
			return 1;
		case 'n':
		case 'N':
			return 2;
		default:
			response[0] = 0; // Ask again.
			break;
		}
	} while (!response[0]); // Ask again if the response was illegal.

	// This shouldn't be reachable.
	return -1;
}

coordinates prompt_next_move()
{
	// Return coordinate variable.
	coordinates c;

	// Space to hold the user response.
	char response[MAX_INPUT_LENGTH];

	// Prompt user for the coordinates.
	printf("Enter row number: ");
	fgets(response, MAX_INPUT_LENGTH, stdin);
	c.row = atoi(response);
	printf("Enter column number: ");
	fgets(response, MAX_INPUT_LENGTH, stdin);
	c.column = atoi(response);

	// Convert coordinates to 0-based index.
	c.row--;
	c.column--;

	return c;
}

int prompt_tournament()
{
	// Return variable.
	int ret = 0;
	// Space to hold the user response.
	char response[MAX_INPUT_LENGTH];

	while (ret == 0)
	{
		printf("This tournament will be best of x games.\n");
		printf("Enter x: ");
		fgets(response, MAX_INPUT_LENGTH, stdin);

		ret = atoi(response);

		if (ret < 1)
		{
			// ret is less than 1.
			// Any tournament smaller than best of 1 is impossible.
			ret = 0; // Ask again.
		}
		else
		{
			// ret >= 1
			return ret;
		}
	}

	// This shouldn't be reachable.
	return -1;
}

void print_board(state *s)
{
	int i, j;
	for (i = 0; i < s->board_size; i++)
	{
		printf("%-2d", i + 1);
	}
	printf("\n");

	for (i = 0; i < s->board_size; i++)
	{
		for (j = 0; j < s->board_size; j++)
		{
			switch (s->board[i][j])
			{
			case 0:
				printf(" ");
				break;
			case 1:
				printf("X");
				break;
			case 2:
				printf("O");
				break;
			default:
				break;
			}
			if (j != s->board_size - 1)
				printf("|");
			else
				printf("%d\n", i + 1);
		}

		if (i != s->board_size - 1)
		{
			for (j = 0; j < s->board_size; j++)
			{
				printf("-");
				if (j != s->board_size - 1)
					printf("+");
				else
					printf("\n");
			}
		}
	}
}

void print_game_result(int game_result)
{
	switch (game_result)
	{
	case 1:
		printf("X Won!\n");
		break;
	case 2:
		printf("O Won!\n");
		break;
	case 3:
		printf("It Is a Tie!\n");
		break;
	default:
		break;
	}
}

void print_tournament_result(tournament *t)
{
	// Determine the result.
	int tournament_result = check_tournament_over(t);

	// Brief the score.
	int i;
	printf("+");
	for (i=0; i<16; i++) printf("-");
	printf("+\n");
	printf("|Computer : Human|\n");
	printf("| %-7d : %4d |\n", t->computer, t->human);
	printf("+");
	for (i=0; i<16; i++) printf("-");
	printf("+\n");
	printf("|%13s%-3d|\n", "Best of ", t->bestof);
	printf("+");
	for (i=0; i<16; i++) printf("-");
	printf("+\n");

	// If tournament is over, state the result.
	switch (tournament_result)
	{
	case 1:
		printf("You Won!\n");
		break;
	case 2:
		printf("You Lost!\n");
		break;
	case 3:
		printf("This is a tie. No winner.\n");
		break;
	default:
		break;
	}
}