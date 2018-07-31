#pragma once

#include "CEvent.h"

#include <SDL2/SDL.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int FRAMES_PER_SECOND = 2;


class CApp : public CEvent {
private:
    bool    mIsRunning;

    SDL_Window*    mWindow;

    SDL_Texture* mTexture;

    SDL_Renderer* mRenderer;

public:
    CApp();
    ~CApp();

    int OnExecute();

public:

    bool OnInit();

    void OnEvent(SDL_Event* Event);

    void OnLoop();

    void OnRender();

    void OnCleanup();

    void OnExit();

    void OnResize(int w,int h);

    void OnKeyDown(SDL_Keycode sym, Uint16 mod, SDL_Scancode unicode);
};