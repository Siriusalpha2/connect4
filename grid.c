#include "grid.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "consts.h"

extern int errno;

////////////////////////////////////////////////////////////////////////////////

struct Connect4Grid* createGrid(uint8_t width, uint8_t height) {
    struct Connect4Grid* grid = NULL;

    if (width < C4_GRID_MIN_DIM || width > C4_GRID_MAX_WIDTH) return grid;
    if (height < C4_GRID_MIN_DIM || height > C4_GRID_MAX_HEIGHT) return grid;

    grid = (struct Connect4Grid*)malloc(sizeof(struct Connect4Grid));
    if (!grid) {
        perror("[ERROR] createGrid malloc grid failed");
        return grid;
    }

    grid->cells = (uint8_t*)malloc((size_t)width * height);
    if (!grid->cells) {
        perror("[ERROR] createGrid malloc cells failed");
        free(grid);
        grid = NULL;
        return grid;
    }

    memset(grid->cells, C4_GRID_DEFAULT_CELL_VALUE, (size_t)width * height);

    grid->height = height;
    grid->width = width;
    grid->isGameFinished = false;

    return grid;
}

////////////////////////////////////////////////////////////////////////////////

void destroyGrid(struct Connect4Grid* grid) {
    if (!grid) return;
    if (grid->cells) free(grid->cells);
    free(grid);
}

////////////////////////////////////////////////////////////////////////////////