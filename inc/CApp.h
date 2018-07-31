#pragma once
#include <SDL2/SDL.h>



class CApp {
private:
    bool    Running;

    SDL_Window*    mWindow;

    SDL_Texture* mTexture;

    SDL_Renderer* mRenderer;

public:
    CApp();

    int OnExecute();

public:

    bool OnInit();

    void OnEvent(SDL_Event* Event);

    void OnLoop();

    void OnRender();

    void OnCleanup();
};