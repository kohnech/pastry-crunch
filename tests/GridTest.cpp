#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Grid.h"

#include "json.hpp"


using json = nlohmann::json;


TEST(GridTests, Test_function_load)
{
    Assets assets;
    assets.load("assets.json");

    Grid testGrid;

    Pair pos = testGrid.getPosition();
    EXPECT_EQ(pos.first, 0);
    EXPECT_EQ(pos.second, 0);

    Pair size = testGrid.getSize();
    EXPECT_EQ(size.first, 0);
    EXPECT_EQ(size.second, 0);

    testGrid.load(assets);

    size = testGrid.getSize();
    EXPECT_EQ(size.first, 10);
    EXPECT_EQ(size.second, 10);

    pos = testGrid.getPosition();
    EXPECT_EQ(pos.first, 100);
    EXPECT_EQ(pos.second, 100);

    std::vector<std::string> vec = testGrid.getAssets();
    EXPECT_EQ(vec.size(), 5u);

    Pair gridSize = testGrid.getBoardSize();
    EXPECT_EQ(gridSize.first, 5);
    EXPECT_EQ(gridSize.second, 5);
}

TEST(GridTests, Test_function_getIndexesFromPosition)
{
    Assets assets;
    assets.load("assets.json");

    Grid testGrid;
    testGrid.load(assets);

    Pair size = testGrid.getSize();
    EXPECT_EQ(size.first, 10);
    EXPECT_EQ(size.second, 10);

    Index ind;
    ind = testGrid.getIndexesFromPosition(50, 50);
    EXPECT_EQ(ind.column, 0);
    EXPECT_EQ(ind.row, 0);

    ind = testGrid.getIndexesFromPosition(100, 100);
    EXPECT_EQ(ind.column, 0);
    EXPECT_EQ(ind.row, 0);

    ind = testGrid.getIndexesFromPosition(105, 103);
    EXPECT_EQ(ind.column, 0);
    EXPECT_EQ(ind.row, 0);

    ind = testGrid.getIndexesFromPosition(110, 110);
    EXPECT_EQ(ind.column, 1);
    EXPECT_EQ(ind.row, 1);

    ind = testGrid.getIndexesFromPosition(121, 122);
    EXPECT_EQ(ind.column, 2);
    EXPECT_EQ(ind.row, 2);

    ind = testGrid.getIndexesFromPosition(121, 122);
    EXPECT_EQ(ind.column, 2);
    EXPECT_EQ(ind.row, 2);

    // Test extreme point
    ind = testGrid.getIndexesFromPosition(150, 150);
    EXPECT_EQ(ind.column, 0);
    EXPECT_EQ(ind.row, 0);

    ind = testGrid.getIndexesFromPosition(149, 149);
    EXPECT_EQ(ind.column, 4);
    EXPECT_EQ(ind.row, 4);
}

