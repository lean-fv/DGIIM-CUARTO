// A_star.h
#ifndef A_STAR_H
#define A_STAR_H

#include <queue>
#include <vector>
#include <list>
#include <unordered_set>
#include <set>
#include <cmath>
#include <string>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Enum to represent the possible moves in the puzzle.
 */
enum class Action {
    UP,    // Move the empty tile down
    DOWN,  // Move the empty tile up
    LEFT,  // Move the empty tile right
    RIGHT  // Move the empty tile left
};
////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Node structure to store the state of the board, the cost, and the moves made.
 */
struct node {
    vector<vector<int>> board; // The current state of the board
    int cost;                  // The real cost to reach this node
    pair<int, int> pos0;       // The position of the empty tile on the board
    list<Action> moves;        // The list of moves made to reach this node

    /**
     * @brief Default constructor for the node.
     */
    node() {
        this->cost = 0;
    }

    /**
     * @brief Parameterized constructor for the node.
     * @param board The state of the board
     * @param cost The cost to reach this node
     * @param pos0 The position of the empty tile
     * @param moves The list of moves made to reach this node
     */
    node(const vector<vector<int>>& board, int cost, const pair<int, int>& pos0, const list<Action>& moves) {
        this->board = board;
        this->cost = cost;
        this->pos0 = pos0;
        this->moves = moves;
    }

    /**
     * @brief Copy constructor for the node.
     * @param other The node to copy from
     */
    node(const node& other) { *this = other; }

    /**
     * @brief Overloading the assignment operator to copy the values of a node.
     * @param other The node to copy from
     * @return A reference to the assigned node
     */
    node& operator=(const node& other) {
        if (this != &other) {
            this->board = other.board;
            this->cost = other.cost;
            this->pos0 = other.pos0;
            this->moves = other.moves;
        }
        return *this;
    }

    /**
     * @brief Overloading the equality operator to compare two nodes.
     * @param other The node to compare with
     * @return True if the boards are equal, false otherwise
     */
    bool operator==(const node& other) const { return this->board == other.board; }

    /**
     * @brief Overloading the less-than operator to compare two nodes.
     * @param other The node to compare with
     * @return True if this node is less than the other node, false otherwise
     */
    bool operator<(const node& other) const { return this->board < other.board; }
};


////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Function to calculate the Manhattan distance heuristic.
 * @param board The state of the board
 * @return The Manhattan distance heuristic value
 */
int ManhattanDistanceHeuristic(const vector<vector<int>>& board);
////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Function to calculate the Inversion distance heuristic.
 * @param board The state of the board
 * @return The Inversion distance heuristic value
 */
int InversionDistanceHeuristic(const vector<vector<int>>& board);
////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Function to calculate the Walking distance heuristic.
 * @param board The state of the board
 * @param weight The weight for the heuristic
 * @return The Walking distance heuristic value
 */
double WalkingDistanceHeuristic(const vector<vector<int>>& board, double weight = 2);
////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Functor for the priority queue to compare nodes based on their cost.
 */
class Comparer {
public:
    /**
     * @brief Comparison operator to compare two nodes.
     * @param a The first node
     * @param b The second node
     * @return True if the cost of node a is greater than the cost of node b, false otherwise
     */
    bool operator()(const node& a, const node& b) {
        return a.cost + WalkingDistanceHeuristic(a.board) > b.cost + WalkingDistanceHeuristic(b.board);
    }
};
////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Hash function for the unordered set to hash nodes.
 */
class Hash {
public:
    /**
     * @brief Hash function to generate a hash value for a node.
     * @param node The node to hash
     * @return The hash value of the node
     */
    size_t operator()(const node& node) const {
        size_t hashValue = 0;
        hash<int> hashInt; // Hash Function for integers

        for (int i = 0; i < node.board.size(); i++) {
            for (int j = 0; j < node.board[i].size(); j++) {
                hashValue ^= hashInt(node.board[i][j]) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
            }
        }
        return hashValue;
    }
};
////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Function to find the empty tile on the board.
 * @param board The state of the board
 * @return The position of the empty tile
 */
pair<int,int> findEmptyTile(const vector<vector<int>>& board);
////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Function to determine if a board is a solution.
 * @param board The state of the board
 * @return True if the board is a solution, false otherwise
 */
bool isSolution(const vector<vector<int>>& board);
////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Function to permutate the tiles of the board.
 * @param board The state of the board
 * @param pos0 The position of the empty tile
 * @param action The action to perform
 * @return The new position of the empty tile
 */
pair<int,int> permutateBoard(vector<vector<int>>& board, const pair<int,int>& pos0, const Action& action);
////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Function to generate a child node by applying an action to the current node.
 * @param current_node The current node
 * @param action The action to apply
 * @return The generated child node
 */
node Apply(const node& n, const Action& action);
////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief A* algorithm to solve the puzzle.
 * @param board The initial state of the board
 * @return The list of actions to solve the puzzle
 */
list<Action> A_star(const vector<vector<int>>& board);
////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Function to convert the string to actions.
 * @param action The string to convert
 * @return The action representation of the string
 */
Action stringToAction(char action);
////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Function to convert the actions to string.
 * @param action The action to convert
 * @return The string representation of the action
 */
string actionToString(const Action& action);
////////////////////////////////////////////////////////////////////////////////////////////////

#endif // A_STAR_H