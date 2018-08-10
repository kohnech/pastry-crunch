#pragma once

#include <vector>

#include "CAnimation.h"
#include "CSurface.h"


class Entity
{
public:
    Entity();

    Entity(int id);

    virtual ~Entity();

    virtual bool OnLoad(std::string file, int width, int height);

    virtual void OnLoop();

    virtual void OnRender(SDL_Surface* Surf_Display, int x, int y);

    virtual void OnCleanup();

    int            id;


protected:
    SDL_Surface*    Surf_Entity;


private:

    int             mWidth;
    int             mHeight;
    std::string    mAsset;


};
