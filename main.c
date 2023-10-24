#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#include "generator.h"

// --- MAIN ---
int main(){
    srand(time(NULL));
    const int ROWS = 10;
    const int COLS = 10;
    board *pboard = initBoard(ROWS, COLS);
    floodBoard(pboard);
    printBoard(pboard);
    return 0;
}