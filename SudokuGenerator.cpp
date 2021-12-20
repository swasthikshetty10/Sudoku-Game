#include <iostream>
#include <algorithm>
#include <ctime>
#include <string>
#include <vector>
#include "SudokuSolver.cpp"
#define UNASSIGNED 0

using namespace std;

class SudokuGenerator : virtual SudokuSolver
{
private:
    int solnGrid[9][9];
    int guessNum[9];
    int gridPos[81];
    bool grid_status;

public:
    int grid[9][9];
    SudokuGenerator();
    void createSeed();
    void printGrid();
    void countSoln(int &number);
    void genPuzzle();
    bool solveGrid();
    bool verifyGridStatus();
};

// Function to Generate random number
int genRandNum(int maxLimit)
{
    return rand() % maxLimit;
}

// Function to Create seed grid
void SudokuGenerator::createSeed()
{
    this->solveGrid();
    // Saving the solution grid
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            this->solnGrid[i][j] = this->grid[i][j];
}

// Function to Intialising
SudokuGenerator::SudokuGenerator()
{
    srand(time(NULL));
    // Randomly shuffling the array of removing grid positions
    for (int i = 0; i < 81; i++)
        this->gridPos[i] = i;

    random_shuffle(this->gridPos, (this->gridPos) + 81, genRandNum);
    // Randomly shuffling the guessing number array
    for (int i = 0; i < 9; i++)
        this->guessNum[i] = i + 1;

    random_shuffle(this->guessNum, (this->guessNum) + 9, genRandNum);

    // Initialising the grid
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            this->grid[i][j] = 0;
        }
    }
    grid_status = true;
}

//  Verification status of the custom grid passed
bool SudokuGenerator::verifyGridStatus()
{
    return grid_status;
}

// Function to Check if the grid is uniquely solvable
void SudokuGenerator::countSoln(int &number)
{
    int row, col;

    if (!FindUnassignedLocation(this->grid, row, col))
    {
        number++;
        return;
    }

    for (int i = 0; i < 9 && number < 2; i++)
    {
        if (isSafe(this->grid, row, col, this->guessNum[i]))
        {
            this->grid[row][col] = this->guessNum[i];
            countSoln(number);
        }

        this->grid[row][col] = UNASSIGNED;
    }
}
bool SudokuGenerator::solveGrid()
{
    int row, col;

    // If there is no unassigned location, we are done
    if (!FindUnassignedLocation(this->grid, row, col))
        return true; // success!

    // Consider digits 1 to 9
    for (int num = 0; num < 9; num++)
    {
        // if looks promising
        if (isSafe(this->grid, row, col, this->guessNum[num]))
        {
            // make tentative assignment
            this->grid[row][col] = this->guessNum[num];

            // return, if success
            if (solveGrid())
                return true;

            // failure, undo & try again
            this->grid[row][col] = UNASSIGNED;
        }
    }

    return false; // this triggers backtracking
}

// Function to Gneerate puzzle
void SudokuGenerator::genPuzzle()
{
    for (int i = 0; i < 81; i++)
    {
        int x = (this->gridPos[i]) / 9;
        int y = (this->gridPos[i]) % 9;
        int temp = this->grid[x][y];
        this->grid[x][y] = UNASSIGNED;

        // If now more than 1 solution , replace the removed cell back.
        int check = 0;
        countSoln(check);
        if (check != 1)
        {
            this->grid[x][y] = temp;
        }
    }
}
