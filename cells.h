#include <stdbool.h>
#include <stdio.h>

typedef enum CellType {EMPTY, LAND, WATER} cellType;

typedef struct Cell
{
    cellType type;
    unsigned short row;
    unsigned short col;
    short island;
    short hint;
} cell;

typedef struct CellNode
{
    cell *cell;
    struct CellNode *next;
} cellNode;

typedef struct CellList
{
    cellNode *head;
} cellList;

void printCell(cell *c);
void cellToFile(cell *c, FILE *fp, bool solved);
void setCellStatus(cell *c, cellType type);
cellList *initCellList();
void printCellList(cellList *list);
void appendToCellList(cellList *list, cell *c);
cell *popCellList(cellList *list);