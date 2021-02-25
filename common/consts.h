#include <stdbool.h>
#include <stdint.h>

/// Default connect 4 grid number of rows
const uint8_t C4_GRID_DEFAULT_WIDTH = 7;
/// Default connect 4 grid number of cols
const uint8_t C4_GRID_DEFAULT_HEIGHT = 6;
/// Default cell value of unoccupied cells
const uint8_t C4_GRID_EMPTY_CELL_VALUE = ' ';

/// Max allowed grid width
const uint8_t C4_GRID_MAX_WIDTH = 101;
/// Max allowed grid width
const uint8_t C4_GRID_MAX_HEIGHT = 20;
/// Minimum width/height of connect 4 grid
const uint8_t C4_GRID_MIN_DIM = 4;

/// Minimum connected tokens to win
const uint8_t C4_WIN_CONDITION = 4;

/// Default text color string
const char* DEFAULT_TEXT_COLOR = "\033[0;37m";

/// Value of cells occupied by player one
const uint8_t P1 = 'O';
/// Player two color string (red)
const char* P1_COLOR = "\033[0;31m";

/// Value of cells occupied by player two
const uint8_t P2 = 'X';
/// Player one color string (yellow)
const char* P2_COLOR = "\033[0;33m";
