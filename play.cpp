#include <bits/stdc++.h>
#include "SudokuSolver.cpp"
#include "SudokuGenerator.cpp"
using namespace std;
#define N 9
class Sudoku : virtual SudokuSolver
{

private:
    int grid[N][N], Qgrid[N][N];
    string player_name;
    SudokuGenerator *puzzle;
    bool gameOver = 0;

public:
    Sudoku()
    {
        srand(time(NULL));
    }
    ~Sudoku()
    {
        delete puzzle;
    }
    void start()
    {
        int choice, row, col, num;
        char temp;
        while (1)
        {
            cout << "\033[2J\033[1;1H";
            cout << "--------Welcome To Sudoku Game--------"
                 << "\n\n";
            cout << "1 -> START"
                 << "\n";
            cout << "2 -> HIGH SCORE"
                 << "\n";
            cout << "3 -> EXIT"
                 << "\n\n";
            cout << "ENTER YOUR CHOICE : "
                 << "\n";
            cin >> choice;
            if (choice == 1)
            {
                delete puzzle;
                newGame();
                while (gameOver != 1)
                {
                    cout << "\033[2J\033[1;1H";
                    cout << "Solve this :                                                         | Enter 0 & 0 to exit   \n";
                    printGrid(grid);
                    cout << "Enter Row & Column:\n ";
                    cin >> row >> col;
                    if (row == 0 & col == 0)
                    {
                        cout << "\033[2J\033[1;1H";
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
                    }
                }
            }
            if (choice == 2)
            {
                cout << "High Score";
            }
            if (choice == 3)
            {
                exit(0);
            }
        }
    }
    void newGame()
    {
        puzzle = new SudokuGenerator();
        puzzle->createSeed();
        puzzle->genPuzzle();
        puzzle->calculateDifficulty();
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
            {
                Qgrid[i][j] = (puzzle->grid)[i][j];
                grid[i][j] = (puzzle->grid)[i][j];
            }
        SolveSudoku(puzzle->grid);
        gameOver = 0;
    }
    void printGrid(int grid[N][N])
    {

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if ((i == 0 | i == 3 | i == 6) && j == 0)
                    cout << " -------------------------"
                         << "\n";
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
                }
                else
                    cout << '-';
            }
            cout << " | \n";
        }
        cout << " -------------------------"
             << "\n";
    }
    bool isValid(int row, int col)
    {
        if (Qgrid[row][col] == 0)
            return 1;
        else
            return 1;
    };
};
int main()
{
    Sudoku Game;
    Game.start();
    return 0;
}
