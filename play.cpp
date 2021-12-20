#include <bits/stdc++.h>
#include "SudokuGenerator.cpp"
using namespace std;
#define N 9

// Sudoku Game
class Sudoku : virtual SudokuSolver
{

private:
    int grid[N][N], Qgrid[N][N];
    string player_name;
    SudokuGenerator *puzzle;
    bool gameOver = 0;
    string clearscreen = "\033[2J\033[1;1H"; // Clear Screen
    int solved = 0;                          // To keep count of correct entry

public:
    // Constructor
    Sudoku()
    {
        srand(time(NULL)); // Using current time as seed for random generator
    }
    // Distructor
    ~Sudoku()
    {
        delete puzzle;
    }
    // START: Main game starts here
    void start()
    {
        int row, col, num;
        char temp, choice;
        while (1)
        {
            cout << clearscreen; // Clear screen
            cout << "--------Welcome To Sudoku Game--------\n\n";
            cout << "1 -> START\n";
            cout << "2 -> HIGH SCORE\n";
            cout << "3 -> EXIT\n\n";
            cout << "ENTER YOUR CHOICE : \n";
            cin >> choice;
            if (choice - '0' == 1) // check for choices
            {
                newGame(); // initializing new game(generating new puzzle)
                cout << "Enter your name : \n";
                cin >> player_name;
                while (gameOver != 1)
                {
                    cout << clearscreen;
                    cout << "Hi " << player_name << " Solve this :                                                         | Enter 0 & 0 to exit   \n";
                    printGrid(grid);
                    cout << "Enter Row & Column:\n ";
                    cin >> row >> col;
                    if (row == 0 & col == 0)
                    {
                        cout << clearscreen;
                        cout << "Solution : " << endl;
                        printGrid(puzzle->grid);
                        cout << "press any key to exit \n";
                        cin >> temp;
                        gameOver = 1;
                        break;
                    }
                    if (isValid(row - 1, col - 1))
                    {
                        cout << "Enter Number to be Enterd (1-9) :\n ";
                        cin >> num;
                        if (num < 10 && num > 0)
                        {
                            grid[row - 1][col - 1] = num;
                        }
                        if (solved == 81)
                        {
                            gameOver = 1;
                            cout << "You Won :) \n";
                            cout << "Press any key to exit" << endl;
                            cin >> temp;
                        }
                    }
                }
            }
            if (choice - '0' == 2)
            {
                displayHighScore();
            }
            if (choice - '0' == 3)
            {
                exit(0);
            }
        }
    }
    // function to initialize new puzzle(new object of class SudokuGenerator)
    void newGame()
    {
        puzzle = new SudokuGenerator();
        puzzle->createSeed();
        puzzle->genPuzzle();
        // making two copy of question grid
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
            {
                Qgrid[i][j] = (puzzle->grid)[i][j];
                grid[i][j] = (puzzle->grid)[i][j];
            }
        // solve question
        SolveSudoku(puzzle->grid);
        gameOver = 0;
    }
    // function to print grid to console
    void printGrid(int grid[N][N])
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if ((i == 0 | i == 3 | i == 6) && j == 0)
                    cout << " -------------------------\n";
                if (j == 0 | j == 3 | j == 6)
                    cout << " | ";
                else
                    cout << " ";
                if (grid[i][j])
                {
                    if (grid[i][j] == (puzzle->grid)[i][j])
                    {
                        cout << grid[i][j];
                    }
                    else
                    {
                        cout << grid[i][j];
                    }
                    solved++;
                }

                else
                    cout << '-';
            }
            cout << " | \n";
        }
        cout << " -------------------------\n";
    }
    // function  check if entered location valid
    bool isValid(int row, int col)
    {
        if (Qgrid[row][col] == 0)
            return 1;
        else
            return 1;
    }
    void displayHighScore()
    {
        cout << "High Score:-\n";
    }
};

// Main Function
int main()
{
    // Initializing Game object
    Sudoku Game;
    // start Game
    Game.start();
    return 0;
}
