/**
 * Created by Michael Calle, Allison Lee, Angus Hu on December 27, 2023
*/

#ifndef TIC_TAC_TOE_HPP
#define TIC_TAC_TOE_HPP

#include <iostream>
#include <vector>

enum EndResult{Draw, XWins, OWins};

class TicTacToe{
private:
    // a board has 9 cells, each cell can have value of empty, X, or O
    std::vector<int> board_;
    // an array of cells that are empty
    std::vector<int> available_spaces_;
    // bool representing if player one's turn
    bool is_player_one_turn;
public:
    /**
     * Default constructor makes a game of TicTacToe
    */
    TicTacToe();

    /**
     * a human chooses an available space and inputs X, player can only be X. That space then becomes unavailable
    */
    void humanPlayerTurn();

    /**
     * a random space is chosen is chosen and inputs O
    */
    void computerPlayerTurn();

    /**
     * takes cell values of board and displays, empty cells represented by #
    */
    void displayBoard() const; 

    /**
     * if player one, changes to player two and vice versa
    */
    void togglePlayer(); 

    /**
     * @return: true if no spaces left, every element in available_space_ is 0
    */
    bool checkNoSpaces() const;

    /**
     * @return: true if three cells in a row are the same non empty value
    */
    bool checkThreeInRow() const;

    /**
     * checks if there is three in a row or no more spaces left
     * @return: true if there is a winner or draw, false if not
    */
    bool gameOver() const;

    /**
     * a game with two humans
    */
    bool twoPlayerGame(); 

    /**
     * a game with a human and computer
    */
    bool onePlayerGame();

};

#endif