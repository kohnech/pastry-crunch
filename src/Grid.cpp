#include "Grid.h"
#include "CSurface.h"
#include "SDL_image.h"

#include <iostream>
#include <map>
#include <random>

Grid Grid::instance;

Grid::Grid(int x, int y)
: mBrickWidth{ ICON_WIDTH }
, mBrickHeight{ ICON_HEIGHT }
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


bool Grid::load(CAssets& assets)
{
    mAssets = assets.getGridAssets();
    std::pair<int, int> gridAssetSize = assets.getGridAssetSize();
    mBrickWidth = gridAssetSize.first;
    mBrickHeight = gridAssetSize.second;

    std::cout << "mTileAsset: " << mTileAsset << std::endl;

    std::pair<int, int> gridPosition = assets.getGridPosition();
    mX = gridPosition.first;
    mY = gridPosition.second;

    Board::load(assets);

    initGrid();

    return true;
}


void Grid::render(SDL_Surface* Surf_Display)
{
    Board::render(Surf_Display);
    for (int x = 0; x < GRID_WIDTH; ++x)
    {
        for (int y = 0; y < GRID_HEIGHT; ++y)
        {
            int xPos = x * mBrickWidth;
            int yPos = y * mBrickHeight;

            Entity* entity = mGrid[x][y];
            // CSurface::OnDraw(Surf_Display, src->Surf_Entity, xPos, yPos, 0, 0, 100, 100);

            entity->render(Surf_Display, mX + xPos, mY + yPos);
        }
    }
}

void Grid::cleanup()
{
    for (int x = 0; x < GRID_WIDTH; ++x)
    {
        for (int y = 0; y < GRID_HEIGHT; ++y)
        {
            delete mGrid[x][y];
        }
    }
}

/*
void Grid::findHorizontalMatches()
{
    // Loop over rows
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        int type = type = mGrid[0][y]->id;
        int numInARow = 0;
        for (int x = 1; x < GRID_WIDTH; ++x) {
            if (mGrid[x-1][y] == mGrid[x][y]) {

            }

        }
    }
}

void Grid::findVerticalMatches()
{

}*/


int Grid::getRandomInt()
{
    // Seed with a real random value, if available
    std::random_device r;

    // Choose a random mean between 1 and 6
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(0, 4);
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


    for (int row = 0; row < GRID_HEIGHT; row++)
    {
        for (int column = 0; column < GRID_WIDTH; column++)
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
    // TODO use mTileWidth / mTileHeight instead for Tile below... Need to read it out from asset mng.
    entity->load(asset.c_str(), mBrickWidth, mBrickHeight);
    mGrid[row][column] = entity;
}

void Grid::onLButtonDown(int x, int y)
{
    std::cout << "onLButtonDown: (" << x << "," << y << ")" << std::endl;

    std::cout << "mWidth: " << mWidth << ", mHeight: " << mHeight << std::endl;

    getIndexesFromPosition(x, y);
}

std::pair<int, int> Grid::getIndexesFromPosition(int x, int y)
{
    if (mWidth == 0 || mWidth == 0) {
        return {0,0};
    }

    /// Calculate board coordinate
    int row = (x - mX) / mWidth;
    int column = (y - mY) / mHeight;
    std::cout << "Pressed coordinate: (" << row << ", " << column << ")" << std::endl;

    mHighlightX = row;
    mHighlightY = column;

    std::pair<int, int> indexes;
    indexes.first = row;
    indexes.second = column;
    return indexes;
};


void Grid::onKeyDown(SDL_Keycode sym, Uint16 mod, SDL_Scancode unicode)
{
    std::cout << "Key pressed: " << unicode << std::endl;
    std::cout << "mX:" << mX << "mY: " << mY << std::endl;
}
