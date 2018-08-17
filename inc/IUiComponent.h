#pragma once

#include "Assets.h"
#include "CommonTypes.h"

#include <SDL2/SDL.h>

#include <iostream>

class IUiComponent
{
public:
    IUiComponent()
    : mX{ 0 }
    , mY{ 0 }
    , mSurface{ NULL }
    , mWidth{ 0 }
    , mHeight{ 0 }
    {
    }

    virtual bool load()
    {
        std::cout << "WARNING: Unimplemented method: " << __FILE__ << ":" << __LINE__ << std::endl;
        return false;
    }
    virtual bool load(Assets& assets)
    {
        std::cout << "WARNING: Unimplemented method: " << __FILE__ << ":" << __LINE__ << std::endl;
        return false;
    }
    virtual bool load(std::string file, int width, int height)
    {
        std::cout << "WARNING: Unimplemented method: " << __FILE__ << ":" << __LINE__ << std::endl;
        return false;
    }


    virtual void render(SDL_Surface* Surf_Display) = 0;
    virtual void cleanup() = 0;

    inline void setPosition(int x, int y)
    {
        mX = x;
        mY = y;
    }
    
    inline Pair getPosition()
    {
        Pair position;
        position.first = mX;
        position.second = mY;
        return position;
    }

    inline Pair getSize()
    {
        Pair size;
        size.first = mWidth;
        size.second = mHeight;
        return size;
    }

    inline void setSize(Pair size)
    {
        mWidth = size.first;
        mHeight = size.second;
    }

protected:
    int mX, mY;
    SDL_Surface* mSurface;
    int mWidth, mHeight;
};