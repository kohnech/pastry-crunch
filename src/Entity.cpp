#include "Entity.h"
#include <iostream>

Entity::Entity()
        : id { 0 }
        , Surf_Entity { NULL }
        , Surf_Tile { NULL }
        , mWidth { 0 }
        , mHeight { 0 }
        , mAsset { "" }
{
}


Entity::Entity(int id)
: id { id }
, Surf_Entity { NULL }
, Surf_Tile { NULL }
, mWidth { 0 }
, mHeight { 0 }
, mAsset { "" }
{
}

Entity::~Entity()
{
}

bool Entity::load(std::string assetFile, int width, int height,
                    std::string tileFile, int tileWidth, int tileHeight)
{
    mAsset.assign(assetFile);
    if((Surf_Entity = CSurface::OnLoad(assetFile)) == NULL)
    {
        return false;
    }
    if((Surf_Tile = CSurface::OnLoad(tileFile)) == NULL)
    {
        return false;
    }

    CSurface::Transparent(Surf_Entity, 255, 0, 255);

    mWidth = width;
    mHeight = height;
    mTileWidth = tileWidth;
    mTileHeight = tileHeight;
    mTileAsset.assign(tileFile);

    return true;
}

bool Entity::load(std::string assetFile, int width, int height)
{
    mAsset.assign(assetFile);
    if((Surf_Entity = CSurface::OnLoad(assetFile)) == NULL) {
        return false;
    }

    CSurface::Transparent(Surf_Entity, 255, 0, 255);

    mWidth = width;
    mHeight = height;

    return true;
}


void Entity::render(SDL_Surface* Surf_Display, int x, int y)
{
    if(Surf_Entity == NULL || Surf_Display == NULL) return;

    if (Surf_Tile != NULL) {
        CSurface::OnDraw(Surf_Display, Surf_Tile, x, y, 0, 0, mTileWidth, mTileHeight);
    }
    CSurface::OnDraw(Surf_Display, Surf_Entity, x, y, 0, 0, mWidth, mHeight);
}

void Entity::OnCleanup()
{
    if(Surf_Entity) {
        SDL_FreeSurface(Surf_Entity);
    }

    if(Surf_Tile) {
        SDL_FreeSurface(Surf_Tile);
    }

    Surf_Entity = NULL;
    Surf_Tile = NULL;
}
