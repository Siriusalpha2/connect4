#include <stdio.h>

#include "grid/Connect4Grid.h"

int main() {
    struct Connect4Grid* grid = createGrid(7, 6);
    printf("Grid size: %dx%d\n", grid->width, grid->height);
    displayGrid(grid);
    destroyGrid(grid);
    grid = NULL;
    displayGrid(grid);

    return 0;
}