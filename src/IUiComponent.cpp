#include "IUiComponent.h"

#include <iostream>

IUiComponent::IUiComponent()
    : animate{ false }
    , fromX { 0 }
    , fromY{ 0 }
    , mX{ 0 }
    , mY{ 0 }
    , mSurface{ nullptr }
    , mWidth{ 0 }
    , mHeight{ 0 }
{
}

IUiComponent::~IUiComponent()
{
	if (mSurface != nullptr) {
		SDL_FreeSurface(mSurface);
		mSurface = nullptr;
	}
};

bool IUiComponent::load()
{
	std::cerr << "WARNING: Unimplemented method: " << __FILE__ << ":" << __LINE__ << std::endl;
	return false;
}

bool IUiComponent::load(Assets& assets)
{
	std::cerr << "WARNING: Unimplemented method: " << __FILE__ << ":" << __LINE__ << std::endl;
	return false;
}

bool IUiComponent::load(std::string file, int width, int height)
{
	std::cerr << "WARNING: Unimplemented method: " << __FILE__ << ":" << __LINE__ << std::endl;
	return false;
}

void IUiComponent::setPosition(int x, int y)
{
	mX = x;
	mY = y;
}

Pair IUiComponent::getPosition() const
{
	Pair position;
	position.first = mX;
	position.second = mY;
	return position;
}

Pair IUiComponent::getSize() const
{
	Pair size;
	size.first = mWidth;
	size.second = mHeight;
	return size;
}

void IUiComponent::setSize(Pair size)
{
	mWidth = size.first;
	mHeight = size.second;
}
