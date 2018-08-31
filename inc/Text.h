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
    bool load(Assets& assets) override;
    void render(SDL_Surface* display) override;
    void cleanup() override;
    void setText(std::string msg);

private:
    TTF_Font* mFont;
    int mFontSize;
    std::string mMessage;
    SDL_Surface* mTextSurface;
};