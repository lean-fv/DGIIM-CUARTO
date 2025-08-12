// generator.cpp
#include "../include/generator.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Function to get a random number from the vector without repetition.
 * @param v The vector from which to get the random number
 * @return A random number from the vector
 */
int getNum(vector<int>& v) {
    // Size of the vector
    int n = v.size();

    // Generate a random number
    // Make sure the number is within the index range
    int index = rand() % n;

    // Get random number from the vector
    int num = v[index];

    // Remove the number from the vector
    swap(v[index], v[n-1]);
    v.pop_back();

    // Return the removed number
    return num;
}
////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Function to generate a random vector of n different numbers.
 * @param n The number of different numbers to generate
 * @return A vector of n different random numbers
 */
vector<int> generateRandom(int n) {
    vector<int> v(n-1);

    // Fill the vector with the values 1, 2, 3, ..., n - 1
    for (int i = 1; i < n; i++) v[i-1] = i;

    vector<int> u;

    for (int i = 0; i < 3; i++) u.push_back(getNum(v));

    return u;
}
////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Function to generate a permuted matrix.
 * @param n The size of the matrix (n x n)
 * @return A permuted matrix of size n x n
 */
vector<vector<int>> generateBoard(int n) {
    
    srand(time(NULL));

    int n_squared = n*n;
    vector<int> permutation(n_squared);

    // Fill the board with the numbers from 0 to n^2 - 1
    for (int i = 0; i < n_squared; i++) permutation[i] = i;

    // Do the permutations
    for (int i = 0; i < N_PERMUTATIONS; i++) {
        
        vector<int> swapper = generateRandom(n_squared);
        
        int swap = permutation[swapper[0]];
        permutation[swapper[0]] = permutation[swapper[1]];
        permutation[swapper[1]] = swap;

        swap = permutation[swapper[2]];
        permutation[swapper[2]] = permutation[swapper[0]];
        permutation[swapper[0]] = swap;
    }


    // Constructing the new permuted matrix
    int index = 0;
    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = permutation[index++];
        }
    }

    return matrix;
}
////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Function to show a matrix.
 * @param matrix The matrix to show
 */
void showMatrix(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl << endl;
    }
}
////////////////////////////////////////////////////////////////////////////////////////