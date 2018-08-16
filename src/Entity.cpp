#include "Entity.h"
#include <iostream>

Entity::Entity()
: id{ 0 }
, Surf_Entity{ NULL }
, mAsset{ "" }
, isStart{ true }
{
}


Entity::Entity(int id)
: id{ id }
, Surf_Entity{ NULL }
, mAsset{ "" }
, isStart{ true }
{
}

Entity::~Entity()
{
    cleanup();
}


bool Entity::load(std::string assetFile, int width, int height)
{
    mAsset.assign(assetFile);
    if ((Surf_Entity = Surface::OnLoad(assetFile)) == NULL)
    {
        return false;
    }

    Surface::Transparent(Surf_Entity, 255, 0, 255);

    mWidth = width;
    mHeight = height;

    return true;
}


void Entity::render(SDL_Surface* Surf_Display, int x, int y)
{
    if (Surf_Entity == NULL || Surf_Display == NULL)
        return;

    Surface::OnDraw(Surf_Display, Surf_Entity, x, y, 0, 0, mWidth, mHeight);
}


void Entity::renderAnimation(SDL_Surface* Surf_Display, int xstart, int ystart, int xstop, int ystop)
{
    if (isStart)
    {
        mX = xstart;
        mY = ystart;
    }
    isStart = false;

    if (Surf_Entity == NULL || Surf_Display == NULL)
        return;

    /*
    int FrameRate = 300; // Milliseconds
    if (SDL_GetTicks() < mPrevTime + FrameRate)
    {
        return;
    }*/

    mPrevTime = SDL_GetTicks();

    if (mX < xstop)
        mX += 5;
    if (mY < ystop)
        mY += 5;

    Surface::OnDraw(Surf_Display, Surf_Entity, mX, mY, 0, 0, mWidth, mHeight);
}


void Entity::render(SDL_Surface* Surf_Display)
{
}


void Entity::cleanup()
{
    if (Surf_Entity)
    {
        SDL_FreeSurface(Surf_Entity);
    }

    Surf_Entity = NULL;
}
