#pragma once

#include <vector>

#include "CAnimation.h"
#include "CSurface.h"
#include "IUiComponent.h"

class Entity : public IUiComponent
{
public:
    Entity();

    Entity(int id);

    virtual ~Entity();

    /*!
     * Load an Entity based on asset in file, its width & height,
     * @param assetFile
     * @param width
     * @param height
     * @return
     */
    virtual bool load(std::string assetFile, int width, int height);

    virtual void render(SDL_Surface* Surf_Display);
    virtual void render(SDL_Surface* Surf_Display, int x, int y);

    virtual void cleanup();

    /*!
     * The type of the entity used for matching neighbours with
     * same id
     */
    int id;


protected:
    SDL_Surface* Surf_Entity;


private:
    std::string mAsset;
};
