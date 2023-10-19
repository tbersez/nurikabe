#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>

#define ROWS 7
#define COLS 7
#define EMPTY 0 // unasigned cell
#define WATER 1 // water cell
#define LAND 2 // land cell

void printBoard(int board[ROWS][COLS]){
    // Prints board to terminal.
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }   
}
void initBoard(int (*board)[ROWS][COLS]){
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            (*board)[i][j] = EMPTY;
        }
    }
}

bool isInBoard(int row, int col) {
    // Returns true if the [row][col] is within bounds,
    // false otherwise.
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS)
    {
        return true;
    }
    return false;
}

bool createsPool(int (*pboard)[ROWS][COLS], int row, int col){
    // Returns true if flooding [row][col] creates a pool,
    // false otherwise.
    assert(isInBoard(row, col) == true); // Safety check!
    // Upper left pool
    if (row != 0 && col != 0)
    {
        if ((*pboard)[row - 1][col - 1] == WATER && \
        (*pboard)[row][col - 1] == WATER && \
        (*pboard)[row - 1][col] == WATER)
        {
            return true;
        }
        
    }
    // Lower left pool
    if (row != ROWS && col != 0)
    {
        if ((*pboard)[row + 1][col - 1] == WATER && \
        (*pboard)[row][col - 1] == WATER && \
        (*pboard)[row + 1][col] == WATER)
        {
            return true;
        }
        
    }
    return false;
    // Upper right pool
    if (row != 0 && col != COLS)
    {
        if ((*pboard)[row - 1][col] == WATER && \
        (*pboard)[row - 1][col + 1] == WATER && \
        (*pboard)[row][col + 1] == WATER)
        {
            return true;
        }
        
    }
    return false;
    // Lower right pool
    if (row != ROWS && col != COLS)
    {
        if ((*pboard)[row + 1][col] == WATER && \
        (*pboard)[row][col + 1] == WATER && \
        (*pboard)[row + 1][col + 1] == WATER)
        {
            return true;
        }
        
    }
    return false;
}

void floodCell(int (*pboard)[ROWS][COLS], int i, int j){
    // Turns an empty cell into water, then recurse
    // on one orthogonaly adjacent cell, if possible.
    if(!createsPool(pboard, i, j)){
        (*pboard)[i][j] = WATER;
        // Upper cell
        if(isInBoard(i - 1, j) && (*pboard)[i - 1][j] != WATER){
            floodCell(pboard, i - 1, j);
        }
        // Lower cell
        if(isInBoard(i + 1, j) && (*pboard)[i + 1][j] != WATER){
            floodCell(pboard, i + 1, j);
        }
        // Left cell
        if(isInBoard(i, j - 1) && (*pboard)[i][j - 1] != WATER){
            floodCell(pboard, i, j - 1);
        }
        // Right cell
        if(isInBoard(i, j + 1) && (*pboard)[i][j + 1] != WATER){
            floodCell(pboard, i, j + 1);
        }
    }
}

void floodBoard(int (*pboard)[ROWS][COLS]){
    // Creates the water area.
    int start_i = rand() % ROWS;
    int start_j = rand() % COLS;
    floodCell(pboard, start_i, start_j);
}

// --- MAIN ---
int main(){
    srand(time(NULL));
    int board[ROWS][COLS];
    int (*pboard)[ROWS][COLS] = &board;
    floodBoard(pboard);
    printBoard(board);
    return 0;
}