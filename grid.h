#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

////////////////////////////////////////////////////////////////////////////////

/// Connect4Grid is the struct storing the content of a game grid
struct Connect4Grid {
    uint8_t width;
    uint8_t height;
    // Default value of free cells
    uint8_t* cells;

    bool isGameFinished;
};

////////////////////////////////////////////////////////////////////////////////

/// Game grid allocation and initialization function
/// @param width Number of columns in the grid, between 4 and 20
/// @param height Number of rows in the grid, between 4 and 20
/// @return Initialized, empty connect 4 grid
struct Connect4Grid* createGrid(uint8_t width, uint8_t height);

////////////////////////////////////////////////////////////////////////////////

/// Game grid deallocation and destruction function
/// @param grid grid structure to free
void destroyGrid(struct Connect4Grid* grid);

////////////////////////////////////////////////////////////////////////////////