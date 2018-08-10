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

    /*!
     * Load an Entity based on asset in file, its width & height,
     * Load its background tile and its width & height
     * @param assetFile
     * @param width
     * @param height
     * @param tileFile
     * @param tileWidth
     * @param tileHeight
     * @return
     */
    virtual bool load(std::string assetFile, int width, int height, std::string tileFile, int tileWidth, int tileHeight);


    virtual bool load(std::string assetFile, int width, int height);

    virtual void render(SDL_Surface* Surf_Display, int x, int y);

    virtual void OnCleanup();

    /*!
     * The type of the entity used for matching neighbours with
     * same id
     */
    int id;


protected:
    SDL_Surface* Surf_Entity;
    SDL_Surface* Surf_Tile;


private:
    int mWidth, mHeight;
    int mTileWidth, mTileHeight;
    std::string mAsset;
    std::string mTileAsset;
};
