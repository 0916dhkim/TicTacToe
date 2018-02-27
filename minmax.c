#include <minmax.h>
#include <stdlib.h> // malloc
#define MAX_UTILITY 1000000 // utility value of win state.
#define MAX_DEPTH 3 // Maximum depth of search in game tree.

// Allocate a new node in memory.
// Make sure to free the resulting node!
node *new_node();

node *clone_node(node *original);

// Given the root of a game tree,
// free the entire tree.
void free_tree(node *root);

// Add a child node to the given node.
void add_child_node(node *parent, node *child);

// Generate children of the given node.
// Each child represents a possible action on current state.
void generate_children_node(node *parent);

// Generate game tree to given depth.
void generate_game_tree(node *root, int depth);

// Calculate the utility value of a terminal node's state.
int calculate_utility(state *s);

// Calculate the utility value of just one case.
// ex. 1 triple in vertical direction.
int calculate_utility_one_case(int c1, int c2, int c3);

// Calculate the utility value of parent nodes
// from children nodes.
int recursive_utility_check(node *tree);

node *new_node()
{
    // Allocate new node;
    node *n = malloc(sizeof(node));

    // Initialize pointers.
    n->leftmost_child = NULL;
    n->right_sibling = NULL;

    return n;
}

node *clone_node(node *original)
{
    // Allocate new node.
    node *n = new_node();

    // Copy original state.
    n->s = original->s;

    return n;
}

void free_tree(node *root)
{
    if (root->right_sibling != NULL)
    {
        // If root has a right sibling
        free_tree(root->right_sibling);
    }

    if (root->leftmost_child != NULL)
    {
        // If root has a child
        free_tree(root->leftmost_child);
    }

    // Free the root node.
    free(root);
}

void add_child_node(node *parent, node *child)
{
    node *n = parent->leftmost_child;

    if (n == NULL)
    {
        // If parent node does not have any child node.
        // Assign the given node as the leftmost child of the parent node.
        parent->leftmost_child = child;
    }
    else
    {
        // If parent node has at least one child node.
        // Find the rightmost child.
        while (n->right_sibling != NULL)
        {
            n = n->right_sibling;
        }

        // Now n is the rightmost child.
        n->right_sibling = child;
    }
}

void generate_children_node(node *parent)
{
    int i, j;

    // For all coordinates on the board.
    for (i = 0; i < parent->s.board_size; i++)
    {
        for (j = 0;j < parent->s.board_size;j++)
        {
            node *n = clone_node(parent);

            // Check if move to coordinate (i, j) is legal.
            coordinates c;
            c.row = i;
            c.column = j;
            int move_result = make_move(&(n->s), c);
            if (move_result == 0)
            {
                // Move success.
                // Add the cloned node to parent.
                add_child_node(parent, n);
            }
            else
            {
                // Move fail.
                // Free the cloned node.
                free_tree(n);
            }
        }
    }
}

void generate_game_tree(node *root, int depth)
{
    if (depth == 1 || check_game_over(&(root->s)) != 0)
    {
        return;
    }
    else
    {
        generate_children_node(root);
        node *n = root->leftmost_child;
        while (n != NULL)
        {
            generate_game_tree(n, depth - 1);
            n = n->right_sibling;
        }
        return;
    }
}

int calculate_utility(state *s)
{
    // In perspective of player X:
    // A combination 1 move away from win state is +10.
    // A combination 2 moves away from win state is +1.
    // A combination 1 move away from lose state is -10.
    // A combination 2 moves away from lose state is -1.
    // A win state is MAX_UTILITY.
    // A lose state is -MAX_UTILITY.

    int utility = 0;

    // Check every win case.
    int i, j;
    for (i = 0; i < s->board_size; i++)
    {
        for (j = 0; j < s->board_size; j++)
        {
            int case_utility;
            // Check vertical.
            if (i < s->board_size - 2)
            {
                case_utility = calculate_utility_one_case(s->board[i][j], s->board[i + 1][j], s->board[i + 2][j]);
                if (case_utility == MAX_UTILITY || case_utility == -MAX_UTILITY) return case_utility;
                else utility += case_utility;
            }

            // Check horizontal.
            if (j < s->board_size - 2)
            {
                case_utility = calculate_utility_one_case(s->board[i][j], s->board[i][j + 1], s->board[i][j + 2]);
                if (case_utility == MAX_UTILITY || case_utility == -MAX_UTILITY) return case_utility;
                else utility += case_utility;
            }

            // Check right diagonal.
            if (i < s->board_size - 2 && j < s->board_size - 2)
            {
                case_utility = calculate_utility_one_case(s->board[i][j], s->board[i + 1][j + 1], s->board[i + 2][j + 2]);
                if (case_utility == MAX_UTILITY || case_utility == -MAX_UTILITY) return case_utility;
                else utility += case_utility;
            }

            // Check left diagonal.
            if (i < s->board_size - 2 && j >= 2)
            {
                case_utility = calculate_utility_one_case(s->board[i][j], s->board[i + 1][j - 1], s->board[i + 2][j - 2]);
                if (case_utility == MAX_UTILITY || case_utility == -MAX_UTILITY) return case_utility;
                else utility += case_utility;
            }
        }
    }

    return utility;
}

int calculate_utility_one_case(int c1, int c2, int c3)
{
    int empty = !c1 + !c2 + !c3; // Number of empty cells.
    int x = c1 % 2 + c2 % 2 + c3 % 2; // Number of X marks.
    int o = c1 / 2 + c2 / 2 + c3 / 2; // Number of O marks.

    if (empty == 2)
    {
        // Either X or O has one cell occupied.
        return x - o;
    }
    else if (empty == 1)
    {
        if (x == 2)
        {
            // X is 1 move away from win state.
            return 10;
        }
        else if (o == 2)
        {
            // O is 1 move away from win state.
            return -10;
        }
        else
        {
            // Each player has one cell occupied.
            // No chance of win in this case.
            return 0;
        }
    }
    else if (empty == 0)
    {
        if (x == 3)
        {
            // X win state.
            return MAX_UTILITY;
        }
        else if (o == 3)
        {
            // O win state.
            return -MAX_UTILITY;
        }
        else
        {
            // All three cells are occupied,
            // but there is no winner.
            // No chance of win in this case.
            return 0;
        }
    }
    else
    {
        // empty == 3
        // All three cells are empty.
        return 0;
    }
}

int recursive_utility_check(node *tree)
{
    int ret;
    if (tree->leftmost_child == NULL)
    {
        // Terminal node.
        ret = calculate_utility(&(tree->s));
    }
    else
    {
        node *n = tree->leftmost_child;
        int recursive_utility;
        // Non-terminal node.
        if (tree->s.current_player == 1)
        {
            // Player X's turn.
            // Pick max.
            ret = -MAX_UTILITY;
            while (n != NULL)
            {
                recursive_utility = recursive_utility_check(n);
                if (recursive_utility > ret) ret = recursive_utility;
                n = n->right_sibling;
            }
        }
        else
        {
            // Player O's turn.
            // Pick min.
            ret = MAX_UTILITY;
            while (n != NULL)
            {
                recursive_utility = recursive_utility_check(n);
                if (recursive_utility < ret) ret = recursive_utility;
                n = n->right_sibling;
            }
        }
    }

    return ret;
}

coordinates determine_next_move(state s)
{
    node *tree = new_node(); // Root node of game tree.
    tree->s = s; // Initial state.

    generate_game_tree(tree, MAX_DEPTH);

    node *n = tree->leftmost_child;
    state *desired_state = &(tree->leftmost_child->s);
    int desired_utility = tree->s.current_player == 1 ? -MAX_UTILITY : MAX_UTILITY;

    while (n != NULL)
    {
        int recursive_utility = recursive_utility_check(n);

        if (tree->s.current_player == 1)
        {
            // Current player is X.
            // Need to find max.
            if (recursive_utility > desired_utility)
            {
                desired_utility = recursive_utility;
                desired_state = &(n->s);
            }
        }
        else
        {
            // Current player is O.
            // Need to find min.
            if (recursive_utility < desired_utility)
            {
                desired_utility = recursive_utility;
                desired_state = &(n->s);
            }
        }

        n = n->right_sibling;
    }

    // Found the desired state.
    // Calculate the move to get to the desired state.
    int i, j;
    coordinates ret;
    for (i = 0; i < desired_state->board_size; i++)
    {
        for (j = 0; j < desired_state->board_size; j++)
        {
            if (tree->s.board[i][j] != desired_state->board[i][j])
            {
                // Find one cell that is different in desired state from current state.
                // Return the coordinate of the different cell.
                ret.row = i;
                ret.column = j;
            }
        }
    }

    // Free game tree
    free_tree(tree);

    return ret;
}