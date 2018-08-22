#include "Text.h"
#include "Define.h"
#include "Surface.h"


#include <string>

Text::Text()
: mFont{ NULL }
, mFontSize{ 30 }
, mMessage{ "" }
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

    if (mFont < 0)
    {
        printf("Could not load fond TTF_OpenFont");
        return false;
    }

	

    return true;
}

void Text::render(SDL_Surface* display)
{
	mSurface = TTF_RenderUTF8_Solid(mFont, mMessage.c_str(), BLUE);
	if (mSurface == nullptr)
	{
		std::cout << "Got error TTF_RenderUTF8_Solid: " << SDL_GetError() << std::endl;
		return;
	}

	Surface::OnDraw(display, mSurface, mX, mY);
	SDL_FreeSurface(mSurface);
}

void Text::cleanup()
{
    TTF_CloseFont(mFont);
}

void Text::setText(std::string msg)
{
    mMessage.assign(msg);
}
