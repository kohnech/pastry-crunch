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
    EXPECT_EQ(size.first, 64);
    EXPECT_EQ(size.second, 72);

    pos = testGrid.getPosition();
    EXPECT_EQ(pos.first, 400);
    EXPECT_EQ(pos.second, 200);

    std::vector<std::string> vec = testGrid.getAssets();
    EXPECT_EQ(vec.size(), 5u);
}
