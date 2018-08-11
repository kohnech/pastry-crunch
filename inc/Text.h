#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>

class Text
{
public:
    Text();
    bool OnLoad();
    void OnRender(SDL_Surface* display, std::string msg, int x, int y);
    void OnCleanup();

private:
    SDL_Surface* mSurface; // Text surface
    TTF_Font* mFont;
    int mFontSize;
};