#pragma once

#include <SDL2/SDL.h>

#include <string>

class CSurface
{
public:
    CSurface();

public:
    static SDL_Texture* loadTexture(SDL_Renderer* renderer, std::string path);

    static SDL_Surface* loadSurface(std::string path);

    static SDL_Surface* OnLoad(const char* File);

    static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int x, int y);

    static bool
    OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int x, int y, int x2, int y2, int w, int h);

    static bool Transparent(SDL_Surface* texture, int r, int g, int b);
};