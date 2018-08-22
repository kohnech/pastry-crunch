#pragma once

#include "Assets.h"
#include "IUiComponent.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>

class Text : public IUiComponent
{
public:
    Text();
    ~Text();
    virtual bool load(Assets& assets);
    virtual void render(SDL_Surface* display);
    virtual void cleanup();
    void setText(std::string msg);

private:
    TTF_Font* mFont;
    int mFontSize;
    std::string mMessage;
};