#pragma once

#include "Assets.h"
#include "Event.h"
#include "IUiComponent.h"

#include <string>

/*!
 * The game board base class that handles basic user input events
 * and draw the game board tiles.
 */


class Board : public IUiComponent
{
public:
    static Board instance;

    Board();

    ~Board();

    virtual bool load(Assets& assets);

    virtual void render(SDL_Surface* Surf_Display);

    virtual void cleanup();

    Pair getBoardSize();

protected:
    std::string mTileAsset;
    int mHighlightX, mHighlightY;
    int mGridRowSize, mGridColumnSize;

private:
    SDL_Surface* mHighlightSurf;

    bool mIsHighlightVisible;
};
