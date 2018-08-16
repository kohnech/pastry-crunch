#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Grid.h"

#include "json.hpp"


using json = nlohmann::json;

const int GRID_WIDTH = 5;
const int GRID_HEIGHT = 3;

// Fixture
class GridTest : public ::testing::Test {
protected:
    void SetUp() override
    {
        Assets assets;
        assets.loadFile("assets.json");
        grid_.load(assets);
        grid_.initGrid();
    }

    void createEmptyRow(int row)
    {
        std::vector<Index> matches;
        /// Create empty vertical pilar at row position
        for (int i = 0; i < GRID_HEIGHT; i++)
        {
            Index ind(row, i);
            matches.push_back(ind);
        }
        grid_.removeMatches(matches);
    }

    void createEmptyColumn(int column)
    {
        std::vector<Index> matches;
        /// Create empty vertical pilar at row position
        for (int i = 0; i < GRID_WIDTH; i++)
        {
            Index ind(i, column);
            matches.push_back(ind);
        }
        grid_.removeMatches(matches);
    }

    void printIds()
    {
        for (int column = 0; column < GRID_HEIGHT; column++)
        {
            for (int row = 0; row < GRID_WIDTH; row++)
            {
                Index ind(row, column);
                Entity *entity = grid_.getEntity(ind);
                if (entity == NULL) {
                    std::cout << "id: " << "V" << ", ";
                }
                else {
                    std::cout << "id: " << entity->id << ", ";
                }
            }
            std::cout << std::endl;
        }
    }

    void recordIds()
    {
        for (int column = 0; column < GRID_HEIGHT; column++)
        {
            for (int row = 0; row < GRID_WIDTH; row++)
            {
                Index ind(row, column);
                Entity *entity = grid_.getEntity(ind);
                if (entity == NULL) {
                    ids[row][column] = -1;
                } else {
                    ids[row][column] = entity->id;
                }
            }
        }
    }

    void compareIds()
    {
        for (int column = 0; column < GRID_HEIGHT; column++) {
            for (int row = 0; row < GRID_WIDTH; row++) {

                if (ids[row][column] == -1) {
                    continue;
                }
                else {
                    Index ind(row, column);
                    Entity *entity = grid_.getEntity(ind);

                    ids[row][column] = entity->id;

                    EXPECT_TRUE(ids[row][column] == entity->id);
                }
            }
        }
    }

    Grid grid_;
    int ids[GRID_WIDTH][GRID_HEIGHT];
};

TEST(GridTests, Test_function_load)
{
    Assets assets;
    assets.loadFile("assets.json");

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
    EXPECT_EQ(gridSize.first, GRID_WIDTH);
    EXPECT_EQ(gridSize.second, GRID_HEIGHT);
}

TEST_F(GridTest, Test_function_getIndexesFromPosition)
{
    Pair size = grid_.getSize();
    EXPECT_EQ(size.first, 10);
    EXPECT_EQ(size.second, 10);

    Index ind;
    // Outside the board
    ind = grid_.getIndexesFromPosition(50, 50);
    EXPECT_EQ(ind.column, -1);
    EXPECT_EQ(ind.row, -1);

    ind = grid_.getIndexesFromPosition(100, 100);
    EXPECT_EQ(ind.column, 0);
    EXPECT_EQ(ind.row, 0);

    ind = grid_.getIndexesFromPosition(105, 103);
    EXPECT_EQ(ind.column, 0);
    EXPECT_EQ(ind.row, 0);

    ind = grid_.getIndexesFromPosition(110, 110);
    EXPECT_EQ(ind.column, 1);
    EXPECT_EQ(ind.row, 1);

    ind = grid_.getIndexesFromPosition(121, 122);
    EXPECT_EQ(ind.column, 2);
    EXPECT_EQ(ind.row, 2);

    ind = grid_.getIndexesFromPosition(121, 122);
    EXPECT_EQ(ind.column, 2);
    EXPECT_EQ(ind.row, 2);

    // Test extreme point now we are outside of the board
    ind = grid_.getIndexesFromPosition(150, 130);
    EXPECT_EQ(ind.column, -1);
    EXPECT_EQ(ind.row, -1);

    // still inside... so a valid index...
    ind = grid_.getIndexesFromPosition(149, 129);
    EXPECT_EQ(ind.row, 4);
    EXPECT_EQ(ind.column, 2);
}

TEST_F(GridTest, Test_function_isAdjacent)
{
    // Set mPrevClickedPosition with a mouse click... Now it is att Index (0,0)
    grid_.onLButtonDown(100,100);
    EXPECT_TRUE(grid_.isAdjacent(Index(1,0)));
    EXPECT_TRUE(grid_.isAdjacent(Index(0,1)));

    // Click index (4,0)
    grid_.onLButtonDown(149,100);
    EXPECT_TRUE(grid_.isAdjacent(Index(3,0)));
    EXPECT_TRUE(grid_.isAdjacent(Index(4,1)));

    // Click index (4,2)
    grid_.onLButtonDown(149,129);
    EXPECT_TRUE(grid_.isAdjacent(Index(4,1)));
    EXPECT_TRUE(grid_.isAdjacent(Index(3,2)));

    // Click index (2,1)
    grid_.onLButtonDown(120,110);
    EXPECT_TRUE(grid_.isAdjacent(Index(2,0)));
    EXPECT_TRUE(grid_.isAdjacent(Index(2,2)));
    EXPECT_TRUE(grid_.isAdjacent(Index(1,1)));
    EXPECT_TRUE(grid_.isAdjacent(Index(3,1)));

    // Click index (2,1)
    //testGrid.onLButtonDown(130,120);
    //EXPECT_TRUE(testGrid.isAdjacent(Index(3,2)));
    //EXPECT_TRUE(testGrid.isAdjacent(Index(2,3)));
    //EXPECT_TRUE(testGrid.isAdjacent(Index(4,3)));
    //EXPECT_TRUE(testGrid.isAdjacent(Index(3,4)));
}

TEST_F(GridTest, Test_function_swapEntity)
{
    Index indFrom(0,0);
    Index indTo(1,1);
    Entity* from = grid_.getEntity(indFrom);
    Entity* to = grid_.getEntity(indTo);

    grid_.swapEntity(indFrom, indTo);
    Entity* newFrom = grid_.getEntity(indFrom);
    Entity* newTo = grid_.getEntity(indTo);

    EXPECT_EQ(from, newTo);
    EXPECT_EQ(to, newFrom);

    ////
    indFrom = Index(4,4);
    indTo = Index(3,4);
    from = grid_.getEntity(indFrom);
    to = grid_.getEntity(indTo);

    grid_.swapEntity(indFrom, indTo);
    newFrom = grid_.getEntity(indFrom);
    newTo = grid_.getEntity(indTo);

    EXPECT_EQ(from, newTo);
    EXPECT_EQ(to, newFrom);

    // Try swap impossible case. This case will result in NO swap!!!
    indFrom = Index(4,4);
    indTo = Index(5,4);
    from = grid_.getEntity(indFrom);
    to = grid_.getEntity(indTo);

    grid_.swapEntity(indFrom, indTo);
    newFrom = grid_.getEntity(indFrom);
    newTo = grid_.getEntity(indTo);

    EXPECT_EQ(grid_.getEntity(Index(4, 4)), newTo);
    EXPECT_EQ(from, newFrom);
    EXPECT_EQ(grid_.getEntity(Index(4, 4)), to);
}

TEST_F(GridTest, Test_function_getDistinctRows)
{
    std::vector<Index> matches;
    Index ind1(1, 1);
    Index ind2(2, 1);
    Index ind3(3, 1);

    matches = {ind1, ind2, ind3};

    std::vector<int> columns = grid_.getDistinctRows(matches);
    EXPECT_EQ(columns.size(), 3u);
    EXPECT_EQ(columns.at(0), 1);
    EXPECT_EQ(columns.at(1), 2);
    EXPECT_EQ(columns.at(2), 3);

    matches.clear();
    columns.clear();
    ind1 = Index(1, 1);
    ind2 = Index(1, 2);
    ind3 = Index(1, 3);
    matches = {ind1, ind2, ind3};

    columns = grid_.getDistinctRows(matches);
    EXPECT_EQ(columns.size(), 1u);
    EXPECT_EQ(columns.at(0), 1);

    matches.clear();
    columns.clear();
    ind1 = Index(1, 1);
    matches = {ind1};

    columns = grid_.getDistinctRows(matches);
    EXPECT_EQ(columns.size(), 1u);
    EXPECT_EQ(columns.at(0), 1);

    /// 4 in a row
    matches.clear();
    columns.clear();
    ind1 = Index(1, 0);
    ind2 = Index(1, 1);
    ind3 = Index(1, 2);
    Index ind4(1, 3);
    matches = {ind1, ind2, ind3, ind4};

    columns = grid_.getDistinctRows(matches);
    EXPECT_EQ(columns.size(), 1u);
    EXPECT_EQ(columns.at(0), 1);


    /// 4 in a column
    matches.clear();
    columns.clear();
    ind1 = Index(0, 1);
    ind2 = Index(1, 1);
    ind3 = Index(2, 1);
    ind4 = Index(3, 1);
    matches = {ind1, ind2, ind3, ind4};

    columns = grid_.getDistinctRows(matches);
    EXPECT_EQ(columns.size(), 4u);
    EXPECT_EQ(columns.at(0), 0);
    EXPECT_EQ(columns.at(1), 1);
    EXPECT_EQ(columns.at(2), 2);
    EXPECT_EQ(columns.at(3), 3);
}


TEST_F(GridTest, Test_function_collapse)
{
    // Test collapse Index (1, 1)
    Index ind0(1, 0);
    Index ind1(1, 1);
    grid_.setVoid(ind1);
    EXPECT_TRUE(grid_.getEntity(ind0) != NULL);
    EXPECT_EQ(NULL, grid_.getEntity(ind1));

    // Now collapse the void
    std::vector<int> columns = {1};
    int num = grid_.collapse(columns);

    // Check we collapsed the above index (1, 0)
    EXPECT_EQ(NULL, grid_.getEntity(ind0));
    EXPECT_TRUE(grid_.getEntity(ind1) != NULL);
    EXPECT_EQ(1, num);


    // Test collapse Index (4, 1), (4, 2)
    ind0 = Index(4, 0);
    ind1 = Index(4, 1);
    Index ind2(4, 2);
    grid_.setVoid(ind1);
    grid_.setVoid(ind2);

    EXPECT_TRUE(grid_.getEntity(ind0) != NULL);
    EXPECT_EQ(NULL, grid_.getEntity(ind1));
    EXPECT_EQ(NULL, grid_.getEntity(ind2));

    // Now collpase the voids
    columns = {4};
    num = grid_.collapse(columns);

    // Check we collapsed the above index (1, 0)
    EXPECT_EQ(NULL, grid_.getEntity(ind0));
    EXPECT_EQ(NULL, grid_.getEntity(ind1));
    EXPECT_TRUE(grid_.getEntity(ind2) != NULL);
    EXPECT_EQ(2, num);
}

TEST_F(GridTest, Test_function_collapse_4_in_a_column)
{
    /// Get all ids above row to be collapsed
    std::vector<int> ids;
    for (int i = 0; i < GRID_WIDTH; i++)
    {
        Entity *entity = grid_.getEntity(Index(i, 0));
        ids.push_back(entity->id);
        std::cout << "GetEntity id: " << entity->id << std::endl;
    }

    /// Test collapse 4 in a column
    for (int i = 0; i < GRID_WIDTH; i++)
    {
        Index ind0(i, 1);
        grid_.setVoid(ind0);
        Entity* evoid = grid_.getEntity(Index(i, 1));
        EXPECT_TRUE(evoid == NULL);

        Entity* nonvoid = grid_.getEntity(Index(i, 0));
        EXPECT_TRUE(nonvoid != NULL);

        nonvoid = grid_.getEntity(Index(i, 2));
        EXPECT_TRUE(nonvoid != NULL);
    }

    std::vector<int> rows = {0, 1, 2, 3, 4};
    grid_.collapse(rows);

    for (int i = 0; i < GRID_WIDTH; i++)
    {
        Entity *evoid = grid_.getEntity(Index(i, 0));
        EXPECT_TRUE(evoid == NULL);
        Entity *entity = grid_.getEntity(Index(i, 1));
        EXPECT_EQ(entity->id, ids.at(i));
    }

}

TEST_F(GridTest, Test_function_collapse_3_in_a_row)
{
    /// Get all ids above row to be collapsed
    std::vector<int> idsLeftRow;
    std::vector<int> idsRightRow;
    for (int i = 0; i < GRID_HEIGHT; i++)
    {
        Entity *entity = grid_.getEntity(Index(0, i));
        idsLeftRow.push_back(entity->id);
        entity = grid_.getEntity(Index(2, i));
        idsRightRow.push_back(entity->id);
        std::cout << "GetEntity id: " << entity->id << std::endl;
    }

    /// Test collapse 3 in a row
    for (int i = 0; i < GRID_HEIGHT; i++)
    {
        Index ind0(1, i);
        grid_.setVoid(ind0);
        Entity* evoid = grid_.getEntity(Index(1, i));
        EXPECT_TRUE(evoid == NULL);

        Entity* nonvoid = grid_.getEntity(Index(0, i));
        EXPECT_TRUE(nonvoid != NULL);

        nonvoid = grid_.getEntity(Index(2, i));
        EXPECT_TRUE(nonvoid != NULL);
    }

    std::vector<int> rows = {0 ,1, 2, 3, 4};  // Test collapse all rows
    grid_.collapse(rows);

    for (int i = 0; i < GRID_HEIGHT; i++)
    {
        Entity *neighbour = grid_.getEntity(Index(1, i));
        EXPECT_TRUE(neighbour == NULL); // We have yet not refilled the grid
        Entity *entity = grid_.getEntity(Index(0, i));
        EXPECT_EQ(entity->id, idsLeftRow.at(i));
        entity = grid_.getEntity(Index(2, i));
        EXPECT_EQ(entity->id, idsRightRow.at(i));
    }
}

TEST_F(GridTest, Test_function_removeMatches_horizontally)
{
    std::vector<Index> matches;
    std::vector<int> idsTopColumn;
    std::vector<int> idsBottomColumn;
    /// Test remove matches = creating voids 4 in a column
    for (int i = 0; i < 4; i++)
    {
        Entity *entity = grid_.getEntity(Index(i, 0));
        idsTopColumn.push_back(entity->id);
        entity = grid_.getEntity(Index(i, 2));
        idsBottomColumn.push_back(entity->id);

        Index ind(i, 1);
        matches.push_back(ind);
    }

    grid_.removeMatches(matches);

    for (int i = 0; i < 4; i++)
    {
        Entity *entity = grid_.getEntity(Index(i, 0));
        EXPECT_EQ(entity->id, idsTopColumn.at(i));
        entity = grid_.getEntity(Index(i, 2));
        EXPECT_EQ(entity->id, idsBottomColumn.at(i));

        Index ind(i, 1);
        Entity *neighbour = grid_.getEntity(ind);
        EXPECT_TRUE(neighbour == NULL);
    }
}

TEST_F(GridTest, Test_function_removeMatches_vertically)
{
    std::vector<Index> matches;
    std::vector<int> idsLeftRow;
    std::vector<int> idsRightRow;
    /// Test remove matches = creating voids 4 in a column
    for (int i = 0; i < GRID_HEIGHT; i++)
    {
        Entity *entity = grid_.getEntity(Index(0, i));
        idsLeftRow.push_back(entity->id);
        entity = grid_.getEntity(Index(2, i));
        idsRightRow.push_back(entity->id);

        Index ind(1, i);
        matches.push_back(ind);
    }

    grid_.removeMatches(matches);

    for (int i = 0; i < GRID_HEIGHT; i++)
    {
        Entity *entity = grid_.getEntity(Index(0, i));
        EXPECT_EQ(entity->id, idsLeftRow.at(i));
        entity = grid_.getEntity(Index(2, i));
        EXPECT_EQ(entity->id, idsRightRow.at(i));

        Index ind(1, i);
        Entity *neighbour = grid_.getEntity(ind);
        EXPECT_TRUE(neighbour == NULL);
    }
}

TEST_F(GridTest, Test_function_getEmptyItemsOnRow)
{
    createEmptyRow(1);
    createEmptyRow(2);

    std::vector<Index> voids1 = grid_.getEmptyItemsOnRow(1);
    std::vector<Index> voids2 = grid_.getEmptyItemsOnRow(2);

    EXPECT_EQ(voids1.size(), 3u);
    EXPECT_EQ(voids2.size(), 3u);
    for (auto ind : voids1)
    {
        EXPECT_EQ(ind.row, 1);
    }
    for (auto ind : voids2)
    {
        EXPECT_EQ(ind.row, 2);
    }
}

TEST_F(GridTest, Test_function_getEmptyItemsOnRow_column_empty)
{
    createEmptyColumn(1);

    std::vector<Index> voids0 = grid_.getEmptyItemsOnRow(0);
    std::vector<Index> voids1 = grid_.getEmptyItemsOnRow(1);
    std::vector<Index> voids2 = grid_.getEmptyItemsOnRow(2);
    std::vector<Index> voids3 = grid_.getEmptyItemsOnRow(3);
    std::vector<Index> voids4 = grid_.getEmptyItemsOnRow(4);

    EXPECT_EQ(voids0.size(), 1u);
    EXPECT_EQ(voids1.size(), 1u);
    EXPECT_EQ(voids2.size(), 1u);
    EXPECT_EQ(voids3.size(), 1u);
    EXPECT_EQ(voids4.size(), 1u);
}

TEST_F(GridTest, Test_function_createNewEntitiesInRows_with_emptyColumn)
{
    createEmptyColumn(1);

    printIds();
    recordIds();

    std::vector<Index> voids0 = grid_.getEmptyItemsOnRow(0);
    std::vector<Index> voids1 = grid_.getEmptyItemsOnRow(1);
    std::vector<Index> voids2 = grid_.getEmptyItemsOnRow(2);
    std::vector<Index> voids3 = grid_.getEmptyItemsOnRow(3);
    std::vector<Index> voids4 = grid_.getEmptyItemsOnRow(4);

    EXPECT_EQ(voids0.size(), 1u);
    EXPECT_EQ(voids1.size(), 1u);
    EXPECT_EQ(voids2.size(), 1u);
    EXPECT_EQ(voids3.size(), 1u);
    EXPECT_EQ(voids4.size(), 1u);

    std::vector<int> rows = {0, 1, 2, 3, 4};

    grid_.createNewEntitiesInRows(rows);

    std::cout << std::endl << std::endl;
    printIds();
    compareIds();
}

TEST_F(GridTest, Test_function_createNewEntitiesInRows_with_emptyRow)
{
    createEmptyRow(1);

    //printIds();
    recordIds();

    std::vector<Index> voids0 = grid_.getEmptyItemsOnRow(0);
    std::vector<Index> voids1 = grid_.getEmptyItemsOnRow(1);
    std::vector<Index> voids2 = grid_.getEmptyItemsOnRow(2);
    std::vector<Index> voids3 = grid_.getEmptyItemsOnRow(3);
    std::vector<Index> voids4 = grid_.getEmptyItemsOnRow(4);

    EXPECT_EQ(voids0.size(), 0u);
    EXPECT_EQ(voids1.size(), 3u);
    EXPECT_EQ(voids2.size(), 0u);
    EXPECT_EQ(voids3.size(), 0u);
    EXPECT_EQ(voids4.size(), 0u);

    std::vector<int> rows = {0, 1, 2, 3, 4};

    grid_.createNewEntitiesInRows(rows);

    std::cout << std::endl << std::endl;
    //printIds();
    compareIds();
}


