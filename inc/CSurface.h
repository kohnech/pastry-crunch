#pragma once

#include <SDL2/SDL.h>

#include <string>

class CSurface {
public:
    CSurface();

public:
    static SDL_Texture* loadTexture( SDL_Renderer* renderer, std::string path );

    static SDL_Surface* OnLoad(const char* File);

    static bool OnDraw(SDL_Renderer* renderer, SDL_Texture* Surf_Src, int X, int Y);
};