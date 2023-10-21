typedef enum CellType {EMPTY, LAND, WATER} cellType;

typedef struct Cell
{
    cellType type;
    unsigned short row;
    unsigned short col;
} cell;

void printCell(cell *c);