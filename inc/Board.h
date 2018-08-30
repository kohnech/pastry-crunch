#pragma once

#include "Assets.h"
#include "IUiComponent.h"

#include <string>

/*!
 * The game board base class that handles basic user input events
 * and draw the game board tiles.
 */


class Board : public IUiComponent
{
public:
    Board();

    ~Board();

    bool load(Assets& assets) override;

    void render(SDL_Surface* Surf_Display) override;

    void cleanup() override;

    Pair getBoardSize();

protected:
    std::string mTileAsset;
    int mHighlightX, mHighlightY;
    int mGridRowSize, mGridColumnSize;

private:
    SDL_Surface* mHighlightSurf;
    bool mIsHighlightVisible;
};
