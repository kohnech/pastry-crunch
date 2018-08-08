#include "CEntity.h"
#include <iostream>


CEntity::CEntity()
: Surf_Entity { NULL }
, mWidth { 0 }
, mHeight { 0 }
{
}

CEntity::~CEntity()
{
}

bool CEntity::OnLoad(std::string File, int width, int height)
{
    if((Surf_Entity = CSurface::OnLoad(File)) == NULL) {
        return false;
    }

    CSurface::Transparent(Surf_Entity, 255, 0, 255);

    mWidth = width;
    mHeight = height;

    return true;
}

void CEntity::OnLoop()
{
}

void CEntity::OnRender(SDL_Surface* Surf_Display, int x, int y)
{
    if(Surf_Entity == NULL || Surf_Display == NULL) return;

    CSurface::OnDraw(Surf_Display, Surf_Entity, x, y, 0, 0, mWidth, mHeight);
}

void CEntity::OnCleanup()
{
    if(Surf_Entity) {
        SDL_FreeSurface(Surf_Entity);
    }

    Surf_Entity = NULL;
}
