#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#include "board.h"

// --- MAIN ---
int main(){
    const int ROWS = 10;
    const int COLS = 10;
    board *pboard = initBoard(ROWS, COLS);
    printBoard(pboard);
    return 0;
}