#include "CApp.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

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
    return true;
}

void CApp::OnEvent(SDL_Event* Event) {
}

void CApp::OnLoop() {
}

void CApp::OnRender() {
}

void CApp::OnCleanup() {
}