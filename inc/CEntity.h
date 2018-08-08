#pragma once

#include <vector>

#include "CAnimation.h"
#include "CSurface.h"

class CEntity
{
public:
    CEntity();

    virtual ~CEntity();

    virtual bool OnLoad(std::string File, int Width, int Height);

    virtual void OnLoop();

    virtual void OnRender(SDL_Surface* Surf_Display, int x, int y);

    virtual void OnCleanup();


protected:
    SDL_Surface*    Surf_Entity;


private:
    int             mWidth;
    int             mHeight;

};
