#include <iostream>
#include <vector>

using namespace std;

bool isSafe(vector<vector<char>>& board, int row, int col, int n) {
    // Check if there is any queen in the same column
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 'Q') {
            return false;
        }
    }

    // Check if there is any queen in the upper left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 'Q') {
            return false;
        }
    }

    // Check if there is any queen in the upper right diagonal
    for (int i = row, j = col; i >= 0 && j < n; i--, j++) {
        if (board[i][j] == 'Q') {
            return false;
        }
    }

    return true;
}

void solveNQueens(vector<vector<char>>& board, int row, int n, int queensLeft, int& count) {
    if (queensLeft == 0) {
        // Found a valid configuration, increment the count
        count++;

        // Print the board
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << board[i][j];
            }
            cout << endl;
        }
        cout << endl;

        return;
    }

    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col, n)) {
            // Place the queen
            board[row][col] = 'Q';

            // Move to the next row
            solveNQueens(board, row + 1, n, queensLeft - 1, count);

            // Backtrack and remove the queen
            board[row][col] = '.';
        }
    }
}

void solveNQueens(int n, int k) {
    vector<vector<char>> board(n, vector<char>(n, '.'));

    int count = 0;
    solveNQueens(board, 0, n, k, count);

    cout << count << endl;
}

int main() {
    int n;
    cin >> n;

    int k;
    cin >> k;

    solveNQueens(n, k);

    return 0;
}

// cai tien bang branch and bound

// alpha beta pruning?

// bien the: thay hậu bằng mã, xe, ...

