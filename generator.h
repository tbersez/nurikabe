#include "board.h"
#include <stdbool.h>

bool isPoolSafe(board *pboard, int row, int col);
cellType landOrWater();
void asignCell(board *pboard, int row, int col, cellType status);
void fillEmptyCells(board *pboard);
void floodBoard(board *pboard);