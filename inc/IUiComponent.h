#pragma once

#include "CAssets.h"
#include <SDL2/SDL.h>

#include <iostream>

class IUiComponent
{
public:
    IUiComponent()
    : mX{ 0 }
    , mY { 0 }
    , mSurface { NULL }
    {
    }

    virtual bool load()
    {
        std::cout << "WARNING: Unimplemented method: " << __FILE__ << ":" << __LINE__ << std::endl;
        return false;
    }
    virtual bool load(CAssets& assets)
    {
        std::cout << "WARNING: Unimplemented method: " << __FILE__ << ":" << __LINE__ << std::endl;
        return false;
    }


    virtual void render(SDL_Surface* Surf_Display) = 0;
    virtual void cleanup() = 0;

protected:
    int mX, mY;
    SDL_Surface* mSurface;
};