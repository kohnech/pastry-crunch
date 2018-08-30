#pragma once

#include "IUiComponent.h"
#include "Surface.h"

#include <vector>

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
    bool load(std::string assetFile, int width, int height) override;

    void render(SDL_Surface* Surf_Display) override;

    void renderAnimation(SDL_Surface* Surf_Display);

    virtual void cleanup() override;

    /*!
     * The type of the entity used for matching neighbours with
     * same id
     */
    int id;

private:
    std::string mAsset;

    long mPrevTime;
};
