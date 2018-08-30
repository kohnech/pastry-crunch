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
    virtual bool load(Assets& assets) override;
    virtual void render(SDL_Surface* display) override;
    virtual void cleanup() override;
    void setText(std::string msg);

private:
    TTF_Font* mFont;
    int mFontSize;
    std::string mMessage;
};