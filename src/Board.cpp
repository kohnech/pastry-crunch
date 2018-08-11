#include "Board.h"

#include <iostream>

Board Board::instance;

Board::Board()
: mX { 0 }
, mY { 0 }
{}

void Board::test()
{
    std::cout << "Hello Board!" << std::endl;
}

void Board::onLButtonDown(int x, int y)
{
    std::cout << "onLButtonDown: (" << x << "," << y << ")" << std::endl;
}

void Board::onKeyDown(SDL_Keycode sym, Uint16 mod, SDL_Scancode unicode)
{
    std::cout << "Key pressed: " << unicode << std::endl;
    std::cout << "mX:" << mX << "mY: " << mY << std::endl;
}