#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Grid.h"


TEST(GridTests, Test_function_getIndexesFromPosition)
{
    Grid testGrid;
    std::pair<int, int> pos = testGrid.getPosition();
    EXPECT_EQ(pos.first, 0);
    EXPECT_EQ(pos.second, 0);
}