#pragma once

#include <SDL.h>
#include "Define.h"
#include <string>
#include "CEntity.h"

class CGrid
{
public:
    static CGrid            GridInstance;

    CGrid();
    bool load(std::string icon);
    void render(SDL_Surface* Surf_Display, int MapX, int MapY);
    void cleanup();


private:
    CEntity* mMap[GRID_WIDTH][GRID_HEIGHT];
    std::string mImagePath;
};