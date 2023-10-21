#include "cells.h"

typedef struct Board
{
    int rows;
    int cols;
    cell **grid;
} board;

board *initBoard(int rows, int cols);
void printBoard(board *board);