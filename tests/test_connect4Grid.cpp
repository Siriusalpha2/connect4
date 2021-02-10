extern "C" {
#include "grid/Connect4Grid.h"
}
#include "gtest/gtest.h"

////////////////////////////////////////////////////////////////////////////////

TEST(Connect4Grid, CreationDestructionValidGrid) {
    struct Connect4Grid* grid = createGrid(7, 6);
    ASSERT_TRUE(grid != NULL);
    EXPECT_EQ(grid->height, 6);
    EXPECT_EQ(grid->width, 7);
    EXPECT_FALSE(grid->isGameFinished);
    destroyGrid(grid);
}

////////////////////////////////////////////////////////////////////////////////

TEST(Connect4Grid, CreationInvalidGridWidthAxis) {
    struct Connect4Grid* grid = createGrid(1, 6);
    EXPECT_TRUE(grid == NULL);
    destroyGrid(grid); 
}

////////////////////////////////////////////////////////////////////////////////

TEST(Connect4Grid, CreationInvalidGridHeightAxis) {
    struct Connect4Grid* grid = createGrid(7, 1);
    EXPECT_TRUE(grid == NULL);
    destroyGrid(grid); 
}

////////////////////////////////////////////////////////////////////////////////

TEST(Connect4Grid, CreationInvalidGridBothAxis) {
    struct Connect4Grid* grid = createGrid(1, 1);
    EXPECT_TRUE(grid == NULL);
    destroyGrid(grid); 
}

////////////////////////////////////////////////////////////////////////////////