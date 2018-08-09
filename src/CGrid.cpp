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



bool CGrid::load(std::vector<std::string> assets)
{
    /*
    for (std::string asset : assets)
    {
        CEntity* entity = new CEntity();
        entity->OnLoad ( asset.c_str(), ICON_WIDTH, ICON_HEIGHT);
        mBricks.push_back(entity);
    }*/
    mAssets = assets;
    initGrid();

    return true;
}


void CGrid::render(SDL_Surface* Surf_Display)
{
    for (int x = 0; x < GRID_WIDTH; ++x)
    {
        for (int y = 0; y < GRID_HEIGHT; ++y) {
            int xPos = x * ICON_WIDTH;
            int yPos = y * ICON_HEIGHT;

            CEntity* src = mGrid[x][y];
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

void CGrid::initGrid()
{
    for (int x = 0; x < GRID_WIDTH; ++x)
    {
        for (int y = 0; y < GRID_HEIGHT; ++y)
        {
            std::string asset = mAssets[getRandomInt()];
            CEntity* entity = new CEntity();
            entity->OnLoad ( asset.c_str(), ICON_WIDTH, ICON_HEIGHT);

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