#pragma once

#include "CAnimation.h"
#include "CEvent.h"
#include "Entity.h"


#include "CArea.h"
#include "CCamera.h"
#include "Thread.h"

#include <SDL2/SDL.h>

// Screen dimension constants


const int FRAMES_PER_SECOND = 2;


class CApp : public CEvent, public IThread
{
public:
    CApp();
    ~CApp();

    bool onInit();

    void onEvent(SDL_Event* Event);

    void onLoop();

    void onRender();

    void onCleanup();


    /// Events
    void onExit();

    void onResize(int w, int h);

    void onKeyDown(SDL_Keycode sym, Uint16 mod, SDL_Scancode unicode);

    virtual bool ThreadMethod();

private:
    bool mIsRunning;

    SDL_Window* mWindow;
    SDL_Surface* Surf_Display;
    SDL_Surface* Surf_Test;

    CAnimation Anim_Yoshi;

    Entity Entity1;
    Entity Entity2;

    SDL_Surface* Background_Surf;

    std::vector<Entity*> EntityList;

    int mWidth;
    int mHeight;
};
