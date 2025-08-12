#include "../include/generator.h"
#include "../include/A_star.h"

using namespace std;

int main() {
    int n; // Length of the board

    // Presentation
    cout << "Welcome to the (n^2 - 1)-puzzle solver!!!!!" << endl;

    do{
        cout << "Introduce a board size between " << LOWER_BOUND << " and " << UPPER_BOUND << ": ";
        cin >> n;
    }while (n < LOWER_BOUND || n > UPPER_BOUND);

    // Generate the board
    cout << "You chose the board size: " << n << " x " << n << endl;
    if (n == 4) cout << "You will play the famous 15-puzzle!!!!" << endl;
    cout << "Your puzzle to solve is: " << endl << endl;

    vector<vector<int>> board;

    // Generate a board that is not a solution
    do{
        board = generateBoard(n);
    }while (isSolution(board));

    pair<int, int> pos0 = findEmptyTile(board);
    showMatrix(board);

    int option;
    do{
        cout << "Press 0 to solve the puzzle by yourself or 1 to solve it automatically: ";
        cin >> option;
    }while (option != 0 && option != 1);
    cout << endl;

    // Manual Solver
    if (option == 0) {
        char move;

        do {
            cout << "You chose to solve the puzzle by yourself!!!!" << endl;
            cout << "Use the following keys to move the empty tile: " << endl;
            cout << "W: Move the empty tile down" << endl;
            cout << "S: Move the empty tile up" << endl;
            cout << "A: Move the empty tile right" << endl;
            cout << "D: Move the empty tile left" << endl;
            cout << "Q: Quit the game" << endl;
            cout << endl;
            showMatrix(board);

            cout << "Select a key: ";
            cin >> move;
            cout << endl;

            if (move == 'w' || move == 'a' || move == 's' || move == 'd') {
                Action move_s = stringToAction(move);
                pos0 = permutateBoard(board, pos0, move_s);
                actionToString(move_s);
            } else if (move != 'q') {
                cout << "Select a valid key!!!!" << endl << endl;
            }
        } while (!isSolution(board) && move != 'q');

        // Not playing anymore
        if (move == 'q') cout << "You quit the game!!!!" << endl;
        else cout << "The puzzle has been solved!!!!" << endl;
    }
    // Automatic Solver
    else {
        cout << "You chose to solve the puzzle automatically!!!!" << endl;
        cout << endl << "Solving the puzzle..." << endl;

        list<Action> moves = A_star(board);

        cout << "The solution is: " << endl << endl;
        showMatrix(board);

        for (auto it = moves.begin(); it != moves.end(); it++) {
            cout << actionToString(*it) << endl;
            pos0 = permutateBoard(board, pos0, *it);
            showMatrix(board);
        }
        cout << endl << "The puzzle has been solved!!!!" << endl;
    }
    cout << "////////////////////////////////////////////////////////////" << endl;
    
    return 0;
}