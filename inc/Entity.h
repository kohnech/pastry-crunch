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
    virtual void render(SDL_Surface* Surf_Display, int x, int y);


    void renderAnimation(SDL_Surface* Surf_Display, int xstart, int ystart, int xstop, int ystop);

    virtual void cleanup();

    /*!
     * The type of the entity used for matching neighbours with
     * same id
     */
    int id;

    bool animate;

    // Animate from these coordinates, the grid always are aware of its new position
    // since that is encoded in the mGrid indexes...
    int fromX{0};
    int fromY{0};

protected:
    SDL_Surface* Surf_Entity;


private:
    std::string mAsset;

    long mPrevTime;

    bool isStart;
};
