#include "Text.h"
#include "Define.h"
#include "Surface.h"

#include <string>
#include <iostream>

Text::Text()
: mFont{ nullptr }
, mFontSize{ 30 }
, mMessage{ "" }
, mTextSurface{ nullptr }
{
}

Text::~Text()
{
    cleanup();
}

bool Text::load(Assets& assets)
{
    std::string font = assets.getFont();
    mFontSize = assets.getFontSize();
    if (TTF_Init() < 0)
    {
        std::cerr << "TTF_Init failed: " << SDL_GetError() << std::endl;
    }

    mFont = TTF_OpenFont(font.c_str(), mFontSize);

    if (mFont == nullptr)
    {
        std::cerr << "Could not load fond TTF_OpenFont" << std::endl;
        return false;
    }

    if (mFont == nullptr)
    {
        std::cerr << "Could not load fond TTF_OpenFont" << std::endl;
        return false;
    }


    return true;
}

void Text::render(SDL_Surface* display)
{
    if (mMessage.empty())
    {
        std::cerr << "Empty message!" << std::endl;
        return;
    }
    if(mFont == nullptr)
    {
        std::cerr << "Empty mFont!" << std::endl;
        return;
    }
    if (display == nullptr)
    {
        std::cerr << "Empty display!" << std::endl;
        return;
    }

    mTextSurface = TTF_RenderUTF8_Solid(mFont, mMessage.c_str(), BLUE);
    if (mTextSurface == nullptr)
    {
        std::cerr << "Got error TTF_RenderUTF8_Solid: " << SDL_GetError() << std::endl;
        std::cerr << "Trying to display message: " << mMessage << std::endl;
        return;
    }

    Surface::OnDraw(display, mTextSurface, mX, mY);
    SDL_FreeSurface(mTextSurface);
}

void Text::cleanup()
{
    TTF_CloseFont(mFont);
    mFont = nullptr;
}

void Text::setText(std::string msg)
{
    mMessage.assign(msg);
}
