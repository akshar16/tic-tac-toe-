# Tic-Tac-Toe with Minimax AI (SFML)

This repository contains a Tic-Tac-Toe game implemented using C++ and the SFML (Simple Fast Multimedia Library) for graphics.  The game features a Minimax AI opponent.

## Features

*   **Graphical Interface:** The game is displayed within an SFML window, providing a visually appealing user experience.
*   **Human vs. AI:**  Players can play against an AI opponent powered by the Minimax algorithm.
*   **Minimax AI:** The AI utilizes the Minimax algorithm to make strategic decisions, making it a challenging opponent.
*   **Keyboard Controls:** Players can use the keyboard to navigate the game board and make moves.
*   **Reset Feature:**  A simple reset functionality allows players to restart the game.

## How to Play

1.  **Build and Run:** Compile the C++ code using a C++ compiler that supports SFML (e.g., g++ with SFML libraries linked).
    ```bash
     -std=c++17 tic_tac_toe.cpp -o sfml_test -I/opt/homebrew/include -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system
    ```
    *Replace `main.cpp` with the name of your source file.*
    *   Run the executable: `./tictactoe`
2.  **Controls:**
    *   **Move Cursor:** Use the `W`, `A`, `S`, and `D` keys (or the arrow keys) to move the cursor around the Tic-Tac-Toe board.
    *   **Place Mark:**  Press the `Space` key (or the `Enter` key) to place your mark ('X') at the currently selected cell.
    *   **Reset Game:** Press the `R` key to reset the game and start a new round.

## Code Structure

*   **`main.cpp`:** This file contains the complete C++ source code for the game. It includes:
    *   The necessary SFML headers.
    *   Game state definitions.
    *   Functions for:
        *   `checkWinner()`: Determines if there is a winner or if the game is a tie.
        *   `minimax()`: Implements the Minimax algorithm to determine the AI's optimal move.
        *   `getAvailableMoves()`: Gets a list of available moves on the board.
        *   `getBestMove()`: Uses `minimax` to determine the best move for the AI.
        *   SFML drawing functions: Draw the grid, X's, O's, cursor, and winning line.
        *   Main game loop: Manages game turns, player input, AI moves, and rendering.

## Dependencies

*   **SFML (Simple Fast Multimedia Library):** You will need to have the SFML libraries installed and linked to compile and run the code.

## Known Issues/Limitations

*   **Case Mismatch:** *This was the primary issue discussed in the previous responses.*  While the game uses uppercase 'X' and 'O' for the AI and win condition checks, the human player input was set to use lowercase 'x'.  The provided solution *corrects* this in the input, making sure that the game works as intended.  Make sure this part is working correctly and the AI works before building.
*   **No Difficulty Settings:** The AI always plays at its optimal level.
*   **Basic UI:** The graphical interface is functional, but could be enhanced with more polished visuals.
*   **Potential Improvements:** The AI's decision making process, and the presentation of the game could both be improved with more visual elements.
