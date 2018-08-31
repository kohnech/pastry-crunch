#include "Entity.h"
#include <iostream>

Entity::Entity()
: id{ 0 }
, mAsset{ "" }
{
}


Entity::Entity(int id)
: id{ id }
, mAsset{ "" }
{
}

Entity::~Entity()
{
    cleanup();
}


bool Entity::load(std::string assetFile, int width, int height)
{
    mAsset.assign(assetFile);
    if ((mSurface = Surface::loadImage(assetFile)) == NULL)
    {
        return false;
    }

    Surface::Transparent(mSurface, 255, 0, 255);

    mWidth = width;
    mHeight = height;

    return true;
}

void Entity::render(SDL_Surface* Surf_Display)
{
    if (mSurface == NULL || Surf_Display == NULL)
        return;

    Surface::OnDraw(Surf_Display, mSurface, mX, mY, 0, 0, mWidth, mHeight);
}

void Entity::renderAnimation(SDL_Surface* Surf_Display)
{
    if (mSurface == NULL || Surf_Display == NULL)
        return;

    /*
    int FrameRate = 300; // Milliseconds
    if (SDL_GetTicks() < mPrevTime + FrameRate)
    {
        return;
    }*/

    mPrevTime = SDL_GetTicks();


    if (mX > fromX && fromX < mX)
        fromX += 5;
    if (mY > fromY && fromY < mY)
        fromY += 5;
    if (mX < fromX && fromX > mX)
        fromX -= 5;
    if (mY < fromY && fromY > mY)
        fromY -= 5;

    Surface::OnDraw(Surf_Display, mSurface, fromX, fromY, 0, 0, mWidth, mHeight);
}

void Entity::cleanup()
{
}
