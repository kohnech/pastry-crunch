#include "CApp.h"
#include "CSurface.h"


#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL_image.h>

#include <iostream>



CApp::CApp()
        : Surf_Display { NULL }
        , Surf_Test { NULL }
        , Texture_Test { NULL }
        , renderer{ NULL }
{
    Running = true;
}

int CApp::OnExecute() {
    if(OnInit() == false) {
        return -1;
    }

    SDL_Event Event;

    while(Running) {
        while(SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }

        OnLoop();
        OnRender();
    }

    OnCleanup();

    return 0;
}

bool CApp::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    Surf_Display = SDL_CreateWindow("Game Window",
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    640, 480,
                                    SDL_WINDOW_RESIZABLE);

    if(Surf_Display == NULL) {
        std::cout << "CreateWindow got NULL!" << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(Surf_Display, -1, 0);

    if (renderer == NULL) {
        std::cout << "renderer got NULL!" << std::endl;
        return false;
    }

    std::string img = "astronaut.png";
    Texture_Test = CSurface::loadTexture(renderer, img);

    if(Texture_Test == NULL) {
        std::cout << "Could not loadTexture!" << std::endl;
        return false;
    }

    //Texture_Test = SDL_CreateTextureFromSurface(renderer, Surf_Test);

/*    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(3000);*/

    return true;
}

void CApp::OnEvent(SDL_Event* Event) {
    if(Event->type == SDL_QUIT) {
        std::cout << "Quiting... bye!" << std::endl;
        Running = false;
    }
}

void CApp::OnLoop() {
}

void CApp::OnRender() {
    SDL_RenderClear( renderer );
    //CSurface::OnDraw(renderer, Texture_Test, 0, 0);
    SDL_RenderCopy(renderer, Texture_Test, NULL, NULL);

    //SDL_Flip(Surf_Display);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000); // 1 fps
}

void CApp::OnCleanup() {
    SDL_FreeSurface(Surf_Test);
    SDL_DestroyWindow(Surf_Display);
    SDL_Quit();
    std::cout << "Quitting..." << std::endl;
}
