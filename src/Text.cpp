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
        printf("TTF_Init failed: %s\n", SDL_GetError());
    }

    mFont = TTF_OpenFont(font.c_str(), mFontSize);

    if (mFont == nullptr)
    {
        printf("Could not load fond TTF_OpenFont");
        return false;
    }

    if (mFont == NULL)
    {
        printf("Could not load fond TTF_OpenFont");
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
    std::cout << "mFont:" << mFont << ", mMEssage: " << mMessage << std::endl;

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
    std::cout << "Te3xt cleanup() starting" << std::endl;
    TTF_CloseFont(mFont);
    mFont = nullptr;
    std::cout << "Te3xt cleanup() finish" << std::endl;
}

void Text::setText(std::string msg)
{
    mMessage.assign(msg);
}

void Text::setPosition(int x, int y)
{
    mX = x;
    mY = y;
}
