#pragma once

#include "CAnimation.h"
#include "CEvent.h"
#include "CEntity.h"

#include <SDL2/SDL.h>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

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