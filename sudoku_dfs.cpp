// Sudoku Solver using BFS

#include <bits/stdc++.h>
using namespace std;

// Sudoku solver using DFS (backtracking)
// Board is 9x9 with '.' or '0' for empty cells

bool isValid(vector<vector<char>>& board, int row, int col, char c) {
    for (int i = 0; i < 9; i++) {
        // check row
        if (board[row][i] == c) return false;
        // check column
        if (board[i][col] == c) return false;
        // check 3x3 block
        int br = 3 * (row / 3) + i / 3;
        int bc = 3 * (col / 3) + i % 3;
        if (board[br][bc] == c) return false;
    }
    return true;
}

bool dfs(vector<vector<char>>& board) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] == '.' || board[row][col] == '0') {
                for (char c = '1'; c <= '9'; c++) {
                    if (isValid(board, row, col, c)) {
                        board[row][col] = c;
                        if (dfs(board)) return true;
                        board[row][col] = '.'; // backtrack
                    }
                }
                return false; // no valid number found, trigger backtracking
            }
        }
    }
    // no empty cell left, solution found
    return true;
}

void solveSudoku(vector<vector<char>>& board) {
    dfs(board);
}

int main() {
    vector<vector<char>> board(9, vector<char>(9));
    cout << "Enter the Sudoku puzzle (use . or 0 for empty):" << endl;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> board[i][j];
        }
    }

    solveSudoku(board);

    cout << "Solved Sudoku:" << endl;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << board[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}
