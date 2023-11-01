#include "generator.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

// ----------------------
// --- FLOODING RULES ---
// ----------------------

bool isPoolSafe(board *pboard, int row, int col)
// Checks if flooding [row][col] creates a 2x2
// pool or not. There is 4 possible pools per cell.
{
    int n_rows = pboard -> rows;
    int n_cols = pboard -> cols;
    // Upper left pool
    if (row != 0 && col != 0)
    {
        if (getStatus(pboard, row - 1, col - 1) == WATER && getStatus(pboard, row, col - 1) == WATER && getStatus(pboard, row - 1, col) == WATER)
        {
            return false;
        }
    }
    // Lower left pool
    if (row != (n_rows - 1) && col != 0)
    {
        if (getStatus(pboard, row + 1, col - 1) == WATER && getStatus(pboard, row, col - 1) == WATER && getStatus(pboard, row + 1, col) == WATER)
        {
            return false;
        }
    }
    // Upper right pool
    if (row != 0 && col != (n_cols - 1))
    {
        if (getStatus(pboard, row - 1, col) == WATER && getStatus(pboard, row - 1, col + 1) == WATER && getStatus(pboard, row, col + 1) == WATER)
        {
            return false;
        }
    }
    // Lower right pool
    if (row != (n_rows - 1) && col != (n_cols - 1))
    {
        if (getStatus(pboard, row + 1, col) == WATER && getStatus(pboard, row, col + 1) == WATER && getStatus(pboard, row + 1, col + 1) == WATER)
        {
            return false;
        }
    }
    return true;
}

// --------------------------
// --- FLOODING ALGORITHM ---
// --------------------------

cellType landOrWater()
// Randomly pick between land and water
{
    int landLikelyhood = 33;
    int cursor = rand() % 100;
    if (cursor <= landLikelyhood)
    {
        return LAND;
    }
    return WATER;
}

void asignCell(board *pboard, int row, int col, cellType status)
{
    int new_row, new_col;
    cell *pc;
    cellList *list = initCellList();
    setCellStatus(&(pboard -> grid[row][col]), status);
    list = getOrthogonalCells(pboard, row, col);
    if (status == WATER) {
        pc = popCellList(list);
        while (pc != NULL)
        {
            new_row = pc -> row;
            new_col = pc -> col;
            if (isInBoard(pboard, new_row, new_col) && (getStatus(pboard, new_row, new_col) == EMPTY))
            {
                if (isPoolSafe(pboard, new_row, new_col) == false)
                {
                    setCellStatus(&(pboard -> grid[new_row][new_col]), LAND);
                } else {
                    asignCell(pboard, new_row, new_col, landOrWater());
                }
            }
            pc = popCellList(list);
        }
    }
}

void fillEmptyCells(board *pboard)
// Turns empty cells into land
{
    cell *pcell;
    int n_rows = pboard -> rows;
    int n_cols = pboard -> cols;
    for (size_t i = 0; i < n_rows; i++) { 
        for (size_t j = 0; j < n_cols; j++) {
            pcell = &(pboard -> grid[i][j]);
            if (pcell -> type == EMPTY)
            {
                setCellStatus(pcell, LAND);
            }
        }
    }
}

// --------------- //
// --- ISLANDS --- //
// --------------- //

void markIsland(board *pboard, int row, int col, int id)
// Marks cells as island with id then recurse orthogonaly.
{
    cell *pc;
    cellList *list = getOrthogonalCells(pboard, row, col);
    pc = &(pboard -> grid[row][col]);
    pc -> island = id;
    pc = popCellList(list);
    while (pc != NULL)
    {
        if ((pc -> type) == LAND && (pc -> island) == -1)
        {
            markIsland(pboard, pc -> row, pc -> col, id);
        }
        pc = popCellList(list);
    }
    
}

void markIslands(board *pboard)
// Mark islands of the board.
{
    int nrow, ncol, id;
    cell *pc;
    nrow = pboard -> rows;
    ncol = pboard -> cols;
    id = 0;
    for (size_t i = 0; i < nrow; i++)
    {
        for (size_t j = 0; j < ncol; j++)
        {
            pc = &(pboard -> grid[i][j]);
            if ((pc -> island) == -1 && (pc -> type) == LAND)
            {
                markIsland(pboard, i, j, id);
                id++;
            }
        }
    }
}

void unmarkIslands(board *pboard)
// Resets island markings
{
    int nrow, ncol;
    cell *pc;
    nrow = pboard -> rows;
    ncol = pboard -> cols;
    for (size_t i = 0; i < nrow; i++)
    {
        for (size_t j = 0; j < ncol; j++)
        {
            pc = &(pboard -> grid[i][j]);
            pc -> island = -1;
        }
    }
}

int countIslands(board *pboard)
// Counts the number of islands on the board
{
    cell *pc;
    int nrow, ncol, maxIslandId;
    nrow = pboard -> rows;
    ncol = pboard -> cols;
    maxIslandId = 0;
    for (size_t i = 0; i < nrow; i++)
    {
        for (size_t j = 0; j < ncol; j++)
        {
            pc = &(pboard -> grid[i][j]);
            if ((pc -> island) > maxIslandId)
            {
                maxIslandId = (pc -> island);
            }
        }
    }
    return maxIslandId + 1;
}

int *getIslandSizes(board *pboard, int nIsland)
// Return an array detailing island sizes:
// ["island Id"] = "island size"
{
    cell *pc;
    int nrow, ncol, *sizes;
    nrow = pboard -> rows;
    ncol = pboard -> cols;
    sizes = malloc(nIsland * sizeof(int));
    for (size_t i = 0; i < nrow; i++)
    {
        for (size_t j = 0; j < ncol; j++)
        {
            pc = &(pboard -> grid[i][j]);
            if ((pc -> type) == LAND, (pc -> island) != -1)
            {
                sizes[pc -> island]++;
            }
            
        }
    }
    return sizes;
}

void clearIsland(board *pboard, int islandId)
// Resets type and island attributes of the
// given island.
{
    cell *pc;
    int nrow, ncol;
    nrow = pboard -> rows;
    ncol = pboard -> cols;
    for (int i = 0; i < nrow; i++)
    {
        for (int j = 0; j < ncol; j++)
        {
            pc = &(pboard -> grid[i][j]);
            if ((pc -> island) == islandId)
            {
                pc -> island = -1;
                pc -> type = EMPTY;
            }
            
        }
    }

}

// ----------------------- //
// --- HINTS PLACEMENT --- //
// ----------------------- //

void placeHints(board *pboard, int *sizes, int nIslands)
// Places hints randomly on islands
{
    int nrows, ncols, nCell, counter;
    cell *pc;
    bool placedHint;
    nrows = pboard -> rows;
    ncols = pboard -> cols;
    for (int k = 0; k < nIslands; k++)
    {
        placedHint = false;
        counter = 0;
        nCell = rand() % sizes[k];
        for (int i = 0; i < nrows; i++)
        {
           for (int j = 0; j < ncols; j++)
           {
                pc = &(pboard -> grid[i][j]);
                if ((pc -> island) == k)
                {
                    if(counter == nCell){
                        pc -> hint = sizes[k];
                        placedHint = true;
                    }
                    counter++;
                }
                if(placedHint){break;}
           }
           if(placedHint){break;}
        }
    }
    

}

// -----------------
// --- GENERATOR ---
// -----------------

void floodBoard(board *pboard)
// Board flooding algorithm
{   
    int maxItter = 10;
    int seed_row, seed_col, *sizes, \
    nIslands, idLargestIsland, maxIslandSize, \
    nrows, ncols;
    bool foundWaterAdjacent;
    cell *pc, *poc;
    cellList *cList;
    // Maximum island size is set to the size
    // of the longest board edge - 1
    nrows = (pboard -> rows);
    ncols = (pboard -> cols);
    maxIslandSize = MAX(nrows, ncols) - 2;
    // Select a random seed cell
    seed_row = rand() % nrows;
    seed_col = rand() % ncols;
    idLargestIsland = 0;
    // Flood the board
    asignCell(pboard, seed_row, seed_col, WATER);
    // Asign left over cells to land
    fillEmptyCells(pboard);
    markIslands(pboard);
    // Check for island sizes
    nIslands = countIslands(pboard);
    sizes = getIslandSizes(pboard, nIslands);
    for (int i = 0; i < nIslands; i++)
    {
        if (sizes[i] > sizes[idLargestIsland])
        {
            idLargestIsland = i;
        }
        
    }
    // Clear the largest island and re-flood
    // if the largest island is too big
    while (sizes[idLargestIsland] > maxIslandSize)
    {
        maxItter--;
        foundWaterAdjacent = false;
        clearIsland(pboard, idLargestIsland);
        unmarkIslands(pboard);
        for (int i = 0; i < nrows; i++)
        {
            for (int j = 0; j < ncols; j++)
            {
                pc = &(pboard -> grid[i][j]);
                if (((pc -> type) == EMPTY))
                {
                    cList = getOrthogonalCells(
                        pboard, pc -> row, pc -> col);
                    poc = popCellList(cList);
                    while(poc != NULL)
                    {
                        if((poc -> type) == WATER && \
                        isPoolSafe(pboard, pc -> row, pc -> col))
                        {
                            foundWaterAdjacent = true;
                        }
                        poc = popCellList(cList); 
                    }
                }
                if(foundWaterAdjacent){break;}
            }
            if(foundWaterAdjacent){break;}
        }
        asignCell(pboard, pc -> row, pc -> col, WATER);
        fillEmptyCells(pboard);
        markIslands(pboard);
        nIslands = countIslands(pboard);
        sizes = getIslandSizes(pboard, nIslands);
        for (int i = 0; i < nIslands; i++)
        {
            if (sizes[i] > sizes[idLargestIsland])
            {
                idLargestIsland = i;
            }    
        }
    }
    placeHints(pboard, sizes, nIslands);
    if (maxItter == 0)
    {
        // The algorithm should coverge in less that 10 itterations
        maxItter = 10;
        pboard = initBoard(nrows, ncols);
        asignCell(pboard, seed_row, seed_col, WATER);
    }
    
}

board *generator(int row, int cols)
// Board genertor
{
   board *pboard = initBoard(row, cols);
   floodBoard(pboard);
   return pboard;
}

// ----------
// --- IO ---
// ----------

void writePuzzleToFile(char *filename, board *pboard, bool solved)
// Writes puzzle to file.
{
    cell *pc;
    int nrow = pboard -> rows;
    int ncol = pboard -> cols;
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error opening the file %s", filename);
        exit (0);
    }
    fprintf(fp, "-");
    for (size_t k = 0; k < nrow; k++)
    {
        fprintf(fp, "----");
    }
    fprintf(fp, "\n");
    for (size_t i = 0; i < nrow; i++)
    {
        fprintf(fp, "|");
        for (size_t j = 0; j < ncol; j++)
        {
            pc = &(pboard -> grid[i][j]);
            cellToFile(pc, fp, solved);
            fprintf(fp, "|");
        }
        fprintf(fp, "\n");
        fprintf(fp, "-");
        for (size_t k = 0; k < nrow; k++)
        {
            fprintf(fp, "----");
        }
        fprintf(fp, "\n");
    }
}
