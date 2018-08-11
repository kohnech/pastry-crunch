#pragma once

#include "CAssets.h"
#include "IUiComponent.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>

class Text : public IUiComponent
{
public:
    Text();
    ~Text();
    bool load(CAssets& assets);
    void render(SDL_Surface* display);
    void cleanup();
    void setText(const std::string& msg, int x, int y);

private:
    TTF_Font* mFont;
    int mFontSize;
    std::string mMessage;
};