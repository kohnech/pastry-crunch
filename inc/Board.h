#pragma once

#include "CEvent.h"
#include "IUiComponent.h"
#include "CAssets.h"

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

    bool load(CAssets& assets);

    void render(SDL_Surface* Surf_Display);

    void cleanup();

protected:
    std::string mTileAsset;
    int mHighlightX, mHighlightY;

private:
    SDL_Surface* mHighlightSurf;

    bool mIsHighlightVisible;
};
