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
            emptyCell.island = -1; // -1 stands for no island
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

cellList *getOrthogonalCells(board *pboard, int row, int col){
    assert(isInBoard(pboard, row, col));
    cellList *list = initCellList();
    int ort_row, ort_col;
    int cases[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (int i = 0; i < 4; i++)
        {
            ort_row = row + cases[i][0];
            ort_col = col + cases[i][1];
            if (isInBoard(pboard, ort_row, ort_col))
            {
                appendToCellList(list, &(pboard -> grid[ort_row][ort_col]));
            }
            
        }
    return list;
}

// ---------------
// --- DISPLAY ---
// ---------------

void printBoard(board *pboard)
// Prints board to terminal
{
    cell *pc;
    for (size_t i = 0; i < (pboard -> rows); i++) {
        for (size_t j = 0; j < (pboard -> cols); j++) {
            printCell(&(pboard -> grid[i][j]));
        }
        printf("\n");
    }
}