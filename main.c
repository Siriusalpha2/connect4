#include <stdio.h>

#include "connect4.h"
#include "grid.h"

int main() {
    foo();

    struct Connect4Grid* grid = createGrid(7, 6);
    printf("Grid size: %dx%d\n", grid->width, grid->height);
    destroyGrid(grid);
    grid = NULL;

    return 0;
}