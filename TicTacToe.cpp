/**
 * Created by Michael Calle, Allison Lee, Angus Hu on December 27, 2023
*/

#include "TicTacToe.hpp"

/**
 * Default constructor makes a game of TicTacToe
 * Default values of board are empty
 * Default values of available spaces are ints 1-9
 * Default value of is_player_one_turn is true
*/
TicTacToe::TicTacToe(){
    for (int i = 0; i < 9; i++)
    {
        board_[i] = empty; // all cell values are empty
    }
    for (int i = 0; i < 9; i++)
    {
        available_spaces_[i] = 1; // all spaces are available
    }
    is_player_one_turn = true; // starts with player one's turn
}

/**
 * a human chooses an available space and inputs X, player can only be X. That space then becomes unavailable
*/
void TicTacToe::humanPlayerTurn(){
    // prints a board with available spaces, blank if not available
    for (int i = 0; i < 9; i++){
        // if value is 0, prints an empty space
        if(available_spaces_[i] == 0){
            std::cout << "[ ]";
        }
        else{
            std::cout << "[" << i << "]";
        }
        if (i == 2 || i == 5 || i == 8){
            std::cout << std::endl;
        }
    }
    // user inputs a value for what space they want
    int user_input;
    std::cout << "Enter an available space: ";
    std::cin >> user_input;
    // if the input is not an avaliable space, asks user to reenter
    while (available_spaces_[user_input] != 1){
        std::cout << "Invalid input, please reenter: ";
        std::cin >> user_input;
    }
    // sets the chosen space to 0, marking that it is not available
    available_spaces_[user_input] = 0;
    // marks corresponding board space with X
    board_[user_input] = X;
}

/**
 * a random space is chosen is chosen and inputs O
*/
void TicTacToe::computerPlayerTurn(){

}

/**
 * takes cell values of board and displays, empty cells represented by #
 * Example: [#][O][#] 
 *          [#][#][X]
 *          [X][#][#]
*/
void TicTacToe::displayBoard(){
    // angus
}

/**
 * if player one, changes to player two and vice versa
*/
void TicTacToe::togglePlayer(){
    // angus
}

/**
 * checks if there is three in a row or no more spaces left
 * @return: true if there is a winner or draw, false if not
*/
bool TicTacToe::gameOver(){

}
/**
 * a game with two humans
*/
void TicTacToe::twoPlayerGame(){

}

/**
 * a game with a human and computer
*/
void TicTacToe::onePlayerGame(){

}