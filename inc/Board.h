#pragma once

#include "CEvent.h"
#include <string>

/*!
 * The game board base class that handles basic user input events
 * and draw the game board tiles.
 */


class Board : public CEvent
{
public:
    static Board instance;

    Board();

    bool loadBoard(std::string tileFile, int tileWidth, int tileHeight);

    void renderBoard(SDL_Surface* Surf_Display, int x, int y);

    void cleanupBoard();

    virtual void onLButtonDown(int mX, int mY);
    //virtual void onLButtonUp(int mX, int mY);
    virtual void onKeyDown(SDL_Keycode sym, Uint16 mod, SDL_Scancode unicode);

protected:
    int mX, mY;
    int mTileWidth, mTileHeight;
    std::string mTileAsset;

private:
    SDL_Surface* Surf_Tile;
};