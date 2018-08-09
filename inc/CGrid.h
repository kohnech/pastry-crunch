#pragma once

#include <SDL.h>
#include "Define.h"
#include <string>
#include "CEntity.h"

class CGrid
{
public:
    static CGrid            instance;

    CGrid(int xpos, int ypos);
    CGrid();
    void setPosition(int xpos, int ypos);
    bool load(std::string icon);
    void render(SDL_Surface* Surf_Display);
    void cleanup();


private:
    CEntity* mMap[GRID_WIDTH][GRID_HEIGHT];
    std::string mImagePath;
    int mX, mY;
};
