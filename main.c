#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#include "generator.h"

// --- MAIN ---
int main(){
    srand(time(NULL));
    const int ROWS = 20;
    const int COLS = 20;
    board *pboard = initBoard(ROWS, COLS);
    floodBoard(pboard);
    printBoard(pboard);
    return 0;
}