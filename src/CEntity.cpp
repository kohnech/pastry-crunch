#include "CEntity.h"

std::vector<CEntity*> CEntity::EntityList;

CEntity::CEntity()
: Surf_Entity { NULL }
, mCSurface{ new CSurface }
, X { 0.0f }
, Y { 0.0f }
, Width { 0 }
, Height { 0 }
, AnimState { 0 }
{
}

CEntity::~CEntity()
{
}

bool CEntity::OnLoad(std::string File, int Width, int Height, int MaxFrames)
{
    if((Surf_Entity = mCSurface->OnLoad(File)) == NULL) {
        return false;
    }

    CSurface::Transparent(Surf_Entity, 255, 0, 255);

    this->Width = Width;
    this->Height = Height;

    Anim_Control.MaxFrames = MaxFrames;

    return true;
}

void CEntity::OnLoop()
{
    Anim_Control.OnAnimate();
}

void CEntity::OnRender(SDL_Surface* Surf_Display)
{
    if(Surf_Entity == NULL || Surf_Display == NULL) return;

    mCSurface->OnDraw(Surf_Display, Surf_Entity, X, Y, AnimState * Width, Anim_Control.GetCurrentFrame() * Height, Width, Height);
}

void CEntity::OnCleanup()
{
    if(Surf_Entity) {
        SDL_FreeSurface(Surf_Entity);
    }

    delete mCSurface;

    Surf_Entity = NULL;
}
