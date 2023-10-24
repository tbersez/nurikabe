#include "cells.h"
#include <stdbool.h>

typedef struct Board
{
    int rows;
    int cols;
    cell **grid;
} board;

board *initBoard(int rows, int cols);
bool isInBoard(board *pboard, int row, int col);
cellType getStatus(board *pboard, int row, int col);
cellList *getOrthogonalCells(board *pboard, int row, int col);
void floodBoard(board *pboard);
void printBoard(board *board);