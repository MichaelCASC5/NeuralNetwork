/**
 * Created by Michael Calle, Allison Lee, Angus Hu on December 27, 2023
*/

enum cell{empty, X, O};

class TicTacToe{
private:
    // a board has 9 cells, each cell can have value of empty, X, or O
    cell board_[9]; 
    // an array of cells that are empty
    cell available_spaces_[9];
public:
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
    void displayBoard(); 

    /**
     * if player one, changes to player two and vice versa
    */
    void togglePlayer(); 

    /**
     * a game with two humans
    */
    void twoPlayerGame(); 

    /**
     * a game with a human and computer
    */
    void onePlayerGame();

};