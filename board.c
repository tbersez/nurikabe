#include "board.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

// -------------------------
// --- BOARD INITIALIZER ---
// -------------------------

board *initBoard(int n_rows, int n_cols)
// Initialize board with empty cells
{
    board *pboard;
    cell emptyCell;
    pboard = malloc(sizeof(board));
    pboard -> rows = n_rows;
    pboard -> cols = n_cols;
    pboard -> grid = malloc(n_rows * sizeof(cell *));
    for (size_t i = 0; i < n_rows; i++) { 
        pboard -> grid[i] = malloc(n_cols * sizeof(cell));
        for (size_t j = 0; j < n_cols; j++) {
            emptyCell.row = i;
            emptyCell.col = j;
            emptyCell.island = 0;
            pboard -> grid[i][j] = emptyCell;

        }
    }
    return pboard;
}
// --------------------------
// --- BOARD MANIPULATION ---
// --------------------------

bool isInBoard(board *pboard, int row, int col)
{
    int n_rows = pboard -> rows;
    int n_cols = pboard -> cols;
    if (row >= 0 && row < n_rows && col >= 0 && col < n_cols)
    {
        return true;
    }
    return false;
}

cellType getStatus(board *pboard, int row, int col)
// Returns true is a cell is flooded
{
    cell c = pboard -> grid[row][col];
    return c.type;
}

// cellNode *getOrthogonalCells(board *pboard, int row, int col){
//     assert(isInBoard(pboard, row, col));
//     cellNode *list = initCellList(&((pboard -> grid[row][col])));
//     // int cases[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
//     // int new_row, new_col;
//     // for (int i = 0; i < 4; i++)
//     //     {
//     //         new_row = row + cases[i][0];
//     //         new_col = col + cases[i][1];
//     //         if (isInBoard(pboard, new_row, new_col))
//     //         {
//     //             /* code */
//     //         }
            
//     //     }
//     return list;
// }

// ----------------------
// --- FLOODING RULES ---
// ----------------------

bool isPoolSafe(board *pboard, int row, int col)
// Checks if flooding [row][col] creates a 2x2
// pool or not. There is 4 possible pools per cell.
{
    int n_rows = pboard -> rows;
    int n_cols = pboard -> cols;
    // Upper left pool
    if (row != 0 && col != 0)
    {
        if (getStatus(pboard, row - 1, col - 1) == WATER && getStatus(pboard, row, col - 1) == WATER && getStatus(pboard, row - 1, col) == WATER)
        {
            return false;
        }
    }
    // Lower left pool
    if (row != (n_rows - 1) && col != 0)
    {
        if (getStatus(pboard, row + 1, col - 1) == WATER && getStatus(pboard, row, col - 1) == WATER && getStatus(pboard, row + 1, col) == WATER)
        {
            return false;
        }
    }
    // Upper right pool
    if (row != 0 && col != (n_cols - 1))
    {
        if (getStatus(pboard, row - 1, col) == WATER && getStatus(pboard, row - 1, col + 1) == WATER && getStatus(pboard, row, col + 1) == WATER)
        {
            return false;
        }
    }
    // Lower right pool
    if (row != (n_rows - 1) && col != (n_cols - 1))
    {
        if (getStatus(pboard, row + 1, col) == WATER && getStatus(pboard, row, col + 1) == WATER && getStatus(pboard, row + 1, col + 1) == WATER)
        {
            return false;
        }
    }
    return true;
}

// --------------------------
// --- FLOODING ALGORITHM ---
// --------------------------

cellType landOrWater()
// Randomly pick between land and water
{
    int landLikelyhood = 33;
    int cursor = rand() % 100;
    if (cursor <= landLikelyhood)
    {
        return LAND;
    }
    return WATER;
}

void asignCell(board *pboard, int row, int col, cellType status)
{
    setCellStatus(&(pboard -> grid[row][col]), status);
    if (status == WATER) {
        int cases[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int new_row, new_col;
        for (int i = 0; i < 4; i++)
        {
            new_row = row + cases[i][0];
            new_col = col + cases[i][1];
            if (isInBoard(pboard, new_row, new_col) && (getStatus(pboard, new_row, new_col) == EMPTY))
            {
                if (isPoolSafe(pboard, new_row, new_col) == false)
                {
                    setCellStatus(&(pboard -> grid[new_row][new_col]), LAND);
                } else {
                    asignCell(pboard, new_row, new_col, landOrWater());
                }
            }
        }
    }
}

void fillEmptyCells(board *pboard)
// Turns empty cells into land
{
    cell *pcell;
    int n_rows = pboard -> rows;
    int n_cols = pboard -> cols;
    for (size_t i = 0; i < n_rows; i++) { 
        for (size_t j = 0; j < n_cols; j++) {
            pcell = &(pboard -> grid[i][j]);
            if (pcell -> type == EMPTY)
            {
                setCellStatus(pcell, LAND);
            }
        }
    }
}

void floodBoard(board *pboard)
// Creates the water area
{   
    int seed_row, seed_col;
    seed_row = rand() % (pboard -> rows);
    seed_col = rand() % (pboard -> cols);
    asignCell(pboard, seed_row, seed_col, WATER);
    fillEmptyCells(pboard);
}

// ---------------
// --- ISLANDS ---
// ---------------

void markAsIsland(board *pboard, int row, int col, int islandId){}

// ---------------
// --- DISPLAY ---
// ---------------

void printBoard(board *pboard)
// Prints board to terminal
{
    for (size_t i = 0; i < (pboard -> rows); i++) {
        for (size_t j = 0; j < (pboard -> cols); j++) {
            printCell(&(pboard -> grid[i][j]));
        }
        printf("\n");
    }
}