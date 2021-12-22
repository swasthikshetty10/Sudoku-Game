#include <bits/stdc++.h>
#include <windows.h>
#include "SudokuGenerator.cpp"
#include "ScoreHandler.cpp"
#define N 9
using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // To set text color
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
    ScoreHandler Score;

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
            system("cls||clear"); // Clear screen
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
                    Score.startime(); // start time to record score;
                    system("cls||clear");
                    cout << "Hi " << player_name << " Solve this :                                                         | Enter 0 & 0 to exit   \n";
                    printGrid(grid);
                    cout << "Enter Row & Column:\n ";
                    cin >> row >> col;
                    if (row == 0 & col == 0)
                    {
                        system("cls||clear");
                        cout << "Solution : " << endl;
                        printGrid(puzzle->grid);
                        cout << "press any key to exit ... \n";
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
                            Score.endtime(); // end time to record score;
                            Score.setHighScore(player_name);
                            cout << "You Won :) \n";
                            cout << "Press any key to exit ..." << endl;
                            cin >> temp;
                        }
                    }
                }
            }
            if (choice - '0' == 2)
            {
                Score.display();
                cout << "Press any key to exit ..." << endl;
                cin >> temp;
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
        solved = 0;
        for (int i = 0; i < 9; i++)
        {
            SetConsoleTextAttribute(hConsole, 3); // setting Light Aqua as text color for console
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
                        if (grid[i][j] == Qgrid[i][j])
                            SetConsoleTextAttribute(hConsole, 7); // setting white as text color
                        else
                            SetConsoleTextAttribute(hConsole, 2); // setting green as text color
                        cout << grid[i][j];
                        solved++;
                    }
                    else
                    {
                        SetConsoleTextAttribute(hConsole, 4); // setting red as text color
                        cout << grid[i][j];
                    }
                }
                else
                {
                    SetConsoleTextAttribute(hConsole, 3);
                    cout << '-';
                }
                SetConsoleTextAttribute(hConsole, 3);
            }
            cout << " | \n";
        }
        cout << " -------------------------\n";
        SetConsoleTextAttribute(hConsole, 7);
    }
    // function  check if entered location valid
    bool isValid(int row, int col)
    {
        if (Qgrid[row][col] == 0)
            return 1;
        else
            return 0;
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
