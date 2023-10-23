#include "generator.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

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
    int new_row, new_col;
    cell *pc;
    cellList *list = initCellList();
    setCellStatus(&(pboard -> grid[row][col]), status);
    list = getOrthogonalCells(pboard, row, col);
    if (status == WATER) {
        pc = popCellList(list);
        while (pc != NULL)
        {
            new_row = pc -> row;
            new_col = pc -> col;
            if (isInBoard(pboard, new_row, new_col) && (getStatus(pboard, new_row, new_col) == EMPTY))
            {
                if (isPoolSafe(pboard, new_row, new_col) == false)
                {
                    setCellStatus(&(pboard -> grid[new_row][new_col]), LAND);
                } else {
                    asignCell(pboard, new_row, new_col, landOrWater());
                }
            }
            pc = popCellList(list);
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