#include "CGrid.h"
#include "SDL_image.h"
#include "CSurface.h"

#include <iostream>
#include <random>

CGrid CGrid::instance;

CGrid::CGrid(int x, int y)
{
    mX = x;
    mY = y;

}

CGrid::CGrid()
: mX { 0 }
, mY { 0 }
, mBrickWidth { ICON_WIDTH }
, mBrickHeight { ICON_HEIGHT }
{
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

void CGrid::setBrickSize(int w, int h)
{
    mBrickWidth = w;
    mBrickHeight = h;
}


bool CGrid::load(std::vector<std::string> assets)
{
    mAssets = assets;
    initGrid();

    return true;
}


void CGrid::render(SDL_Surface* Surf_Display)
{
    for (int x = 0; x < GRID_WIDTH; ++x)
    {
        for (int y = 0; y < GRID_HEIGHT; ++y) {
            int xPos = x * mBrickWidth;
            int yPos = y * mBrickHeight;

            Entity* src = mGrid[x][y];
            //CSurface::OnDraw(Surf_Display, src->Surf_Entity, xPos, yPos, 0, 0, 100, 100);

            src->OnRender(Surf_Display, mX + xPos, mY + yPos);
        }
    }
}

void CGrid::cleanup()
{
    for (int x = 0; x < GRID_WIDTH; ++x)
    {
        for (int y = 0; y < GRID_HEIGHT; ++y) {
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
    for (int x = 0; x < GRID_WIDTH; ++x)
    {
        for (int y = 0; y < GRID_HEIGHT; ++y)
        {
            int random = getRandomInt();
            std::string asset = mAssets[random];
            Entity* entity = new Entity(random);
            entity->OnLoad ( asset.c_str(), mBrickWidth, mBrickHeight);

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