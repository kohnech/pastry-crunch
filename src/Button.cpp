#include "Button.h"
#include "Surface.h"

Button::Button(int x, int y, std::string text)
{
    mX = x;
    mY = y;
    mStr = text;
}

Button::~Button()
{
    cleanup();
}

bool Button::load(Assets& assets)
{
    // Load sound assets
    std::string asset = assets.getButtonAsset();
    Pair size = assets.getButtonSize();
    mWidth = size.first;
    mHeight = size.second;

    if ((mSurface = Surface::OnLoad(asset)) == NULL)
    {
        std::cout << "ERROR: could not create mSurface: " << SDL_GetError() << std::endl;
        return false;
    }
    std::cout << "Loaded asset: " << asset << std::endl;

    mText.load(assets);
    mText.setPosition(mX + mWidth / 2 - mStr.size() * 6, mY + mHeight / 2 - 20);
    mText.setText(mStr);

    std::cout << "text width" << mText.getPosition().first << mText.getPosition().second << std::endl;

    return true;
}

void Button::cleanup()
{
    if (mSurface)
    {
        SDL_FreeSurface(mSurface);
    }

    mSurface = NULL;
}

void Button::render(SDL_Surface* Surf_Display)
{
    if (Surf_Display == NULL || mSurface == NULL)
        return;

    Surface::OnDraw(Surf_Display, mSurface, mX, mY, 0, 0, mWidth, mHeight);
    mText.render(Surf_Display);
}

void Button::onLButtonDown(int x, int y)
{
    std::cout << "Button got event!!!!!!!!!" << std::endl;
    std::cout << "onLButtonDown: (" << x << "," << y << ")" << std::endl;

    std::cout << "mWidth: " << mWidth << ", mHeight: " << mHeight << std::endl;

    if (mWidth == 0 || mWidth == 0)
    {
        return;
    }

    /// Check outside boundaries
    if (x < mX || x >= (mWidth + mX) || y < mY || y >= (mHeight + mY))
    {
        std::cout << "Out of boundary" << std::endl;
        return;
    }

    onClicked();
}


void Button::onClicked()
{
    std::cout << "Button clicked!" << std::endl;
}