#include "CGrid.h"
#include "CSurface.h"
#include "SDL_image.h"

#include <iostream>
#include <map>
#include <random>

CGrid CGrid::instance;

CGrid::CGrid(int x, int y)
: mBrickWidth{ ICON_WIDTH }
, mBrickHeight{ ICON_HEIGHT }
{
    mX = x;
    mY = y;
}


CGrid::~CGrid()
{
    cleanup();
}


void CGrid::setPosition(int x, int y)
{
    mX = x;
    mY = y;
}


bool CGrid::load(CAssets& assets)
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


void CGrid::render(SDL_Surface* Surf_Display)
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

void CGrid::cleanup()
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
void CGrid::findHorizontalMatches()
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

void CGrid::findVerticalMatches()
{

}*/

/*!
 * Populate a Grid randomly without any matches.
 */
void CGrid::initGrid()
{
    std::map<int, int> numberId;
    for (int x = 0; x < GRID_WIDTH; ++x)
    {
        for (int y = 0; y < GRID_HEIGHT; ++y)
        {
            int random = getRandomInt();
            int newRandom = random;
            numberId[random]++;
            if (numberId[random] == 2)
            {

                /// shuffle until we get a new ID
                while (newRandom == random)
                {
                    newRandom = getRandomInt();
                }
                numberId[random]--;
            }

            std::string asset = mAssets[newRandom];
            Entity* entity = new Entity(newRandom);
            // TODO use mTileWidth / mTileHeight instead for Tile below... Need to read it out from asset mng.
            entity->load(asset.c_str(), mBrickWidth, mBrickHeight);

            std::cout << "Loading image CGid..." << std::endl;
            mGrid[x][y] = entity;
        }
    }
}

int CGrid::getRandomInt()
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
