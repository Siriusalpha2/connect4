#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// #include "common/consts.h"
#include "grid/Connect4Grid.h"

int main() {
    srand(time(NULL));

    struct Connect4Grid* grid = createGrid(6, 7);
    printf("Grid size: %dx%d\n", grid->width, grid->height);
    displayGrid(grid);

    for (size_t i = 0; i < 300; ++i) {
        printf("Move %lu\n", i);
        uint8_t col = rand() % grid->width;
        if (!addToken(grid, col)) {
            printf("Can't insert, grid is full or col invalid\n");
        } else {
            displayGrid(grid);
            if (hasWon(grid)) {
                puts("A player won!");
                puts("Clearing grid and starting new game...");
                usleep(1e5);
                clearGrid(grid);
            }
        }

        usleep(1e5);
    }

    destroyGrid(grid);

    return 0;
}