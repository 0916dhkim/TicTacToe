#include <tournament.h>

void init_tournament(tournament *t)
{
    t->human = 0;
    t->computer = 0;
    t->tie = 0;
}

int check_tournament_over(tournament *t)
{
    if (t->human > t->bestof / 2)
    {
        // Human has won more than half of the games.
        return 1;
    }
    else if (t->computer > t->bestof / 2)
    {
        // Computer has won more than half of the games.
        return 2;
    }
    else if (t->human + t->computer + t->tie == t->bestof)
    {
        // Players have finished playing all games.
        if (t->human > t->computer)
        {
            // Human has won more games than computer.
            return 1;
        }
        else if (t->computer > t->human)
        {
            // Computer has won more games than human.
            return 2;
        }
        else
        {
            // Human and computer has won same number of games.
            return 3;
        }
    }
    else
    {
        // Tournament is not over.
        return 0;
    }
}

void update_tournament(tournament *t, int game_result, int human_player)
{
    switch (game_result)
    {
    case 1:
    case 2:
        if (game_result == human_player) t->human++;
        else t->computer++;
        break;
    case 3:
        t->tie++;
        break;
    default:
        break;
    }
}
