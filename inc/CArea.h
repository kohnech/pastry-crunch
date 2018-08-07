#pragma once

#include "CMap.h"

class CSurface;

class CArea {
public:
    static CArea            AreaControl;

public:
    std::vector<CMap>       MapList;

private:
    int                     AreaSize;

    SDL_Surface*        Surf_Tileset;

    CSurface* mCSurface;

public:
    CArea();
    ~CArea();

    bool    OnLoad(char* File);

    void    OnRender(SDL_Surface* Surf_Display, int CameraX, int CameraY);

    void    OnCleanup();
};
