#ifndef MINMAX_H
#define MINMAX_H
#include <state.h>
// This file defines data structures and functions to implement
// the minimax algorithm for tic-tac-toe AI.

// Node of game tree
typedef struct node
{
    state s;
    struct node *leftmost_child;
    struct node *right_sibling;
} node;

// Decide next move with Minmax Algorithm.
// Assume state s is not a end state.
coordinates determine_next_move(state s);
#endif