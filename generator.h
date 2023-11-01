#include "board.h"
#include <stdbool.h>

board *generator(int row, int cols);
void writePuzzleToFile(char *filename, board *pboard, bool solved);