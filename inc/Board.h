#pragma once

#include "CEvent.h"
#include "IUiComponent.h"
#include "CAssets.h"

#include <string>

/*!
 * The game board base class that handles basic user input events
 * and draw the game board tiles.
 */


class Board : public CEvent, public IUiComponent
{
public:
    static Board instance;

    Board();

    ~Board();

    bool load(CAssets& assets);

    void render(SDL_Surface* Surf_Display);

    void cleanup();

    virtual void onLButtonDown(int mX, int mY);
    //virtual void onLButtonUp(int mX, int mY);
    virtual void onKeyDown(SDL_Keycode sym, Uint16 mod, SDL_Scancode unicode);

protected:
    std::string mTileAsset;

private:
    SDL_Surface* mHighlightSurf;
    int mHighlightX, mHighlightY;
    bool mIsHighlightVisible;
};
