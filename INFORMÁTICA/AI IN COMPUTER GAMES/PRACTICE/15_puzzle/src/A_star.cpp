// A_star.cpp
#include "../include/A_star.h"

using namespace std;


////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Function to calculate the Manhattan distance heuristic.
 * @param board The state of the board
 * @return The Manhattan distance heuristic value
 */
int ManhattanDistanceHeuristic(const vector<vector<int>>& board) {
    int cost = 0;
    int n = board.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] != 0)
                cost += abs(i - board[i][j] / n) + abs(j - board[i][j] % n);
        }
    }
    return cost;
}
////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Function to calculate the Inversion distance heuristic.
 * @param board The state of the board
 * @return The Inversion distance heuristic value
 */
int InversionDistanceHeuristic(const vector<vector<int>>& board) {
    
    int n = board.size();
    int inversion_count = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n-1; j++) {
            if (board[i][j] != 0 && board[i][j] > board[i][j+1]) inversion_count++;
            if (board[j][i] != 0 && board[j][i] > board[j+1][i]) inversion_count++;
        }
    }
    
    return inversion_count/3 + inversion_count%3;
}
////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Function to calculate the Walking distance heuristic.
 * @param board The state of the board
 * @return The Walking distance heuristic value
 */
double WalkingDistanceHeuristic(const vector<vector<int>>& board, double weight) {
    return ManhattanDistanceHeuristic(board) + weight*InversionDistanceHeuristic(board);
}
////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Function to find the empty tile on the board.
 * @param board The state of the board
 * @return The position of the empty tile
 */
pair<int,int> findEmptyTile(const vector<vector<int>>& board) {
    int n = board.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 0)
                return pair<int,int>(i, j);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Function to determine if a board is a solution.
 * @param board The state of the board
 * @return True if the board is a solution, false otherwise
 */
bool isSolution(const vector<vector<int>>& board) {
    int n = board.size();
    bool isSolution = true;

    for (int i = 0; i < n && isSolution; i++) {
        for (int j = 0; j < n && isSolution; j++) {
            if (board[i][j] != i*n + j)
                isSolution = false;
        }
    }

    return isSolution;
}
////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Function to permutate the tiles of the board.
 * @param board The state of the board
 * @param pos0 The position of the empty tile
 * @param action The action to perform
 * @return The new position of the empty tile
 */
pair<int,int> permutateBoard(vector<vector<int>>& board, const pair<int,int>& pos0, const Action& action) {
    int i = pos0.first;
    int j = pos0.second;

    switch (action) {
        case Action::DOWN:
            if (i != 0) {
                swap(board[i][j], board[i-1][j]);
                i = i-1;
            }
            break;
        case Action::UP:
            if (i != board.size()-1) {
                swap(board[i][j], board[i+1][j]);
                i = i+1;
            }
            break;
        case Action::RIGHT:
            if (j != 0) {
                swap(board[i][j], board[i][j-1]);
                j = j-1;
            }
            break;
        case Action::LEFT:
            if (j != board.size()-1) {
                swap(board[i][j], board[i][j+1]);
                j = j+1;
            }
            break;
    }

    return pair<int,int>(i, j);
}
////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Function to generate a child node by applying an action to the current node.
 * @param current_node The current node
 * @param action The action to apply
 * @return The generated child node
 */
node Apply(const node& n, const Action& action) {
    
    vector<vector<int>> board = n.board;
    int cost = n.cost;
    pair<int,int> pos0 = n.pos0;
    int i = pos0.first;
    int j = pos0.second;
    list<Action> moves = n.moves;

    if ((action == Action::UP && i != board.size()-1) ||
        (action == Action::DOWN && i != 0) ||
        (action == Action::LEFT && j != board.size()-1) ||
        (action == Action::RIGHT && j != 0)) {
        pos0 = permutateBoard(board, pos0, action);
        cost++;
        moves.push_back(action);
    }

    return node(board, cost, pos0, moves);
}
////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief A* algorithm to solve the puzzle.
 * @param board The initial state of the board
 * @return The list of actions to solve the puzzle
 */
list<Action> A_star(const vector<vector<int>>& board) {
    
    node current_node(board, 0, findEmptyTile(board), list<Action>());
    priority_queue<node, vector<node>, Comparer> frontier;
    set<node> explored;
    list<Action> moves;

    bool solutionFound = isSolution(current_node.board);
    frontier.push(current_node);

    while (!solutionFound && !frontier.empty()) {
        frontier.pop();
        explored.insert(current_node);

        if (isSolution(current_node.board)) solutionFound = true;

        if (!solutionFound) {
            // Generate child UP
            node child_up = Apply(current_node, Action::UP);
            if (explored.find(child_up) == explored.end()) frontier.push(child_up);
        }

        if (!solutionFound) {
            // Generate child DOWN
            node child_down = Apply(current_node, Action::DOWN);
            if (explored.find(child_down) == explored.end()) frontier.push(child_down);
        }

        if (!solutionFound) {
            // Generate child LEFT
            node child_left = Apply(current_node, Action::LEFT);
            if (explored.find(child_left) == explored.end()) frontier.push(child_left);
        }

        if (!solutionFound) {
            // Generate child RIGHT
            node child_right = Apply(current_node, Action::RIGHT);
            if (explored.find(child_right) == explored.end()) frontier.push(child_right);
        }

        if (!solutionFound and !frontier.empty()) {
            current_node = frontier.top();
            while (!frontier.empty() && explored.find(current_node) != explored.end()) {
                frontier.pop();
                if (!frontier.empty())
                    current_node = frontier.top();
            }
        }

        if (solutionFound) moves = current_node.moves;
    }

    return moves;
}
////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Function to convert the string to actions.
 * @param action The string to convert
 * @return The action representation of the string
 */
Action stringToAction(char action) {
    switch (action) {
        case 'w': return Action::UP;
        case 's': return Action::DOWN;
        case 'a': return Action::LEFT;
        case 'd': return Action::RIGHT;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Function to convert the actions to string.
 * @param action The action to convert
 * @return The string representation of the action
 */
string actionToString(const Action& action) {
    switch (action) {
        case Action::UP: return "UP";
        case Action::DOWN: return "DOWN";
        case Action::LEFT: return "LEFT";
        case Action::RIGHT: return "RIGHT";
    }
}
////////////////////////////////////////////////////////////////////////////////////////////