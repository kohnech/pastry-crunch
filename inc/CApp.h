#pragma once
#include <SDL2/SDL.h>



class CApp {
private:
    bool    Running;

    SDL_Window*    Surf_Display;

    SDL_Surface*    Surf_Test;

    SDL_Texture* Texture_Test;

    SDL_Renderer* renderer;

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