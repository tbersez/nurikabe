#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "generator.h"

typedef enum PrgMode {GENERATE, SOLVE} prgMode;

int main (int argc, char *argv[])
{
    // CLI
    prgMode mode;
    int ROWS, COLS;
    switch (*argv[1])
    {
    case 'g':
        mode = GENERATE;
        break;
    case 's':
        mode = SOLVE;
        break;
    default:
        printf(
            "Unvalid mode: %s\n"
            "Use 'g' for generator or 's' for the solver.\n",
            argv[1]
        );
        exit (1);
        break;
    }
    if (mode == GENERATE)
    {
        ROWS = atoi(argv[2]);
        COLS = atoi(argv[3]);
    }
    srand(time(NULL));
    board *pboard = generator(ROWS, COLS);
    printBoard(pboard);
    writePuzzleToFile("test/puzzle.txt", pboard, false);
    writePuzzleToFile("test/solution.txt", pboard, true);
    exit (0);
}