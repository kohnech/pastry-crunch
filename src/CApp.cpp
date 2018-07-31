#include "CApp.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

#include <iostream>

CApp::CApp() {
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

    Surf_Display = SDL_CreateWindow("Buggy Window",
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    0, 0,
                                    SDL_WINDOW_FULLSCREEN_DESKTOP);

    if(Surf_Display == NULL) {
        return false;
    }

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
}

void CApp::OnCleanup() {
    SDL_Quit();
}