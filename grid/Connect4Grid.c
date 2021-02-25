#include "grid/Connect4Grid.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/consts.h"

extern int errno;

////////////////////////////////////////////////////////////////////////////////

bool addToken(struct Connect4Grid* grid, uint8_t col) {
    if (!grid || !grid->cells) {
        puts("[ERROR] addToken: grid is empty");
        return false;
    }

    uint8_t cellVal = grid->cells[(grid->height - 1) * grid->width + col];

    // If column index is invalid or column is full, do nothing
    if (col >= grid->width || cellVal != C4_GRID_EMPTY_CELL_VALUE) {
        return false;
    }

    uint8_t row = getInsertionRow(grid, col);
    // Redundant check on invalid row index
    if (row >= grid->height) return false;

    grid->cells[row * grid->width + col] = grid->currentPlayer;
    grid->currentPlayer = grid->currentPlayer == P1 ? P2 : P1;

    grid->lastMoveColumn = col;
    grid->lastMoveRow = row;

    printf("Inserting token at (c=%u,r=%u)\n", (unsigned)col, (unsigned)row);
    printf("New cell Value: %c\n", grid->cells[row * grid->width + col]);

    return true;
}

////////////////////////////////////////////////////////////////////////////////

void clearGrid(struct Connect4Grid* grid) {
    if (!grid || !grid->cells) {
        puts("[ERROR] clearGrid: grid is empty");
        return;
    }

    size_t nCells = grid->width * grid->height;
    memset(grid->cells, C4_GRID_EMPTY_CELL_VALUE, nCells);

    grid->isGameFinished = false;
    grid->currentPlayer = P1;

    grid->lastMoveColumn = grid->width;
    grid->lastMoveRow = grid->height;
}

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

    grid->height = height;
    grid->width = width;

    clearGrid(grid);

    return grid;
}

////////////////////////////////////////////////////////////////////////////////

void destroyGrid(struct Connect4Grid* grid) {
    if (!grid) return;
    if (grid->cells) free(grid->cells);
    free(grid);
}

////////////////////////////////////////////////////////////////////////////////

void displayGrid(struct Connect4Grid* grid) {
    if (!grid || !grid->cells) {
        puts("[ERROR] displayGrid: grid is empty");
        return;
    }
    int32_t width = (int32_t)grid->width;
    int32_t height = (int32_t)grid->height;

    printf("\n\n");
    // Display column indices
    printf("col\t ");
    for (int32_t col = 0; col < width; ++col) {
        printf("%3d ", col);
    }
    // Display row indices and grid
    printf("\nrow\n");
    for (int32_t row = height - 1; row >= 0; --row) {
        printf("%d\t|", row);
        for (int32_t col = 0; col < width; ++col) {
            uint8_t val = grid->cells[row * width + col];
            if (val == P1) {
                printf(" %s%c\033[0;37m |", P1_COLOR,
                       grid->cells[row * width + col]);
            } else if (val == P2) {
                printf(" %s%c\033[0;37m |", P2_COLOR,
                       grid->cells[row * width + col]);
            } else {
                printf(" %c |", grid->cells[row * width + col]);
            }
        }
        printf("\n");
    }
    // Display feet
    printf("\t|");
    for (int32_t col = 0; col < width; ++col) {
        printf("---|");
    }
    printf("\n\t|");
    for (int32_t col = 0; col < width; ++col) {
        if (col + 1 == width) {
            printf("   |");
        } else {
            printf("    ");
        }
    }
    printf("\n\t|");
    for (int32_t col = 0; col < width; ++col) {
        if (col + 1 == width) {
            printf("   |");
        } else {
            printf("    ");
        }
    }
    printf("\n\n");
}

////////////////////////////////////////////////////////////////////////////////

uint8_t getInsertionRow(struct Connect4Grid* grid, uint8_t col) {
    if (!grid || !grid->cells) {
        puts("[ERROR] getInsertionRow: grid is empty");
        return C4_GRID_MAX_HEIGHT;
    }

    uint8_t row = 0;
    for (; row < grid->height; ++row) {
        if (grid->cells[row * grid->width + col] == C4_GRID_EMPTY_CELL_VALUE)
            break;
    }

    return row;
}

////////////////////////////////////////////////////////////////////////////////

uint8_t getLongestStreak(struct Connect4Grid* grid, uint8_t col, uint8_t row,
                         int32_t stepCol, int32_t stepRow) {
    uint8_t connected = 0;
    if (!grid || !grid->cells) {
        puts("[ERROR] hasWon: grid is empty");
        return connected;
    }

    uint8_t origin = grid->cells[row * grid->width + col];
    if (origin == C4_GRID_EMPTY_CELL_VALUE) return connected;

    // Count the starting position token
    ++connected;

    int32_t curCol = (int32_t)col + stepCol, curRow = (int32_t)row + stepRow;
    // Keep counting as long as we are still in the grid and on the same token
    while ((curCol >= 0 && curRow >= 0) &&
           (curCol < grid->width && curRow < grid->height) &&
           (grid->cells[curRow * grid->width + curCol] == origin)) {
        curCol += stepCol;
        curRow += stepRow;
        ++connected;
    }
    // Count again in the opposite direction
    curCol = (int32_t)col - stepCol, curRow = (int32_t)row - stepRow;
    while ((curCol >= 0 && curRow >= 0) &&
           (curCol < grid->width && curRow < grid->height) &&
           (grid->cells[curRow * grid->width + curCol] == origin)) {
        curCol -= stepCol;
        curRow -= stepRow;
        ++connected;
    }

    return connected;
}

////////////////////////////////////////////////////////////////////////////////

bool hasWon(struct Connect4Grid* grid) {
    if (!grid || !grid->cells) {
        puts("[ERROR] hasWon: grid is empty");
        return false;
    }

    // Check indices are valid
    if (grid->lastMoveColumn >= grid->width ||
        grid->lastMoveRow >= grid->height) {
        return false;
    }

    uint8_t c = grid->lastMoveColumn, r = grid->lastMoveRow;

    int32_t stepsCol[4] = {1, 0, 1, -1};
    int32_t stepsRow[4] = {0, 1, 1, 1};
    // Check in all 8 possible directions: up, down, left, right and
    // diagonals
    for (size_t i = 0; i < 4 && !grid->isGameFinished; ++i) {
        uint8_t streak = getLongestStreak(grid, c, r, stepsCol[i], stepsRow[i]);
        grid->isGameFinished |= streak >= C4_WIN_CONDITION;
    }

    return grid->isGameFinished;
}