#pragma once

#include <SDL2/SDL.h>

class CSurface {
public:
    CSurface();

public:
    static SDL_Surface* OnLoad(char* File);

    static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y);
};