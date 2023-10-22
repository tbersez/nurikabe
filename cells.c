#include "cells.h"
#include <stdio.h>

void printCell(cell *c)
// Prints cell using terminal background color
{
    switch (c -> type)
    {
    case EMPTY: printf("\033[107m   \033[49m"); break;
    case LAND: printf("\033[42m   \033[49m"); break;
    case WATER: printf("\033[104m   \033[49m"); break;
    }
}

void setCellStatus(cell *c, cellType type)
// Sets cell type
{
    c -> type = type;
}