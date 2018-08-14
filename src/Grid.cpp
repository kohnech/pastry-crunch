#include "Grid.h"
#include "Surface.h"
#include "SDL_image.h"

#include <iostream>
#include <map>
#include <random>
#include <stdlib.h>

Grid Grid::instance;

Grid::Grid(int x, int y)
: mGrid{ NULL }
, mImagePath{""}
, mTileWidth{ ICON_WIDTH }
, mTileHeight{ ICON_HEIGHT }
, mPrevClickedIndexes{ 0, 0 }
{
    mX = x;
    mY = y;
}


Grid::~Grid()
{
    cleanup();
}


void Grid::setPosition(int x, int y)
{
    mX = x;
    mY = y;
}


bool Grid::load(Assets& assets)
{
    assets.printAssets();
    mAssets = assets.getGridAssets();
    std::pair<int, int> gridAssetSize = assets.getGridAssetSize();
    mTileWidth = gridAssetSize.first;
    mTileHeight = gridAssetSize.second;

    std::cout << "mTileAsset: " << mTileAsset << std::endl;

    std::pair<int, int> gridPosition = assets.getGridPosition();
    mX = gridPosition.first;
    mY = gridPosition.second;

    std::pair<int, int> gridSize = assets.getGridSize();
    mGridRowSize = gridSize.first; // x-axis
    mGridColumnSize = gridSize.second; // y-axis

    std::cout << "Grid size: " << mGridRowSize << " x " << mGridColumnSize << std::endl;

    // Allocate on heap the grid
    mGrid = new Entity**[mGridRowSize];
    for (int i = 0; i < mGridRowSize; i++) {
        mGrid[i] = new Entity *[mGridColumnSize];
    }

    Board::load(assets);

    initGrid();

    return true;
}


void Grid::render(SDL_Surface* Surf_Display)
{
    Board::render(Surf_Display);
    for (int x = 0; x < mGridRowSize; ++x)
    {
        for (int y = 0; y < mGridColumnSize; ++y)
        {
            int xPos = x * mTileWidth;
            int yPos = y * mTileHeight;

            Entity* entity = mGrid[x][y];
            // CSurface::OnDraw(Surf_Display, src->Surf_Entity, xPos, yPos, 0, 0, 100, 100);

            entity->render(Surf_Display, mX + xPos, mY + yPos);
        }
    }
}

void Grid::cleanup()
{
    if (mGrid == NULL) {
        std::cout << "ERROR: You must initialize the grid with load()!" << std::endl;
        return;
    }
    for (int x = 0; x < mGridRowSize; ++x)
    {
        for (int y = 0; y < mGridColumnSize; ++y)
        {
            if (mGrid[x][y]) {
                delete mGrid[x][y];
                mGrid[x][y] = NULL;
            }
        }
    }
}


int Grid::getRandomInt()
{
    // Seed with a real random value, if available
    std::random_device r;

    // Choose a random mean between 0 and number of unique assets/icon
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(0, mAssets.size() - 1);
    int mean = uniform_dist(e1);
    std::cout << "Randomly-chosen mean: " << mean << '\n';
    return mean;
}


/*!
 * Populate a Grid randomly without any matches.
 */
void Grid::initGrid()
{
    //initScore();

    //if (mGrid != null)
    //    destroyAllEntities();

<<<<<<< 670935e3980bd2a6bf2584e3cb2360abe9afb584

    for (int row = 0; row < mGridRowSize; row++)
=======
    for (int row = 0; row < mGridColumnSize; row++)
>>>>>>> Add collapse game logic NOTE WIP!
    {
        for (int column = 0; column < mGridColumnSize; column++)
        {

            int newId = getRandomInt();

            //check if two previous horizontal are of the same type
            while (column >= 2 && (mGrid[row][column - 1]->id == newId)
                   && mGrid[row][column - 2]->id == newId)
            {
                newId = getRandomInt();
            }

            //check if two previous vertical are of the same type
            while (row >= 2 && (mGrid[row - 1][column]->id == newId)
                   &&  mGrid[row - 2][column]->id == newId)
            {
                newId = getRandomInt();
            }

            loadEntity(row, column, newId);
        }
    }
}

void Grid::loadEntity(int row, int column, int id)
{
    std::string asset = mAssets[id];
    Entity* entity  = new Entity(id);
    entity->load(asset.c_str(), mTileWidth, mTileHeight);
    mGrid[row][column] = entity;
}

void Grid::onLButtonDown(int x, int y)
{
    std::cout << "onLButtonDown: (" << x << "," << y << ")" << std::endl;

    std::cout << "mWidth: " << mWidth << ", mHeight: " << mHeight << std::endl;

    Index index = getIndexesFromPosition(x, y);
    setHighlightPosition(index);

    update(index);
}

void Grid::onKeyDown(SDL_Keycode sym, Uint16 mod, SDL_Scancode unicode)
{
    std::cout << "Key pressed: " << unicode << std::endl;
    std::cout << "mX:" << mX << "mY: " << mY << std::endl;
}

Index Grid::getIndexesFromPosition(int x, int y)
{
    if (mWidth == 0 || mWidth == 0)
    {
        return {0, 0};
    }

    /// Check board boundaries
    if (x < mX || x >= (mWidth * mGridRowSize + mX) ||
        y < mY || y >= (mHeight * mGridColumnSize + mY))
    {
        std::cout << "Out of boundary" << std::endl;
        return {0, 0};
    }

    /// Calculate board coordinate
    int row = (x - mX) / mWidth;
    int column = (y - mY) / mHeight;
    std::cout << "Pressed coordinate: (" << row << ", " << column << ")" << std::endl;

    if (row < 0 || column < 0)
    {
        return {0, 0};
    }

    Index index(row, column);
    return index;
};


void Grid::update(const Index& pos)
{
    if (isAdjacent(pos))
    {
        std::cout << "Found adjacent cookies!!!" << std::endl;
        swapEntity(mPrevClickedIndexes, pos);

        std::vector<Index> matches;
        matches = findVerticalMatches(pos);
        std::vector<Index> matchesHor = findHorizontalMatches(pos);
        // Get total matches
        matches.insert( matches.end(), matchesHor.begin(), matchesHor.end() );

        for (auto ind : matches)
        {
            std::cout << "match: (" << ind.row << ", " << ind.column << ")" << std::endl;
        }

        // Undo swap if no more than 3
        if (matches.size() < 3) // TODO fix magic number
        {
            swapEntity(pos, mPrevClickedIndexes); // Undo swap
            mPrevClickedIndexes = pos;
            return;
        }

        // Now we need collapse the matces
        removeMatches(matches);
    }
    else {
        std::cout << "No adjacent neighbour found!!!" << std::endl;
    }

    mPrevClickedIndexes = pos;
}

bool Grid::isAdjacent(const Index& ind)
{
    return (ind.column == mPrevClickedIndexes.column ||
            ind.row == mPrevClickedIndexes.row)
           && abs(ind.column - mPrevClickedIndexes.column) <= 1
           && abs(ind.row - mPrevClickedIndexes.row) <= 1;
}

void Grid::swapEntity(Index from, Index to)
{
    // First make boundary checks
    if (from.row < 0 || from.column < 0 || to.row < 0 || to.column < 0)
    {
        std::cout << "Try a better index!" << std::endl;
        return;
    }
    Index max = getMaximumGridIndex();

    if (from.row > max.row || from.column > max.column || to.row > max.row || to.column > max.column)
    {
        std::cout << "Try a better index!" << std::endl;
        return;
    }

    // swap entities by swapping them in the grid matrix
    Entity* temp = mGrid[from.row][from.column];
    mGrid[from.row][from.column] = mGrid[to.row][to.column];
    mGrid[to.row][to.column] = temp;
}

std::vector<Index> Grid::findVerticalMatches(const Index& ind)
{
    std::vector<Index> matches;

    matches.push_back(ind);
    Entity* shape = mGrid[ind.row][ind.column];
    //check left
    if (ind.column != 0)
        for (int column = ind.column - 1; column >= 0; column--)
        {
            if (mGrid[ind.row][column]->id == shape->id)
            {
                Index tmp(ind.row, column);
                matches.push_back(tmp);
            }
            else
                break;
        }

    //check right
    if (ind.column != mGridRowSize - 1)
        for (int column = ind.column + 1; column < mGridColumnSize; column++)
        {
            if (mGrid[ind.row][column]->id == shape->id)
            {
                Index tmp(ind.row, column);
                matches.push_back(tmp);
            }
            else
                break;
        }
    std::cout << "size of matches: " << matches.size() << std::endl;

    // TODO read from settings... 3, no magic numbers!!!
    // we are only interested in a set of more than 3 connected entities
    if (matches.size() < 3)
        matches.clear();

    return matches;
}

std::vector<Index> Grid::findHorizontalMatches(const Index& ind)
{
    std::vector<Index> matches;
    matches.push_back(ind);
    Entity* shape = mGrid[ind.row][ind.column];
    //check bottom
    if (ind.row != 0)
        for (int row = ind.row - 1; row >= 0; row--)
        {
            if (mGrid[row][ind.column] != NULL &&
                mGrid[row][ind.column]->id == shape->id)
            {
                Index tmp(row, ind.column);
                matches.push_back(tmp);
            }
            else
                break;
        }

    //check top
    if (ind.row != mGridRowSize - 1)
        for (int row = ind.row + 1; row < mGridRowSize; row++)
        {
            if (mGrid[row][ind.column] != NULL &&
                mGrid[row][ind.column]->id == shape->id)
            {
                Index tmp(row, ind.column);
                matches.push_back(tmp);
            }
            else
                break;
        }

    if (matches.size() < 3) // TODO fixme
        matches.clear();

    return matches;
}


std::vector<std::string> Grid::getAssets()
{
    return mAssets;
}

Entity* Grid::getEntity(Index ind)
{
    // First make boundary checks
    if (ind.row < 0 || ind.column < 0)
    {
        std::cout << "Try a better index, return minimum entity at index (0,0)!" << std::endl;
        return mGrid[0][0];
    }

    Index max = getMaximumGridIndex();

    if (ind.row > max.row || ind.column > max.column)
    {
        std::cout << "Try a better index, return maximum entity!" << std::endl;
        return mGrid[max.row][max.column];
    }

    return mGrid[ind.row][ind.column];
}

void Grid::setGridMatrix(Entity*** grid)
{
    mGrid = grid;
}

void Grid::setHighlightPosition(const Index& index)
{
    mHighlightX = index.row;
    mHighlightY = index.column;
}

Index Grid::getMaximumGridIndex()
{
    // Simple math here...
    int row = mGridRowSize - 1;
    int column = mGridColumnSize - 1;
    Index ind(row, column);
    std::cout << "Maximum coordinate: (" << row << ", " << column << ")" << std::endl;
    return ind;
}

void Grid::removeMatches(const std::vector<Index>& matches)
{
    // First create new entities with number of matches
    /*for(Index ind : matches)
    {
        int newId = getRandomInt();
        loadEntity(row, column, newId);
    }*/


    for (Index ind : matches)
    {
        delete mGrid[ind.row][ind.column];
        mGrid[ind.row][ind.column] = NULL;
    }

    /*
    collapseColumns(matches);
printGrid();

    fillCollapsedColumns(matches);
printGrid();
     */

printGrid();

    std::vector<int> columns = getDistinctColumns(matches);

    collapse(columns);
printGrid();
    createNewEntitiesInColumns(columns);

    /*
    // get columns that we have to collapse
    var columns = totalMatches.Select(go => go.GetComponent<Shape>().Column).Distinct();

    //the order the 2 methods below get called is important!!!
    //collapse the ones gone
    var collapsedCandyInfo = shapes.Collapse(columns);
    //create new ones
    var newCandyInfo = CreateNewCandyInSpecificColumns(columns);*/
}

void Grid::collapseColumns(const std::vector<Index>& matches)
{
    for (Index ind : matches)
    {
        for (int column = ind.column; column > 0; --column)
        {
            mGrid[ind.row][column] = mGrid[ind.row][column -1];
        }
    }
}

void Grid::printGrid() {
    for (int column = 0; column < mGridColumnSize; column++)
    {
        for (int row = 0; row < mGridRowSize; row++)
        {
            if (mGrid[row][column] == NULL) {
                std::cout << 0;
            }
            else {
                std::cout << 1;
            }
        }
        std::cout << std::endl;
    }
}

void Grid::fillCollapsedColumns(const std::vector<Index>& matches)
{
    std::vector<int> columns = getDistinctColumns(matches);

    collapse(columns);


/*    std::map<int, int> collapsed;
    std::vector<int> number

    for (Index ind : matches)
    {
        collapsed[ind.column]++;
        std::cout << "ind.column: "<< ind.column << std::endl;
    }

    for (auto col : collapsed)
    {
        std::cout << "column:  " << col.first <<  "number:" <<   col.second << std::endl;
    }*/
}

std::vector<int> Grid::getDistinctColumns(const std::vector<Index>& matches)
{
    std::vector<int> columns;
    for (Index ind : matches)
    {
        columns.push_back(ind.column);
    }
    std::sort(columns.begin(), columns.end());
    auto last = std::unique(columns.begin(), columns.end());
    columns.erase(last, columns.end());

    for (int column : columns)
    {
        std::cout << "column: " << column  << std::endl;
    }
    return columns;
}


void Grid::collapse(std::vector<int> columns)
{
    //AlteredCandyInfo collapseInfo = new AlteredCandyInfo();


    ///search in every column
    for (int column : columns)
    {
        //begin from bottom row
        for (int row = 0; row < mGridRowSize - 1; row++)
        {
            //if you find a null item
            if (mGrid[row][column] == NULL)
            {
                //start searching for the first non-null
                for (int row2 = row + 1; row2 < mGridRowSize; row2++)
                {
                    //if you find one, bring it down (i.e. replace it with the null you found)
                    if (mGrid[row2][column] != NULL)
                    {
                        mGrid[row][column] = mGrid[row2][column];
                        mGrid[row2][column] = NULL;

                        //calculate the biggest distance
                       // if (row2 - row > collapseInfo.MaxDistance)
                       //     collapseInfo.MaxDistance = row2 - row;

                        //assign new row and column (name does not change)
                        //mGrid[row][column].GetComponent<Shape>().Row = row;
                        //mGrid[row][column].GetComponent<Shape>().Column = column;

                        //collapseInfo.AddCandy(shapes[row, column]);
                        break;
                    }
                }
            }
        }
    }

    //return collapseInfo;
}

void Grid::createNewEntitiesInColumns(std::vector<int> columns)
{
    //AlteredCandyInfo newCandyInfo = new AlteredCandyInfo();

    //find how many null values the column has
    for (int column : columns)
    {
        std::vector<Index> emptyItems = getEmptyItemsOnColumn(column);
        for (auto item : emptyItems)
        {
            int go = getRandomInt();

            loadEntity(item.row, item.column, go);

            //GameObject newCandy = Instantiate(go, SpawnPositions[column], Quaternion.identity)
            //as GameObject;

            //newCandy.GetComponent<Shape>().Assign(go.GetComponent<Shape>().Type, item.Row, item.Column);

            //if (Constants.Rows - item.Row > newCandyInfo.MaxDistance)
            //    newCandyInfo.MaxDistance = Constants.Rows - item.Row;

            //mGrid[item.Row][item.Column] = newCandy;
            //newCandyInfo.AddCandy(newCandy);
        }
    }
    //return newCandyInfo;
}


std::vector<Index> Grid::getEmptyItemsOnColumn(int column)
{
    std::vector<Index> emptyItems;
    for (int row = 0; row < mGridRowSize; row++)
    {
        if (mGrid[row][column] == NULL)
            emptyItems.push_back(Index(row,column));
    }
    return emptyItems;
}

