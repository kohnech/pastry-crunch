#pragma once

#include "Assets.h"
#include "IUiComponent.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>

class Text : public IUiComponent
{
public:
    Text();
    ~Text();
    bool load(Assets& assets);
    void render(SDL_Surface* display);
    void cleanup();
    void setText(std::string msg);

private:
    TTF_Font* mFont;
    int mFontSize;
    std::string mMessage;
};