#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <limits>

using namespace std;

struct GameState {
    bool currentPlayer;
    vector<vector<char>> board;
    int moveCount;
};

void printBoard(const vector<vector<char>>& board) {
    cout << "\tTIC-TAC-TOE GAME:" << endl;
    for (int i = 0; i < 3; ++i) {
        cout << "| " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << " |\n";
        if (i != 2) cout << "-----\n";
    }
    cout << endl;
}

// Function to check the game state (win/tie/ongoing)
string checkWinner(const vector<vector<char>>& board) {
    // Check rows
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return (board[i][0] == 'X') ? "X wins" : "O wins";
    }

    // Check columns
    for (int j = 0; j < 3; ++j) {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != ' ')
            return (board[0][j] == 'X') ? "X wins" : "O wins";
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return (board[0][0] == 'X') ? "X wins" : "O wins";
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return (board[0][2] == 'X') ? "X wins" : "O wins";

    // Check for tie
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] == ' ') return "ongoing";

    return "TIE";
}

int minimax(vector<vector<char>>& board, bool isMaximizing) {
    string result = checkWinner(board);
    if (result == "X wins") return 1;
    if (result == "O wins") return -1;
    if (result == "TIE") return 0;

    if (isMaximizing) { // Corrected logic here
        int bestScore = numeric_limits<int>::min();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    bestScore = max(bestScore, minimax(board, !isMaximizing));
                    board[i][j] = ' ';
                }
            }
        }
        return bestScore;
    } else {        // Corrected logic here
        int bestScore = numeric_limits<int>::max();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    bestScore = min(bestScore, minimax(board, !isMaximizing));
                    board[i][j] = ' ';
                }
            }
        }
        return bestScore;
    }
}


// Function to get available moves
vector<pair<int, int>> getAvailableMoves(const vector<vector<char>>& board) {
    vector<pair<int, int>> moves;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') moves.push_back({i, j});
        }
    }
    return moves;
}

pair<int, int> getBestMove(vector<vector<char>>& board, bool isMaximizing) {
    int bestScore = isMaximizing ? numeric_limits<int>::min() : numeric_limits<int>::max();
    pair<int, int> bestMove;
    char player = isMaximizing ? 'X' : 'O';

    for (auto& move : getAvailableMoves(board)) {
        board[move.first][move.second] = player;
        int score = minimax(board, !isMaximizing);
        board[move.first][move.second] = ' ';

        if (isMaximizing) {
            if (score > bestScore) {
                bestScore = score;
                bestMove = move;
            }
        } else {
            if (score < bestScore) {
                bestScore = score;
                bestMove = move;
            }
        }
    }
    return bestMove;
}

int main() {
    srand(time(0));

    vector<vector<char>> board(3, vector<char>(3, ' '));
    bool isXPlayer = true;
    string result = "ongoing";

    while (result == "ongoing") {
        printBoard(board);

        if (isXPlayer) {
            int row, col;
            while (true) {
                cout << "Enter row (0-2) and column (0-2): ";
                cin >> row >> col;

                if (row >= 0 && row <= 2 && col >= 0 && col <= 2 && board[row][col] == ' ') {
                    board[row][col] = 'X';
                    break;
                } else {
                    cout << "Invalid move. Try again.\n";
                }
            }
        } else {
            cout << "AI's turn...\n";
            pair<int, int> bestMove = getBestMove(board, false);
            board[bestMove.first][bestMove.second] = 'O';
        }

        result = checkWinner(board);
        isXPlayer = !isXPlayer;
    }

    printBoard(board);
    cout << result << endl;
    return 0;
}
