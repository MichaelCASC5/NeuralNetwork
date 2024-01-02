/**
 * Created by Michael Calle, Allison Lee, Angus Hu on December 27, 2023
*/

// #include "TicTacToe.hpp"

/**
 * Default constructor makes a game of TicTacToe
 * Default values of board are empty
 * Default values of available spaces are ints 1-9
 * Default value of is_player_one_turn is true
*/
TicTacToe::TicTacToe() {
    board_.clear();
    available_spaces_.clear();
    for (int i = 0; i < 9; i++) {
        board_.push_back(0); // all cell values are empty
    }
    for (int i = 0; i < 9; i++) {
        available_spaces_.push_back(1); // all spaces are available
    }
    is_player_one_turn = true; // starts with player one's turn
}

/**
 * a human chooses an available space and inputs X, player can only be X. That space then becomes unavailable
*/
void TicTacToe::humanPlayerTurn() {
    // prints a board with available spaces, blank if not available
    for (int i = 0; i < 9; i++) {
        // if value is 0, prints an empty space
        if(available_spaces_[i] == 0) {
            std::cout << "[ ]";
        } else {
            std::cout << "[" << i << "]";
        }
        if (i == 2 || i == 5 || i == 8) {
            std::cout << std::endl;
        }
    }
    // user inputs a value for what space they want
    int user_input;
    std::cout << "Enter an available space: ";
    std::cin >> user_input;
    // if the input is not an avaliable space, asks user to reenter
    while (available_spaces_[user_input] != 1) {
        std::cout << "Invalid input, please reenter: ";
        std::cin >> user_input;
    }
    // sets the chosen space to 0, marking that it is not available
    available_spaces_[user_input] = 0;
    // marks corresponding board space with X
    if (is_player_one_turn) {
        board_[user_input] = 1;
    } else {
        board_[user_input] = 2;
    }
}

/**
    * Decides the neural network's move during its turn
    *
    * The board's vector<int> is converted to a vector<double> that the network
    * can read. If the network is player 2 (O), the input is flipped as to represent
    * a player 1 (X) board. Then, that is propagated through the network and stored in an output
    * vector<double>. The output is interpreted to deduce where the network has 
    * decided to play on the board. If the decided move happens to be a cell that
    * is already occupied, then add 1 to the decided move until a free space is found.
    * NOTICE: In future implementation, if the decided move happens to an occupied cell,
    * choose a random cell on the board to play on.
    * Then, the chosen cell is filled with the AI's move. All necessary process is handled.
    *
    * @param network The network that will play
*/
void TicTacToe::computerPlayerTurn(Network & network) {
    //If the computer is player 2 (O), the board will be flipped so that it percieves it is player 1 (X)
    std::vector<int> boardInput;
    if (is_player_one_turn) {
        boardInput = board_;
    } else {
        boardInput = flipBoard();
    }

    //Convert board's vector<int> to vector<double> for network input
    std::vector<double> input(boardInput.begin(), boardInput.end());

    //Propagate through network
    std::vector<double> output = network.forwardPropagation(input);

    //Interpreting the computer's output to deduce where on the board to play
    int computer_input = interpretOutput(output);
    
    /**
        * IMPLEMENT: Choose a random space on the board if the chosen cell is occupied.
    */

    //Add one to the computer's decision if the cel is already occupied until a free cell is found. 
    while (available_spaces_[computer_input] != 1) {
        std::cerr << "Invalid computer input, moving up by one: " << computer_input;
        computer_input = (computer_input + 1) % 9;
    }

    // sets the chosen space to 0, marking that it is not available
    available_spaces_[computer_input] = 0;

    // marks corresponding board space with X
    if (is_player_one_turn) {
        board_[computer_input] = 1;
    } else {
        board_[computer_input] = 2;
    }
}

/**
 * @post: prints a tictactoe board using cell values from board_
 * Example: [ ][O][ ] 
 *          [ ][ ][X]
 *          [X][ ][ ]
*/
void TicTacToe::displayBoard() const {
    if (is_player_one_turn) {
        std::cout << "Player One (X): " << std::endl;
    } else {
        std::cout << "Player Two (O): " << std::endl;
    }
    for (int i = 0; i < 9; i ++ ) {
        if (board_[i] == 1) {
            std :: cout << "[X]";
        } else if (board_[i] == 2) {   
            std :: cout  << "[O]";
        } else {
            std :: cout<<"[ ]";
        }
        if (i == 2 || i == 5|| i == 8) {
            std::cout << std::endl;
        }
    }
    std::cout<< std::endl;
}

/**
 * @post: if is_player_one_turn true, changes to false and vice versa
*/
void TicTacToe::togglePlayer() {
    is_player_one_turn = !is_player_one_turn;
}

/**
 * @return: true if no spaces left, every element in available_space_ is 0
*/
bool TicTacToe::checkNoSpaces() const {
    for (int i = 0; i < 9; i ++) {
        if( available_spaces_[i] != 0) {
           return false;
        }
    }
    return true;
    
}

/**
 * @return: true if three cells in a row are the same non empty value
*/
bool TicTacToe::checkThreeInRow() const {
    // checks if three non empty cells in a row
    if ((board_[0] == board_[1] && board_[1] == board_[2]) && available_spaces_[0] == 0) {
        return true; // first row
    }
    if ((board_[3] == board_[4] && board_[4] == board_[5]) && available_spaces_[3] == 0) {
        return true; // second row
    }
    if ((board_[6] == board_[7] && board_[7] == board_[8]) && available_spaces_[6] == 0) {
        return true; // third row
    }
    if ((board_[0] == board_[3] && board_[3] == board_[6]) && available_spaces_[0] == 0) {
        return true; // first column
    }
    if ((board_[1] == board_[4] && board_[4] == board_[7]) && available_spaces_[1] == 0) {
        return true; // second column
    }
    if ((board_[2] == board_[5] && board_[5] == board_[8]) && available_spaces_[2] == 0) {
        return true; // third column
    }
    if ((board_[0] == board_[4] && board_[4] == board_[8]) && available_spaces_[0] == 0) {
        return true; // l to r diagonal
    }
    if ((board_[2] == board_[4] && board_[4] == board_[6]) && available_spaces_[2] == 0) {
        return true; // r to l diagonal
    }
    return false;
}

/**
 * checks if there is three in a row or no more spaces left
 * @return: true if there is a winner or draw, false if not
 * @post: if there is a winner, print who winner is
*/
bool TicTacToe::gameOver() const {
    return checkThreeInRow() || checkNoSpaces();
}

/**
    * Sets up a game between two human players
    * 
    * In a game loop, the human is prompted to enter the input.
    * Then the win conditions are checked. If they are not met then check
    * if the game has drawed between the players. If the game has drawed
    * return true. Player one wins if it is the first player to force the draw.
    * If the win conditions are met, then the program returns true/false depending
    * on whether player one won.
    *
    * @return If player one won the game.
*/
bool TicTacToe::twoPlayerGame() {
    bool output;
    while (1) {

        //Displays board and lets the player move
        displayBoard();
        humanPlayerTurn();
        std::cout << std::endl;
        
        //Win conditions
        if (checkThreeInRow()) {
            if (is_player_one_turn) {
                displayBoard();
                output = true;
                break;
            } else {
                displayBoard();
                output = false;
                break;
            }
        }

        //Draw
        if (checkNoSpaces()) {
            displayBoard();
            output = true;
            break;
        }

        //Switch player
        togglePlayer();
    }

    return output; 
}

/**
    * Sets up a game with a human and neural network
    * 
    * In a game loop, the human is prompted to enter the input. After the human
    * plays, the neural network plays.
    * Then the win conditions are checked. If they are not met then check
    * if the game has drawed between the players. If the game has drawed
    * return true. Player one wins if it is the first player to force the draw.
    * If the win conditions are met, then the program returns true/false depending
    * on whether player one won.
    *
    * @return If player one (human) won the game.
*/
bool TicTacToe::onePlayerGame(Network & network) {
    bool output;
    while (1) {

        //Displays board and lets the player move
        if (is_player_one_turn) {
            displayBoard();
            humanPlayerTurn();
        } else {
            computerPlayerTurn(network);
        }

        //Win conditions
        if (checkThreeInRow()) {
            if (is_player_one_turn) {
                displayBoard();
                output = true;
                break;
            } else {
                displayBoard();
                output = false;
                break;
            }
        }

        //Draw
        if (checkNoSpaces()) {
            displayBoard();
            output = true;
            break;
        }

        //Switch player
        togglePlayer();
    }

    return output; 
}

/**
    * NEURAL FUNCTIONS
*/
/**
    * Interprets neural output
    * 
    * Traverses the vector in search of the maximum value and its index. The index
    * of the greatest value is returned in order to deduce what cell the network
    * should play to during a game.
    *
    * @param vec The vector<double> that is to be searched
    * @return The index of the greatest value.
*/
int TicTacToe::interpretOutput(std::vector<double> vec) {
    //Initializing the maximum value found and its index
    double max = 0.0;
    int index = 0;

    //Loop that finds the max value and its index
    double val;
    for (int i = 0; i < vec.size(); i++) {
        val = vec[i];

        //If this particular value is greater than max, save the max and its index
        if (val > max) {
            max = val;
            index = i;
        }
    }

    return index;
}

/**
    * Flips the X and O values in the board_
    * 
    * Iterates through the board_ and checks if a cell is 1 (X) or 2 (O).
    * If the cell is X, flip it to O. If it is O, flip it to X.
    * Make a new board with those flipped values.
    * 
    * @return A vector of ints representing the flipped board_
*/
std::vector<int> TicTacToe::flipBoard() {
    //Initializing output
    std::vector<int> output;

    //Traverse board_ and push each item to output, but flip the 1s (X) and 2s (O)
    int flip;
    for (int i = 0; i < board_.size(); i++) {
        //Assign flip to the item
        flip = board_[i];

        //If that item is X, make O
        if (flip == 1) {
            flip = 2;
        } else if (flip == 2) { //if item is O, make X
            flip = 1;
        }

        //Push the flipped item to the output
        output.push_back(flip);
    }

    return output;
}