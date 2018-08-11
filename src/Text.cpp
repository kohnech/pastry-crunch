#include "Text.h"
#include "Define.h"
#include "CSurface.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


#include <string>

Text::Text()
: mSurface{ NULL }
, mFont{ NULL }
, mFontSize{ 30 }
{}

bool Text::OnLoad()
{
    if (TTF_Init() < 0) {
        printf("TTF_Init failed: %s\n", SDL_GetError());
    }

    mFont = TTF_OpenFont("./assets/Ubuntu-C.ttf", mFontSize);

    if (mFont < 0) {
        printf("Could not load fond TTF_OpenFont");
        return false;
    }
    return true;
}

void Text::OnRender(SDL_Surface* display, std::string msg, int x, int y)
{
    mSurface = TTF_RenderUTF8_Solid(mFont, msg.c_str(), BLUE);
    CSurface::OnDraw(display, mSurface, x, y);
}

void Text::OnCleanup()
{
    TTF_CloseFont(mFont);
}
