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
    mGridRowSize = gridSize.first;
    mGridColumnSize = gridSize.second;

    std::cout << "Grid size: " << mGridRowSize << " x " << mGridColumnSize << std::endl;

    // Allocate on heap the grid
    mGrid = new Entity**[mGridRowSize];
    for (int i = 0; i < mGridRowSize; ++i)
        mGrid[i] = new Entity*[mGridColumnSize];

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


    for (int row = 0; row < mGridColumnSize; row++)
    {
        for (int column = 0; column < mGridRowSize; column++)
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

    mHighlightX = row;
    mHighlightY = column;

    Index index(row, column);
    return index;
};


void Grid::update(const Index& pos)
{
    if (isAdjacent(pos))
    {
        std::cout << "Found adjacent cookies!!!" << std::endl;
        swapEntity(mPrevClickedIndexes, pos);

        std::vector<Index> matches = findVerticalMatches(pos);
        std::vector<Index> matchesHor = findHorizontalMatches(pos);

        for (auto ind : matches)
        {
            std::cout << "match: (" << ind.row << ", " << ind.column << ")" << std::endl;
        }

        for (auto ind : matchesHor)
        {
            std::cout << "match: (" << ind.row << ", " << ind.column << ")" << std::endl;
        }
        //swapEntity(pos, mPrevClickedIndexes); // Undo swap
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
        for (int column = ind.column + 1; column < mGridRowSize; column++)
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
