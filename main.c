#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#include "board.h"

// --- MAIN ---
int main(){
    srand(time(NULL));
    const int ROWS = 7;
    const int COLS = 7;
    board *pboard = initBoard(ROWS, COLS);
    floodBoard(pboard);
    printBoard(pboard);
    cellList *list = initCellList();
    appendToCellList(list, &(pboard -> grid[0][0]));
    appendToCellList(list, &(pboard -> grid[2][3]));
    printCellList(list);
    return 0;
}