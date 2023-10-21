#include "board.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

board *initBoard(int n_rows, int n_cols)
{
    board *pboard;
    cell emptyCell;
    pboard = malloc(sizeof(board));
    pboard -> rows = n_rows;
    pboard -> cols = n_cols;
    pboard -> grid = malloc(n_rows * sizeof(cell *));
    for (size_t i = 0; i < n_rows; i++) { 
        pboard -> grid[i] = malloc(n_cols * sizeof(cell));
        for (size_t j = 1; j < n_cols; j++) {
            emptyCell.row = i;
            emptyCell.col = j;
            pboard -> grid[i][j] = emptyCell;

        }
    }
    return pboard;
}

void printBoard(board *pboard)
{
    for (size_t i = 0; i < (pboard -> rows); i++) {
        for (size_t j = 0; j < (pboard -> cols); j++) {
            printCell(&(pboard -> grid[i][j]));
        }
        printf("\n");
    }
}