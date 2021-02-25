#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

////////////////////////////////////////////////////////////////////////////////

/// Connect4Grid is the struct storing the content of a game grid
struct Connect4Grid {
    /// Number of columns in this grid
    uint8_t width;
    /// Number of rows in this grid
    uint8_t height;
    /// Default value of free cells
    uint8_t* cells;
    /// Id of the next player to insert a token in this grid
    uint8_t currentPlayer;
    /// Termination condition for this grid's game
    bool isGameFinished;
    /// Last move column index
    uint8_t lastMoveColumn;
    /// Last move row index
    uint8_t lastMoveRow;
};

////////////////////////////////////////////////////////////////////////////////

/// Add a token in the grid at given indices. The token belongs to the player
// whose turn is ongoing according to the grid
/// @param grid Grid structure to update
/// @param col Index of the colum where to insert token
/// @return True for successful operation, false if column is invalid or full
bool addToken(struct Connect4Grid* grid, uint8_t col);

////////////////////////////////////////////////////////////////////////////////

/// Clear grid content and game over flag. Size stays the same
/// @param grid Grid structure to clear
void clearGrid(struct Connect4Grid* grid);

////////////////////////////////////////////////////////////////////////////////

/// Game grid allocation and initialization function
/// @param width Number of columns in the grid, between 4 and 20
/// @param height Number of rows in the grid, between 4 and 20
/// @return Initialized, empty connect 4 grid
struct Connect4Grid* createGrid(uint8_t width, uint8_t height);

////////////////////////////////////////////////////////////////////////////////

/// Game grid deallocation and destruction function
/// @param grid Grid structure to free
void destroyGrid(struct Connect4Grid* grid);

////////////////////////////////////////////////////////////////////////////////

/// Displays current grid content in a terminal
/// @param grid grid structure to free
void displayGrid(struct Connect4Grid* grid);

////////////////////////////////////////////////////////////////////////////////

/// Returns the lowest empty row in the grid at given column index
/// @param grid Grid structure to update
/// @param col Index of the colum where to check tokens
/// @return The lowest empty row index, or the grid height if there is none. If
/// the grid is not set, returns the maximum grid height constant
uint8_t getInsertionRow(struct Connect4Grid* grid, uint8_t col);

////////////////////////////////////////////////////////////////////////////////

/// Returns the highest number of identical tokens in the grid, given a starting
/// point coordinates and the direction to follow.
/// @param grid Grid structure to update
/// @param col Index of the colum where to start checking
/// @param row Index of the row where to start checking
/// @param stepCol step value to iterate over on the vertical axis
/// @param stepRow step value to iterate over on the horizontal axis
/// @return the number of connected tokens
uint8_t getLongestStreak(struct Connect4Grid* grid, uint8_t col, uint8_t row,
                         int32_t stepCol, int32_t stepRow);

////////////////////////////////////////////////////////////////////////////////

/// Checks if the victory conditions are achieved for the last player who played
/// @param grid Grid structure to update
/// @return True if the last move connected 4 token, otherwise false
bool hasWon(struct Connect4Grid* grid);