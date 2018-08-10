#include "Entity.h"
#include <iostream>

Entity::Entity()
        : Surf_Entity { NULL }
        , mId { 0 }
        , mWidth { 0 }
        , mHeight { 0 }
        , mAsset { "" }
{
}

Entity::Entity(int id)
: Surf_Entity { NULL }
, mId { id }
, mWidth { 0 }
, mHeight { 0 }
, mAsset { "" }
{
}

Entity::~Entity()
{
}

bool Entity::OnLoad(std::string file, int width, int height)
{
    mAsset.assign(file);
    if((Surf_Entity = CSurface::OnLoad(file)) == NULL) {
        return false;
    }

    CSurface::Transparent(Surf_Entity, 255, 0, 255);

    mWidth = width;
    mHeight = height;

    return true;
}

void Entity::OnLoop()
{
}

void Entity::OnRender(SDL_Surface* Surf_Display, int x, int y)
{
    if(Surf_Entity == NULL || Surf_Display == NULL) return;

    CSurface::OnDraw(Surf_Display, Surf_Entity, x, y, 0, 0, mWidth, mHeight);
}

void Entity::OnCleanup()
{
    if(Surf_Entity) {
        SDL_FreeSurface(Surf_Entity);
    }

    Surf_Entity = NULL;
}
