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

    if ((mSurface = Surface::loadImage(asset)) == nullptr)
    {
        std::cerr << "ERROR: could not create mSurface: " << SDL_GetError() << std::endl;
        return false;
    }

    mText.load(assets);
    mText.setPosition(mX + mWidth / 2 - mStr.size() * 6, mY + mHeight / 2 - 20);
    mText.setText(mStr);

    return true;
}

void Button::cleanup()
{
    if (mSurface)
    {
        SDL_FreeSurface(mSurface);
    }

    mSurface = nullptr;
}

void Button::render(SDL_Surface* Surf_Display)
{
    if (Surf_Display == nullptr || mSurface == nullptr)
        return;

    Surface::OnDraw(Surf_Display, mSurface, mX, mY, 0, 0, mWidth, mHeight);
    mText.render(Surf_Display);
}

void Button::onLButtonDown(int x, int y)
{
    if (mWidth == 0 || mWidth == 0)
    {
        return;
    }

    /// Check outside boundaries
    if (x < mX || x >= (mWidth + mX) || y < mY || y >= (mHeight + mY))
    {
        std::cout << "Button Out of boundary" << std::endl;
        return;
    }

    onClicked();
}


void Button::onClicked() const
{
    std::cout << "Button clicked!" << std::endl;
    mClickedCallback();
}

void Button::addClickedCallback(ClickedCallback cb)
{
    mClickedCallback = cb;
}
