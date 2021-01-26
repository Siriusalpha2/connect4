#include <stdbool.h>
#include <stdint.h>

/// Value of cells occupied by player one
const uint8_t P1 = 1;
/// Value of cells occupied by player two
const uint8_t P2 = 2;
/// Default connect 4 grid number of rows
const uint8_t C4_GRID_DEFAULT_WIDTH = 7;
/// Default connect 4 grid number of cols
const uint8_t C4_GRID_DEFAULT_HEIGHT = 6;
/// Default cell value of unoccupied cells
const uint8_t C4_GRID_DEFAULT_CELL_VALUE = 0;
/// Max allowed grid width
const uint8_t C4_GRID_MAX_WIDTH = 20;
/// Max allowed grid width
const uint8_t C4_GRID_MAX_HEIGHT = 20;
/// Minimum width/height of connect 4 grid
const uint8_t C4_GRID_MIN_DIM = 4;
