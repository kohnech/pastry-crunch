#include "Board.h"
#include "CSurface.h"
#include "Define.h"
#include "CAssets.h"

#include <iostream>
#include <string>

Board Board::instance;

Board::Board()
: mTileWidth { 0 }
, mTileHeight { 0 }
, mTileAsset{""}
, mHighlightSurf { NULL }
, mHighlightX{ 0 }
, mHighlightY{ 0 }
, mIsHighlightVisible{ true }
{
}

Board::~Board()
{
    cleanup();
}

bool Board::load(CAssets& assets)
{
    mTileAsset.assign(assets.getTileAsset());
    std::string highlightFile = assets.getHighlightAsset();
    std::pair<int, int> tileSize = assets.getTileSize();

    mTileWidth = tileSize.first;
    mTileHeight = tileSize.second;

    std::cout << "Hello Board!" << std::endl;

    if ((mSurface = CSurface::OnLoad(mTileAsset)) == NULL)
    {
        return false;
    }

    if ((mHighlightSurf = CSurface::OnLoad(highlightFile)) == NULL)
    {
        std::cout << "ERROR: could not create mHighlightSurf: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void Board::render(SDL_Surface* Surf_Display)
{
    if (Surf_Display == NULL || mSurface == NULL)
        return;

    for (int x = 0; x < GRID_WIDTH; ++x) {
        for (int y = 0; y < GRID_HEIGHT; ++y) {
            int xPos = x * mTileWidth;
            int yPos = y * mTileHeight;

            if (mIsHighlightVisible && ((x == mHighlightX) && (y == mHighlightY)) )
            {
                CSurface::OnDraw(Surf_Display, mHighlightSurf, mX + xPos, mY + yPos, 0, 0, mTileWidth, mTileHeight);
            }
            else {
                CSurface::OnDraw(Surf_Display, mSurface, mX + xPos, mY + yPos, 0, 0, mTileWidth, mTileHeight);
            }
        }
    }
}

void Board::cleanup()
{
    if (mSurface)
    {
        SDL_FreeSurface(mSurface);
    }

    if (mHighlightSurf)
    {
        SDL_FreeSurface(mHighlightSurf);
    }

    mSurface = NULL;
    mHighlightSurf = NULL;
}

void Board::onLButtonDown(int x, int y)
{
    std::cout << "onLButtonDown: (" << x << "," << y << ")" << std::endl;

    std::cout << "mTileWidth: " << mTileWidth << ", mTileHeight: " << mTileHeight << std::endl;

    if (mTileWidth == 0 || mTileWidth == 0) {
        return;
    }

    /// Calculate board coordinate
    int row = (x - mX) / mTileWidth;
    int column = (y - mY) / mTileHeight;
    std::cout << "Pressed coordinate: (" << row << ", " << column << ")" << std::endl;

    mHighlightX = row;
    mHighlightY = column;
}

void Board::onKeyDown(SDL_Keycode sym, Uint16 mod, SDL_Scancode unicode)
{
    std::cout << "Key pressed: " << unicode << std::endl;
    std::cout << "mX:" << mX << "mY: " << mY << std::endl;
}
