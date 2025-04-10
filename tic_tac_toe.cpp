#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <limits>
#include <SFML/Graphics.hpp>

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

string checkWinner(const vector<vector<char>>& board) {

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
    int c_x = 1;
    int c_y = 1;
    char w = ' ';
    sf::RenderWindow window(sf::VideoMode({600, 600}), "Tic-Tac-Toe");

    float space = 0.3f * 600.f;
    float size = 0.8f * space;
    float width = 0.1f * size;

    sf::CircleShape o;
    sf::RectangleShape x;
    sf::RectangleShape line;
    sf::RectangleShape c;
    sf::RectangleShape wline;
    o.setPointCount(60);

    auto drawX = [&](float pos_x, float pos_y) {
        x.setOrigin(x.getGeometricCenter());
        x.setFillColor(sf::Color(170, 255, 0));
        x.setSize({200.f, 20.f});
        x.setPosition({pos_x, pos_y});
        x.setRotation(sf::degrees(45.f));
        window.draw(x);
        x.setRotation(sf::degrees(-45.f));
        window.draw(x);
    };

    auto drawO = [&](float pos_x, float pos_y) {
        o.setRadius(90.f);
        o.setOrigin(o.getGeometricCenter());
        o.setFillColor(sf::Color::Transparent);
        o.setOutlineColor(sf::Color(0, 170, 255));
        o.setOutlineThickness(-20.f);
        o.setPosition({pos_x, pos_y});
        window.draw(o);
    };

    auto drawW = [&](float pos_x, float pos_y, float angle, float s = 1.f) {
        wline.setOrigin(line.getGeometricCenter());
        wline.setSize({1000.f * s, 10.f});
        wline.setPosition({pos_x, pos_y});
        wline.setFillColor(sf::Color::White);
        wline.setRotation(sf::degrees(angle));
        window.draw(wline);
    };

    auto drawC = [&](float pos_x, float pos_y) {
        c.setSize({200.f, 200.f});
        c.setOrigin(c.getGeometricCenter());
        c.setPosition({pos_x, pos_y});
        c.setFillColor(sf::Color::Transparent);
        c.setOutlineColor(sf::Color::White);
        c.setOutlineThickness(-10.f);
        window.draw(c);
    };

    auto drawG = [&](float space, float width, float position_x, float position_y) {
        line.setSize({space * 3, width});
        line.setOrigin(line.getGeometricCenter());
        line.setFillColor(sf::Color(128, 128, 128));
        line.setRotation(sf::degrees(0.f));
        line.setPosition({position_x, position_y - space / 2});
        window.draw(line);
        line.setPosition({position_x, position_y + space / 2});
        window.draw(line);
        line.setRotation(sf::degrees(90.f));
        line.setPosition({position_x - space / 2, position_y});
        window.draw(line);
        line.setPosition({position_x + space / 2, position_y});
        window.draw(line);
    };

    while (window.isOpen()) {
        window.clear(sf::Color(64, 64, 64));
        drawG(space, width / 4, 300.f, 300.f);

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (auto* key = event->getIf<sf::Event::KeyPressed>()) {
                if (result == "ongoing") {
                    if (isXPlayer) {
                        if ((key->scancode == sf::Keyboard::Scancode::A) && (c_x > 0)) c_x--;
                        else if ((key->scancode == sf::Keyboard::Scancode::D) && (c_x < 2)) c_x++;
                        else if ((key->scancode == sf::Keyboard::Scancode::W) && (c_y > 0)) c_y--;
                        else if ((key->scancode == sf::Keyboard::Scancode::S) && (c_y < 2)) c_y++;
                        if ((key->scancode == sf::Keyboard::Scancode::Space) && (board[c_y][c_x] == ' ')) {
                            board[c_y][c_x] = 'X';
                            isXPlayer = !isXPlayer;
                            result = checkWinner(board);
                        }
                    }
                }
                if (key->scancode == sf::Keyboard::Scancode::R) {
                    for (int i = 0; i < 3; ++i)
                        for (int j = 0; j < 3; ++j)
                            board[i][j] = ' ';
                    result = "ongoing";
                    isXPlayer = true;
                    c_x = 1;
                    c_y = 1;
                    w = ' ';
                }
            }
        }

        if (result == "ongoing" && !isXPlayer) {
            pair<int, int> bestMove = getBestMove(board, false);
            board[bestMove.first][bestMove.second] = 'O';
            isXPlayer = !isXPlayer;
            result = checkWinner(board);
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 'O') {
                    drawO(300.f + 200.f * (j - 1), 300.f + 200.f * (i - 1));
                }
                if (board[i][j] == 'X') {
                    drawX(300.f + 200.f * (j - 1), 300.f + 200.f * (i - 1));
                }
            }
        }

        w = ' ';

        for (int i = 0; i < 3; ++i) {
            if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
                drawW(300.f, 300.f + 200.f * (i - 1), 0.f);
                w = board[i][0];
            }
        }
        // Check columns
        for (int j = 0; j < 3; ++j) {
            if (board[0][j] != ' ' && board[0][j] == board[1][j] && board[1][j] == board[2][j]) {
                drawW(300.f + 200.f * (j - 1), 300.f, 90.f);
                w = board[0][j];
            }
        }
        // Check diagonals
        if ((board[0][2] != ' ') && (board[0][2] == board[1][1]) && (board[1][1] == board[2][0])) {
            drawW(300.f, 300.f, -45.f, 1.4f);
            w = board[1][1];
        }
        if ((board[0][0] != ' ') && (board[0][0] == board[1][1]) && (board[1][1] == board[2][2])) {
            drawW(300.f, 300.f, 45.f, 1.4f);
            w = board[1][1];
        }

        if (result == "ongoing") drawC(300.f + 200.f * (c_x - 1), 300.f + 200.f * (c_y - 1));

        window.display();
    }

    return 0;
}