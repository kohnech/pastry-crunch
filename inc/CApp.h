#pragma once

#include "CAnimation.h"
#include "CEvent.h"
#include "CEntity.h"


#include "CArea.h"
#include "CCamera.h"

#include <SDL2/SDL.h>

// Screen dimension constants


const int FRAMES_PER_SECOND = 2;


class CApp : public CEvent
{
private:
    bool mIsRunning;

    SDL_Window* mWindow;
    SDL_Surface* Surf_Display;
    SDL_Surface*    Surf_Test;

    CAnimation Anim_Yoshi;

    CEntity         Entity1;
    CEntity         Entity2;

    SDL_Surface* Background_Surf;

    std::vector<CEntity*>    EntityList;

    int mWidth;
    int mHeight;

public:
    CApp();
    ~CApp();

public:
    bool onInit();

    void onEvent(SDL_Event* Event);

    bool onLoop();

    void onRender();

    void onCleanup();

    void onExit();

    void onResize(int w, int h);

    void onKeyDown(SDL_Keycode sym, Uint16 mod, SDL_Scancode unicode);
};