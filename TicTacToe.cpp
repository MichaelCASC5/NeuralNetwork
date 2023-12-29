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
    for (int i = 0; i < 9; i++) {
        board_[i] = empty; // all cell values are empty
    }
    for (int i = 0; i < 9; i++) {
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
        } else {
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
    if (is_player_one_turn){
        board_[user_input] = X;
    }
    else{
        board_[user_input] = O;
    }
}

/**
 * a random space is chosen is chosen and inputs O
*/
void TicTacToe::computerPlayerTurn(){
    srand(time(NULL));
    bool notset; 
    while(notset){
        int x = rand()%9;
        if(board_[x]!= 0){
            board_[x] = O;
        }
        else {
            continue;
        }
    }

}

/**
 * @post: prints a tictactoe board using cell values from board_
 * Example: [ ][O][ ] 
 *          [ ][ ][X]
 *          [X][ ][ ]
*/
void TicTacToe::displayBoard(){
   
    // angus
    for(int i = 0; i< 9; i ++ ){
        if(board_[i] == 1){
            std :: cout << "[" << "x";
        }
        else if (board_[i] == 2)
        {   
            std :: cout  << "[" << "o"<<"]";
        }
        else{
            std :: cout<<"[ ]";
        }
        if(i == 2 || i == 5|| i == 8){
            std :: cout<<std::endl;
        }
    }
}

/**
 * @post: if is_player_one_turn true, changes to false and vice versa
*/
void TicTacToe::togglePlayer(){
    // angus
    is_player_one_turn = true;
}  

/**
 * checks if there is three in a row or no more spaces left
 * @return: true if there is a winner or draw, false if not
 * @post: if there is a winner, print who winner is
*/
bool TicTacToe::gameOver(){
    if(board_[0] == board_[1]== board_[2]){
        return true;
    }
    if (board_[0] == board_[3] == board_[6])
    {
        return true;
    }
    if (board_[0] == board_[4] == board_[8])
    {
        return true;
    }
    if (board_[2] == board_[5] == board_[8])
    {
        return true;
    }
    if (board_[6] == board_[7] == board_[8])
    {
        return true;
    }
    if (board_[3] == board_[4] == board_[5])
    {
        return true;
    }
    if (board_[2] == board_[4] == board_[6])
    {
        return true;
    }
    if (board_[1] == board_[4] == board_[7])
    {
        return true;
    }
    return false;
}

/**
 * @post: sets up a game with two humans
*/
bool TicTacToe::twoPlayerGame(){
    // while(!gameOver){
    //     humanPlayerTurn();
    //     togglePlayer();
    // }
}

/**
 * @post: sets up a game with a human and dumb computer
*/
bool TicTacToe::onePlayerGame(){


}

int main (){

    TicTacToe x; 
    x.displayBoard();
}