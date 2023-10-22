typedef enum CellType {EMPTY, LAND, WATER} cellType;

typedef struct Cell
{
    cellType type;
    unsigned short row;
    unsigned short col;
    unsigned short island;
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
void setCellStatus(cell *c, cellType type);
cellList *initCellList();
void printCellList(cellList *list);
void appendToCellList(cellList *list, cell *c);