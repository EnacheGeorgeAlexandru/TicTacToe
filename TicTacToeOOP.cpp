#include <iostream>
#include<string> 

class Tile {
    std::string type = " ";
public:
    bool isTileEmpty = 1;
    virtual void show() 
    {
        std::cout << type; 
    }
    virtual std::string get_type() 
    {
        return type;
    }
};

class X : public Tile{
    std::string type = "x";
public:
    void show() 
    {
        std::cout << type;
    }
    std::string get_type() 
    {
        return type; 
    }
};

class Zero : public Tile{
    std::string type = "0";
public:
    void show()
    { 
        std::cout << type;
    }
    std::string get_type() 
    {
        return type; 
    }  
};

class Lines {
    Tile* line[3];
    bool hadInput;
public:
    Lines()
    {
        for (int i = 0; i < 3; i++)
            line[i] = new Tile;
        hadInput = 0;
    }
    void inputLine(int i, int j, std::string s)
    {
        if (s == "x") line[j] = new X;
        if (s == "0") line[j] = new Zero;
        hadInput = 1;
    }
    bool isLineComplete()
    {
        if (hadInput == 1)
            if (line[0]->get_type() == line[1]->get_type() && line[1]->get_type() == line[2]->get_type())
                return true;
        return false;
    }
}line0,line1,line2;

class Columns {
    Tile* column[3];
    bool hadInput;
public:
    Columns()
    {
        for (int i = 0; i < 3; i++)
            column[i] = new Tile;
        hadInput = 0;
    }
    void inputColumn(int i, int j, std::string s)
    {
        if (s == "x") column[i] = new X;
        if (s == "0") column[i] = new Zero;
        hadInput = 1;
    }
    bool isColumnComplete()
    {
        if (hadInput)
            if (column[0]->get_type() == column[1]->get_type() && column[1]->get_type() == column[2]->get_type())
                return true;
        return false;
    }
}col0, col1, col2;

class Diagonals {
    Tile* diagonal[3];
    bool hadInput;
public:
    Diagonals()
    {
        for (int i = 0; i < 3; i++)
            diagonal[i] = new Tile;
        hadInput = 0;
    }
    void inputDiagonals(int i, int j, std::string s)
    {
        if (s == "x") diagonal[i] = new X;
        if (s == "0") diagonal[i] = new Zero;
        hadInput = 1;
    }
    bool isDiagonalComplete()
    {
        if (hadInput)
            if (diagonal[0]->get_type() == diagonal[1]->get_type() && diagonal[1]->get_type() == diagonal[2]->get_type())
                return true;
        return false;
    }
}firstDiagonal, secondDiagonal;

class Board {
    Tile* board[3][3];
public:
    Tile* getBoardTile(int i, int j) 
    { 
        return board[i][j]; 
    }
    void initializeBoard()
    {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                board[i][j] = new Tile;
    }
    void inputBoard(int i, int j, std::string s)
    {
        if (s == "x") board[i][j] = new X;
        if (s == "0") board[i][j] = new Zero;
        whichLine(i)->inputLine(i, j, s);
        whichColumn(j)->inputColumn(i, j, s);
        if (isOnDiagonal(i, j))
            boardInputDiagonal(i, j, s);
    }
    Lines* whichLine(int i) //!!!
    {
        if (i == 0) return &line0;
        if (i == 1) return &line1;
        if (i == 2) return &line2;
    }
    Columns* whichColumn(int j)
    {
        if (j == 0) return &col0;
        if (j == 1) return &col1;
        if (j == 2) return &col2;
    }
    bool isOnDiagonal(int i, int j)
    {
        if (i == j)
            return true;
        if (i + j == 2)
            return true;
        return false; 
    }
    void boardInputDiagonal(int i, int j, std::string s)
    {
        if (i == j)
            firstDiagonal.inputDiagonals(i, j, s);
        if (i + j == 2)
            secondDiagonal.inputDiagonals(i, j, s);
    }
    void printBoard()
    {
        for (int i = 0; i < 3; i++)
        {
            std::cout << "-------------" << "\n" << "|";
            for (int j = 0; j < 3; j++)
            {
                std::cout << " ";
                board[i][j]->show();
                std::cout << " |";
            }
            std::cout << '\n';
        }
        std::cout << "-------------" << "\n";
    }
};

class Player {
    std::string name;
    std::string xZero;
public:
    void setName() 
    { 
        std::string nameP; 
        std::cin >> nameP; 
        name = nameP;
    }
    void set_xZero() 
    { 
        std::string xZeroP; 
        std::cin >> xZeroP; 
        if (isInputXorZero(xZeroP))
            xZero = xZeroP;
        else set_xZero();
    }
    std::string getName() 
    {
        return name; 
    }
    std::string get_xZero() 
    {
        return xZero; 
    }
    bool isInputXorZero(std::string s)
    {
        if (s == "x" || s == "0")
            return true;
        return false;
    }
    std::string returnOpposite()
    {
        if (xZero == "x") return "0";
        if (xZero == "0") return "x";
    }
};

class Game {
public:
    void takeNextTurn(Board& gameBoard, Player player)
    {
        std::cout << player.getName()<<", please enter coordinates:"<<"\n";
        int i, j;
        std::cin >> i >> j;
        if (coordinatesInsideBoard(i,j) && gameBoard.getBoardTile(i,j)->isTileEmpty)
        {
            gameBoard.inputBoard(i, j, player.get_xZero());
            gameBoard.getBoardTile(i,j)->isTileEmpty = 0;
        }
        else 
        {
            std::cout << "That's not a valid input. ";
            return takeNextTurn(gameBoard, player);
        }
    }
    bool coordinatesInsideBoard(int i, int j)
    {
        if (i >= 0 && i <= 2 && j >= 0 && j <= 2)
            return true;
        return false;
    }
    bool isAnyWinner()
    {
        if (line0.isLineComplete()) return true;
        if (line1.isLineComplete()) return true;
        if (line2.isLineComplete()) return true;
        if (col0.isColumnComplete()) return true;
        if (col1.isColumnComplete()) return true;
        if (col2.isColumnComplete()) return true;
        if (firstDiagonal.isDiagonalComplete()) return true;
        if (secondDiagonal.isDiagonalComplete()) return true;
        return false;
    }
    void doGameLoop(Board& gameBoard, Player player1, Player player2)
    {
        for (int i = 0; i < 9; i++)
        {   
            if (i % 2 == 0)
            {
                takeNextTurn(gameBoard, player1);
                gameBoard.printBoard();
                if (isAnyWinner())
                {
                    std::cout << player1.getName() << " has won. Congratulations!"; 
                    return; 
                }
            }
            if (i % 2 == 1)
            {
                takeNextTurn(gameBoard, player2);
                gameBoard.printBoard();
                if (isAnyWinner()) 
                {
                    std::cout << player2.getName() << " has won. Congratulations!";
                    return;
                }
            }
        }
        std::cout << "The game has finished. It's a tie!";
    }
    void initializeGame(Board& gameBoard, Player& player1, Player& player2)
    {
        gameBoard.initializeBoard();
        std::cout << "Hello! Welcome to Tic Tac Toe!" << "\n";
        std::cout << "Enter first player's name:" << "\n";
        player1.setName();
        std::cout << player1.getName() << ", enter x if you want to play as x or 0 otherwise"<<"\n";
        player1.set_xZero();

        std::cout << "Enter second player's name:" << "\n";
        player2.setName();
        std::cout << player2.getName() << ", you will be playing as " << player1.returnOpposite();
        std::cout << ". Enter " << player1.returnOpposite() << " to start the game." << "\n";
        player2.set_xZero();
        gameBoard.printBoard();
    }
    void playGame()
    {
        Board gameBoard;
        Player player1;
        Player player2;
        initializeGame(gameBoard, player1, player2);
        doGameLoop(gameBoard, player1, player2);
    }
};

int main()
{
    Game myGame;
    myGame.playGame();
}

