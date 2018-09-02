#pragma once

#include "Assets.h"
#include "CommonTypes.h"

#include <SDL.h>

class IUiComponent
{
public:
    IUiComponent()
    : mIsRendering{ true }
    , mX{ 0 }
    , mY{ 0 }
    , mSurface{ nullptr }
    , mWidth{ 0 }
    , mHeight{ 0 }
    {
    }

	virtual ~IUiComponent();

	virtual bool load();
	virtual bool load(Assets& assets);
	virtual bool load(std::string file, int width, int height);

    virtual void render(SDL_Surface* Surf_Display) = 0;
    virtual void cleanup() = 0;

	void setPosition(int x, int y);

	Pair getPosition() const;

	Pair getSize() const;

	void setSize(Pair size);

    bool animate{ false };

    // Animate from these coordinates
    int fromX{ 0 };
    int fromY{ 0 };

    bool mIsRendering;

protected:
    int mX, mY;
    SDL_Surface* mSurface;
    int mWidth, mHeight;

};



