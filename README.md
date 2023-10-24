# nurikabe

C language Nukikabe pencil-puzzle solver and generator.

## Nurika-what?

### Origins

### Rules

### What-is-this-project-about?

## Run the project

### How to compile it

### CLI

## Algorithmic details

What's going on behind the curtains? Here are some details...

### Board generation

The board is represented as a 2D array of cells bellonging to one of the 3 following types:
* `WATER` for water cells.
* `LAND` for island cells.
* `EMPTY` for cells that have not been set yet.

The generator picks a random cell from the board, sets it to `WATER` and recurses in orthogonal cells, affecting them to `LAND` or `WATER` randomly. For each itteration, the posibility of a 2 by 2 `WATER` pool is checked ensuring that no such pools are created.

Once the algorithm explored all cells or got stuck, empty cells are affected to `LAND`. If the largest island is larger than the number of rows or columns of the board minus 1, it cell are set to `EMPTY` before re-calling the generator on an empty cell orthogonaly adjacent to a `WATER` cell.

### Solver

## A bit of reading

* Many thanks to: [Generating rationally solvable instances of NP-hard logic puzzles](https://ntnuopen.ntnu.no/ntnu-xmlui/bitstream/handle/11250/3021932/no.ntnu%3Ainspera%3A102231297%3A25765051.pdf?sequence=1)
* To: [Counting Islands in Nurikabe](https://www.semanticscholar.org/paper/Counting-Islands-in-Nurikabe-Boswell-Clark/17e179c9b66e246202350cbc9241e48251f28876)
* And: [On The NP-Completeness of The Nurikabe Pencil Puzzle and Variants Thereof](https://www.semanticscholar.org/paper/On-The-NP-Completeness-of-The-Nurikabe-Pencil-and-Holzer-Klein/4855b7160c651c8cc883def72348463fd77cdbed)