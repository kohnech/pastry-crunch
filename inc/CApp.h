#pragma once

#include "CEvent.h"

#include <SDL2/SDL.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


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
};