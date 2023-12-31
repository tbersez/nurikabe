#include "cells.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// -------------
// --- CELLS ---
// -------------

void printCell(cell *c)
// Prints cell using terminal background color
{
    switch (c -> type)
    {
    case EMPTY: printf("\033[107m   \033[49m"); break;
    case LAND: 
        switch (c -> hint)
        {
        case 0:
            printf("\033[42m   \033[49m");
            break;
        default:
            printf("\033[42m%3d\033[49m", c -> hint);
            break;
        };
        break;
    case WATER: printf("\033[104m   \033[49m"); break;
    }
}

void cellToFile(cell *c, FILE *fp, bool solved)
// Write hidden or solved cell to file
{
    if (solved)
    {
        if(c -> type == LAND)
        {
            if (c -> hint == 0)
            {
                fprintf(fp, " · ");
            }
            else
            {
                fprintf(fp, "%3d", c -> hint);
            }
            
        } else {
            fprintf(fp, " W ");
        }
    } else {
        if (c -> hint == 0)
            {
                fprintf(fp, "   ");
            }
            else
            {
                fprintf(fp, "%3d", c -> hint);
            }
    }
}

void setCellStatus(cell *c, cellType type)
// Sets cell type
{
    c -> type = type;
}

// ------------------
// --- CELL LISTS ---
// ------------------

cellList *initCellList()
// Creates an empty cell list
{
    cellList *list;
    list = (cellList*)malloc(sizeof(cellList));
    list -> head = NULL;
    return list;
}

void appendToCellList(cellList *list, cell *c)
// Append cell node *c to cell list
{
    cellNode *new_node, *current;
    new_node = (cellNode*)malloc(sizeof(cellNode));
    new_node -> cell = c;
    new_node -> next = NULL;
    current = list -> head;
    if ((list -> head) == NULL)
    {
       list -> head = new_node; 
    } else {
        while (current -> next != NULL) {
            current = current -> next;
        }
        current -> next = new_node;
    }
}

cell *popCellList(cellList *list)
// Pops last cell from list
{
    cell *pcell;
    cellNode *temp;
    if ((list -> head) == NULL)
    {
       return NULL;
    }
    temp = list -> head;
    list -> head = temp -> next;
    pcell = temp -> cell;
    return pcell;
}

void printCellList(cellList *list)
// Prints cellList
{
    cell *c;
    cellNode *current = list -> head;
   	while (current != NULL) {
        c = current -> cell;
        printf("[%d, %d]", c -> row, c -> col);
        current = current -> next;
    }
    printf("\n");
}