#include <bits/stdc++.h>
using namespace std;
#define UNASSIGNED 0
#define N 9

// Sudoku Solver
class SudokuSolver
{
public:
    // Function to solve Sudoke
    bool SolveSudoku(int grid[N][N])
    {
        int row, col;

        if (!FindUnassignedLocation(grid, row, col))
            return true;
        for (int num = 1; num <= 9; num++)
            if (isSafe(grid, row, col, num))
            {
                grid[row][col] = num;

                // Return, if success
                if (SolveSudoku(grid))
                    return true;

                // Failure, unmake & try again
                grid[row][col] = UNASSIGNED;
            }
        return false;
    }
    //--Helper Functions--//

    // Check if is it safe to insert number in grid[row][col]
    bool isSafe(int grid[N][N], int row, int col, int num)
    {
        return !UsedInRow(grid, row, num) && !UsedInCol(grid, col, num) && !UsedInBox(grid, row - row % 3, col - col % 3, num) && grid[row][col] == UNASSIGNED;
    }
    // Function to find next empty block
    bool FindUnassignedLocation(int grid[N][N], int &row, int &col)
    {
        for (row = 0; row < N; row++)
            for (col = 0; col < N; col++)
                if (grid[row][col] == UNASSIGNED)
                    return true;
        return false;
    }
    // Function to check if number is present in row
    bool UsedInRow(int grid[N][N], int row, int num)
    {
        for (int col = 0; col < N; col++)
            if (grid[row][col] == num)
                return true;
        return false;
    }
    // Function to check if number is present in col
    bool UsedInCol(int grid[N][N], int col, int num)
    {
        for (int row = 0; row < N; row++)
            if (grid[row][col] == num)
                return true;
        return false;
    }
    // Function to check if number is present in 3X3 grid
    bool UsedInBox(int grid[N][N], int boxStartRow, int boxStartCol, int num)
    {
        for (int row = 0; row < 3; row++)
            for (int col = 0; col < 3; col++)
                if (grid[row + boxStartRow][col + boxStartCol] == num)
                    return true;
        return false;
    }
};
