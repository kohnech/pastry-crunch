#include "CApp.h"
#include "CSurface.h"


#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL_image.h>

#include <iostream>



CApp::CApp()
        : mWindow { NULL }
        , mTexture { NULL }
        , mRenderer{ NULL }
{
    mIsRunning = true;
}

CApp::~CApp(){}

int CApp::OnExecute() {
    if(OnInit() == false) {
        return -1;
    }

    SDL_Event Event;

    while(mIsRunning) {
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

    mWindow = SDL_CreateWindow("Game Window",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH,
                               SCREEN_HEIGHT,
                               SDL_WINDOW_RESIZABLE);

    if(mWindow == NULL) {
        std::cout << "SDL_CreateWindow got NULL!" << std::endl;
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, 0);

    if (mRenderer == NULL) {
        std::cout << "SDL_CreateRenderer got NULL!" << std::endl;
        return false;
    }

    std::string img = "astronaut.png";
    mTexture = CSurface::loadTexture(mRenderer, img);

    if(mTexture == NULL) {
        std::cout << "Could not loadTexture!" << std::endl;
        return false;
    }

    SDL_SetRenderDrawColor(mRenderer, 0, 255, 0, 255); // green
    SDL_RenderClear(mRenderer);
    SDL_RenderPresent(mRenderer);
    SDL_Delay(3000);

    return true;
}

void CApp::OnEvent(SDL_Event* event) {
    CEvent::OnEvent(event);
}

void CApp::OnLoop() {
}

void CApp::OnRender() {
    SDL_RenderClear( mRenderer );
    //CSurface::OnDraw(mRenderer, mTexture, 0, 0);
    SDL_RenderCopy(mRenderer, mTexture, NULL, NULL);

    SDL_RenderPresent(mRenderer);
    SDL_Delay(1000); // 1 fps
}

void CApp::OnCleanup() {
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
    std::cout << "Quitting..." << std::endl;
}

void CApp::OnExit() {
    std::cout << "Quiting... bye!" << std::endl;
    mIsRunning = false;
}

