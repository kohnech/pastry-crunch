#pragma once

#include "CEvent.h"

/*!
 * The game board base class that handles basic user input events
 * and draw the game board tiles.
 */


class Board : public CEvent
{
public:
    static Board instance;

    Board();

    void test();

    virtual void onLButtonDown(int mX, int mY);
    //virtual void onLButtonUp(int mX, int mY);
    virtual void onKeyDown(SDL_Keycode sym, Uint16 mod, SDL_Scancode unicode);

protected:
    int mX, mY;
};