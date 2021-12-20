#include <iostream>
#include <algorithm>
#include <ctime>
#include <string>
#include <vector>
#define UNASSIGNED 0

using namespace std;

class SudokuGenerator
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
    bool solveGrid();
    void countSoln(int &number);
    void genPuzzle();
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

// Helper functions for solving grid
bool FindUnassignedLocation(int grid[9][9], int &row, int &col)
{
    for (row = 0; row < 9; row++)
    {
        for (col = 0; col < 9; col++)
        {
            if (grid[row][col] == UNASSIGNED)
                return true;
        }
    }

    return false;
}

bool UsedInRow(int grid[9][9], int row, int num)
{
    for (int col = 0; col < 9; col++)
    {
        if (grid[row][col] == num)
            return true;
    }

    return false;
}

bool UsedInCol(int grid[9][9], int col, int num)
{
    for (int row = 0; row < 9; row++)
    {
        if (grid[row][col] == num)
            return true;
    }

    return false;
}

bool UsedInBox(int grid[9][9], int boxStartRow, int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (grid[row + boxStartRow][col + boxStartCol] == num)
                return true;
        }
    }

    return false;
}

bool isSafe(int grid[9][9], int row, int col, int num)
{
    return !UsedInRow(grid, row, num) && !UsedInCol(grid, col, num) && !UsedInBox(grid, row - row % 3, col - col % 3, num);
}

// Modified SudokuGeneratorsolver
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
