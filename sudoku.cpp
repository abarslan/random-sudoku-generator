#include <iostream>
#include <random>
#include <ctime>

using namespace std;

const int rows = 9;
const int cols = 9;

bool isOccur(int blankmap[rows][cols], int row, int col, int num) {
    // Checkpoint if number is already in the same row
    for (int i = 0; i < 9; i++) {
        if (blankmap[row][i] == num) {
            return true;
        }
    }

    // Checkpoint if number is already in the same column
    for (int i = 0; i < 9; i++) {
        if (blankmap[i][col] == num) {
            return true;
        }
    }

    int boxrow = row / 3;
    int boxcol = col / 3;

    // Checkpoint for number is already in the same 3x3 box
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (blankmap[boxrow * 3 + i][boxcol * 3 + j] == num) {
                return true;
            }
        }
    }

    return false;
}

void showmap(int blankmap[rows][cols]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << blankmap[i][j] << " ";
        }
        cout << endl;
    }
}

void createBlankMap(int blankmap[rows][cols]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            blankmap[i][j] = 0;
        }
    }
}

bool createmapunit(int blankmap[rows][cols], int row, int col) {
    if (row == rows - 1 && col == cols) {
        return true; // Successfully created the whole sudoku map
    }

    if (col == cols) {
        row++;
        col = 0;
    }

    if (blankmap[row][col] != 0) {
        return createmapunit(blankmap, row, col + 1);
    }

    for (int num = 1; num <= 9; num++) {
        if (!isOccur(blankmap, row, col, num)) {
            blankmap[row][col] = num;
            if (createmapunit(blankmap, row, col + 1)) {
                return true;
            }
            blankmap[row][col] = 0; // Reset the value
        }
    }

    return false; // No valid number found
}

int main() {
    int blankmap[rows][cols];

    mt19937 rng(static_cast<unsigned int>(time(NULL))); // Mersenne Twister Random Number Generator
    uniform_int_distribution<int> distribution(0, cols - 1);

    srand(time(NULL));
    createBlankMap(blankmap);

    // Create a permutation of column indices for randomization
    int colIndices[cols];
    for (int i = 0; i < cols; i++) {
        colIndices[i] = i;
    }
    for (int i = cols - 1; i > 0; i--) {
        int j = rng() % (i + 1);
        swap(colIndices[i], colIndices[j]);
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            createmapunit(blankmap, i, colIndices[j]);
        }
    }
    
    cout << endl << "Sudoku Map:" << endl << endl;
    showmap(blankmap);

    return 0;
}
