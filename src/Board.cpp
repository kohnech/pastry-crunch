#include "Board.h"
#include "CSurface.h"
#include "Define.h"

#include <iostream>
#include <string>

Board Board::instance;

Board::Board()
: mX { 0 }
, mY { 0 }
, mTileWidth { 0 }
, mTileHeight { 0 }
, mTileAsset{""}
, Surf_Tile{ NULL }
{}

bool Board::loadBoard(std::string tileFile, int tileWidth, int tileHeight)
{
    mTileAsset.assign(tileFile);
    std::cout << "Hello Board!" << std::endl;

    if ((Surf_Tile = CSurface::OnLoad(tileFile)) == NULL)
    {
        return false;
    }

    mTileWidth = tileWidth;
    mTileHeight = tileHeight;
    return true;
}

void Board::renderBoard(SDL_Surface* Surf_Display, int x, int y)
{
    if (Surf_Display == NULL || Surf_Tile == NULL)
        return;

    for (int x = 0; x < GRID_WIDTH; ++x) {
        for (int y = 0; y < GRID_HEIGHT; ++y) {
            int xPos = x * mTileWidth;
            int yPos = y * mTileHeight;
            CSurface::OnDraw(Surf_Display, Surf_Tile, mX + xPos, mY + yPos, 0, 0, mTileWidth, mTileHeight);
        }
    }
}

void Board::cleanupBoard()
{
    if (Surf_Tile)
    {
        SDL_FreeSurface(Surf_Tile);
    }

    Surf_Tile = NULL;
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

