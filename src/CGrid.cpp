#include "CGrid.h"
#include "SDL_image.h"
#include "CSurface.h"

#include <iostream>

CGrid CGrid::instance;

CGrid::CGrid(int xpos, int ypos)
{
    mX = xpos;
    mY = ypos;
}

CGrid::CGrid()
: mX { 0 }
, mY { 0 }
{
}


void CGrid::setPosition(int xpos, int ypos)
{
    mX = xpos;
    mY = ypos;
}

bool CGrid::load(std::string icon)
{
    // TODO check string not empty
    mImagePath = icon;
    for (int x = 0; x < GRID_WIDTH; ++x)
    {
        for (int y = 0; y < GRID_HEIGHT; ++y)
        {
            std::cout << "Loading image CGid..." << std::endl;
            CEntity* entity = new CEntity();
            mMap[x][y] = entity;
            entity->OnLoad ( icon.c_str(), ICON_WIDTH, ICON_HEIGHT);
        }
    }
    return true;
}


void CGrid::render(SDL_Surface* Surf_Display)
{

    for (int x = 0; x < GRID_WIDTH; ++x)
    {
        for (int y = 0; y < GRID_HEIGHT; ++y) {
            int xPos = x * ICON_WIDTH;
            int yPos = y * ICON_HEIGHT;

            CEntity* src = mMap[x][y];
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
            delete mMap[x][y];
        }
    }
}
