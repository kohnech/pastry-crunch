#include "Text.h"
#include "Define.h"
#include "CSurface.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


#include <string>

Text::Text()
: mFont{ NULL }
, mFontSize{ 30 }
{
}

Text::~Text()
{
    cleanup();
}

bool Text::load(CAssets& assets)
{
    std::string font = assets.getFont();
    if (TTF_Init() < 0) {
        printf("TTF_Init failed: %s\n", SDL_GetError());
    }

    mFont = TTF_OpenFont(font.c_str(), mFontSize);

    if (mFont < 0) {
        printf("Could not load fond TTF_OpenFont");
        return false;
    }
    return true;
}

void Text::render(SDL_Surface* display)
{
    mSurface = TTF_RenderUTF8_Solid(mFont, mMessage.c_str(), BLUE);
    CSurface::OnDraw(display, mSurface, 0, 0);
}

void Text::cleanup()
{
    TTF_CloseFont(mFont);
}

void Text::setText(const std::string& msg, int x, int y)
{
    mMessage.assign(msg);
}