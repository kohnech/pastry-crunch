#pragma once

#include <vector>

#include "CAnimation.h"
#include "IUiComponent.h"
#include "Surface.h"

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

    void renderAnimation(SDL_Surface* Surf_Display);

    virtual void cleanup();

    /*!
     * The type of the entity used for matching neighbours with
     * same id
     */
    int id;

private:
    std::string mAsset;

    long mPrevTime;
};
